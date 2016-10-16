//gps-utils.cpp

#include <iostream>
#include <libgpsmm.h>
#include <stdio.h>
#include <thread>

using namespace std;
void readGPS(gpsmm gps);
void print();
void print_data(struct gps_data_t *gpsdata);


void readGPS(gpsmm gpsStruct) {
    int timeoutCounter = 0;

    for (;;) {
        struct gps_data_t* gpsData;

        if (!gpsStruct.waiting(50000000)) {
            timeoutCounter++;

            if(timeoutCounter > 1000) {
                cout<< "GPS timeout" << endl;
		break;
            }
	    continue;
        }

        if ((gpsData = gpsStruct.read()) == nullptr) {
            return;
        } else {
            print_data(gpsData);
        }
    }
}
