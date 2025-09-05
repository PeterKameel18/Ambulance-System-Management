# 🚀 GitHub Deployment Guide - Ambulance Management System

## 📋 Overview
This guide shows you how to deploy your ambulance management system using GitHub with multiple deployment options including GitHub Pages, GitHub Actions, and integration with external platforms.

## 🎯 Deployment Options

### Option 1: GitHub Pages (Frontend Only)
- **Best for**: Static frontend showcase
- **Limitations**: No backend API (simulation won't work)
- **Use case**: Portfolio showcase with screenshots

### Option 2: GitHub Actions + Heroku
- **Best for**: Full-stack deployment
- **Features**: Complete system with backend
- **Use case**: Live demo with full functionality

### Option 3: GitHub Actions + Vercel + Railway
- **Best for**: Modern deployment stack
- **Features**: Separate frontend and backend
- **Use case**: Professional portfolio

## 🚀 Option 1: GitHub Pages Deployment

### Step 1: Prepare Repository
```bash
# Initialize git repository
git init

# Add all files
git add .

# Create initial commit
git commit -m "Initial commit: Ambulance Management System"

# Add remote repository
git remote add origin https://github.com/yourusername/ambulance-management-system.git

# Push to GitHub
git push -u origin main
```

### Step 2: Enable GitHub Pages
1. Go to your repository on GitHub
2. Click **Settings** tab
3. Scroll down to **Pages** section
4. Under **Source**, select **Deploy from a branch**
5. Choose **main** branch and **/ (root)** folder
6. Click **Save**

### Step 3: Create Static Demo
Since GitHub Pages can't run Python backend, create a static demo:

```bash
# Create a static demo version
mkdir docs
cp -r web/* docs/
```

### Step 4: Update for Static Demo
Create a static demo that shows the UI without backend:

```html
<!-- docs/index.html - Static demo version -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Ambulance Management System - Demo</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <div class="container">
        <h1>🚑 Ambulance Management System</h1>
        <p>This is a static demo. For full functionality, visit the live deployment.</p>
        <div class="demo-screenshots">
            <!-- Add screenshots of the working system -->
        </div>
    </div>
</body>
</html>
```

## 🚀 Option 2: GitHub Actions + Heroku

### Step 1: Create GitHub Actions Workflow
Create `.github/workflows/deploy.yml`:

```yaml
name: Deploy to Heroku

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  deploy:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Set up Python
      uses: actions/setup-python@v4
      with:
        python-version: '3.9'
    
    - name: Install dependencies
      run: |
        cd backend
        pip install -r requirements.txt
    
    - name: Compile C++ code
      run: |
        g++ -o ambulance_sim Main.cpp -std=c++11
    
    - name: Deploy to Heroku
      uses: akhileshns/heroku-deploy@v3.12.12
      with:
        heroku_api_key: ${{secrets.HEROKU_API_KEY}}
        heroku_app_name: "your-ambulance-system"
        heroku_email: "your-email@example.com"
        appdir: "."
```

### Step 2: Set up Heroku Secrets
1. Go to your GitHub repository
2. Click **Settings** → **Secrets and variables** → **Actions**
3. Add new secret:
   - **Name**: `HEROKU_API_KEY`
   - **Value**: Your Heroku API key

### Step 3: Get Heroku API Key
```bash
# Install Heroku CLI
# Login to Heroku
heroku login

# Get API key
heroku auth:token
```

## 🚀 Option 3: GitHub Actions + Vercel + Railway

### Step 1: Create Frontend Deployment (Vercel)
Create `.github/workflows/deploy-frontend.yml`:

```yaml
name: Deploy Frontend to Vercel

on:
  push:
    branches: [ main ]
    paths: [ 'web/**' ]

jobs:
  deploy-frontend:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Deploy to Vercel
      uses: amondnet/vercel-action@v20
      with:
        vercel-token: ${{ secrets.VERCEL_TOKEN }}
        vercel-org-id: ${{ secrets.ORG_ID }}
        vercel-project-id: ${{ secrets.PROJECT_ID }}
        working-directory: ./web
```

### Step 2: Create Backend Deployment (Railway)
Create `.github/workflows/deploy-backend.yml`:

```yaml
name: Deploy Backend to Railway

on:
  push:
    branches: [ main ]
    paths: [ 'backend/**' ]

jobs:
  deploy-backend:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Deploy to Railway
      uses: bervProject/railway-deploy@v1.0.3
      with:
        railway-token: ${{ secrets.RAILWAY_TOKEN }}
        service: backend
        working-directory: ./backend
```

## 📁 Repository Structure for GitHub

```
ambulance-management-system/
├── .github/
│   └── workflows/
│       ├── deploy.yml
│       ├── deploy-frontend.yml
│       └── deploy-backend.yml
├── backend/
│   ├── server.py
│   └── requirements.txt
├── web/
│   ├── index.html
│   ├── styles.css
│   └── script.js
├── docs/                    # For GitHub Pages
│   ├── index.html
│   └── styles.css
├── .gitignore
├── README.md
├── LICENSE
└── DEPLOYMENT.md
```

## 🔧 GitHub Repository Setup

### Step 1: Create Repository
1. Go to GitHub.com
2. Click **New repository**
3. Name: `ambulance-management-system`
4. Description: `Full-stack ambulance management simulation system`
5. Make it **Public** (for portfolio)
6. Add README, .gitignore, and LICENSE

### Step 2: Initialize Local Repository
```bash
# Navigate to your project
cd /Users/Peter/College/AmbulanceSystem/Ambulance-System-Management

# Initialize git
git init

# Add remote
git remote add origin https://github.com/yourusername/ambulance-management-system.git

# Add all files
git add .

# Commit
git commit -m "Initial commit: Ambulance Management System"

# Push to GitHub
git push -u origin main
```

### Step 3: Create .gitignore
```bash
# Create .gitignore file
cat > .gitignore << EOF
# Python
__pycache__/
*.py[cod]
*$py.class
*.so
.Python
env/
venv/
ENV/
env.bak/
venv.bak/

# C++
*.o
*.exe
*.out
*.app
ambulance_sim

# IDE
.vscode/
.idea/
*.swp
*.swo

# OS
.DS_Store
Thumbs.db

# Logs
*.log

# Environment variables
.env
.env.local
.env.production

# Dependencies
node_modules/
EOF
```

## 🎯 Portfolio Integration

### Step 1: Update README
Replace placeholder URLs in README:
```markdown
# Update these URLs in README.md
- **Portfolio**: https://yourportfolio.com
- **LinkedIn**: https://linkedin.com/in/yourprofile
- **GitHub**: https://github.com/yourusername
- **Email**: your.email@example.com
```

### Step 2: Add Portfolio Badges
```markdown
[![GitHub stars](https://img.shields.io/github/stars/yourusername/ambulance-management-system.svg)](https://github.com/yourusername/ambulance-management-system/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/yourusername/ambulance-management-system.svg)](https://github.com/yourusername/ambulance-management-system/network)
[![GitHub issues](https://img.shields.io/github/issues/yourusername/ambulance-management-system.svg)](https://github.com/yourusername/ambulance-management-system/issues)
[![GitHub license](https://img.shields.io/github/license/yourusername/ambulance-management-system.svg)](https://github.com/yourusername/ambulance-management-system/blob/main/LICENSE)
```

### Step 3: Create Issues and Discussions
1. **Issues**: Create templates for bug reports and feature requests
2. **Discussions**: Enable for community interaction
3. **Wiki**: Add technical documentation

## 🚀 Quick Start Commands

### Complete GitHub Setup
```bash
# 1. Initialize repository
git init
git add .
git commit -m "Initial commit: Ambulance Management System"

# 2. Add remote (replace with your GitHub URL)
git remote add origin https://github.com/yourusername/ambulance-management-system.git

# 3. Push to GitHub
git push -u origin main

# 4. Enable GitHub Pages (via GitHub web interface)
# Go to Settings → Pages → Deploy from branch → main

# 5. Set up GitHub Actions (create .github/workflows/deploy.yml)
# 6. Add secrets for deployment platforms
```

## 📊 Deployment Status

### GitHub Pages
- **URL**: `https://yourusername.github.io/ambulance-management-system`
- **Status**: Static demo only
- **Update**: Automatic on push to main

### Heroku (via GitHub Actions)
- **URL**: `https://your-ambulance-system.herokuapp.com`
- **Status**: Full functionality
- **Update**: Automatic on push to main

### Vercel + Railway
- **Frontend**: `https://ambulance-system.vercel.app`
- **Backend**: `https://ambulance-system-backend.railway.app`
- **Status**: Full functionality
- **Update**: Automatic on push to main

## 🔧 Troubleshooting

### Common Issues
1. **GitHub Pages not updating**: Check if main branch is selected
2. **GitHub Actions failing**: Verify secrets are set correctly
3. **Heroku deployment fails**: Check Procfile and requirements.txt
4. **Vercel deployment fails**: Check build settings and environment variables

### Debug Commands
```bash
# Check git status
git status

# Check remote
git remote -v

# Check GitHub Actions logs
# Go to Actions tab in GitHub repository

# Check Heroku logs
heroku logs --tail --app your-app-name
```

## 🎉 Next Steps

1. **Choose deployment option** (GitHub Pages for quick showcase, Heroku for full demo)
2. **Set up repository** with proper structure
3. **Configure GitHub Actions** for automated deployment
4. **Update README** with live demo links
5. **Add to portfolio** with screenshots and case study
6. **Share on LinkedIn** with technical details

---

**Your ambulance system is now ready for GitHub deployment! Choose your preferred option and start showcasing your work!** 🚀
