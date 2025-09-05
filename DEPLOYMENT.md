# 🚑 Ambulance Management System - Deployment Guide

## 📋 Overview
This is a full-stack ambulance management simulation system built with C++, Python Flask, and modern web technologies. Perfect for showcasing your software engineering skills in your portfolio.

## 🏗️ Architecture
- **Backend**: Python Flask API (Port 5050)
- **Frontend**: HTML5, CSS3, JavaScript (ES6+)
- **Core Logic**: C++ simulation engine
- **Data Visualization**: Chart.js, real-time updates

## 🚀 Quick Start (Local Development)

### Prerequisites
- Python 3.7+
- C++ compiler (g++)
- Modern web browser

### 1. Clone and Setup
```bash
git clone <your-repo-url>
cd Ambulance-System-Management
```

### 2. Install Dependencies
```bash
cd backend
pip install -r requirements.txt
```

### 3. Compile C++ Code
```bash
cd ..
g++ -o ambulance_sim Main.cpp -std=c++11
```

### 4. Start the System
```bash
# Terminal 1: Start backend
cd backend
python3 server.py

# Terminal 2: Start frontend (optional - can open directly)
cd web
python3 -m http.server 8080
```

### 5. Access the Application
- **Main App**: http://localhost:5050
- **Frontend Only**: http://localhost:8080 (if using separate server)

## 🌐 Production Deployment Options

### Option 1: Heroku (Recommended for Portfolio)

#### 1. Create Heroku App
```bash
# Install Heroku CLI first
heroku create your-ambulance-system
```

#### 2. Create Procfile
```bash
echo "web: python3 backend/server.py" > Procfile
```

#### 3. Create runtime.txt
```bash
echo "python-3.9.0" > runtime.txt
```

#### 4. Deploy
```bash
git add .
git commit -m "Deploy ambulance system"
git push heroku main
```

### Option 2: Vercel (Frontend) + Railway (Backend)

#### Frontend (Vercel)
1. Connect your GitHub repo to Vercel
2. Set build command: `npm install && npm run build`
3. Set output directory: `web`

#### Backend (Railway)
1. Connect GitHub repo to Railway
2. Set start command: `cd backend && python3 server.py`
3. Set environment variables

### Option 3: DigitalOcean App Platform

1. Create new app from GitHub
2. Add backend service (Python)
3. Add frontend service (Static site)
4. Configure build settings

## 📁 Project Structure
```
Ambulance-System-Management/
├── backend/
│   ├── server.py              # Flask API server
│   └── requirements.txt       # Python dependencies
├── web/
│   ├── index.html            # Main frontend
│   ├── styles.css            # Styling
│   └── script.js             # Frontend logic
├── Main.cpp                  # C++ simulation core
├── *.h                       # C++ header files
├── input.txt                 # Sample input data
├── run.sh                    # Local startup script
├── README.md                 # Project documentation
├── PORTFOLIO.md              # Portfolio showcase
└── DEPLOYMENT.md             # This file
```

## 🔧 Environment Configuration

### Backend Configuration
```python
# In backend/server.py
app.run(host='0.0.0.0', port=5050, debug=False)  # Production
```

### Frontend Configuration
```javascript
// In web/script.js
const API_BASE_URL = process.env.API_URL || 'http://localhost:5050';
```

## 📊 Features to Highlight in Portfolio

### 🎯 Core Features
- **Real-time Simulation**: Dynamic timestep progression
- **File Upload**: Support for custom input files
- **Interactive Dashboard**: Live data visualization
- **Responsive Design**: Mobile-friendly interface
- **Performance Metrics**: Response times, utilization rates

### 🛠️ Technical Highlights
- **Full-stack Development**: C++, Python, JavaScript
- **RESTful API**: Clean backend architecture
- **Modern Frontend**: ES6+, Chart.js, responsive design
- **Real-time Updates**: WebSocket-like polling
- **File Processing**: Upload and validation
- **Error Handling**: Comprehensive error management

## 🎨 Portfolio Showcase

### Screenshots to Include
1. **Welcome Screen**: Clean, professional landing
2. **File Upload**: Drag-and-drop interface
3. **Simulation Dashboard**: Real-time metrics
4. **Mobile View**: Responsive design
5. **Code Snippets**: Key technical implementations

### Demo Video Script
1. **Introduction** (10s): "Ambulance Management System - Full-stack simulation"
2. **File Upload** (15s): Show file selection and upload process
3. **Simulation Start** (20s): Demonstrate real-time updates
4. **Dashboard Features** (30s): Show metrics, charts, and controls
5. **Technical Overview** (25s): Highlight code architecture

## 🔗 Portfolio Integration

### GitHub Repository
- Clean commit history
- Comprehensive README
- Proper file structure
- Issue tracking enabled

### Live Demo
- Deploy to Heroku/Vercel
- Include demo data
- Add loading states
- Error handling

### Documentation
- Technical documentation
- API documentation
- User guide
- Architecture diagrams

## 🚀 Performance Optimization

### Backend
- Enable gzip compression
- Add caching headers
- Optimize database queries
- Use production WSGI server

### Frontend
- Minify CSS/JS
- Optimize images
- Enable browser caching
- Use CDN for assets

## 🔒 Security Considerations

### Backend
- Input validation
- File upload restrictions
- CORS configuration
- Rate limiting

### Frontend
- XSS prevention
- Input sanitization
- Secure file handling

## 📈 Analytics & Monitoring

### Add to Portfolio
- User interaction tracking
- Performance metrics
- Error logging
- Usage statistics

## 🎯 Next Steps for Portfolio

1. **Deploy to Heroku** (Easiest option)
2. **Create demo video** (2-3 minutes)
3. **Write case study** (Technical challenges, solutions)
4. **Add to portfolio website**
5. **Share on LinkedIn** with technical details

## 📞 Support

For deployment issues:
- Check server logs
- Verify environment variables
- Test locally first
- Check port availability

---

**Ready to deploy? Start with Heroku for the quickest portfolio showcase!** 🚀
