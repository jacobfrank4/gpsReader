//gpsprint.cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gps.h>
using namespace std;

void time();
void location();
void information();

int main(void) {
    time();
    location();
    information();
}
void time() {
    
    struct gps_data_t gpsdata;
	
    time_t gpsTime;
    gpsTime = (time_t) gpsdata.fix.time;
    cout << gmtime(&gpsTime) << endl;
}

void location() {
    
    struct gps_data_t gpsdata;
    double lat;
    double lon;
    
    lat = gpsdata.fix.latitude;
    lon = gpsdata.fix.latitude;
    cout << "latitude" << lat << endl;
    cout << "longitude" << lon << endl;
}

void information() {
    
    struct gps_data_t data;
    struct satellite_t sat;
    bool use;
    short prn;
    short elevate;
    short azimuth;
    double SNR;
    
    azimuth = sat.azimuth;
    use = sat.used;
    prn = sat.PRN;
    elevate = sat.elevation;
    SNR = sat.ss;
    
    cout << "azimuth: " << azimuth << endl;
    cout << "used: " << use << endl;
    cout << "prn: " <<prn << endl;
    cout << "elevation: " << elevate << endl;
    cout << "SNR: " <<SNR << endl;
}
