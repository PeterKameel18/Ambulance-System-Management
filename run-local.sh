#!/bin/bash

# 🚑 Ambulance Management System - Local Development Server
# This script runs your system locally and makes it accessible to others

echo "🚑 Starting Ambulance Management System..."
echo "========================================"

# Check if we're in the right directory
if [ ! -f "backend/server.py" ]; then
    echo "❌ Please run this script from the Ambulance-System-Management directory"
    exit 1
fi

# Compile C++ code
echo "🔨 Compiling C++ simulation engine..."
g++ -o ambulance_sim Main.cpp -std=c++11
if [ $? -eq 0 ]; then
    echo "✅ C++ code compiled successfully"
else
    echo "❌ C++ compilation failed"
    exit 1
fi

# Start the backend server
echo "🚀 Starting Flask backend server..."
cd backend
python3 server.py &
BACKEND_PID=$!

# Wait a moment for server to start
sleep 3

# Check if server started successfully
if ps -p $BACKEND_PID > /dev/null; then
    echo "✅ Backend server started successfully"
    echo "🌐 Your system is now running at: http://localhost:5050"
    echo ""
    echo "📱 To access from other devices on your network:"
    echo "   1. Find your IP address: ifconfig | grep 'inet '"
    echo "   2. Use: http://YOUR_IP:5050"
    echo ""
    echo "🛑 To stop the server, press Ctrl+C"
    echo ""
    
    # Open browser
    echo "🌐 Opening browser..."
    open http://localhost:5050
    
    # Wait for user to stop
    wait $BACKEND_PID
else
    echo "❌ Failed to start backend server"
    exit 1
fi
