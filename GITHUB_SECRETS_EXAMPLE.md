# GitHub Secrets To Add

Go to:

`GitHub repository` -> `Settings` -> `Secrets and variables` -> `Actions`

Add these repository secrets:

## Required

- `LEETCODE_SESSION`
  - Value: your `LEETCODE_SESSION` cookie from `https://leetcode.com`
- `CSRFTOKEN`
  - Value: your `csrftoken` cookie from `https://leetcode.com`

## Optional

- `PREFERRED_LANGS`
  - Recommended value: `cpp,c++,c`
  - Purpose: if the same problem was solved in multiple languages, prefer C++ for the canonical saved solution

## Important

- Secrets are case-sensitive.
- Do not put quotes around the values.
- If sync starts failing later, your LeetCode cookies may have expired and need to be refreshed.
