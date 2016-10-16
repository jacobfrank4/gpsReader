//gps-utils.cpp

#include <iostream>
#include <libgpsmm.h>
#include <stdio.h>
#include <thread>

using namespace std;
void readGPS(gpsmm gps);
void print();
void print_data(struct gps_data_t *gpsdata);

//Currently I bypass this thread function and just call readGPS from Main()
//If I figure out how to properly implement this thread, I will reinstate this function
void startThread(gpsmm& gpsStruct) {
    cout << "inside start thread" << endl;
    thread gpsThread(readGPS, gpsStruct);
    gpsThread.join();
}

void readGPS(gpsmm gpsStruct) {
    int timeoutCounter = 0;
//    cout << "Before for loop" << endl;

    for (;;) {
         struct gps_data_t* newdata;

//        cout << "Before waiting statement" << endl;
        if (!gpsStruct.waiting(50000000)) {
//            cout << "inside waiting statement" << endl;
            timeoutCounter++;
            if(timeoutCounter > 1000) {
//                cout << "GPS Time Out" << endl;
                break;
            }
	    continue;
       }
//        cout << "After waiting statement" << endl;

//        cout << "Before read statement" << endl;
        if ((newdata = gpsStruct.read()) == nullptr) { //SEG FAULTS HERE WHEN THREAD IS USED******
//            cerr << "Read error.\n";
            return;
        } else {
            cout << "inside readGPS" << endl;
            print_data(newdata);// Need to call actual print statement
        }
//        cout << "After read statement" << endl;
    }
}

//Once Correct print function has been implemented, delete this function
void print() {
    cout << "Print statement" << endl;
}

