#pragma once

#include "Patient.h"
#include "Hospital.h"
#include "Organizer.h"
#include "Car.h"
#include "CancellationRequest.h"
#include "priQueue.h"
#include "LinkedQueue.h"
#include "CancelPriQueue.h"
#include <iostream>
using namespace std;
class UI {
public:
    void printHospital(int hospitalID, CancelQueue<Patient*>& npQueue, LinkedQueue<Patient*>& spQueue,
        priQueue<Patient*>& epQueue, LinkedQueue<Car*>& normalCars, LinkedQueue<Car*>& specialCars) {
        cout << "========== HOSPITAL #" << hospitalID << " data ===========" << endl;
        cout << epQueue.getCount() << " ";
        cout << "EP requests: ";
        epQueue.print();
        cout << endl;
        cout << spQueue.getCount() << " ";
        cout << "SP requests: ";
        spQueue.print();
        cout << endl;
        cout << npQueue.getCount() << " ";
        cout << "NP requests: ";
        npQueue.print();
        cout << endl;
        cout << "Free Cars: " << specialCars.getCount() << " " << "SCars," << " " << normalCars.getCount() << " " << "NCars" << endl;
        cout << "==================== HOSPITAL #" << hospitalID << " data end ====================" << endl;
    }
    void printSystem(CancelPriQueue<Car*>& outCars, priQueue<Car*>& backCars, LinkedQueue<Patient*>& finishlist, LinkedQueue<CancellationRequest*>& cancellationlist, LinkedQueue<Car*>& listOfcheckupcars) {
        cout << "--------------------------------" << endl;
        cout << outCars.getCount() << " ==> Out cars:";
        if (outCars.getCount() > 0) {
            CancelPriQueue<Car*> tempQueue;
            bool first = true;
            while (!outCars.isEmpty()) {
                Car* car = nullptr;
                int x = 0;
                outCars.dequeue(car, x);
                if (!first) {
                    cout << ", ";
                }
                first = false;
                cout << car->getCarID() << "_"
                    << "H" << car->getAssignedPatient()->getHospitalID() << "_"
                    << "P" << car->getAssignedPatient()->getID();
                tempQueue.enqueue(car, x);
            }
            while (!tempQueue.isEmpty()) {
                Car* car = nullptr;
                int x = 0;
                tempQueue.dequeue(car, x);
                outCars.enqueue(car, x);
            }
        }
        cout << endl;
        cout << backCars.getCount() << " <== Back cars:";
        if (backCars.getCount() > 0) {
            priQueue<Car*> tempQueue;
            bool first = true;
            while (!backCars.isEmpty()) {
                Car* car = nullptr;
                int x = 0;
                backCars.dequeue(car, x);
                if (!first) {
                    cout << ", ";
                }
                first = false;
                cout << car->getCarID() << "_"
                    << "H" << car->getAssignedPatient()->getHospitalID() << "_"
                    << "P" << car->getAssignedPatient()->getID();
                tempQueue.enqueue(car, x);
            }
            while (!tempQueue.isEmpty()) {
                Car* car = nullptr;
                int x = 0;
                tempQueue.dequeue(car, x);
                backCars.enqueue(car, x);
            }
        }
        cout << endl;
        cout << listOfcheckupcars.getCount() << "==>> Number of Checkup cars" << endl;
        if (listOfcheckupcars.getCount() > 0) {
            LinkedQueue<Car*> tempQueue;
            bool first = true;
            while (!listOfcheckupcars.isEmpty()) {
                Car* car = nullptr;
                listOfcheckupcars.dequeue(car);
                if (!first) {
                    cout << ", ";
                }
                first = false;
                cout << car->getCarID() << "_"
                    << "H" << car->getAssignedPatient()->getHospitalID() << "_"
                    << "P" << car->getAssignedPatient()->getID();
                tempQueue.enqueue(car);
            }
            while (!tempQueue.isEmpty()) {
                Car* car = nullptr;
                int x = 0;
                tempQueue.dequeue(car);
                listOfcheckupcars.enqueue(car);
            }
        }
        cout << "--------------------------------" << endl;
        cout << finishlist.getCount() << " Finished Patients: ";
        finishlist.print();
        cout << cancellationlist.getCount() << " Cancelled Patients: ";
        cancellationlist.print();
    }
};