# 🚀 PythonAnywhere Deployment - Step by Step

## 🎯 Goal
Deploy your ambulance system to get a permanent URL that works on any device for your portfolio.

## 📋 Prerequisites
- PythonAnywhere account (free)
- Your deployment package: `deploy-package.zip`

## 🚀 Step-by-Step Deployment

### Step 1: Create PythonAnywhere Account
1. **Go to**: https://www.pythonanywhere.com
2. **Click**: "Start a free account"
3. **Choose**: "Beginner" (free tier)
4. **Sign up** with your email
5. **Verify** your email address

### Step 2: Upload Your Code
1. **Login** to PythonAnywhere
2. **Go to**: Files tab
3. **Navigate to**: `/home/yourusername/`
4. **Click**: "Upload a file"
5. **Upload**: `deploy-package.zip`
6. **Extract** the zip file:
   ```bash
   unzip deploy-package.zip
   ```

### Step 3: Install Dependencies
1. **Go to**: Consoles tab
2. **Start**: New console (Bash)
3. **Navigate** to your project:
   ```bash
   cd /home/yourusername/deploy-package
   ```
4. **Install** Python dependencies:
   ```bash
   pip3.10 install --user flask
   ```

### Step 4: Compile C++ Code
1. **In the same console**:
   ```bash
   g++ -o ambulance_sim Main.cpp -std=c++11
   ```

### Step 5: Create Web App
1. **Go to**: Web tab
2. **Click**: "Add a new web app"
3. **Choose**: "Flask"
4. **Python version**: 3.10
5. **Flask project path**: `/home/yourusername/deploy-package/backend`
6. **Flask app file**: `server.py`

### Step 6: Configure Web App
1. **Go to**: Web tab → your web app
2. **Click**: "Reload" to start your app
3. **Your app will be available at**: `https://yourusername.pythonanywhere.com`

### Step 7: Update Frontend URLs
1. **Edit**: `web/script.js`
2. **Change** the API URL:
   ```javascript
   const API_BASE_URL = 'https://yourusername.pythonanywhere.com/api';
   ```
3. **Save** the file
4. **Reload** your web app

## 🎉 Result
Your ambulance system will be live at:
- **Main App**: `https://yourusername.pythonanywhere.com`
- **Full functionality** with real-time simulation
- **File upload** and demo features
- **Mobile responsive** design
- **Works on any device** with internet connection

## 🔧 Troubleshooting
- **If C++ compilation fails**: Make sure all `.h` files are uploaded
- **If Flask import fails**: Check Python version (use 3.10)
- **If app doesn't start**: Check the error logs in Web tab
- **If frontend doesn't load**: Check the file paths in script.js

## 📱 Mobile Access
Your app will work perfectly on mobile devices at the same URL!

## 🎯 For Your Portfolio
- **Add this URL** to your portfolio website
- **Share this URL** with potential employers
- **Use this URL** in your resume and LinkedIn profile
- **This URL works 24/7** and is accessible from anywhere

## 🚀 Alternative: Railway (If PythonAnywhere doesn't work)
1. **Go to**: https://railway.app
2. **Sign up** with GitHub
3. **Connect** your repository
4. **Deploy** automatically
5. **Get** a permanent URL

## 📊 What You Get
✅ **Permanent URL** for your portfolio
✅ **Full functionality** with real-time simulation
✅ **Mobile responsive** design
✅ **File upload** and demo features
✅ **Professional** appearance
✅ **24/7 availability** from any device

---

**Your ambulance system will be live and accessible from anywhere!** 🚑
