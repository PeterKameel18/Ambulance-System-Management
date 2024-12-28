#pragma once

#include <iostream>
#include "LinkedQueue.h"  
#include "priQueue.h"
using namespace std;
class Patient {
public:
    enum status {
        Waiting, Picked, Finished, Cancelled
    };
    string patientType;
    int requestTime;
    int pickupTime;
    int finishTime;
    int waitingTime;
    int assignmentTime;
    int patientID;
    int hospitalID;
    int distance;
    int severity;
    bool isBeingHandled;
    status patientStatus;
    Patient(const string& pt = "", int timestep = 0, int pid = 0, int hid = 0, int dist = 0, int sev = -1)
        : patientType(pt), requestTime(timestep), patientID(pid), hospitalID(hid), distance(dist), severity(sev) {
        if (patientType != "EP") {
            severity = -1;
        }
        isBeingHandled = 0;
    }
    int getID() const {
        return patientID;
    }
    int getHospitalID() {
        return hospitalID;
    }
    int getDistance() {
        return distance;
    }
    string getType() { return patientType; }
    int getSev() { return severity; }
    friend ostream& operator<<(ostream& os, const Patient& patient) {
        os << patient.getID();
        return os;
    }
    int getReq() { return requestTime; }
    void setFinish(int f) { finishTime = f; }
    int getFinish() { return finishTime; }
    void setPickup(int p) { pickupTime = p; }
    int getPickup() { return pickupTime; }
    void setWait(int w) { waitingTime = w; }
    int getWait() {
        waitingTime = pickupTime - requestTime;
        return waitingTime;
    }
    void setAssign(int a) { assignmentTime = a; }
    int getAssign() { return assignmentTime; }
    void setHandling(bool h) {
        isBeingHandled = h;
    }
    bool getHandling() {
        return isBeingHandled;
    }
    void setPatientStatus(status s) { patientStatus = s; }
    bool isFinished() {
        return(patientStatus == Patient::Finished);
    }
};