//gps-utils.cpp

#include <iostream>
#include <libgpsmm.h>
#include <stdio.h>
#include <thread>

using namespace std;
void readGPS(gpsmm gps);
void print();
void print_gps_data(struct gps_data_t *gpsdata);

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: readGPS
--
-- DATE: October 16, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jacob Frank and Justen DePourq
--
-- PROGRAMMER: Jacob Frank
--
-- RETURNS: void.
--
-- NOTES:
-- function reads data from the gps and passes it to a secondary print function.
-- If function cannot read a GPS signal it will timeout after 250 attempts and exit the program.
----------------------------------------------------------------------------------------------------------------------*/
void readGPS(gpsmm gpsStruct) {
    int timeoutCounter = 0;

    for (;;) {
        struct gps_data_t* gpsData;

	//If the function cannot detect a gps signal after 50 milliseconds
	//the timout counter is incremented and GPS detection is tried again
	//Can occur a maximum of 250 times before timing out and exiting program
        if (!gpsStruct.waiting(50000000)) {
	    cout << "Timeout++" << endl;
            timeoutCounter++;

            if(timeoutCounter > 250) {
                cout<< "GPS timeout" << endl;
		break;
            }
	    continue;
        }
	
	//Ensures the GPS struct is not null before passing it to the print function.
        if ((gpsData = gpsStruct.read()) == nullptr) {
		cout << "break" << endl;
	    	break;
        } else {
	    print_gps_data(gpsData);
        }
    }
}
