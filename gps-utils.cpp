//gps-utils.cpp

#include "headers/gps-utils.h"

using namespace std;
void readGPS(gpsmm gps);
void print_gps_data(struct gps_data_t *gpsdata);

/*------------------------------------------------------------------------------------------------------------------
 -- FUNCTION: readGPS
 --
 -- DATE: October 16, 2016
 --
 -- REVISIONS: 
 -- Justen DePourcq, October 18th 2016:
 -- Created timeout counter and print statements, for looking for GPS
 -- and eventually timing out.
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
        if (!gpsStruct.waiting(500000)) {
            timeoutCounter++;
            
            if(timeoutCounter == 1) {
                cout << "Looking for GPS1..." << endl;
            }
            if(timeoutCounter % 40 == 0) {
                cout << "Looking for GPS2..." << endl;
            }
            
            if(timeoutCounter > 250) {
                cout << "No signal found, Timeout" << endl;
                break;
            }
            continue;
        }
        //Ensures the GPS struct is not null before passing it to the print function.
        if ((gpsData = gpsStruct.read()) == nullptr) {
            break;
        } else {
            timeoutCounter = 1;
            print_gps_data(gpsData);
        }
    }
}
