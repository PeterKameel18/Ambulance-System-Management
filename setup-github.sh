#!/bin/bash

# 🚑 Ambulance Management System - GitHub Setup Script
# This script helps you set up your repository for GitHub deployment

echo "🚑 Ambulance Management System - GitHub Setup"
echo "============================================="

# Check if git is initialized
if [ ! -d ".git" ]; then
    echo "📁 Initializing Git repository..."
    git init
    echo "✅ Git repository initialized"
else
    echo "✅ Git repository already exists"
fi

# Check if remote exists
if ! git remote get-url origin &> /dev/null; then
    echo "🔗 Please add your GitHub repository URL:"
    echo "   Example: https://github.com/yourusername/ambulance-management-system.git"
    read -p "Enter your GitHub repository URL: " REPO_URL
    
    if [ ! -z "$REPO_URL" ]; then
        git remote add origin "$REPO_URL"
        echo "✅ Remote origin added: $REPO_URL"
    else
        echo "❌ No repository URL provided. Please add it manually:"
        echo "   git remote add origin https://github.com/yourusername/ambulance-management-system.git"
    fi
else
    echo "✅ Remote origin already exists: $(git remote get-url origin)"
fi

# Add all files
echo "📦 Adding files to Git..."
git add .

# Check if there are changes to commit
if git diff --staged --quiet; then
    echo "✅ No changes to commit"
else
    echo "💾 Committing changes..."
    git commit -m "Initial commit: Ambulance Management System with GitHub deployment"
    echo "✅ Changes committed"
fi

# Push to GitHub
echo "🚀 Pushing to GitHub..."
if git push -u origin main; then
    echo "✅ Successfully pushed to GitHub!"
    echo ""
    echo "🎉 Next steps:"
    echo "1. Go to your GitHub repository"
    echo "2. Enable GitHub Pages (Settings → Pages → Deploy from branch → main)"
    echo "3. Set up GitHub Actions secrets for deployment:"
    echo "   - HEROKU_API_KEY (for Heroku deployment)"
    echo "   - VERCEL_TOKEN (for Vercel deployment)"
    echo "   - RAILWAY_TOKEN (for Railway deployment)"
    echo "4. Update README.md with your actual URLs"
    echo ""
    echo "📚 For detailed instructions, see GITHUB_DEPLOYMENT.md"
else
    echo "❌ Failed to push to GitHub. Please check your repository URL and try again."
    echo "   You can also push manually: git push -u origin main"
fi

echo ""
echo "🔗 Your repository should be available at:"
echo "   https://github.com/$(git remote get-url origin | sed 's/.*github.com[:/]\([^/]*\/[^/]*\)\.git.*/\1/')"
