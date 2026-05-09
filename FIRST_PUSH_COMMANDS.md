# Exact Commands After You Create Your GitHub Repo

Replace:

- `<your-username>`
- `<your-repo>`

Then run these commands from this folder:

```powershell
git remote add origin https://github.com/<your-username>/<your-repo>.git
git push -u origin main
```

If you already created a different remote by mistake:

```powershell
git remote remove origin
git remote add origin https://github.com/<your-username>/<your-repo>.git
git push -u origin main
```

If you edit files locally before your first push, commit those changes first:

```powershell
git add .
git commit -m "Update LeetCode sync setup"
git push -u origin main
```
