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
}

void information() {
    
    struct gps_data_t gpsdata;
    bool use;
    short prn;
    short elevate;
    short azimuth;
    double SNR;
    
    elevate = gpsdata.azimuth;
}
