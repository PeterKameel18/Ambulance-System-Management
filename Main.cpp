#include <iostream>
#include "Organizer.h"
#include <Windows.h>

void clear()
{
    system("CLS"); //clears the console 
}

int ReadMode()  // reads the required mode 1-> interactive 2-> silent 
{
    int mode;
    cout << "1. Interactive Mode" << endl << "2. Silent Mode" << endl << "Please choose a mode: ";
    cin >> mode;  // takes the input
    while (mode != 1 && mode != 2 )  // validates input is only 1, 2 
    {
        clear();
        cout << endl;
        cout << "Invalid Entry!!" << endl << "1. Interactive Mode" << endl << "2. Silent Mode" << endl << "Please choose a mode: ";
        cin >> mode;
    }
    return mode;
}


int main() {
    Organizer organizer;

    string filename = "input.txt"; 
    organizer.fileLoading(filename);
    
    int currentTimestep = 1;
    int mode = ReadMode();
    while (true) {
        organizer.simulateTimestep(currentTimestep);
        if (mode == 1)
        {
            cout << "Current Timestep:  " << currentTimestep << endl;
            organizer.print();
            cout << "please press enter to continue." << endl;
            getchar();	// Waits for user to press "Enter" 
        }
        if (organizer.allRequestsHandled()) {
            cout << "Done and output file created" << endl;
            organizer.GenerateOutputFile(currentTimestep);
            break; 
        }

        currentTimestep++;
    }
   
    return 0;
}
