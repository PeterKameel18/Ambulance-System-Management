#!/bin/bash

# Ambulance Management System - Startup Script
# This script compiles the C++ simulation and starts the web server

echo "🚑 Starting Ambulance Management System..."

# Check if we're in the right directory
if [ ! -f "Main.cpp" ]; then
    echo "❌ Error: Please run this script from the Ambulance-System-Management directory"
    exit 1
fi

# Compile the C++ simulation
echo "🔨 Compiling C++ simulation..."
g++ -o ambulance Main.cpp -std=c++11

if [ $? -eq 0 ]; then
    echo "✅ C++ simulation compiled successfully"
else
    echo "❌ Error: Failed to compile C++ simulation"
    exit 1
fi

# Check if Python is available
if ! command -v python3 &> /dev/null; then
    echo "❌ Error: Python 3 is required but not installed"
    exit 1
fi

# Install Python dependencies
echo "📦 Installing Python dependencies..."
cd backend
pip3 install -r requirements.txt

if [ $? -eq 0 ]; then
    echo "✅ Python dependencies installed successfully"
else
    echo "❌ Error: Failed to install Python dependencies"
    exit 1
fi

# Start the web server
echo "🌐 Starting web server..."
echo "📍 Frontend will be available at: http://localhost:5050"
echo "📍 API will be available at: http://localhost:5050/api/"
echo ""
echo "Press Ctrl+C to stop the server"
echo ""

python3 server.py
