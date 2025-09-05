#pragma once
#include <iostream>
#include "Car.h"
#include "Patient.h"
#include "LinkedQueue.h"
#include "CancelPriQueue.h"
#include "priQueue.h"
#include "CancelQueue.h"
using namespace std;

class Hospital {
private:
    static int hospitalCounter;
    int hospitalID;
    int numSpecialCars;
    int numNormalCars;
    LinkedQueue<Patient*> sPatients; 
    CancelQueue<Patient*> nPatients;
    priQueue<Patient*> ePatients;
    priQueue<Patient*> handlingEPatients; 
    LinkedQueue<Patient*> handlingSPatients; 
    CancelQueue<Patient*> handlingNPatients;  
    LinkedQueue<Car*> freeScars;
    LinkedQueue<Car*> freeNcars;
    LinkedQueue<Car*> CheckUpCarsH;
    int currentTimestep;
    int TotalBusyCars;

public:
    Hospital() {
        hospitalCounter++;
        hospitalID = hospitalCounter;
        numSpecialCars = 0;
        numNormalCars = 0;
        currentTimestep = 0;
    }
     priQueue<Patient*>& getHandlingEPatients()  { return handlingEPatients; }
     LinkedQueue<Patient*>& getHandlingSPatients()  { return handlingSPatients; }
     CancelQueue<Patient*>& getHandlingNPatients()  { return handlingNPatients; }
     //bool removePatientByID(int patientID, Patient*& removedPatient, Car*& assignedCar) {
    //    removedPatient = nullptr;
    //    assignedCar = nullptr;
    //    if (!ePatients.isEmpty()) {
    //        Patient* tempPatient = nullptr;
    //        int severity;
    //        priQueue<Patient*> tempQueue;

    //        while (!ePatients.isEmpty()) {
    //            ePatients.dequeue(tempPatient, severity);
    //            if (tempPatient->getID() == patientID) {
    //                removedPatient = tempPatient;
    //                break;
    //            }
    //            else {
    //                tempQueue.enqueue(tempPatient, severity);
    //            }
    //        }
    //        while (!tempQueue.isEmpty()) {
    //            tempQueue.dequeue(tempPatient, severity);
    //            ePatients.enqueue(tempPatient, severity);
    //        }
    //    }
    //    if (!removedPatient && !sPatients.isEmpty()) {
    //        LinkedQueue<Patient*> tempQueue;
    //        Patient* tempPatient = nullptr;

    //        while (!sPatients.isEmpty()) {
    //            sPatients.dequeue(tempPatient);
    //            if (tempPatient->getID() == patientID) {
    //                removedPatient = tempPatient;
    //                break;
    //            }
    //            else {
    //                tempQueue.enqueue(tempPatient);
    //            }
    //        }
    //        while (!tempQueue.isEmpty()) {
    //            tempQueue.dequeue(tempPatient);
    //            sPatients.enqueue(tempPatient);
    //        }
    //    }
    //    if (!removedPatient && !nPatients.isEmpty()) {
    //        CancelQueue<Patient*> tempQueue;
    //        Patient* tempPatient = nullptr;

    //        while (!nPatients.isEmpty()) {
    //            nPatients.dequeue(tempPatient);
    //            if (tempPatient->getID() == patientID) {
    //                removedPatient = tempPatient;
    //                break;
    //            }
    //            else {
    //                tempQueue.enqueue(tempPatient);
    //            }
    //        }
    //        while (!tempQueue.isEmpty()) {
    //            tempQueue.dequeue(tempPatient);
    //            nPatients.enqueue(tempPatient);
    //        }
    //    }

    //    if (removedPatient) {
    //        for (Car* car : handlingCars) { // handlingCars is a list of currently assigned cars 
    //            if (car->getAssignedPatient() == removedPatient) { 
    //                assignedCar = car; 
    //                car->assignPatient(nullptr); // Unassign the patient from the car 
    //                break;
    //            }
    //        }
    //    }

    //    return removedPatient != nullptr;
    //}
    //bool removePatientByID(int patientID, Patient*& removedPatient, Car*& assignedCar) {
    //    removedPatient = nullptr;
    //    assignedCar = nullptr;

    //    // Search in Emergency Patients Queue
    //    if (!ePatients.isEmpty()) {
    //        Patient* tempPatient = nullptr;
    //        int severity;
    //        priQueue<Patient*> tempQueue;

    //        while (!ePatients.isEmpty()) {
    //            ePatients.dequeue(tempPatient, severity);
    //            if (tempPatient->getID() == patientID) {
    //                removedPatient = tempPatient;
    //                break;
    //            }
    //            else {
    //                tempQueue.enqueue(tempPatient, severity);
    //            }
    //        }

    //        // Restore the queue
    //        while (!tempQueue.isEmpty()) {
    //            tempQueue.dequeue(tempPatient, severity);
    //            ePatients.enqueue(tempPatient, severity);
    //        }
    //    }

    //    // If not found, search in Special Patients Queue
    //    if (!removedPatient && !sPatients.isEmpty()) {
    //        LinkedQueue<Patient*> tempQueue;
    //        Patient* tempPatient = nullptr;

    //        while (!sPatients.isEmpty()) {
    //            sPatients.dequeue(tempPatient);
    //            if (tempPatient->getID() == patientID) {
    //                removedPatient = tempPatient;
    //                break;
    //            }
    //            else {
    //                tempQueue.enqueue(tempPatient);
    //            }
    //        }

    //        // Restore the queue
    //        while (!tempQueue.isEmpty()) {
    //            tempQueue.dequeue(tempPatient);
    //            sPatients.enqueue(tempPatient);
    //        }
    //    }

    //    // If not found, search in Normal Patients Queue
    //    if (!removedPatient && !nPatients.isEmpty()) {
    //        CancelQueue<Patient*> tempQueue;
    //        Patient* tempPatient = nullptr;

    //        while (!nPatients.isEmpty()) {
    //            nPatients.dequeue(tempPatient);
    //            if (tempPatient->getID() == patientID) {
    //                removedPatient = tempPatient;
    //                break;
    //            }
    //            else {
    //                tempQueue.enqueue(tempPatient);
    //            }
    //        }

    //        // Restore the queue
    //        while (!tempQueue.isEmpty()) {
    //            tempQueue.dequeue(tempPatient);
    //            nPatients.enqueue(tempPatient);
    //        }
    //    }

    //    // Check if a car is assigned to this patient
    //    LinkedQueue<Car*> tempCarQueue;
    //    Car* car = nullptr;
    //    
    //    while (!assignedCar->isEmpty()) {
    //        assignedCar.dequeue(car);
    //        if (car->getAssignedPatient() == removedPatient) {
    //            assignedCar = car;
    //            car->assignPatient(nullptr); // Unassign the patient
    //        }
    //        else {
    //            tempCarQueue.enqueue(car);
    //        }
    //    }

    //    // Restore the assigned cars queue
    //    while (!tempCarQueue.isEmpty()) {
    //        tempCarQueue.dequeue(car);
    //        assignedCars.enqueue(car);
    //    }

    //    return removedPatient != nullptr;
    //}
//bool removePatientByID(int patientID, Patient*& removedPatient, Car*& assignedCar) {
//    removedPatient = nullptr;
//    assignedCar = nullptr;
//
//    // Check Emergency Patients
//    if (!ePatients.isEmpty()) {
//        Patient* tempPatient = nullptr;
//        int severity;
//        priQueue<Patient*> tempQueue;
//
//        while (!ePatients.isEmpty()) {
//            ePatients.dequeue(tempPatient, severity);
//            if (tempPatient->getID() == patientID) {
//                removedPatient = tempPatient;
//                break;
//            }
//            else {
//                tempQueue.enqueue(tempPatient, severity);
//            }
//        }
//
//        // Restore remaining patients
//        while (!tempQueue.isEmpty()) {
//            tempQueue.dequeue(tempPatient, severity);
//            ePatients.enqueue(tempPatient, severity);
//        }
//    }
//
//    // Check Special Patients
//    if (!removedPatient && !sPatients.isEmpty()) {
//        LinkedQueue<Patient*> tempQueue;
//        Patient* tempPatient = nullptr;
//
//        while (!sPatients.isEmpty()) {
//            sPatients.dequeue(tempPatient);
//            if (tempPatient->getID() == patientID) {
//                removedPatient = tempPatient;
//                break;
//            }
//            else {
//                tempQueue.enqueue(tempPatient);
//            }
//        }
//
//        // Restore remaining patients
//        while (!tempQueue.isEmpty()) {
//            tempQueue.dequeue(tempPatient);
//            sPatients.enqueue(tempPatient);
//        }
//    }
//
//    // Check Normal Patients
//    if (!removedPatient && !nPatients.isEmpty()) {
//        CancelQueue<Patient*> tempQueue;
//        Patient* tempPatient = nullptr;
//
//        while (!nPatients.isEmpty()) {
//            nPatients.dequeue(tempPatient);
//            if (tempPatient->getID() == patientID) {
//                removedPatient = tempPatient;
//                break;
//            }
//            else {
//                tempQueue.enqueue(tempPatient);
//            }
//        }
//
//        // Restore remaining patients
//        while (!tempQueue.isEmpty()) {
//            tempQueue.dequeue(tempPatient);
//            nPatients.enqueue(tempPatient);
//        }
//    }
//
//    // Check assigned cars for this patient
//    if (removedPatient) {
//        assignedCar = nullptr;
//
//        LinkedQueue<Car*> tempCarQueue;
//        Car* car = nullptr;
//
//        while (!handlingCars.isEmpty()) {
//            handlingCars.dequeue(car);
//            if (car->getAssignedPatient() == removedPatient) {
//                assignedCar = car;
//                car->assignPatient(nullptr); // Clear assignment
//            }
//            else {
//                tempCarQueue.enqueue(car);
//            }
//        }
//
//        // Restore remaining cars
//        while (!tempCarQueue.isEmpty()) {
//            tempCarQueue.dequeue(car);
//            handlingCars.enqueue(car);
//        }
//    }
//
//    return removedPatient != nullptr;
//}

     int getTotalOfCars()
     {
         return numNormalCars + numSpecialCars;
     }

     int getnumNormalCars()
     {
         return numNormalCars;
     }
     int getnumSpecialCars()
     {
         return numSpecialCars;
     }
    void addCar(Car* car) {
        if (car->getCarType() == Car::Special) {
            freeScars.enqueue(car);
            numSpecialCars++;
        }
        else if (car->getCarType() == Car::Normal) {
            freeNcars.enqueue(car);
            numNormalCars++;
        }
    }
    int getHospitalID() const {
        return hospitalID;
    }
    void AddNormalPatient(Patient* p) {
        nPatients.enqueue(p);
    }
    void AddSpecialPatient(Patient* p) {
        sPatients.enqueue(p);
    }
    void AddEmergencyPatient(Patient* p, int sev) {
        ePatients.enqueue(p, sev);
    }
    CancelQueue<Patient*>& getNormalPatientsQueue() {
        return nPatients;
    }
    LinkedQueue<Patient*>& getSpecialPatientsQueue() {
        return sPatients;
    }
    priQueue<Patient*>& getEmergencyPatientsQueue() {
        return ePatients;
    }
    LinkedQueue<Car*>& getFreeNormalCars() {
        return freeNcars;
    }
    LinkedQueue<Car*>& getFreeSpecialCars() {
        return freeScars;
    }
    bool areAllRequestsHandled() const {
        return ePatients.isEmpty() &&
            sPatients.isEmpty() &&
            nPatients.isEmpty();
    }
    LinkedQueue<Car*>& getCheckUpCars() {
        return CheckUpCarsH;
    }
    int getdistanceofEP(Patient* P) {
        if (P->getType() == "EP") {
            return P->getDistance();
        }
        return -1; // Return -1 if patient is not EP type
    }
    void processRequests(int currentTimestep, CancelPriQueue<Car*>& outCars, priQueue<Car*>& backCars) {
        Patient* patient = nullptr;
        Car* car = nullptr;

        while (!ePatients.isEmpty()) {
            int severity;
            ePatients.dequeue(patient, severity);

            if (!patient->getHandling()) {
                if (!this->freeNcars.isEmpty()) {
                    this->freeNcars.dequeue(car);
                    patient->setAssign(currentTimestep);
                    assignCartoPatient(car, patient, severity, currentTimestep, outCars, backCars);
                    patient->setPickup(patient->getAssign() + (patient->getDistance() / car->getSpeed()));
                    patient->setHandling(true);
                    handlingEPatients.enqueue(patient,severity);  
                }
                else if (!this->freeScars.isEmpty()) {
                    this->freeScars.dequeue(car);
                    assignCartoPatient(car, patient, severity, currentTimestep, outCars, backCars);
                    patient->setPickup(patient->getAssign() + (patient->getDistance() / car->getSpeed()));
                    patient->setHandling(true);
                    handlingEPatients.enqueue(patient, severity);
                }
                else {
                    ePatients.enqueue(patient, severity);


                }
            }
        }

        while (!sPatients.isEmpty()) {
            sPatients.dequeue(patient);
            int severity = patient->getDistance();
            if (!patient->getHandling()) {
                if (!this->freeScars.isEmpty()) {
                    patient->setAssign(currentTimestep);
                    this->freeScars.dequeue(car);
                    assignCartoPatient(car, patient, severity, currentTimestep, outCars, backCars);
                    patient->setPickup(patient->getAssign() + (patient->getDistance() / car->getSpeed()));
                    patient->setHandling(true);
                    handlingSPatients.enqueue(patient); 
                }
                else {
                    sPatients.enqueue(patient);
                    break;
                }
            }
        }

        while (!nPatients.isEmpty()) {
            nPatients.dequeue(patient);
            patient->setAssign(currentTimestep);
            int severity = patient->getDistance();
            if (!patient->getHandling()) {
                if (!this->freeNcars.isEmpty()) {
                    this->freeNcars.dequeue(car);
                    patient->setAssign(currentTimestep);
                    assignCartoPatient(car, patient, severity, currentTimestep, outCars, backCars);
                    patient->setPickup(patient->getAssign() + (patient->getDistance() / car->getSpeed()));
                    patient->setHandling(true);
                    handlingNPatients.enqueue(patient);  
                }
                else {
                    nPatients.enqueue(patient);
                    break;
                }
            }
        }
    }
    void assignCartoPatient(Car* car, Patient* patient, int severity, int currentTimestep,CancelPriQueue<Car*>&outCars,priQueue<Car*>&backCars) {
        car->setCarStatus(Car::ASSIGNED);
        car->assignPatient(patient);
        int arrivalTime = currentTimestep + ((patient->getDistance() + car->getSpeed() - 1) / car->getSpeed());
        int returnTime = arrivalTime + ceil((double)(car->getAssignedPatient()->getDistance()) / car->getSpeed());
        patient->setPickup(arrivalTime);
        patient->setFinish(returnTime);
        outCars.enqueue(car, severity);
    
    }
    void updateAssignedCars(int currentTimestep, CancelPriQueue<Car*>& outCars, priQueue<Car*>& backCars) {
        Car* car = nullptr;
        int priority;
        CancelPriQueue<Car*> tempQueue;
        while (!outCars.isEmpty()) {
            outCars.peek(car, priority);
            if (car->getAssignedPatient()->getPickup() <= currentTimestep && car->getHospitalID() == hospitalID) {
                outCars.dequeue(car, priority);
                car->pickupPatient(currentTimestep, backCars);
            }
            else {
                outCars.dequeue(car, priority);
                tempQueue.enqueue(car, priority);
            }
        }
        while (!tempQueue.isEmpty()) {
            tempQueue.dequeue(car, priority);
            outCars.enqueue(car, priority);
        }
    }
    void updateLoadedCars(int currentTimestep, priQueue<Car*>& backCars) {
        Car* car = nullptr;
        int priority;
        priQueue<Car*>tempQueue;
        while (!backCars.isEmpty()) {
            backCars.peek(car, priority);
            if (car->getAssignedPatient()->getFinish() <= currentTimestep && car->getHospitalID()==hospitalID) {
                backCars.dequeue(car, priority);
               Patient*p= car->getAssignedPatient();
               p->setFinish(p->getPickup() + (p->getDistance() / car->getSpeed()));
               car->dropoffPatient(currentTimestep, freeScars, freeNcars);
               
            }
            else {
                backCars.dequeue(car, priority);
                tempQueue.enqueue(car, priority);
            }
        }
        while (!tempQueue.isEmpty()) {
            tempQueue.dequeue(car, priority);
            backCars.enqueue(car, priority);
        }
    }
    void moveFinishedPatients(int currentTimestep, LinkedQueue<Patient*>& finishedQueue) {
        LinkedQueue<Patient*>  tempS, tempN;
        priQueue<Patient*>tempE;
        Patient* patient = nullptr;
        int severity;
        while (!handlingEPatients.isEmpty()) {
            handlingEPatients.dequeue(patient,severity);
            if (patient->isFinished()) {
                finishedQueue.enqueue(patient);
            }
            else {
                tempE.enqueue(patient,severity);
            }
        }
        while (!tempE.isEmpty()) {
            tempE.dequeue(patient,severity);
            handlingEPatients.enqueue(patient,severity);
        }

        while (!handlingSPatients.isEmpty()) {
            handlingSPatients.dequeue(patient);
            if (patient->isFinished()) {
                finishedQueue.enqueue(patient);
            }
            else {
                tempS.enqueue(patient);
            }
        }
        while (!tempS.isEmpty()) {
            tempS.dequeue(patient);
            handlingSPatients.enqueue(patient);
        }

        while (!handlingNPatients.isEmpty()) {
            handlingNPatients.dequeue(patient);
            if (patient->isFinished()) {
                finishedQueue.enqueue(patient);
            }
            else {
                tempN.enqueue(patient);
            }
        }
        while (!tempN.isEmpty()) {
            tempN.dequeue(patient);
            handlingNPatients.enqueue(patient);
        }
    }
  
    
};

int Hospital::hospitalCounter = -100;
