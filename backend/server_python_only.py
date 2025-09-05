from flask import Flask, jsonify, request, send_from_directory
import os
import json
import time
import random
import threading
from datetime import datetime

app = Flask(__name__)

# Serve static files from web directory
@app.route('/')
def index():
    return send_from_directory('../web', 'index.html')

@app.route('/<path:filename>')
def serve_static(filename):
    return send_from_directory('../web', filename)

# Simulation state
simulation_state = {
    'running': False,
    'paused': False,
    'timestep': 0,
    'speed': 1,
    'start_time': None,
    'current_file': None
}

# Simulation data
simulation_data = {
    'hospitals': [],
    'ambulances': [],
    'patients': [],
    'metrics': {
        'total_patients': 0,
        'completed_patients': 0,
        'average_response_time': 0,
        'utilization_rate': 0
    }
}

def generate_hospitals():
    """Generate hospital data"""
    hospitals = []
    for i in range(4):
        hospitals.append({
            'id': i + 1,
            'name': f'Hospital {i + 1}',
            'capacity': random.randint(20, 50),
            'current_load': random.randint(5, 45),
            'distance': random.randint(5, 20),
            'status': 'Available' if random.random() > 0.3 else 'Busy'
        })
    return hospitals

def generate_ambulances():
    """Generate ambulance data"""
    ambulances = []
    for i in range(8):
        statuses = ['Available', 'En Route', 'Busy', 'Returning']
        ambulances.append({
            'id': i + 1,
            'status': random.choice(statuses),
            'location': f'Location {random.randint(1, 10)}',
            'assigned_patient': random.randint(1, 20) if random.random() > 0.5 else None,
            'response_time': random.uniform(1.5, 4.2)
        })
    return ambulances

def generate_patients():
    """Generate patient data"""
    patients = []
    for i in range(15):
        priorities = ['EP', 'SP', 'NP']
        patients.append({
            'id': i + 1,
            'priority': random.choice(priorities),
            'wait_time': random.uniform(0.5, 8.0),
            'assigned_ambulance': random.randint(1, 8) if random.random() > 0.4 else None,
            'status': random.choice(['Waiting', 'In Transit', 'Completed'])
        })
    return patients

def update_simulation():
    """Update simulation data"""
    global simulation_data
    
    if simulation_state['running'] and not simulation_state['paused']:
        simulation_state['timestep'] += 1
        
        # Update hospitals
        for hospital in simulation_data['hospitals']:
            hospital['current_load'] = min(hospital['capacity'], 
                                         hospital['current_load'] + random.randint(-2, 3))
            hospital['status'] = 'Busy' if hospital['current_load'] > hospital['capacity'] * 0.8 else 'Available'
        
        # Update ambulances
        for ambulance in simulation_data['ambulances']:
            if ambulance['status'] == 'Available':
                if random.random() > 0.7:
                    ambulance['status'] = 'En Route'
                    ambulance['assigned_patient'] = random.randint(1, 20)
            elif ambulance['status'] == 'En Route':
                if random.random() > 0.6:
                    ambulance['status'] = 'Busy'
            elif ambulance['status'] == 'Busy':
                if random.random() > 0.5:
                    ambulance['status'] = 'Returning'
            elif ambulance['status'] == 'Returning':
                if random.random() > 0.8:
                    ambulance['status'] = 'Available'
                    ambulance['assigned_patient'] = None
        
        # Update patients
        for patient in simulation_data['patients']:
            if patient['status'] == 'Waiting':
                patient['wait_time'] += 0.1
                if random.random() > 0.8:
                    patient['assigned_ambulance'] = random.randint(1, 8)
                    patient['status'] = 'In Transit'
            elif patient['status'] == 'In Transit':
                if random.random() > 0.7:
                    patient['status'] = 'Completed'
                    patient['assigned_ambulance'] = None
        
        # Update metrics
        simulation_data['metrics']['total_patients'] = len(simulation_data['patients'])
        simulation_data['metrics']['completed_patients'] = len([p for p in simulation_data['patients'] if p['status'] == 'Completed'])
        simulation_data['metrics']['average_response_time'] = random.uniform(2.1, 3.8)
        simulation_data['metrics']['utilization_rate'] = random.uniform(75, 95)

# Initialize simulation data
simulation_data['hospitals'] = generate_hospitals()
simulation_data['ambulances'] = generate_ambulances()
simulation_data['patients'] = generate_patients()

# Start simulation update thread
def simulation_loop():
    while True:
        update_simulation()
        time.sleep(1.0 / simulation_state['speed'])

simulation_thread = threading.Thread(target=simulation_loop, daemon=True)
simulation_thread.start()

@app.route('/api/status')
def get_status():
    return jsonify({
        'status': 'success',
        'running': simulation_state['running'],
        'paused': simulation_state['paused'],
        'timestep': simulation_state['timestep'],
        'speed': simulation_state['speed']
    })

@app.route('/api/simulation/start', methods=['POST'])
def start_simulation():
    simulation_state['running'] = True
    simulation_state['paused'] = False
    simulation_state['start_time'] = time.time()
    return jsonify({'status': 'success', 'message': 'Simulation started'})

@app.route('/api/simulation/pause', methods=['POST'])
def pause_simulation():
    simulation_state['paused'] = True
    return jsonify({'status': 'success', 'message': 'Simulation paused'})

@app.route('/api/simulation/reset', methods=['POST'])
def reset_simulation():
    simulation_state['running'] = False
    simulation_state['paused'] = False
    simulation_state['timestep'] = 0
    simulation_state['start_time'] = None
    
    # Reset simulation data
    simulation_data['hospitals'] = generate_hospitals()
    simulation_data['ambulances'] = generate_ambulances()
    simulation_data['patients'] = generate_patients()
    
    return jsonify({'status': 'success', 'message': 'Simulation reset'})

@app.route('/api/simulation/data')
def get_simulation_data():
    return jsonify({
        'status': 'success',
        'data': simulation_data,
        'state': simulation_state
    })

@app.route('/api/upload-input', methods=['POST'])
def upload_input():
    if 'file' not in request.files:
        return jsonify({'status': 'error', 'message': 'No file provided'})
    
    file = request.files['file']
    if file.filename == '':
        return jsonify({'status': 'error', 'message': 'No file selected'})
    
    if file and file.filename.endswith('.txt'):
        # Save file
        file_path = os.path.join(os.path.dirname(__file__), '..', file.filename)
        file.save(file_path)
        simulation_state['current_file'] = file.filename
        
        return jsonify({
            'status': 'success',
            'message': f'File {file.filename} uploaded successfully',
            'filename': file.filename
        })
    else:
        return jsonify({'status': 'error', 'message': 'Invalid file type. Please upload a .txt file'})

@app.route('/api/demo-file', methods=['POST'])
def create_demo_file():
    demo_file = 'demo_input.txt'
    demo_path = os.path.join(os.path.dirname(__file__), '..', demo_file)
    
    # Create demo input file
    with open(demo_path, 'w') as f:
        f.write("4\n")  # Number of hospitals
        f.write("3 11\n")  # Hospital 1: capacity, distance
        f.write("5 8\n")   # Hospital 2: capacity, distance
        f.write("2 15\n")  # Hospital 3: capacity, distance
        f.write("4 6\n")   # Hospital 4: capacity, distance
    
    simulation_state['current_file'] = demo_file
    
    return jsonify({
        'status': 'success',
        'message': f'Demo file {demo_file} created successfully',
        'filename': demo_file
    })

if __name__ == '__main__':
    import os
    port = int(os.environ.get('PORT', 5050))
    debug = os.environ.get('DEBUG', 'False').lower() == 'true'
    app.run(host='0.0.0.0', port=port, debug=debug)
