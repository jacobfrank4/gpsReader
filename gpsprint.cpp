/*------------------------------------------------------------------------------------------------------------------
 -- SOURCE FILE: gpsprint.cpp - An application that will have satellite data passed to it
 --                             and print it to the screen
 --
 -- PROGRAM: GPSLocator
 --
 -- FUNCTIONS:
 -- void time(struct gps_data_t *gpsdata);
 -- void location(struct gps_data_t *gpsdata);
 -- void information(struct gps_data_t *gpsdata);
 --
 -- DATE: October 16, 2016
 --
 -- REVISIONS:
 --
 --
 -- DESIGNERS: Jacob Frank & Justen DePourcq
 --
 -- PROGRAMMER: Justen DePourcq
 --
 -- NOTES:
 -- This program will display the information obtained from the gps satellites to
 -- the user via the command line
 --
 -- The application will continue to run until it is exited by the user.
 ----------------------------------------------------------------------------------------------------------------------*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gps.h>
#include <cmath>
using namespace std;

void time(struct gps_data_t *gpsdata);
void location(struct gps_data_t *gpsdata);
void information(struct gps_data_t *gpsdata);

/*------------------------------------------------------------------------------------------------------------------
 -- FUNCTION: print_gps_data
 --
 -- DATE: October 16, 2016
 --
 -- REVISIONS: (Date and Description)
 --
 -- DESIGNER: Jacob Frank and Justen DePourq
 --
 -- PROGRAMMER: Justen DePourcq
 --
 -- INTERFACE: void print_gps_data(struct gps_data_t *gpsdata)
 --            struct gps_data_t *gpsdata: gps struct with updated information from satellites
 --
 -- RETURNS: void.
 --
 -- NOTES:
 -- function receives in the gps struct and passes it to the other functions within this file in order to print
 -- the data from the satellites
 ----------------------------------------------------------------------------------------------------------------------*/

void print_gps_data(struct gps_data_t *gpsdata) {
    if(gpsdata->fix.mode >= 1) {
        if(gpsdata->satellites_visible == 0) {
            cout << "No satellites found" << endl;
        } else {
            time(gpsdata);
            location(gpsdata);
            information(gpsdata);
        }
    }
}


/*------------------------------------------------------------------------------------------------------------------
 -- FUNCTION: time
 --
 -- DATE: October 16, 2016
 --
 -- REVISIONS: (Date and Description)
 --
 -- DESIGNER: Jacob Frank and Justen DePourq
 --
 -- PROGRAMMER: Justen DePourcq
 --
 -- INTERFACE: void print_gps_data(struct gps_data_t *gpsdata)
 --            struct gps_data_t *gpsdata: gps struct with updated information from satellites
 --
 -- RETURNS: void.
 --
 -- NOTES:
 -- function that obtains the time from the gps struct, converts it to UTC
 -- and prints it to the command line.
 ----------------------------------------------------------------------------------------------------------------------*/

void time(struct gps_data_t *gpsdata) {
    time_t gpsTime;
    gpsTime = (time_t) gpsdata->fix.time;
    time(&gpsTime);
    struct tm *ptm;
    
    ptm = gmtime(&gpsTime);
    cout << ptm->tm_year+1900 << "-" << ptm->tm_mon+1 << "-" << ptm->tm_mday << "T" <<ptm->tm_hour << ":" <<ptm->tm_min<< ":"<< ptm->tm_sec << endl;
    
}


/*------------------------------------------------------------------------------------------------------------------
 -- FUNCTION: location
 --
 -- DATE: October 16, 2016
 --
 -- REVISIONS: (Date and Description)
 --
 -- DESIGNER: Jacob Frank and Justen DePourq
 --
 -- PROGRAMMER: Justen DePourcq
 --
 -- INTERFACE: void print_gps_data(struct gps_data_t *gpsdata)
 --            struct gps_data_t *gpsdata: gps struct with updated information from satellites
 --
 -- RETURNS: void.
 --
 -- NOTES:
 -- function obtains the latitude and longitude of the gps dongle from the staellites and prints
 -- it to the command line, if there are 3 or more useable satellites the altitude of the gps dongle
 -- is also printed to the command line.
 ----------------------------------------------------------------------------------------------------------------------*/

void location(struct gps_data_t *gpsdata) {
    
    double lat;
    double lon;
    lat = gpsdata->fix.latitude;
    lon = gpsdata->fix.longitude;
    
    if(gpsdata->fix.mode == 2) {
        if(lat < 0 && lon >= 0) {
            cout << "Latitude: " << abs(lat) << "S" << "\t" << "Longitude: " << lon << "E" << endl;
        } else if(lat < 0 && lon <0) {
            cout << "Latitude: " << abs(lat) << "S" << "\t" << "Longitude: " << abs(lon) << "W" << endl;
        } else if (lat >=0 && lon < 0) {
            cout << "Latitude: " << lat << "N" << "\t" << "Longitude: " << abs(lon) << "W" << endl;
        } else {
            cout << "Latitude: " << lat << "N" << "\t" << "Longitude: " << lon << "E" << endl;
        }
        
        cout << "Satus: 2D Fix" << endl;
        
    } else if(gpsdata->fix.mode == 3) {
        if(lat < 0 && lon >= 0) {
            cout << "Latitude: " << abs(lat) << "S" << "\t" << "Longitude: " << lon << "E" << endl;
        } else if(lat < 0 && lon <0) {
            cout << "Latitude: " << abs(lat) << "S" << "\t" << "Longitude: " << abs(lon) << "W" << endl;
        } else if (lat >=0 && lon < 0) {
            cout << "Latitude: " << lat << "N" << "\t" << "Longitude: " << abs(lon) << "W" << endl;
        } else {
            cout << "Latitude: " << lat << "N" << "\t" << "Longitude: " << lon << "E" << endl;
        }
        
        cout << "Status: 3D Fix" << "\t" << "Altitude: " << gpsdata->fix.altitude << "m" << endl;
    } else {
        cout << "Latitude: " << "NA" << "\t" << "Longitude: " << "NA" << endl;
    }
    
}


/*------------------------------------------------------------------------------------------------------------------
 -- FUNCTION: information
 --
 -- DATE: October 16, 2016
 --
 -- REVISIONS: (Date and Description)
 --
 -- DESIGNER: Jacob Frank and Justen DePourq
 --
 -- PROGRAMMER: Justen DePourcq
 --
 -- INTERFACE: void print_gps_data(struct gps_data_t *gpsdata)
 --            struct gps_data_t *gpsdata: gps struct with updated information from satellites
 --
 -- RETURNS: void.
 --
 -- NOTES:
 -- function that obtains the information of all the visible satelites including: PRN, elevation,
 -- azimuth, SNR, and wheter the satelite is used or not and prints it to the command line.
 ----------------------------------------------------------------------------------------------------------------------*/

void information(struct gps_data_t *gpsdata) {
    
    
    if(gpsdata->satellites_visible !=0) {
        for(int i = 0; i < gpsdata->satellites_visible; i++) {
            cout << "PRN: " << gpsdata->PRN[i] << "\t";
            cout << "Elevation: " << gpsdata->elevation[i] << "\t";
            cout << "Azimuth: " << gpsdata->azimuth[i] << "\t";
            cout << "SNR: " << gpsdata->ss[i] << "\t";
            if(gpsdata->used[i]) {
                cout << "Used: " << "Y" << endl;
            } else {
                cout << "Used: " << "N" << endl;
            }
        }
    }
    cout << "\n";
}
