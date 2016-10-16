//gpsprint.cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gps.h>
using namespace std;

void time(struct gps_data_t *gpsdata);
void location(struct gps_data_t *gpsdata);
void information(struct gps_data_t *gpsdata);

int gps_data(struct gps_data_t *gpsdata) {
    time(gpsdata);
    location(gpsdata);
    information(gpsdata);
}
void time(struct gps_data_t *gpsdata) {
	
    time_t gpsTime;
    gpsTime = (time_t) gpsdata->fix.time;
    cout << gmtime(&gpsTime) << endl;
}

void location(struct gps_data_t *gpsdata) {
    
    double lat;
    double lon;
    
    lat = gpsdata->fix.latitude;
    lon = gpsdata->fix.latitude;
    cout << "latitude" << lat << endl;
    cout << "longitude" << lon << endl;
}

void information(struct gps_data_t *gpsdata) {
    
    bool use;
    short prn;
    short elevate;
    short azimuth;
    double SNR;
    
    azimuth = gpsdata->azimuth;
    use = gpsdata->used;
    prn = gpsdata->PRN;
    elevate = gpsdata->elevation;
    SNR = gpsdata->ss;
    
    cout << "azimuth: " << azimuth << endl;
    cout << "used: " << use << endl;
    cout << "prn: " <<prn << endl;
    cout << "elevation: " << elevate << endl;
    cout << "SNR: " <<SNR << endl;
}
