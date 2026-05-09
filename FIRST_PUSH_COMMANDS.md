# Exact Commands After You Create Your GitHub Repo

Replace:

- `<your-username>`
- `<your-repo>`

Then run these commands from this folder:

```powershell
git branch -M main
git add .
git commit -m "Initial LeetCode sync setup"
git remote add origin https://github.com/<your-username>/<your-repo>.git
git push -u origin main
```

If you already created a different remote by mistake:

```powershell
git remote remove origin
git remote add origin https://github.com/<your-username>/<your-repo>.git
git push -u origin main
```
