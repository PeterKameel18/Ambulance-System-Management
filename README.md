Here’s a detailed README file for your GitHub project:

---

# Ambulance Management System

This project implements a **centralized system** to effectively manage ambulance services across multiple hospitals. The system automates ambulance allocation, ensuring optimal utilization of resources, efficient service delivery, and timely response to patient requests.  

## Project Overview

Ambulance services play a vital role in healthcare, especially during emergencies where time is critical. Managing these services across multiple hospitals requires a robust system capable of handling allocation, scheduling, and real-time updates. This project is designed to address these challenges using advanced **data structures** and simulation logic.  

The system calculates performance metrics and generates detailed statistics to help improve the overall ambulance management process. By analyzing these metrics, stakeholders can identify bottlenecks and make data-driven decisions for system optimization.  

## Features

1. **Automated Ambulance Allocation**  
   - Assigns ambulances to patients in real-time based on availability, priority, and distance.  

2. **Queue Management**  
   - Handles patient requests in a queue and prioritizes them dynamically.  

3. **Real-Time Car States**  
   - Tracks ambulances in different states:  
     - **Free**: Available for new requests.  
     - **Assigned**: Assigned to pick up a patient.  
     - **Loaded**: Transporting a patient to a hospital.  

4. **Simulation Logic**  
   - Simulates real-world ambulance operations, including handling cancellations, delays, and reassignments.  

5. **Performance Metrics**  
   - Provides statistics such as:  
     - Average response time.  
     - Ambulance utilization rate.  
     - Number of completed and canceled requests.  

6. **Scalability**  
   - Supports multiple hospitals with independent queues while maintaining a centralized allocation system.  

## Technologies Used

- **Programming Language**: C++  
- **Data Structures**:  
  - Queues for managing patient requests.  
  - Linked lists for handling car states.  
  - Custom algorithms for dynamic allocation and simulation.  

## System Architecture

The system is designed with the following components:  

1. **Patient Management**  
   - Manages incoming requests and updates patient status during the simulation.  

2. **Hospital Management**  
   - Tracks the status of all ambulances within each hospital and coordinates allocation.  

3. **Ambulance Management**  
   - Updates the state of ambulances dynamically, ensuring real-time status tracking.  

4. **Simulation Engine**  
   - Processes timesteps to handle ambulance operations such as:  
     - Assigning ambulances.  
     - Transporting patients.  
     - Completing requests or handling cancellations.  


## Sample Input/Output  

- **Input Example**:  
  - Add a patient request with priority and location details.  
  - Update ambulance availability or patient cancellations.  

- **Output Example**:  
  - Statistics showing response time, completed requests, and ambulance utilization.  

## Future Enhancements

- **Real-Time Location Tracking**  
   Incorporate GPS tracking for real-world deployment.  
- **Dynamic Priority Updates**  
   Enhance patient request prioritization based on severity or other criteria.  
- **Machine Learning Integration**  
   Use predictive algorithms to optimize ambulance allocation further.  


