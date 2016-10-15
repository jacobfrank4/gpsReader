//gps-utils.cpp

#include <iostream>
#include <libgpsmm.h>
#include <gps.h>
#include <stdio.h>
#include <thread>
using namespace std;
void readGPS(gpsmm gp);
void print();


void startThread(gpsmm& gps) {
    cout << "inside start thread" << endl;
    thread gpsThread(readGPS, gps);
    gpsThread.join();
}

void readGPS(gpsmm gps) {
    cout << "Before for loop" << endl;
    for (;;) {
        cout << "before GPS struct creation" << endl;
        struct gps_data_t* newdata;
        cout << "After GPS struct creation" << endl;

        cout << "Before waiting statement" << endl;
        if (!gps.waiting(50000000)) {
            cout << "inside waiting statement" << endl;
            continue;
        }
        cout << "After waiting statement" << endl;

        cout << "Before read statement" << endl;
        if ((newdata = gps.read()) == NULL) { //SEG FAULTS HERE***********
            cerr << "Read error.\n";
            return;
        } else {
            cout << "inside readGPS" << endl;
            print();
        }
        cout << "After read statement" << endl;
    }
}

void print() {
    cout << "Print statement" << endl;
}

