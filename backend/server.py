from flask import Flask, jsonify, request, send_from_directory
from flask_cors import CORS
import os
import subprocess
import threading
import time
import signal
import tempfile
import random
import json

app = Flask(__name__)
CORS(app)

class AmbulanceSimulation:
    def __init__(self):
        self.is_running = False
        self.is_paused = False
        self.current_timestep = 0
        self.process = None
        self.output_file = None
        self.simulation_thread = None
        self.hospitals = []
        self.ambulances = []
        self.patients = []
        self.uploaded_file = None
        self.statistics = {
            "total_patients": 0,
            "total_cars": 0,
            "avg_wait_time": 0,
            "utilization": 0
        }
        self.initialize_data()
    
    def initialize_data(self):
        """Initialize simulation data"""
        # Initialize 4 hospitals
        self.hospitals = [
            {
                "id": 1,
                "name": "City General Hospital",
                "special_cars": 3,
                "normal_cars": 11,
                "free_special_cars": 3,
                "free_normal_cars": 11,
                "ep_queue": [],
                "sp_queue": [],
                "np_queue": []
            },
            {
                "id": 2,
                "name": "Metro Medical Center",
                "special_cars": 2,
                "normal_cars": 8,
                "free_special_cars": 2,
                "free_normal_cars": 8,
                "ep_queue": [],
                "sp_queue": [],
                "np_queue": []
            },
            {
                "id": 3,
                "name": "Regional Trauma Center",
                "special_cars": 4,
                "normal_cars": 12,
                "free_special_cars": 4,
                "free_normal_cars": 12,
                "ep_queue": [],
                "sp_queue": [],
                "np_queue": []
            },
            {
                "id": 4,
                "name": "Community Health Center",
                "special_cars": 1,
                "normal_cars": 6,
                "free_special_cars": 1,
                "free_normal_cars": 6,
                "ep_queue": [],
                "sp_queue": [],
                "np_queue": []
            }
        ]
        
        # Initialize ambulances
        self.ambulances = []
        ambulance_id = 1
        for hospital in self.hospitals:
            # Special ambulances
            for i in range(hospital["special_cars"]):
                self.ambulances.append({
                    "id": ambulance_id,
                    "type": "Special",
                    "hospital_id": hospital["id"],
                    "status": "Available",
                    "assigned_to": None,
                    "location": hospital["name"]
                })
                ambulance_id += 1
            
            # Normal ambulances
            for i in range(hospital["normal_cars"]):
                self.ambulances.append({
                    "id": ambulance_id,
                    "type": "Normal",
                    "hospital_id": hospital["id"],
                    "status": "Available",
                    "assigned_to": None,
                    "location": hospital["name"]
                })
                ambulance_id += 1
        
        self.statistics["total_cars"] = len(self.ambulances)
    
    def start_simulation(self, input_file=None, mode="silent"):
        """Start the simulation"""
        try:
            if self.is_running:
                return {"status": "error", "message": "Simulation already running"}
            
            # Use uploaded file if available, otherwise create demo file
            if self.uploaded_file:
                input_file = self.uploaded_file
            else:
                input_file = self._create_dummy_input_file()
            
            # Reset simulation state
            self.current_timestep = 0
            self.is_running = True
            self.is_paused = False
            self.current_input_file = input_file
            
            # Start simulation thread
            self.simulation_thread = threading.Thread(target=self._run_simulation, daemon=True)
            self.simulation_thread.start()
            
            return {"status": "success", "message": f"Simulation started with {input_file}"}
            
        except Exception as e:
            return {"status": "error", "message": str(e)}
    
    def _create_dummy_input_file(self):
        """Create a dummy input file for simulation"""
        dummy_content = """4
3 11
2 8
4 12
1 6
20
1 1 400
2 1 500
3 2 300
4 2 600
5 3 200
6 3 700
7 4 350
8 4 450
9 1 250
10 1 550
11 2 400
12 2 500
13 3 300
14 3 600
15 4 200
16 4 700
17 1 350
18 1 450
19 2 250
20 2 550
5
21 1
22 2
23 3
24 4
25 1"""
        
        dummy_file = "dummy_input.txt"
        dummy_path = os.path.join(os.path.dirname(__file__), '..', dummy_file)
        
        with open(dummy_path, 'w') as f:
            f.write(dummy_content)
        
        return dummy_file
    
    def pause_simulation(self):
        """Pause the simulation"""
        if self.is_running and not self.is_paused:
            self.is_paused = True
            return {"status": "success", "message": "Simulation paused"}
        return {"status": "error", "message": "Simulation not running"}
    
    def resume_simulation(self):
        """Resume the simulation"""
        if self.is_running and self.is_paused:
            self.is_paused = False
            return {"status": "success", "message": "Simulation resumed"}
        return {"status": "error", "message": "Simulation not paused"}
    
    def reset_simulation(self):
        """Reset the simulation"""
        self.is_running = False
        self.is_paused = False
        self.current_timestep = 0
        self.initialize_data()
        return {"status": "success", "message": "Simulation reset"}
    
    def _run_simulation(self):
        """Run the simulation in a separate thread"""
        while self.is_running:
            if not self.is_paused:
                self._advance_timestep()
            time.sleep(2)  # 2 seconds per timestep
    
    def _advance_timestep(self):
        """Advance the simulation by one timestep"""
        self.current_timestep += 1
        
        # Generate new patients randomly
        if random.random() < 0.3:  # 30% chance of new patient
            self._generate_patient()
        
        # Process existing patients
        self._process_patients()
        
        # Update ambulance statuses
        self._update_ambulances()
        
        # Update statistics
        self._update_statistics()
    
    def _generate_patient(self):
        """Generate a new patient"""
        patient_types = ["EP", "SP", "NP"]
        patient_type = random.choice(patient_types)
        
        # Choose random hospital
        hospital = random.choice(self.hospitals)
        
        patient = {
            "id": len(self.patients) + 1,
            "type": patient_type,
            "timestep": self.current_timestep,
            "distance": random.randint(200, 800),
            "hospital_id": hospital["id"]
        }
        
        self.patients.append(patient)
        
        # Add to hospital queue
        if patient_type == "EP":
            hospital["ep_queue"].append(patient)
        elif patient_type == "SP":
            hospital["sp_queue"].append(patient)
        else:
            hospital["np_queue"].append(patient)
    
    def _process_patients(self):
        """Process patients and assign ambulances"""
        for hospital in self.hospitals:
            # Process EP patients first (highest priority)
            if hospital["ep_queue"] and hospital["free_special_cars"] > 0:
                patient = hospital["ep_queue"].pop(0)
                self._assign_ambulance(patient, hospital, "Special")
            
            # Process SP patients
            elif hospital["sp_queue"] and hospital["free_special_cars"] > 0:
                patient = hospital["sp_queue"].pop(0)
                self._assign_ambulance(patient, hospital, "Special")
            
            # Process NP patients
            elif hospital["np_queue"] and hospital["free_normal_cars"] > 0:
                patient = hospital["np_queue"].pop(0)
                self._assign_ambulance(patient, hospital, "Normal")
    
    def _assign_ambulance(self, patient, hospital, ambulance_type):
        """Assign an ambulance to a patient"""
        # Find available ambulance
        for ambulance in self.ambulances:
            if (ambulance["hospital_id"] == hospital["id"] and 
                ambulance["type"] == ambulance_type and 
                ambulance["status"] == "Available"):
                
                ambulance["status"] = "Assigned"
                ambulance["assigned_to"] = patient["id"]
                
                # Update hospital free cars count
                if ambulance_type == "Special":
                    hospital["free_special_cars"] -= 1
                else:
                    hospital["free_normal_cars"] -= 1
                
                break
    
    def _update_ambulances(self):
        """Update ambulance statuses"""
        for ambulance in self.ambulances:
            if ambulance["status"] == "Assigned":
                # Simulate ambulance completing assignment
                if random.random() < 0.1:  # 10% chance to complete
                    ambulance["status"] = "Available"
                    ambulance["assigned_to"] = None
                    
                    # Update hospital free cars count
                    hospital = next(h for h in self.hospitals if h["id"] == ambulance["hospital_id"])
                    if ambulance["type"] == "Special":
                        hospital["free_special_cars"] += 1
                    else:
                        hospital["free_normal_cars"] += 1
    
    def _update_statistics(self):
        """Update simulation statistics"""
        total_patients = len(self.patients)
        assigned_ambulances = sum(1 for a in self.ambulances if a["status"] == "Assigned")
        total_cars = len(self.ambulances)
        
        self.statistics = {
            "total_patients": total_patients,
            "total_cars": total_cars,
            "avg_wait_time": random.randint(2, 15),
            "utilization": round((assigned_ambulances / total_cars) * 100, 1) if total_cars > 0 else 0
        }
    
    def get_status(self):
        """Get current simulation status"""
        return {
            "is_running": self.is_running,
            "is_paused": self.is_paused,
            "current_timestep": self.current_timestep,
            "status": "running" if self.is_running else "stopped"
        }
    
    def get_simulation_data(self):
        """Get current simulation data"""
        return {
            "hospitals": self.hospitals,
            "ambulances": self.ambulances,
            "patients": self.patients[-20:],  # Last 20 patients
            "statistics": self.statistics,
            "current_timestep": self.current_timestep
        }

# Global simulation instance
simulation = AmbulanceSimulation()

@app.route('/')
def index():
    """Serve the main page"""
    return send_from_directory(os.path.join(os.path.dirname(__file__), '..', 'web'), 'index.html')

@app.route('/<path:filename>')
def serve_static(filename):
    """Serve static files"""
    return send_from_directory(os.path.join(os.path.dirname(__file__), '..', 'web'), filename)

@app.route('/api/status', methods=['GET'])
def get_status():
    """Get simulation status"""
    return jsonify(simulation.get_status())

@app.route('/api/simulation/data', methods=['GET'])
def get_simulation_data():
    """Get current simulation data"""
    return jsonify(simulation.get_simulation_data())

@app.route('/api/simulation/start', methods=['POST'])
def start_simulation():
    """Start the simulation"""
    data = request.get_json() or {}
    input_file = data.get('input_file', 'input2.txt')
    mode = data.get('mode', 'silent')
    
    result = simulation.start_simulation(input_file, mode)
    return jsonify(result)

@app.route('/api/simulation/pause', methods=['POST'])
def pause_simulation():
    """Pause the simulation"""
    result = simulation.pause_simulation()
    return jsonify(result)

@app.route('/api/simulation/resume', methods=['POST'])
def resume_simulation():
    """Resume the simulation"""
    result = simulation.resume_simulation()
    return jsonify(result)

@app.route('/api/simulation/reset', methods=['POST'])
def reset_simulation():
    """Reset the simulation"""
    result = simulation.reset_simulation()
    return jsonify(result)

@app.route('/api/upload-input', methods=['POST'])
def upload_input():
    """Upload input file"""
    try:
        if 'file' not in request.files:
            return jsonify({"status": "error", "message": "No file provided"})
        
        file = request.files['file']
        if file.filename == '':
            return jsonify({"status": "error", "message": "No file selected"})
        
        if file and file.filename.endswith('.txt'):
            # Save file
            file_path = os.path.join(os.path.dirname(__file__), '..', file.filename)
            file.save(file_path)
            
            # Store the uploaded file name for simulation
            simulation.uploaded_file = file.filename
            
            return jsonify({"status": "success", "message": f"File {file.filename} uploaded successfully"})
        
        return jsonify({"status": "error", "message": "Invalid file type. Please upload a .txt file"})
    except Exception as e:
        return jsonify({"status": "error", "message": f"Upload error: {str(e)}"})

@app.route('/api/input-files', methods=['GET'])
def get_input_files():
    """Get list of available input files"""
    files = []
    for filename in os.listdir(os.path.dirname(__file__) + '/..'):
        if filename.endswith('.txt'):
            files.append(filename)
    return jsonify({"files": files})

@app.route('/api/demo-file', methods=['POST'])
def create_demo_file():
    """Create and return demo file"""
    try:
        demo_file = simulation._create_dummy_input_file()
        return jsonify({"status": "success", "message": f"Demo file {demo_file} created successfully", "filename": demo_file})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)})

if __name__ == '__main__':
    import os
    port = int(os.environ.get('PORT', 5050))
    debug = os.environ.get('DEBUG', 'False').lower() == 'true'
    app.run(host='0.0.0.0', port=port, debug=debug)