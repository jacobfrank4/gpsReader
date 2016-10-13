/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: dcgps.cpp - An application that will communicate with gps satelites
-- to display location information to the user
--
-- PROGRAM: GPSLocator
--
-- FUNCTIONS:
-- void readGPS (gpsmm)
--
-- DATE: October 12, 2016
--
-- REVISIONS: (Programmer: Date: Description)
--
-- DESIGNER: Jacob Frank & Justen DePourcq
--
-- PROGRAMMER: Jacob Frank
--
-- NOTES:
-- The program will open, start, and monitor a gpsd stream.  As it reads the data coming in the satelites
-- it displays location data to the user via the command line interface.

-- When the program is initiated, it will automatically begin monitoring for GPS data.
--
-- The application will continue to run until it is exited by the user.
----------------------------------------------------------------------------------------------------------------------*/
#include <iostream>
#include <libgpsmm.h>
#include <gps.h>
#include <stdio.h>
//#include "gps-utils.cpp"
using namespace std;
void readGPS();

int main() {
    gpsmm gps_struct("localhost", DEFAULT_GPSD_PORT);

    cout << "Before if statement" << endl;

    if(gps_struct.stream(WATCH_ENABLE|WATCH_JSON) == NULL) {
        cerr << "No GPSD Running. \n";
        return 1;
    }
    cout << "After if statement" << endl;

    readGPS();
}
