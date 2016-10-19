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
#include <ncurses.h>
#include <sstream>
#include <string>
using namespace std;

string getTime(struct gps_data_t *gpsdata);
string location(struct gps_data_t *gpsdata);
string information(struct gps_data_t *gpsdata, int satllite);
string fixMode(struct gps_data_t *gpsdata);

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
cout << "just inside print" << endl;
    if(gpsdata->fix.mode >= 1) {
       if(gpsdata->satellites_visible == 0) {
           cout << "No satellites found" << endl;
       } else if(gpsdata->fix.mode >=1) {
cout << "fix mode > 1" << endl;
            int col;
            WINDOW * win;

refresh();
            if ( (win = initscr()) == NULL ) {
                fputs("Could not initialize screen.", stderr);
                exit(EXIT_FAILURE);
            }

            col = getmaxy(win);
wborder(win, '|', '|' , '-', '-', '+','+','+','+');
//	    box(win, 0, 0);
cout << "before print time" << endl;
            //get time and print to screen
            string gpstime = getTime(gpsdata);
            mvprintw(2,2,gpstime.c_str());
cout << "before lcation" <<endl;
            //get location data and print to screen
            string gpslocation = location(gpsdata);
            mvprintw(3,2,gpslocation.c_str());
cout << "before mode" << endl;
            //get and print the fix mode
            string mode = fixMode(gpsdata);
            mvprintw(4,2,mode.c_str());

            //Draws a horizontal line
            move(5,1);
            hline('_', (col-2));
cout << "before satllite data" << endl;
            if(gpsdata->satellites_visible !=0) {
                for(int i = 0; i < gpsdata->satellites_visible; i++) {
                    //get gps data and print to screen
                    string satinfo = information(gpsdata, i);
                    mvprintw((7+i),2,satinfo.c_str());
	        }
            }
cout << "Just before refresh" << endl;
            refresh();

            getch();
//wclear(win);

            endwin();
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

string getTime(struct gps_data_t *gpsdata) {
    stringstream utcTime;

    time_t gpsTime;
    gpsTime = (time_t) gpsdata->fix.time;
    time(&gpsTime);
    struct tm *ptm;
    
    ptm = gmtime(&gpsTime);
    utcTime << ptm->tm_year+1900 << "-" << ptm->tm_mon+1 << "-" << ptm->tm_mday << "T" <<ptm->tm_hour << ":" <<ptm->tm_min<< ":"<< ptm->tm_sec;
    
    return utcTime.str();
}


string fixMode(struct gps_data_t *gpsdata) {
    stringstream fixMode;

    if(gpsdata->fix.mode == 2) {
         fixMode << "Satus: 2D Fix";

    } else if(gpsdata->fix.mode == 3) { 
        fixMode << "Status: 3D Fix" << "\t" << "Altitude: " << gpsdata->fix.altitude << "m";
    }

    return fixMode.str();
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

string location(struct gps_data_t *gpsdata) {
    
    double lat;
    double lon;
    lat = gpsdata->fix.latitude;
    lon = gpsdata->fix.longitude;

    stringstream latLong;
    
    if(gpsdata->fix.mode >= 2) {
        if(lat < 0 && lon >= 0) {
            latLong << "Latitude: " << abs(lat) << "S" << "\t" << "Longitude: " << lon << "E";
        } else if(lat < 0 && lon <0) {
            latLong << "Latitude: " << abs(lat) << "S" << "\t" << "Longitude: " << abs(lon) << "W";
        } else if (lat >=0 && lon < 0) {
            latLong << "Latitude: " << lat << "N" << "\t" << "Longitude: " << abs(lon) << "W";
        } else {
            latLong << "Latitude: " << lat << "N" << "\t" << "Longitude: " << lon << "E";
        }
        
    } else {
        latLong << "Latitude: " << "NA" << "\t" << "Longitude" << "NA";
    }
    return latLong.str();
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

string information(struct gps_data_t *gpsdata, int satllite) {
    stringstream satInfo;

    satInfo << "PRN: " << gpsdata->PRN[satllite] << "\t";
    satInfo << "Elevation: " << gpsdata->elevation[satllite] << "\t";
    satInfo << "Azimuth: " << gpsdata->azimuth[satllite] << "\t";
    satInfo << "SNR: " << gpsdata->ss[satllite] << "\t";
    if(gpsdata->used[satllite]) {
        satInfo << "Used: " << "Y";
    } else {
        satInfo << "Used: " << "N";
    }
    return satInfo.str();
}
