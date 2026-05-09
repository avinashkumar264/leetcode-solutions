from __future__ import annotations

import json
import os
import re
import time
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path
from typing import Any
from urllib import error, request


ROOT = Path(__file__).resolve().parents[1]
PROBLEMS_DIR = ROOT / "problems"
TOPICS_DIR = ROOT / "topics"
STATE_DIR = ROOT / ".leetcode-sync"
STATE_FILE = STATE_DIR / "state.json"
GRAPHQL_URL = "https://leetcode.com/graphql/"
USER_AGENT = "leetcode-github-sync/1.0"
REQUEST_RETRIES = 4


LIST_QUERY = """
query submissionList($offset: Int!, $limit: Int!, $lastKey: String, $status: Int) {
  submissionList(offset: $offset, limit: $limit, lastKey: $lastKey, status: $status) {
    lastKey
    hasNext
    submissions {
      id
      title
      titleSlug
      statusDisplay
      lang
      langName
      timestamp
      url
      runtime
      memory
    }
  }
}
"""


DETAIL_QUERY = """
query submissionDetails($submissionId: Int!) {
  submissionDetails(submissionId: $submissionId) {
    code
    runtime
    runtimeDisplay
    runtimePercentile
    memory
    memoryDisplay
    memoryPercentile
    timestamp
    statusCode
    lang {
      name
      verboseName
    }
    question {
      questionId
      titleSlug
    }
  }
}
"""


QUESTION_QUERY = """
query questionData($titleSlug: String!) {
  question(titleSlug: $titleSlug) {
    questionId
    questionFrontendId
    title
    titleSlug
    difficulty
    topicTags {
      name
      slug
    }
  }
}
"""


LANG_EXTENSIONS = {
    "c": ".c",
    "c++": ".cpp",
    "cpp": ".cpp",
    "java": ".java",
    "python": ".py",
    "python3": ".py",
    "javascript": ".js",
    "typescript": ".ts",
    "csharp": ".cs",
    "golang": ".go",
    "go": ".go",
    "kotlin": ".kt",
    "rust": ".rs",
    "swift": ".swift",
    "ruby": ".rb",
    "scala": ".scala",
    "mysql": ".sql",
    "php": ".php",
    "dart": ".dart",
    "racket": ".rkt",
    "erlang": ".erl",
    "elixir": ".ex",
}


@dataclass
class Submission:
    submission_id: int
    title: str
    title_slug: str
    timestamp: int
    lang: str
    lang_name: str
    runtime: str | None
    memory: str | None


def main() -> None:
    session = require_env("LEETCODE_SESSION")
    csrf = require_env("CSRFTOKEN")
    preferred_langs = parse_preferred_langs(os.getenv("PREFERRED_LANGS", "cpp,c++,c"))

    # Keep the repo structure ready even before the first successful sync.
    PROBLEMS_DIR.mkdir(parents=True, exist_ok=True)
    TOPICS_DIR.mkdir(parents=True, exist_ok=True)

    client = LeetCodeClient(session=session, csrf=csrf)

    submissions = client.fetch_all_accepted_submissions()
    if not submissions:
        raise SystemExit("No accepted submissions were found for the current LeetCode account.")

    question_cache = load_state().get("question_cache", {})
    latest_by_problem = choose_preferred_submissions(submissions, preferred_langs)

    generated = []
    topic_index: dict[str, list[tuple[str, str]]] = defaultdict(list)
    difficulty_counts: dict[str, int] = {"Easy": 0, "Medium": 0, "Hard": 0}

    for title_slug, submission in sorted(latest_by_problem.items()):
        details = client.fetch_submission_details(submission.submission_id)
        question = question_cache.get(title_slug) or client.fetch_question(title_slug)
        question_cache[title_slug] = question

        difficulty = question.get("difficulty", "Unknown")
        frontend_id = str(question.get("questionFrontendId") or question.get("questionId") or "0000")
        clean_slug = slugify(title_slug)
        folder_name = f"{frontend_id.zfill(4)}-{clean_slug}"
        problem_dir = PROBLEMS_DIR / difficulty.lower() / folder_name
        problem_dir.mkdir(parents=True, exist_ok=True)

        extension = file_extension_for_language(submission.lang, submission.lang_name)
        solution_path = problem_dir / f"solution{extension}"
        readme_path = problem_dir / "README.md"

        code = details.get("code") or ""
        for stale_solution in problem_dir.glob("solution.*"):
            stale_solution.unlink()
        solution_path.write_text(normalize_newlines(code), encoding="utf-8")
        readme_path.write_text(
            build_problem_readme(question=question, submission=submission, details=details),
            encoding="utf-8",
        )

        difficulty_counts[difficulty] = difficulty_counts.get(difficulty, 0) + 1
        generated.append((question["title"], difficulty, problem_dir.relative_to(ROOT).as_posix()))

        for topic in question.get("topicTags", []):
            topic_name = topic.get("name", "Unknown")
            topic_slug = topic.get("slug") or slugify(topic_name)
            topic_index[topic_slug].append((question["title"], problem_dir.relative_to(ROOT).as_posix()))

    write_topic_indexes(topic_index)
    write_root_readme(generated, difficulty_counts)
    save_state({"question_cache": question_cache, "last_sync_epoch": int(time.time())})


def require_env(name: str) -> str:
    value = os.getenv(name)
    if not value:
        raise SystemExit(f"Missing required environment variable: {name}")
    return value


def parse_preferred_langs(raw: str) -> list[str]:
    return [part.strip().lower() for part in raw.split(",") if part.strip()]


def choose_preferred_submissions(
    submissions: list[Submission], preferred_langs: list[str]
) -> dict[str, Submission]:
    grouped: dict[str, list[Submission]] = defaultdict(list)
    for submission in submissions:
        grouped[submission.title_slug].append(submission)

    result: dict[str, Submission] = {}
    for title_slug, items in grouped.items():
        items.sort(key=lambda item: item.timestamp, reverse=True)

        chosen = None
        for preferred in preferred_langs:
            # Keep one canonical solution per problem and prefer C++ when available.
            chosen = next((item for item in items if preferred in normalize_lang(item.lang, item.lang_name)), None)
            if chosen:
                break

        result[title_slug] = chosen or items[0]

    return result


def normalize_lang(lang: str | None, lang_name: str | None) -> str:
    return f"{(lang or '').lower()} {(lang_name or '').lower()}".strip()


def file_extension_for_language(lang: str | None, lang_name: str | None) -> str:
    candidates = [lang or "", lang_name or ""]
    for candidate in candidates:
        normalized = candidate.strip().lower()
        if normalized in LANG_EXTENSIONS:
            return LANG_EXTENSIONS[normalized]
    return ".txt"


def slugify(value: str) -> str:
    value = value.strip().lower()
    value = re.sub(r"[^a-z0-9]+", "-", value)
    return value.strip("-")


def normalize_newlines(text: str) -> str:
    return text.replace("\r\n", "\n").replace("\r", "\n")


def build_problem_readme(question: dict[str, Any], submission: Submission, details: dict[str, Any]) -> str:
    title = question.get("title", submission.title)
    difficulty = question.get("difficulty", "Unknown")
    title_slug = question.get("titleSlug", submission.title_slug)
    frontend_id = question.get("questionFrontendId") or question.get("questionId") or "N/A"
    topic_tags = question.get("topicTags", [])
    topics = ", ".join(tag.get("name", "Unknown") for tag in topic_tags) or "None"
    runtime = details.get("runtimeDisplay") or details.get("runtime") or submission.runtime or "N/A"
    memory = details.get("memoryDisplay") or details.get("memory") or submission.memory or "N/A"
    language = details.get("lang", {}).get("verboseName") or submission.lang_name or submission.lang
    solved_at = time.strftime("%Y-%m-%d %H:%M:%S UTC", time.gmtime(submission.timestamp))

    return f"""# {frontend_id}. {title}

- Difficulty: {difficulty}
- Topics: {topics}
- Language: {language}
- Runtime: {runtime}
- Memory: {memory}
- Synced from accepted submission: {solved_at}
- LeetCode: https://leetcode.com/problems/{title_slug}/

## Notes

Auto-generated by the repository sync workflow.
"""


def write_topic_indexes(topic_index: dict[str, list[tuple[str, str]]]) -> None:
    TOPICS_DIR.mkdir(parents=True, exist_ok=True)

    for old_file in TOPICS_DIR.glob("*.md"):
        old_file.unlink()

    overview_lines = ["# Topic Index", "", "Generated topic pages:", ""]
    for topic_slug in sorted(topic_index):
        entries = sorted(topic_index[topic_slug], key=lambda item: item[0].lower())
        topic_title = topic_slug.replace("-", " ").title()
        topic_file = TOPICS_DIR / f"{topic_slug}.md"
        body = [f"# {topic_title}", "", "Problems:", ""]
        for title, relative_path in entries:
            body.append(f"- [{title}](../{relative_path}/README.md)")
        topic_file.write_text("\n".join(body) + "\n", encoding="utf-8")
        overview_lines.append(f"- [{topic_title}](./{topic_slug}.md)")

    (TOPICS_DIR / "README.md").write_text("\n".join(overview_lines) + "\n", encoding="utf-8")


def write_root_readme(
    generated: list[tuple[str, str, str]],
    difficulty_counts: dict[str, int],
) -> None:
    total = sum(difficulty_counts.values())
    lines = [
        "# LeetCode Solutions",
        "",
        "Automatically synced LeetCode solutions with a clean, internship-friendly structure.",
        "",
        "## Summary",
        "",
        f"- Total solved synced: {total}",
        f"- Easy: {difficulty_counts.get('Easy', 0)}",
        f"- Medium: {difficulty_counts.get('Medium', 0)}",
        f"- Hard: {difficulty_counts.get('Hard', 0)}",
        "",
        "## Structure",
        "",
        "```text",
        "problems/",
        "  easy/",
        "  medium/",
        "  hard/",
        "topics/",
        "```",
        "",
        "## Topic Index",
        "",
        "- [Browse topics](./topics/README.md)",
        "",
        "## Recently generated problem folders",
        "",
    ]

    for title, difficulty, relative_path in generated[:20]:
        lines.append(f"- {title} ({difficulty}) -> [README](./{relative_path}/README.md)")

    if len(generated) > 20:
        lines.extend(["", f"- ...and {len(generated) - 20} more problems"])

    lines.extend(
        [
            "",
            "## Setup",
            "",
            "Follow the instructions in [SETUP.md](./SETUP.md).",
        ]
    )

    (ROOT / "README.md").write_text("\n".join(lines) + "\n", encoding="utf-8")


def load_state() -> dict[str, Any]:
    if not STATE_FILE.exists():
        return {}
    try:
        return json.loads(STATE_FILE.read_text(encoding="utf-8"))
    except json.JSONDecodeError:
        return {}


def save_state(state: dict[str, Any]) -> None:
    STATE_DIR.mkdir(parents=True, exist_ok=True)
    STATE_FILE.write_text(json.dumps(state, indent=2, sort_keys=True), encoding="utf-8")


class LeetCodeClient:
    def __init__(self, session: str, csrf: str) -> None:
        self.session = session
        self.csrf = csrf

    def fetch_all_accepted_submissions(self) -> list[Submission]:
        all_items: list[Submission] = []
        offset = 0
        limit = 20
        has_next = True
        last_key = None

        while has_next:
            payload = {
                "operationName": "submissionList",
                "query": LIST_QUERY,
                "variables": {
                    "offset": offset,
                    "limit": limit,
                    "lastKey": last_key,
                    "status": 10,
                },
            }
            data = self._graphql(payload)
            block = (((data or {}).get("data") or {}).get("submissionList") or {})

            submissions = block.get("submissions") or []
            for item in submissions:
                if item.get("statusDisplay") != "Accepted":
                    continue
                if not item.get("titleSlug"):
                    continue
                all_items.append(
                    Submission(
                        submission_id=int(item["id"]),
                        title=item.get("title", ""),
                        title_slug=item["titleSlug"],
                        timestamp=int(item.get("timestamp") or 0),
                        lang=item.get("lang", ""),
                        lang_name=item.get("langName", ""),
                        runtime=item.get("runtime"),
                        memory=item.get("memory"),
                    )
                )

            has_next = bool(block.get("hasNext"))
            last_key = block.get("lastKey")
            offset += limit
            time.sleep(0.2)

            if not submissions:
                break

        return all_items

    def fetch_submission_details(self, submission_id: int) -> dict[str, Any]:
        payload = {
            "operationName": "submissionDetails",
            "query": DETAIL_QUERY,
            "variables": {"submissionId": submission_id},
        }
        data = self._graphql(payload)
        return (((data or {}).get("data") or {}).get("submissionDetails") or {})

    def fetch_question(self, title_slug: str) -> dict[str, Any]:
        payload = {
            "operationName": "questionData",
            "query": QUESTION_QUERY,
            "variables": {"titleSlug": title_slug},
        }
        data = self._graphql(payload)
        question = (((data or {}).get("data") or {}).get("question") or {})
        if not question:
            return {
                "questionId": "0",
                "questionFrontendId": "0",
                "title": title_slug.replace("-", " ").title(),
                "titleSlug": title_slug,
                "difficulty": "Unknown",
                "topicTags": [],
            }
        return question

    def _graphql(self, payload: dict[str, Any]) -> dict[str, Any]:
        raw = json.dumps(payload).encode("utf-8")
        last_error: Exception | None = None

        for attempt in range(1, REQUEST_RETRIES + 1):
            req = request.Request(
                GRAPHQL_URL,
                data=raw,
                headers={
                    "Content-Type": "application/json",
                    "User-Agent": USER_AGENT,
                    "Referer": "https://leetcode.com/",
                    "Origin": "https://leetcode.com",
                    "Cookie": f"LEETCODE_SESSION={self.session}; csrftoken={self.csrf}",
                    "X-Csrftoken": self.csrf,
                },
                method="POST",
            )

            try:
                with request.urlopen(req, timeout=30) as response:
                    parsed = json.loads(response.read().decode("utf-8"))
                    if parsed.get("errors"):
                        raise RuntimeError(f"LeetCode GraphQL returned errors: {parsed['errors']}")
                    return parsed
            except error.HTTPError as exc:
                body = exc.read().decode("utf-8", errors="replace")
                last_error = RuntimeError(f"LeetCode request failed with HTTP {exc.code}: {body}")
            except error.URLError as exc:
                last_error = RuntimeError(f"Network error while calling LeetCode: {exc}")
            except json.JSONDecodeError as exc:
                last_error = RuntimeError(f"LeetCode returned invalid JSON: {exc}")

            if attempt < REQUEST_RETRIES:
                time.sleep(2 ** attempt)

        raise RuntimeError(
            "Unable to sync from LeetCode after multiple retries. "
            "Your session cookies may be expired, or LeetCode may be temporarily blocking requests."
        ) from last_error


if __name__ == "__main__":
    main()
