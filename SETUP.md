# Beginner Setup Guide

This repository is already prepared to sync your LeetCode submissions to GitHub.

## What you need

1. A GitHub repository for this folder.
2. Your LeetCode login cookies:
   - `LEETCODE_SESSION`
   - `CSRFTOKEN`
3. GitHub Actions enabled with write permission.

## Recommended repo name

- `leetcode-solutions`

If you want a slightly broader placement-ready name:

- `dsa-leetcode-solutions`

## Public or private?

- Start with `private` while you test the first sync.
- Change to `public` after the repo looks clean.

## Step 1: Create a GitHub repository

Create a new empty repository on GitHub.

Recommended:

- Name: `leetcode-solutions`
- Visibility: `private` first
- Add no extra template files if you can avoid it

## Step 2: Push this folder to GitHub

From this folder, run:

```powershell
git branch -M main
git add .
git commit -m "Initial LeetCode sync setup"
git remote add origin https://github.com/<your-username>/<your-repo>.git
git push -u origin main
```

There is also a copy-paste helper here:

- [FIRST_PUSH_COMMANDS.md](./FIRST_PUSH_COMMANDS.md)

## Step 3: Get your LeetCode cookies

1. Open [LeetCode](https://leetcode.com/) and sign in.
2. Press `F12` to open browser developer tools.
3. Go to the `Application` or `Storage` tab.
4. Open `Cookies` for `https://leetcode.com`.
5. Copy these values:
   - `LEETCODE_SESSION`
   - `csrftoken`

Use the `csrftoken` value as your GitHub secret named `CSRFTOKEN`.

Treat both values like passwords.

## Step 4: Add GitHub repository secrets

Open your GitHub repository:

`Settings` -> `Secrets and variables` -> `Actions`

Create these secrets:

- `LEETCODE_SESSION`
- `CSRFTOKEN`

Optional:

- `PREFERRED_LANGS`

Recommended optional values:

- `PREFERRED_LANGS`: `cpp,c++,c`

There is also a ready reference file here:

- [GITHUB_SECRETS_EXAMPLE.md](./GITHUB_SECRETS_EXAMPLE.md)

## Step 5: Enable GitHub Actions write access

Open:

`Settings` -> `Actions` -> `General`

Under workflow permissions:

- choose `Read and write permissions`

## Step 6: Run the first backfill sync

Open:

`Actions` -> `Sync LeetCode`

Then click:

- `Run workflow`

The first run will try to sync all accepted submissions, including older ones.

## Step 7: If the first sync is too large

If you have many accepted problems, the first run may take longer or need another run.

That is okay.

Just run the workflow again. The script is designed to be idempotent and avoid duplicate folders.

## Future submissions

Future accepted submissions are synced automatically by the scheduled workflow.

## Duplicate avoidance

This setup avoids duplicates by:

1. keeping one canonical folder per problem
2. choosing one preferred submission per problem
3. preferring your C++ submission when available
4. regenerating topic indexes instead of copying the same problem into multiple folders

## Recommended privacy settings

- `Private` while testing
- `Public` after cleanup if you want recruiters to see it

If public:

- do not commit secrets
- do not commit `.env`
- avoid noisy experiment files in the repo root

## If LeetCode cookies expire

Your workflow may fail after some time because LeetCode session cookies expire.

If that happens:

1. sign in to LeetCode again
2. get fresh `LEETCODE_SESSION` and `csrftoken`
3. update the GitHub secrets
4. rerun the workflow

## Notes

- This setup is best for C++-first DSA practice.
- Topic organization is generated under `topics/` without duplicating solution folders.
- If LeetCode changes its internal API, the script may need a small update later.
