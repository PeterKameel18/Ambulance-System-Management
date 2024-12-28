#pragma once
#include <iostream>
#include <string>
#include "Patient.h"
#include "LinkedQueue.h"
using namespace std;

class Car {
public:
    enum Status { READY , ASSIGNED, LOADED };
    enum Type { Special, Normal };

private:
    int carNum;
    Status carStatus;
    Patient* assignedPatient;
    static int normalCarCounter;
    static int specialCarCounter;
    Type cartype;
    int speed;
    int hospitalID;
    string carID;
    int busyTime = 0;

public:

    Car(Type type, int s,int h) {
        if (type == Normal) {
            carNum = ++normalCarCounter;
            carID = "N" + to_string(carNum);
        }
        else {
            carNum = ++specialCarCounter;
            carID = "S" + to_string(carNum);
        }
        carStatus = READY;
        assignedPatient = nullptr;
        cartype = type;
        speed = s;
        hospitalID = h;
    }

    int getBusytime()
    {
        return busyTime;
    }

    void assignPatient(Patient* p) {

        assignedPatient = p;

    }
    void setCarStatus(Status status) { carStatus = status; }
    int getHospitalID() {
        return hospitalID;
    }
    int getSpeed() {
        return speed;
    }
    void setSpeed(int s) {
        speed = s;
    }
    Type getCarType() const {
        return cartype;
    }
    Patient* getAssignedPatient() const {
        return assignedPatient;
    }
    string getCarID() const {
        return carID;
    }
    friend ostream& operator<<(ostream& os, const Car& car) {
        os << car.getCarID();
        return os;
    }
    void pickupPatient(int currentTimestep, priQueue<Car*>& backCars) {
        if (assignedPatient && assignedPatient->getPickup() <= currentTimestep) {
            this->setCarStatus(Car::LOADED);
            this->getAssignedPatient()->setPatientStatus(Patient::Picked);
            backCars.enqueue(this, assignedPatient->getDistance());
        
        }
    }
    void dropoffPatient(int currentTimestep, LinkedQueue<Car*>& freeScars, LinkedQueue<Car*>& freeNcars) {
        if (assignedPatient && assignedPatient->getFinish() <= currentTimestep) {
            this->busyTime = currentTimestep - assignedPatient->getAssign();
            this->setCarStatus(Car::READY);
           this->getAssignedPatient()->setPatientStatus(Patient::Finished);
            if (cartype == Car::Special)
                freeScars.enqueue(this);
            else if (cartype == Car::Normal) {
                freeNcars.enqueue(this);
            }
            this->assignedPatient = nullptr;
        }
    }
    
};



int Car::normalCarCounter = 0;
int Car::specialCarCounter = 0;
