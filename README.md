# LeetCode Solutions

Automatically synced LeetCode solutions with a clean, internship-friendly structure.

## Structure

```text
problems/
  easy/
  medium/
  hard/
topics/
scripts/
```

Each problem folder contains:

- `solution.*`
- `README.md`

Each problem README includes:

- problem name
- LeetCode link
- difficulty
- topic tags
- language
- runtime and memory when available

## Sync Model

- Past accepted submissions are backfilled by the sync script.
- Future accepted submissions are synced automatically by GitHub Actions.
- Only one canonical folder is created per problem to avoid duplicates.
- Topic organization is provided through generated index files in `topics/`.

## Setup

Follow the step-by-step instructions in [SETUP.md](./SETUP.md).

Useful quick references:

- [First push commands](./FIRST_PUSH_COMMANDS.md)
- [GitHub secrets example](./GITHUB_SECRETS_EXAMPLE.md)
