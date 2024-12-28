#pragma once
#include <iostream>
using namespace std;
class CancellationRequest {
private:
    int timestep;
    int patientID;
    bool processed;
    int hospitalId;

public:
    CancellationRequest(int ts = 0, int pid = 0, int hid = 0)
        : timestep(ts), patientID(pid), processed(false), hospitalId(hid) {}

    int getID() const { return patientID; }
    int getTime() const { return timestep; }

    int getHospitalID() const {
        return hospitalId;
    }
    int getTimestep() {
        return timestep;
    }
    int getPatientID() {
        return patientID;
    }
    friend ostream& operator<<(ostream& os, const CancellationRequest& cr) {
        os << "P" << cr.getID() << "_H" << cr.getHospitalID();
        return os;
    }
};