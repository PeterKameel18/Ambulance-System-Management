# 🚀 PythonAnywhere Deployment Guide

## 📋 Overview
PythonAnywhere is a free Python hosting service perfect for your ambulance system. It's easy to set up and doesn't require payment verification.

## 🎯 Step-by-Step Deployment

### Step 1: Create PythonAnywhere Account
1. Go to [pythonanywhere.com](https://www.pythonanywhere.com)
2. Click **"Start a free account"**
3. Choose **"Beginner"** (free tier)
4. Sign up with your email

### Step 2: Upload Your Code
1. **Go to Files tab** in PythonAnywhere dashboard
2. **Navigate to `/home/yourusername/`**
3. **Create a new directory**: `ambulance-system`
4. **Upload your files**:
   - Upload `backend/` folder
   - Upload `web/` folder
   - Upload `Main.cpp` and all `.h` files
   - Upload `input.txt`

### Step 3: Install Dependencies
1. **Go to Consoles tab**
2. **Start a new console** (Bash)
3. **Navigate to your project**:
   ```bash
   cd /home/yourusername/ambulance-system
   ```
4. **Install Python dependencies**:
   ```bash
   pip3.10 install --user flask
   ```

### Step 4: Compile C++ Code
1. **In the same console**:
   ```bash
   g++ -o ambulance_sim Main.cpp -std=c++11
   ```

### Step 5: Create Web App
1. **Go to Web tab**
2. **Click "Add a new web app"**
3. **Choose "Flask"**
4. **Python version**: 3.10
5. **Flask project path**: `/home/yourusername/ambulance-system/backend`
6. **Flask app file**: `server.py`

### Step 6: Configure Web App
1. **Go to Web tab → your web app**
2. **Click "Reload"** to start your app
3. **Your app will be available at**: `https://yourusername.pythonanywhere.com`

### Step 7: Update Frontend URLs
1. **Edit `web/script.js`**
2. **Change API URL**:
   ```javascript
   const API_BASE_URL = 'https://yourusername.pythonanywhere.com/api';
   ```

## 🎉 Result
Your ambulance system will be live at:
- **Main App**: `https://yourusername.pythonanywhere.com`
- **Full functionality** with real-time simulation
- **File upload** and demo features
- **Mobile responsive** design

## 🔧 Troubleshooting
- **If C++ compilation fails**: Make sure all `.h` files are uploaded
- **If Flask import fails**: Check Python version (use 3.10)
- **If app doesn't start**: Check the error logs in Web tab

## 📱 Mobile Access
Your app will work perfectly on mobile devices at the same URL!
