#pragma once
#include <iostream>
#include <fstream>
#include <climits>
#include "Hospital.h"
#include "Car.h"
#include "Patient.h"
#include "CancellationRequest.h"
#include "CancelQueue.h"
#include "CancelPriQueue.h"
#include "UI.h"

using namespace std;

const int MAX_HOSPITALS = 100;
class Organizer {
private:
    int numHospitals;
    int specialCarSpeed, normalCarSpeed;
    int distanceMatrix[MAX_HOSPITALS][MAX_HOSPITALS];

    Hospital hospitals[MAX_HOSPITALS];
    LinkedQueue<Patient*> patientsQueue;
    LinkedQueue<CancellationRequest*> cancellationRequestsQueue;
    CancelPriQueue<Car*> outCars;
    priQueue<Car*> backCars;
    LinkedQueue<Patient*> finishedQueue;
    int numRequests = 0;
    int numCancellations = 0;
    UI ui;
    double OutCarFailureProb;
    LinkedQueue<Car*> checkupCars;

public:

    CancelPriQueue<Car*>& getOutCarsQueue() { return outCars; }
    priQueue<Car*>& getBackCarsQueue() { return backCars; }
    CancelQueue<Patient*>& getNormalPatientsQueue(int hospitalIndex) { return hospitals[hospitalIndex].getNormalPatientsQueue(); }
    LinkedQueue<Patient*>& getSpecialPatientsQueue(int hospitalIndex) { return hospitals[hospitalIndex].getSpecialPatientsQueue(); }
    priQueue<Patient*>& getEmergencyPatientsQueue(int hospitalIndex) { return hospitals[hospitalIndex].getEmergencyPatientsQueue(); }
    LinkedQueue<Car*>& getNormalCarsQueue(int hospitalIndex) { return hospitals[hospitalIndex].getFreeNormalCars(); }
    LinkedQueue<Car*>& getSpecialCarsQueue(int hospitalIndex) { return hospitals[hospitalIndex].getFreeSpecialCars(); }
    LinkedQueue<Car*>& getCheckUpCarsQueue(int hospitalIndex) { return hospitals[hospitalIndex].getFreeSpecialCars(); }
    LinkedQueue<Patient*> getPatientsQueue() const { return patientsQueue; }
    LinkedQueue<Patient*>& getFinishList() { return finishedQueue; }
    int getNumHospitals() { return numHospitals; }



    void fileLoading(const string& filename) {
        ifstream inputFile(filename);

        if (!inputFile) {
            cerr << "Error opening file!" << endl;
            return;
        }


        inputFile >> numHospitals;
        inputFile >> specialCarSpeed >> normalCarSpeed;
       // inputFile >> OutCarFailureProb;


        for (int i = 0; i < numHospitals; ++i) {
            hospitals[i] = Hospital();
        }


        for (int i = 0; i < numHospitals; ++i) {
            for (int j = 0; j < numHospitals; ++j) {
                inputFile >> distanceMatrix[i][j];
            }
        }


        for (int i = 0; i < numHospitals; ++i) {
            int special, normal;
            inputFile >> special >> normal;
            for (int j = 0; j < special; ++j) {
                Car* newSpecialCar = new Car(Car::Special, specialCarSpeed, hospitals[i].getHospitalID());
                hospitals[i].addCar(newSpecialCar);

            }

            for (int j = 0; j < normal; ++j) {
                Car* newNormalCar = new Car(Car::Normal, normalCarSpeed, hospitals[i].getHospitalID());
                hospitals[i].addCar(newNormalCar);
            }
        }


        inputFile >> numRequests;
        this->numRequests = numRequests;

        for (int i = 0; i < numRequests; ++i) {
            string patientType;
            int requestTimestep, patientID, hospitalID, distance, severity = -1;
            inputFile >> patientType >> requestTimestep >> patientID >> hospitalID >> distance;

            if (patientType == "EP") {
                inputFile >> severity;
            }

            Patient* newPatient = new Patient(patientType, requestTimestep, patientID, hospitalID, distance, severity);

            patientsQueue.enqueue(newPatient);

            Hospital& hospital = hospitals[hospitalID - 1];


        }

        inputFile >> numCancellations;
        this->numCancellations = numCancellations;

        for (int i = 0; i < numCancellations; ++i) {
            int timestep, patientID, hospitalID;
            inputFile >> timestep >> patientID >> hospitalID;
            CancellationRequest* cancelReq = new CancellationRequest(timestep, patientID, hospitalID);
            cancellationRequestsQueue.enqueue(cancelReq);
        }

        inputFile.close();
    }
    
    void simulateTimestep(int currentTimestep) {

      //  AssignToHospitalWithShortestEPList(currentTimestep);
        sendRequestsToHospitals(currentTimestep);
        handleAllHospitalsRequests(currentTimestep);
        updateStatuses(currentTimestep);
        checkForCarFailures();
        checkupCarsReturn();
        handleCancellations(currentTimestep);
    }
    void handleCancellations(int currentTimestep) {
        CancellationRequest* cancelReq = nullptr;
        LinkedQueue<CancellationRequest*> tempQueue;

        while (!cancellationRequestsQueue.isEmpty()) {
            cancellationRequestsQueue.dequeue(cancelReq);

            if (cancelReq->getTimestep() <= currentTimestep) {
                int hospitalID = cancelReq->getHospitalID();
                int patientID = cancelReq->getPatientID();
                Hospital& hospital = hospitals[hospitalID - 1];

                Patient* removedPatient = nullptr;
                Car* assignedCar = nullptr;

                if (!hospital.getEmergencyPatientsQueue().isEmpty()) {
                    priQueue<Patient*>& epQueue = hospital.getEmergencyPatientsQueue();
                    Patient* tempPatient = nullptr;
                    int severity;
                    priQueue<Patient*> tempQueue;

                    while (!epQueue.isEmpty()) {
                        epQueue.dequeue(tempPatient, severity);
                        if (tempPatient->getID() == patientID) {
                            removedPatient = tempPatient;
                            break;
                        }
                        else {
                            tempQueue.enqueue(tempPatient, severity);
                        }
                    }
                    while (!tempQueue.isEmpty()) {
                        tempQueue.dequeue(tempPatient, severity);
                        epQueue.enqueue(tempPatient, severity);
                    }
                }

                if (!removedPatient && !hospital.getSpecialPatientsQueue().isEmpty()) {
                    LinkedQueue<Patient*>& spQueue = hospital.getSpecialPatientsQueue();
                    Patient* tempPatient = nullptr;
                    LinkedQueue<Patient*> tempQueue;

                    while (!spQueue.isEmpty()) {
                        spQueue.dequeue(tempPatient);
                        if (tempPatient->getID() == patientID) {
                            removedPatient = tempPatient;
                            break;
                        }
                        else {
                            tempQueue.enqueue(tempPatient);
                        }
                    }
                    while (!tempQueue.isEmpty()) {
                        tempQueue.dequeue(tempPatient);
                        spQueue.enqueue(tempPatient);
                    }
                }
                if (!removedPatient && !hospital.getNormalPatientsQueue().isEmpty()) {
                    CancelQueue<Patient*>& npQueue = hospital.getNormalPatientsQueue();
                    Patient* tempPatient = nullptr;
                    CancelQueue<Patient*> tempQueue;

                    while (!npQueue.isEmpty()) {
                        npQueue.dequeue(tempPatient);
                        if (tempPatient->getID() == patientID) {
                            removedPatient = tempPatient;
                            break;
                        }
                        else {
                            tempQueue.enqueue(tempPatient);
                        }
                    }
                    while (!tempQueue.isEmpty()) {
                        tempQueue.dequeue(tempPatient);
                        npQueue.enqueue(tempPatient);
                    }
                }
                if (removedPatient) {
                    LinkedQueue<Car*> tempCarQueue;
                    Car* car = nullptr;

                    while (!hospital.getFreeSpecialCars().isEmpty() || !hospital.getFreeNormalCars().isEmpty()) {
                        hospital.getFreeNormalCars().dequeue(car);
                        if (car->getAssignedPatient() == removedPatient) {
                            assignedCar = car;
                            car->assignPatient(nullptr);
                            backCars.enqueue(car, 0);
                        }
                        else {
                            tempCarQueue.enqueue(car);
                        }
                    }
                    while (!tempCarQueue.isEmpty()) {
                        tempCarQueue.dequeue(car);
                        hospital.getFreeNormalCars().enqueue(car);
                    }

                    delete removedPatient;
                }
            }
            else {
                tempQueue.enqueue(cancelReq);
            }
        }
        while (!tempQueue.isEmpty()) {
            tempQueue.dequeue(cancelReq);
            cancellationRequestsQueue.enqueue(cancelReq);
        }
    }


    void GenerateOutputFile(int currentTime)
    {
        ofstream OutputFile;
    
        string folderName = "OutputFiles";
        string fileName = "outputfile.txt";
        string filePath = fileName;
        LinkedQueue<Patient *>orderedqueue;

        // Open the file for writing
        OutputFile.open(filePath, ios::out);
        
        OutputFile << "FT\tPID\tQT\tWT" << endl;
       
        while (!finishedQueue.isEmpty())
        {
            int min = INT_MAX;
            Patient* least_patient = NULL;
            Patient* current_patient = NULL;
            for (int i = 0; i < finishedQueue.getCount(); i++)
            {
                finishedQueue.dequeue(current_patient);
                if (current_patient->getFinish() < min)
                {
                    if (least_patient)
                    {
                        finishedQueue.enqueue(least_patient);
                    }
                    least_patient = current_patient;
                    min = current_patient->getFinish();
                }
                else
                {
                    finishedQueue.enqueue(current_patient);
                }
            }
            orderedqueue.enqueue(least_patient);
        }
        int NP = 0, SP = 0, EP = 0;
        int sumWaitingtime = 0, avgWaitingTime = 0;
        int TotalBusyCars = 0;
        while (!orderedqueue.isEmpty())
        {
            Patient* p = NULL;
            orderedqueue.dequeue(p);
            OutputFile << p->getFinish()<<  "\t" << p->getID() << "\t" << p->getReq() << "\t" << p->getWait();
            if (p->getType() == "EP") EP++;
            if (p->getType() == "NP") NP++;
            if (p->getType() == "SP") SP++;
            sumWaitingtime += p->getWait();

            OutputFile << endl;
        }
        avgWaitingTime = sumWaitingtime / numRequests;
        OutputFile << "patients: " << numRequests << "\t" << "[NP:" << NP;
        OutputFile << " ," << "SP:" << SP << " ,EP:" << EP;
        OutputFile << "]" << endl;
        OutputFile << "Hospitals = " << numHospitals << endl;
        int totalCars = 0;
        int Scars = 0, Ncars = 0;
        Car* car;
        for (int i = 0; i < numHospitals; ++i)
        {
            totalCars += hospitals[i].getTotalOfCars();
            Scars += hospitals[i].getnumSpecialCars();
            Ncars += hospitals[i].getnumNormalCars();
            while (!(hospitals[i].getFreeNormalCars().isEmpty()))
            {
                hospitals[i].getFreeNormalCars().dequeue(car);
                TotalBusyCars += car->getBusytime();
            }
            while (!(hospitals[i].getFreeSpecialCars().isEmpty()))
            {
                hospitals[i].getFreeSpecialCars().dequeue(car);
                TotalBusyCars += car->getBusytime();
            }
        }
        OutputFile << "cars: " << totalCars << "\t";
        OutputFile << "[SCar: " << Scars << ", NCar: " << Ncars << "]" << endl;
        OutputFile << "Avg wait time = " << avgWaitingTime << endl;
        // percentage of EP //
        OutputFile << "Avg busy time = ";
        OutputFile << TotalBusyCars / totalCars << endl;
        OutputFile << "Avg utilization = " << (float(TotalBusyCars) / (totalCars * currentTime)) * 100;
        OutputFile << "%" << endl;
        OutputFile.close();
        
    

    }
    
    void handleAllHospitalsRequests(int currentTimestep) {
        for (int i = 0; i < numHospitals; ++i) {
            hospitals[i].processRequests(currentTimestep, outCars, backCars);
        }
    }
    
    void updateStatuses(int currentTimestep) {
        for (int i = 0; i < numHospitals; ++i) {
            hospitals[i].updateAssignedCars(currentTimestep, outCars, backCars);
            hospitals[i].updateLoadedCars(currentTimestep, backCars);
            hospitals[i].moveFinishedPatients(currentTimestep, finishedQueue);

        }

    }
   
    
    void sendRequestsToHospitals(int currentTimestep) {
        Patient* patient = nullptr;
        while (!patientsQueue.isEmpty() && patientsQueue.peek(patient)) {
            if (patient->getReq() <= currentTimestep) {
                patientsQueue.dequeue(patient);
                int hospitalID = patient->getHospitalID();

                if (patient->getType() == "EP")
                {
                    hospitals[hospitalID - 1].AddEmergencyPatient(patient, patient->getSev());
                }
                else if (patient->getType() == "SP")
                {
                    hospitals[hospitalID - 1].AddSpecialPatient(patient);
                }
                else if (patient->getType() == "NP")
                {
                    hospitals[hospitalID - 1].AddNormalPatient(patient);
                }
            }
            else {
                break;
            }
        }
    }
    bool allRequestsHandled() const {
        for (const Hospital& hospital : hospitals) {
            if (!hospital.areAllRequestsHandled()) {
                return false;
            }
        }

        if (finishedQueue.getCount() != numRequests) {
            return false;
        }

        return true;
    }
    /*   void sendRequestsToHospitals(int currentTimestep) {
       Patient* patient = nullptr;
       while (!patientsQueue.isEmpty() && patientsQueue.peek(patient)) {
           if (patient->getReq() <= currentTimestep) {
               patientsQueue.dequeue(patient);
               int hospitalID = patient->getHospitalID();

               if (patient->getType() == "EP")
                   hospitals[hospitalID - 1].AddEmergencyPatient(patient, patient->getSev());
               else if (patient->getType() == "SP")
                   hospitals[hospitalID - 1].AddSpecialPatient(patient);
               else if (patient->getType() == "NP")
                   hospitals[hospitalID - 1].AddNormalPatient(patient);
           }
           else {
               break;
           }
       }
   }*/
    void handleCarFailure(Car* car) {
        if (car->getAssignedPatient()) {
            Patient* patient = car->getAssignedPatient();
            int hospitalID = car->getHospitalID();
            Hospital& hospital = hospitals[hospitalID - 1];

            if (patient->getType() == "EP") {
                hospital.getEmergencyPatientsQueue().enqueuefront(patient, patient->getSev());
            }
            else if (patient->getType() == "SP") {
                hospital.getSpecialPatientsQueue().enqueuefront(patient);
            }
            else if (patient->getType() == "NP") {
                hospital.getNormalPatientsQueue().enqueuefront(patient);
            }

            car->assignPatient(nullptr);
        }

        backCars.enqueue(car, 0);

        checkupCars.enqueue(car);
    }
    void checkForCarFailures() {
        double RandomVal = static_cast<double>(rand() % 100) / 100.0;
        if (RandomVal < OutCarFailureProb) {
            // Randomly pick a car to fail
            Car* car = nullptr;
            int priority;

            if (!outCars.isEmpty()) {
                outCars.dequeue(car, priority);
                handleCarFailure(car);
            }
        }
    }
    void checkupCarsReturn() {
        LinkedQueue<Car*> tempQueue;
        Car* car = nullptr;

        while (!checkupCars.isEmpty()) {
            checkupCars.dequeue(car);

            int hospitalID = car->getHospitalID();
            if (car->getCarType() == Car::Special) {
                hospitals[hospitalID - 1].getFreeSpecialCars().enqueue(car);
            }
            else {
                hospitals[hospitalID - 1].getFreeNormalCars().enqueue(car);
            }
        }
    }
    void AssignToHospitalWithShortestEPList(int currentTimestep) {
        Patient* patient = nullptr;
        while (!patientsQueue.isEmpty() && patientsQueue.peek(patient)) {
            if (patient->getReq() <= currentTimestep) {
                patientsQueue.dequeue(patient);
                int shortestEPList = 1000000000;
                int bestHospitalID = -1;
                for (int i = 0; i < numHospitals; ++i) {
                    int epQueueLength = hospitals[i].getdistanceofEP(patient);
                    if (epQueueLength < shortestEPList) {
                        shortestEPList = epQueueLength;
                        bestHospitalID = i;
                    }
                    else if (epQueueLength == shortestEPList && bestHospitalID != -1) {
                        if (distanceMatrix[patient->getHospitalID() - 1][i] < distanceMatrix[patient->getHospitalID() - 1][bestHospitalID]) {
                            bestHospitalID = i;
                        }
                    }
                }

                if (bestHospitalID != -1) {
                    hospitals[bestHospitalID].AddEmergencyPatient(patient, patient->getSev());
                }
            }
            else {
                break;
            }
        }
    }
    void print() {
        for (int i = 0; i < numHospitals; ++i) {
            int hospitalID = i + 1;

            CancelQueue<Patient*>& npQueue = hospitals[i].getHandlingNPatients();
            LinkedQueue<Patient*>& spQueue = hospitals[i].getHandlingSPatients();
            priQueue<Patient*>& epQueue = hospitals[i].getHandlingEPatients();
            LinkedQueue<Car*>& normalCars = getNormalCarsQueue(i);
            LinkedQueue<Car*>& specialCars = getSpecialCarsQueue(i);


            ui.printHospital(hospitalID, npQueue, spQueue, epQueue, normalCars, specialCars);
        }

        ui.printSystem(outCars, backCars, finishedQueue, cancellationRequestsQueue, checkupCars);

    }
};
