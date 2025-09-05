# 🚑 Ambulance Management System

A comprehensive ambulance allocation and tracking system with real-time simulation capabilities, featuring both a C++ backend simulation engine and a modern web-based GUI.

## 🌟 Features

### Core Functionality
- **Real-time Ambulance Allocation**: Intelligent assignment of ambulances based on availability, priority, and distance
- **Multi-Hospital Support**: Manages ambulance resources across multiple hospitals simultaneously
- **Priority Queue Management**: Handles Emergency Priority (EP), Special Priority (SP), and Normal Priority (NP) patients
- **Dynamic Simulation**: Real-time simulation with configurable speed and interactive controls
- **Performance Analytics**: Comprehensive statistics including response times, utilization rates, and completion metrics

### Technical Features
- **C++ Simulation Engine**: High-performance backend simulation with advanced data structures
- **Modern Web GUI**: Responsive, interactive web interface with real-time updates
- **RESTful API**: Flask-based backend API connecting the simulation with the frontend
- **Cross-Platform**: Works on Windows, macOS, and Linux
- **Real-time Updates**: Live monitoring of ambulance status and patient queues

## 🏗️ Architecture

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Web Frontend  │◄──►│   Flask API     │◄──►│  C++ Simulation │
│   (HTML/CSS/JS) │    │   (Python)      │    │   (C++ Engine)  │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

## 🚀 Quick Start

### Prerequisites
- **C++ Compiler**: g++ (Linux/macOS) or Visual Studio (Windows)
- **Python 3.7+**: For the backend API
- **Modern Web Browser**: For the frontend interface

### Installation

1. **Clone the repository**
   ```bash
   git clone <repository-url>
   cd Ambulance-System-Management
   ```

2. **Install Python dependencies**
   ```bash
   cd backend
   pip install -r requirements.txt
   ```

3. **Compile the C++ simulation**
   ```bash
   cd ..
   g++ -o ambulance Main.cpp -std=c++11
   ```

### Running the Application

1. **Start the backend server**
   ```bash
   cd backend
   python server.py
   ```

2. **Open the web interface**
   - Navigate to `http://localhost:5000` in your web browser
   - The GUI will automatically connect to the backend API

3. **Start a simulation**
   - Click "Start Simulation" to begin
   - Use the speed slider to control simulation speed
   - Monitor real-time updates in the dashboard

## 📁 Project Structure

```
Ambulance-System-Management/
├── Main.cpp                 # Main C++ simulation entry point
├── *.h                      # C++ header files (classes, data structures)
├── input.txt               # Sample input file 1
├── input2.txt              # Sample input file 2
├── outputfile.txt          # Generated simulation output
├── web/                    # Frontend web application
│   ├── index.html          # Main HTML interface
│   ├── styles.css          # CSS styling
│   └── script.js           # JavaScript functionality
├── backend/                # Backend API server
│   ├── server.py           # Flask API server
│   └── requirements.txt    # Python dependencies
└── README.md              # This file
```

## 🎮 Usage

### Web Interface

1. **Control Panel**
   - **Start Simulation**: Begin the ambulance simulation
   - **Pause/Resume**: Control simulation execution
   - **Reset**: Restart the simulation
   - **Speed Control**: Adjust simulation speed (1x to 10x)

2. **Dashboard**
   - **Hospital Cards**: Real-time status of each hospital
   - **Statistics Panel**: Key performance metrics
   - **Activity Log**: Live simulation events
   - **Output Panel**: Download simulation results

### Input File Format

The simulation accepts input files with the following format:
```
4                           # Number of hospitals
180 95                      # Special car speed, Normal car speed
0 154 587 634              # Distance matrix (4x4)
154 0 533 214
587 533 0 945
634 214 945 0
3 11                        # Hospital 1: 3 special cars, 11 normal cars
2 2                         # Hospital 2: 2 special cars, 2 normal cars
6 15                        # Hospital 3: 6 special cars, 15 normal cars
1 2                         # Hospital 4: 1 special car, 2 normal cars
30                          # Number of patient requests
NP 3 1 2 700               # Patient type, timestep, ID, hospital, distance
EP 5 3 2 400 8             # EP patients include severity level
...                         # More patient requests
2                           # Number of cancellations
1 2 1                       # Cancellation: timestep, patient ID, hospital
2 1 2                       # Another cancellation
```

## 🔧 API Endpoints

### Simulation Control
- `GET /api/status` - Get current simulation status
- `POST /api/simulation/start` - Start simulation
- `POST /api/simulation/pause` - Pause simulation
- `POST /api/simulation/resume` - Resume simulation
- `POST /api/simulation/stop` - Stop simulation
- `POST /api/simulation/reset` - Reset simulation

### Data Retrieval
- `GET /api/simulation/data` - Get current simulation data
- `GET /api/output` - Get simulation output
- `GET /api/input-files` - List available input files

## 📊 Output Format

The simulation generates detailed output including:
- **Patient Completion Times**: Finish time, patient ID, queue time, wait time
- **System Statistics**: Total patients, hospitals, cars
- **Performance Metrics**: Average wait time, utilization rate

Example output:
```
FT	PID	QT	WT
4	3	5	-3
4	4	8	-6
15	2	3	6
...
patients: 30	[NP:11 ,SP:8 ,EP:11]
Hospitals = 4
cars: 42	[SCar: 12, NCar: 30]
Avg wait time = 2
Avg utilization = 6%
```

## 🛠️ Development

### Building from Source

1. **C++ Compilation**
   ```bash
   g++ -o ambulance Main.cpp -std=c++11
   ```

2. **Python Backend**
   ```bash
   cd backend
   pip install -r requirements.txt
   python server.py
   ```

3. **Web Frontend**
   - No build process required
   - Serves static files directly

### Code Structure

- **Main.cpp**: Entry point and user interface
- **Organizer.h**: Main simulation controller
- **Hospital.h**: Hospital management and car allocation
- **Patient.h**: Patient data and priority handling
- **Car.h**: Ambulance state management
- **Queue Classes**: Priority queues and linked lists for data management

## 🎯 Key Algorithms

1. **Ambulance Allocation**: Distance-based assignment with priority consideration
2. **Queue Management**: Priority-based patient queuing system
3. **Simulation Engine**: Discrete event simulation with timestep processing
4. **Performance Calculation**: Real-time statistics computation

## 🚀 Deployment

### Local Development
- Run the Flask server locally
- Access via `http://localhost:5000`

### Production Deployment
- Deploy Flask app to cloud platform (Heroku, AWS, etc.)
- Configure CORS for cross-origin requests
- Set up proper error handling and logging

## 📈 Performance

- **Simulation Speed**: Up to 10x real-time speed
- **Scalability**: Supports multiple hospitals and hundreds of patients
- **Memory Efficiency**: Optimized data structures for large datasets
- **Real-time Updates**: Sub-second response times for GUI updates

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 👨‍💻 Author

**Peter** - College Project
- GitHub: [Your GitHub Profile]
- LinkedIn: [Your LinkedIn Profile]

## 🙏 Acknowledgments

- Data structures and algorithms course materials
- Flask documentation and community
- Modern web development best practices

---

**Note**: This is a college project demonstrating advanced C++ programming, data structures, and full-stack web development skills.