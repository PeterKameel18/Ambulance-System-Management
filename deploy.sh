#!/bin/bash

# 🚑 Ambulance Management System - Deployment Script
# This script prepares and deploys the system to Heroku

echo "🚑 Ambulance Management System - Deployment Script"
echo "=================================================="

# Check if Heroku CLI is installed
if ! command -v heroku &> /dev/null; then
    echo "❌ Heroku CLI not found. Please install it first:"
    echo "   https://devcenter.heroku.com/articles/heroku-cli"
    exit 1
fi

# Check if user is logged in to Heroku
if ! heroku auth:whoami &> /dev/null; then
    echo "❌ Not logged in to Heroku. Please run: heroku login"
    exit 1
fi

echo "✅ Heroku CLI found and authenticated"

# Create Heroku app (if it doesn't exist)
echo "📱 Creating Heroku app..."
if ! heroku apps:info ambulance-management-system &> /dev/null; then
    heroku create ambulance-management-system
    echo "✅ Heroku app created: ambulance-management-system"
else
    echo "✅ Heroku app already exists: ambulance-management-system"
fi

# Set environment variables
echo "🔧 Setting environment variables..."
heroku config:set DEBUG=False
heroku config:set PORT=5050
echo "✅ Environment variables set"

# Deploy to Heroku
echo "🚀 Deploying to Heroku..."
git add .
git commit -m "Deploy ambulance management system to Heroku"
git push heroku main

# Open the deployed app
echo "🌐 Opening deployed app..."
heroku open

echo ""
echo "🎉 Deployment complete!"
echo "📱 Your app is now live at: https://ambulance-management-system.herokuapp.com"
echo "📊 Check logs with: heroku logs --tail"
echo "🔧 Manage app at: https://dashboard.heroku.com/apps/ambulance-management-system"
