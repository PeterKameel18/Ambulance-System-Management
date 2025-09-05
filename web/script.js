class AmbulanceSystem {
    constructor() {
        this.apiBaseUrl = 'http://localhost:5050/api';
        this.isRunning = false;
        this.isPaused = false;
        this.currentTimestep = 0;
        this.simulationData = null;
        this.pollingInterval = null;
        this.currentFileName = null;
        
        this.initializeElements();
        this.bindEvents();
        this.loadInitialData();
        this.showWelcomeMessage();
    }

    initializeElements() {
        console.log('Initializing elements...');
        
        // Section elements
        this.uploadSection = document.getElementById('uploadSection');
        this.simulationSection = document.getElementById('simulationSection');
        this.dashboardSection = document.getElementById('dashboardSection');
        
        // Upload elements
        this.fileInput = document.getElementById('fileInput');
        this.fileUploadArea = document.getElementById('fileUploadArea');
        this.fileInfo = document.getElementById('fileInfo');
        this.fileName = document.getElementById('fileName');
        this.uploadBtn = document.getElementById('uploadBtn');
        
        // Simulation elements
        this.startBtn = document.getElementById('startBtn');
        this.pauseBtn = document.getElementById('pauseBtn');
        this.resetBtn = document.getElementById('resetBtn');
        this.speedSlider = document.getElementById('speedSlider');
        this.speedValue = document.getElementById('speedValue');
        this.fileName = document.getElementById('fileName');
        
        // Display elements
        this.timestepDisplay = document.getElementById('timestep');
        this.statusDot = document.getElementById('statusDot');
        this.statusText = document.getElementById('statusText');
        
        // Metric elements
        this.totalAmbulances = document.getElementById('totalAmbulances');
        this.totalPatients = document.getElementById('totalPatients');
        this.avgWaitTime = document.getElementById('avgWaitTime');
        this.utilization = document.getElementById('utilization');
        
        // Table elements
        this.hospitalsGrid = document.getElementById('hospitalsGrid');
        this.ambulancesTableBody = document.getElementById('ambulancesTableBody');
        this.patientsTableBody = document.getElementById('patientsTableBody');
        this.mapGrid = document.getElementById('mapGrid');
        
        // Modal elements
        this.activityModal = document.getElementById('activityModal');
        this.activityLog = document.getElementById('activityLog');
        
        console.log('Elements initialized:', {
            uploadSection: !!this.uploadSection,
            fileInput: !!this.fileInput,
            uploadBtn: !!this.uploadBtn,
            currentFile: !!this.currentFileName
        });
    }

    bindEvents() {
        // File upload
        this.fileInput.addEventListener('change', (e) => this.handleFileSelect(e));
        this.fileUploadArea.addEventListener('click', () => this.fileInput.click());
        this.uploadBtn.addEventListener('click', () => {
            console.log('=== UPLOAD BUTTON CLICKED ===');
            console.log('File input files:', this.fileInput.files);
            console.log('File input files length:', this.fileInput.files.length);
            this.uploadFile();
        });
        
        // Simulation controls
        this.startBtn.addEventListener('click', () => this.startSimulation());
        this.pauseBtn.addEventListener('click', () => this.pauseSimulation());
        this.resetBtn.addEventListener('click', () => this.resetSimulation());
        
        // Speed control
        this.speedSlider.addEventListener('input', (e) => {
            this.speedValue.textContent = e.target.value + 'x';
        });
        
        // Modal close
        document.addEventListener('click', (e) => {
            if (e.target === this.activityModal) {
                this.closeModal();
            }
        });
    }

    showWelcomeMessage() {
        this.addLogEntry('🚑 Welcome to the Ambulance Management System!');
        this.addLogEntry('📋 This system simulates emergency medical services operations');
        this.addLogEntry('📁 Please upload an input file or use the demo file to begin');
    }

    async loadInitialData() {
        try {
            await this.fetchSimulationData();
            this.updateDisplay();
        } catch (error) {
            console.error('Error loading initial data:', error);
        }
    }

    async fetchSimulationData() {
        try {
            const response = await fetch(`${this.apiBaseUrl}/simulation/data`);
            const data = await response.json();
            this.simulationData = data;
            this.currentTimestep = data.current_timestep || 0;
        } catch (error) {
            console.error('Error fetching simulation data:', error);
            throw error;
        }
    }

    handleFileSelect(event) {
        console.log('=== FILE SELECT EVENT ===');
        console.log('Event:', event);
        console.log('Target:', event.target);
        console.log('Files:', event.target.files);
        console.log('Files length:', event.target.files.length);
        
        const file = event.target.files[0];
        console.log('Selected file:', file);
        
        if (file) {
            console.log('File details:', {
                name: file.name,
                type: file.type,
                size: file.size
            });
            
            this.fileName.textContent = file.name;
            this.fileInfo.style.display = 'flex';
            this.fileUploadArea.style.display = 'none';
            this.uploadBtn.disabled = false;
            this.addLogEntry(`📁 Selected file: ${file.name}`);
            console.log('File selection UI updated');
        } else {
            console.log('No file selected');
        }
        console.log('=== FILE SELECT END ===');
    }

    removeFile() {
        this.fileInput.value = '';
        this.fileInfo.style.display = 'none';
        this.fileUploadArea.style.display = 'block';
        this.uploadBtn.disabled = true;
        this.addLogEntry('🗑️ File removed');
    }

    async uploadFile() {
        const file = this.fileInput.files[0];
        if (!file) {
            this.showNotification('Please select a file first', 'error');
            return;
        }
        
        console.log('=== UPLOAD START ===');
        console.log('File object:', file);
        console.log('File name:', file.name);
        console.log('File type:', file.type);
        console.log('File size:', file.size);
        
        const formData = new FormData();
        formData.append('file', file);
        console.log('FormData created, file appended');
        
        try {
            this.uploadBtn.disabled = true;
            this.uploadBtn.innerHTML = '<i class="fas fa-spinner fa-spin"></i> Uploading...';
            console.log('Upload button disabled and spinner shown');
            
            console.log('Making API call to:', `${this.apiBaseUrl}/upload-input`);
            
            const response = await fetch(`${this.apiBaseUrl}/upload-input`, {
                method: 'POST',
                body: formData
            });
            
            console.log('Upload response received');
            console.log('Response status:', response.status);
            console.log('Response ok:', response.ok);
            
            if (!response.ok) {
                const errorText = await response.text();
                console.error('Response error text:', errorText);
                throw new Error(`HTTP error! status: ${response.status} - ${errorText}`);
            }
            
            const result = await response.json();
            console.log('Upload result parsed:', result);
            
            if (result.status === 'success') {
                console.log('Upload successful, updating UI...');
                this.currentFileName = file.name;
                this.fileName.textContent = file.name;
                console.log('File name updated in UI');
                this.showNotification(`✅ File ${file.name} uploaded successfully!`, 'success');
                this.addLogEntry(`✅ File ${file.name} uploaded successfully`);
                this.showSimulationSection();
                console.log('Simulation section shown');
            } else {
                console.error('Upload failed with status:', result.status);
                this.showNotification(`❌ Error: ${result.message}`, 'error');
                this.addLogEntry(`❌ Upload failed: ${result.message}`);
            }
        } catch (error) {
            console.error('=== UPLOAD ERROR ===');
            console.error('Error type:', error.constructor.name);
            console.error('Error message:', error.message);
            console.error('Error stack:', error.stack);
            this.showNotification(`❌ Error uploading file: ${error.message}`, 'error');
            this.addLogEntry(`❌ Upload error: ${error.message}`);
        } finally {
            console.log('Upload process finished, resetting button');
            this.uploadBtn.disabled = false;
            this.uploadBtn.innerHTML = '<i class="fas fa-upload"></i> Upload & Continue';
            console.log('=== UPLOAD END ===');
        }
    }

    async useDemoFile() {
        try {
            console.log('Using demo file...');
            this.addLogEntry('🎮 Creating demo file for simulation');
            
            // Call the demo file API
            const response = await fetch(`${this.apiBaseUrl}/demo-file`, {
                method: 'POST'
            });
            
            const result = await response.json();
            console.log('Demo file response:', result);
            
            if (result.status === 'success') {
                this.currentFileName = result.filename;
                this.fileName.textContent = result.filename;
                this.showSimulationSection();
                this.showNotification('🎮 Demo file created successfully! You can now start the simulation.', 'info');
                this.addLogEntry(`✅ Demo file ${result.filename} created successfully`);
                console.log('Demo file setup complete');
            } else {
                throw new Error(result.message);
            }
        } catch (error) {
            console.error('Error using demo file:', error);
            this.showNotification(`❌ Error creating demo file: ${error.message}`, 'error');
            this.addLogEntry(`❌ Demo file error: ${error.message}`);
        }
    }

    showSimulationSection() {
        this.uploadSection.style.display = 'none';
        this.simulationSection.style.display = 'block';
        this.dashboardSection.style.display = 'block';
        this.addLogEntry('🎯 Ready to start simulation!');
    }

    changeFile() {
        this.uploadSection.style.display = 'block';
        this.simulationSection.style.display = 'none';
        this.dashboardSection.style.display = 'none';
        this.addLogEntry('📁 Changing input file...');
    }

    async startSimulation() {
        try {
            const inputFile = this.currentFileName || 'demo_input.txt';
            const response = await fetch(`${this.apiBaseUrl}/simulation/start`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ 
                    input_file: inputFile,
                    mode: 'silent' 
                })
            });
            
            const result = await response.json();
            
            if (result.status === 'success') {
                this.isRunning = true;
                this.isPaused = false;
                this.startBtn.disabled = true;
                this.pauseBtn.disabled = false;
                this.updateStatus('Running');
                this.addLogEntry('🚀 Simulation started successfully!');
                this.startPolling();
                this.showNotification('🚀 Simulation started! Watch the real-time updates below.', 'success');
            } else {
                this.showNotification(`❌ Error: ${result.message}`, 'error');
            }
        } catch (error) {
            console.error('Error starting simulation:', error);
            this.showNotification('❌ Error starting simulation', 'error');
        }
    }

    async pauseSimulation() {
        try {
            const response = await fetch(`${this.apiBaseUrl}/simulation/pause`, {
                method: 'POST'
            });
            
            const result = await response.json();
            
            if (result.status === 'success') {
                this.isPaused = !this.isPaused;
                this.pauseBtn.innerHTML = this.isPaused ? 
                    '<i class="fas fa-play"></i> Resume' : 
                    '<i class="fas fa-pause"></i> Pause';
                this.updateStatus(this.isPaused ? 'Paused' : 'Running');
                this.addLogEntry(`⏸️ Simulation ${this.isPaused ? 'paused' : 'resumed'}`);
                this.showNotification(
                    this.isPaused ? '⏸️ Simulation paused' : '▶️ Simulation resumed', 
                    'info'
                );
            }
        } catch (error) {
            console.error('Error pausing simulation:', error);
        }
    }

    async resetSimulation() {
        try {
            const response = await fetch(`${this.apiBaseUrl}/simulation/reset`, {
                method: 'POST'
            });
            
            const result = await response.json();
            
            if (result.status === 'success') {
                this.isRunning = false;
                this.isPaused = false;
                this.currentTimestep = 0;
                this.startBtn.disabled = false;
                this.pauseBtn.disabled = true;
                this.pauseBtn.innerHTML = '<i class="fas fa-pause"></i> Pause';
                this.updateStatus('Ready');
                this.stopPolling();
                await this.fetchSimulationData();
                this.updateDisplay();
                this.addLogEntry('🔄 Simulation reset');
                this.showNotification('🔄 Simulation reset successfully!', 'info');
            }
        } catch (error) {
            console.error('Error resetting simulation:', error);
        }
    }

    startPolling() {
        if (this.pollingInterval) {
            clearInterval(this.pollingInterval);
        }
        
        this.pollingInterval = setInterval(async () => {
            if (this.isRunning && !this.isPaused) {
                await this.fetchSimulationData();
                this.updateDisplay();
            }
        }, 1000); // Poll every second
    }

    stopPolling() {
        if (this.pollingInterval) {
            clearInterval(this.pollingInterval);
            this.pollingInterval = null;
        }
    }

    updateDisplay() {
        if (!this.simulationData) return;
        
        this.updateTimestep();
        this.updateMetrics();
        this.renderHospitals();
        this.renderAmbulances();
        this.renderPatients();
        this.updateFleetMap();
    }

    updateTimestep() {
        this.timestepDisplay.textContent = this.currentTimestep;
    }

    updateStatus(status) {
        this.statusText.textContent = status;
        this.statusDot.className = 'status-dot';
        
        if (status === 'Running') {
            this.statusDot.classList.add('success');
        } else if (status === 'Paused') {
            this.statusDot.classList.add('warning');
        } else if (status === 'Ready') {
            this.statusDot.classList.add('success');
        }
    }

    updateMetrics() {
        if (!this.simulationData || !this.simulationData.statistics) return;
        
        const stats = this.simulationData.statistics;
        this.totalAmbulances.textContent = stats.total_cars || 0;
        this.totalPatients.textContent = stats.total_patients || 0;
        this.avgWaitTime.textContent = stats.avg_wait_time || 0;
        this.utilization.textContent = `${stats.utilization || 0}%`;
    }

    renderHospitals() {
        if (!this.simulationData || !this.simulationData.hospitals) return;
        
        this.hospitalsGrid.innerHTML = '';
        
        this.simulationData.hospitals.forEach(hospital => {
            const hospitalCard = document.createElement('div');
            hospitalCard.className = 'hospital-card';
            
            // Calculate total patients in queues
            const totalPatients = hospital.ep_queue.length + hospital.sp_queue.length + hospital.np_queue.length;
            
            hospitalCard.innerHTML = `
                <h3>${hospital.name}</h3>
                <div class="hospital-stats">
                    <div class="stat-item">
                        <div class="stat-value">${hospital.special_cars}</div>
                        <div class="stat-label">Special Cars</div>
                    </div>
                    <div class="stat-item">
                        <div class="stat-value">${hospital.normal_cars}</div>
                        <div class="stat-label">Normal Cars</div>
                    </div>
                    <div class="stat-item">
                        <div class="stat-value">${hospital.ep_queue.length}</div>
                        <div class="stat-label">Emergency Patients</div>
                    </div>
                    <div class="stat-item">
                        <div class="stat-value">${hospital.sp_queue.length + hospital.np_queue.length}</div>
                        <div class="stat-label">Other Patients</div>
                    </div>
                </div>
                <div class="hospital-status">
                    <div class="status-indicator">
                        <span class="status-dot ${totalPatients > 5 ? 'danger' : totalPatients > 2 ? 'warning' : 'success'}"></span>
                        <span>${totalPatients > 5 ? 'High Load' : totalPatients > 2 ? 'Medium Load' : 'Low Load'}</span>
                    </div>
                </div>
            `;
            
            this.hospitalsGrid.appendChild(hospitalCard);
        });
    }

    renderAmbulances() {
        if (!this.simulationData || !this.simulationData.ambulances) return;
        
        this.ambulancesTableBody.innerHTML = '';
        
        this.simulationData.ambulances.forEach(ambulance => {
            const row = document.createElement('tr');
            const statusClass = ambulance.status.toLowerCase();
            const assignedTo = ambulance.assigned_to ? `Patient #${ambulance.assigned_to}` : '-';
            
            row.innerHTML = `
                <td><strong>AMB-${ambulance.id.toString().padStart(3, '0')}</strong></td>
                <td><span class="ambulance-type ${ambulance.type.toLowerCase()}">${ambulance.type}</span></td>
                <td><span class="status-badge ${statusClass}">${ambulance.status}</span></td>
                <td>${ambulance.location}</td>
                <td>${assignedTo}</td>
                <td>${new Date().toLocaleTimeString()}</td>
                <td>
                    <button class="btn btn-outline btn-sm" onclick="ambulanceSystem.trackAmbulance(${ambulance.id})" title="Track this ambulance">
                        <i class="fas fa-eye"></i>
                    </button>
                </td>
            `;
            
            this.ambulancesTableBody.appendChild(row);
        });
    }

    renderPatients() {
        if (!this.simulationData || !this.simulationData.patients) return;
        
        this.patientsTableBody.innerHTML = '';
        
        // Show only recent patients (last 20)
        const recentPatients = this.simulationData.patients.slice(-20);
        
        recentPatients.forEach(patient => {
            const row = document.createElement('tr');
            const priorityClass = patient.type.toLowerCase();
            const hospital = this.simulationData.hospitals.find(h => h.id === patient.hospital_id);
            const hospitalName = hospital ? hospital.name : 'Unknown';
            const waitTime = this.currentTimestep - patient.timestep;
            
            row.innerHTML = `
                <td><strong>#${patient.id}</strong></td>
                <td><span class="status-badge ${priorityClass}">${patient.type}</span></td>
                <td>${patient.type === 'EP' ? '🔴 High' : patient.type === 'SP' ? '🟡 Medium' : '🟢 Low'}</td>
                <td>${patient.distance}m</td>
                <td>${hospitalName}</td>
                <td>${waitTime} min</td>
                <td>${waitTime > 10 ? '🔴 Long Wait' : waitTime > 5 ? '🟡 Waiting' : '🟢 Recent'}</td>
            `;
            
            this.patientsTableBody.appendChild(row);
        });
    }

    updateFleetMap() {
        if (!this.simulationData || !this.simulationData.hospitals) return;
        
        // Clear existing markers
        this.mapGrid.innerHTML = '';
        
        // Add hospital markers
        this.simulationData.hospitals.forEach((hospital, index) => {
            const hospitalMarker = document.createElement('div');
            hospitalMarker.className = 'hospital-marker';
            hospitalMarker.style.gridColumn = (index % 2) + 1;
            hospitalMarker.style.gridRow = Math.floor(index / 2) + 1;
            
            hospitalMarker.innerHTML = `
                <i class="fas fa-hospital"></i>
                <span>${hospital.name}</span>
            `;
            
            this.mapGrid.appendChild(hospitalMarker);
        });
        
        // Add ambulance markers
        this.simulationData.ambulances.forEach(ambulance => {
            const ambulanceMarker = document.createElement('div');
            ambulanceMarker.className = `ambulance-marker ${ambulance.status.toLowerCase()}`;
            
            // Position near hospital
            const hospital = this.simulationData.hospitals.find(h => h.id === ambulance.hospital_id);
            if (hospital) {
                const hospitalIndex = this.simulationData.hospitals.indexOf(hospital);
                const baseX = (hospitalIndex % 2) + 1;
                const baseY = Math.floor(hospitalIndex / 2) + 1;
                
                // Add random offset
                const offsetX = (Math.random() - 0.5) * 0.8;
                const offsetY = (Math.random() - 0.5) * 0.8;
                
                ambulanceMarker.style.gridColumn = baseX + offsetX;
                ambulanceMarker.style.gridRow = baseY + offsetY;
            }
            
            ambulanceMarker.innerHTML = `
                <i class="fas fa-ambulance"></i>
                <span>AMB-${ambulance.id.toString().padStart(3, '0')}</span>
                <div class="ambulance-status">${ambulance.status}</div>
            `;
            
            this.mapGrid.appendChild(ambulanceMarker);
        });
    }

    trackAmbulance(ambulanceId) {
        this.addLogEntry(`👁️ Tracking Ambulance AMB-${ambulanceId.toString().padStart(3, '0')}`);
        this.showNotification(`👁️ Now tracking Ambulance AMB-${ambulanceId.toString().padStart(3, '0')}`, 'info');
    }

    addLogEntry(message) {
        const entry = document.createElement('div');
        entry.className = 'activity-entry';
        entry.innerHTML = `
            <div class="activity-time">${new Date().toLocaleTimeString()}</div>
            <div class="activity-message">${message}</div>
        `;
        
        this.activityLog.insertBefore(entry, this.activityLog.firstChild);
        
        // Keep only last 50 entries
        while (this.activityLog.children.length > 50) {
            this.activityLog.removeChild(this.activityLog.lastChild);
        }
    }

    showNotification(message, type = 'info') {
        const notification = document.createElement('div');
        notification.className = `notification notification-${type}`;
        notification.innerHTML = `
            <div class="notification-content">
                <i class="fas fa-${type === 'success' ? 'check-circle' : type === 'error' ? 'exclamation-circle' : 'info-circle'}"></i>
                <span>${message}</span>
            </div>
            <button class="notification-close" onclick="this.parentElement.remove()">
                <i class="fas fa-times"></i>
            </button>
        `;
        
        document.body.appendChild(notification);
        
        setTimeout(() => {
            if (notification.parentElement) {
                notification.remove();
            }
        }, 4000);
    }

    showActivityLog() {
        this.activityModal.style.display = 'block';
    }

    closeModal() {
        this.activityModal.style.display = 'none';
    }
}

// Global functions for onclick handlers
function closeModal() {
    if (window.ambulanceSystem) {
        window.ambulanceSystem.closeModal();
    }
}

function showActivityLog() {
    if (window.ambulanceSystem) {
        window.ambulanceSystem.showActivityLog();
    }
}

function changeFile() {
    if (window.ambulanceSystem) {
        window.ambulanceSystem.changeFile();
    }
}

function removeFile() {
    if (window.ambulanceSystem) {
        window.ambulanceSystem.removeFile();
    }
}

function useDemoFile() {
    if (window.ambulanceSystem) {
        window.ambulanceSystem.useDemoFile();
    }
}

// Initialize the application
let ambulanceSystem;
document.addEventListener('DOMContentLoaded', () => {
    ambulanceSystem = new AmbulanceSystem();
    window.ambulanceSystem = ambulanceSystem;
});