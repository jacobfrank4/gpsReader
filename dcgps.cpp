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

using namespace std;
void startThread(gpsmm& gps);
void readGPS(gpsmm gps);

int main(void) {
    gpsmm gpsStruct("localhost", DEFAULT_GPSD_PORT);

    if(gpsStruct.stream(WATCH_ENABLE|WATCH_JSON) == NULL) {
        cerr << "No GPSD Running. \n";
        return 1;
    }
    //Passes the gpsmm to the read function for interpreting of the stallite gps data
    readGPS(gpsStruct);
}
