# 🚀 Railway Deployment - Alternative Option

## 🎯 Goal
Deploy your ambulance system to Railway for a permanent URL that works on any device.

## 📋 Prerequisites
- GitHub account (you already have this)
- Railway account (free)

## 🚀 Step-by-Step Deployment

### Step 1: Create Railway Account
1. **Go to**: https://railway.app
2. **Click**: "Start a New Project"
3. **Sign up** with GitHub
4. **Authorize** Railway to access your repositories

### Step 2: Deploy from GitHub
1. **Click**: "Deploy from GitHub repo"
2. **Select**: `PeterKameel18/Ambulance-System-Management`
3. **Railway will automatically**:
   - Detect it's a Python project
   - Install dependencies
   - Deploy your app

### Step 3: Configure Environment
1. **Go to**: Your project dashboard
2. **Click**: "Variables" tab
3. **Add** environment variables:
   - `PORT`: `5050`
   - `DEBUG`: `False`

### Step 4: Deploy
1. **Click**: "Deploy" button
2. **Wait** for deployment to complete
3. **Get** your permanent URL: `https://your-project-name.railway.app`

### Step 5: Update Frontend URLs
1. **Go to**: Your project files
2. **Edit**: `web/script.js`
3. **Change** the API URL:
   ```javascript
   const API_BASE_URL = 'https://your-project-name.railway.app/api';
   ```
4. **Commit** and push changes

## 🎉 Result
Your ambulance system will be live at:
- **Main App**: `https://your-project-name.railway.app`
- **Full functionality** with real-time simulation
- **File upload** and demo features
- **Mobile responsive** design
- **Works on any device** with internet connection

## 🔧 Troubleshooting
- **If deployment fails**: Check the logs in Railway dashboard
- **If C++ compilation fails**: Railway might not support C++, use Python-only version
- **If app doesn't start**: Check the environment variables

## 📱 Mobile Access
Your app will work perfectly on mobile devices at the same URL!

## 🎯 For Your Portfolio
- **Add this URL** to your portfolio website
- **Share this URL** with potential employers
- **Use this URL** in your resume and LinkedIn profile
- **This URL works 24/7** and is accessible from anywhere

## 🚀 Advantages of Railway
✅ **Automatic deployment** from GitHub
✅ **Free tier** available
✅ **Easy to use** interface
✅ **Automatic scaling**
✅ **Custom domains** available
✅ **Environment variables** management

---

**Railway is a great alternative if PythonAnywhere doesn't work!** 🚑
