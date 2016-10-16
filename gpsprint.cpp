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

void print_gps_data(struct gps_data_t *gpsdata) {
    time(gpsdata);
    location(gpsdata);
    information(gpsdata);
}
void time(struct gps_data_t *gpsdata) {
    time_t gpsTime;
    gpsTime = (time_t) gpsdata->fix.time;
    cout << ctime(&gpsTime) << "\t";
}

void location(struct gps_data_t *gpsdata) {
    
    double lat;
    double lon;
    lat = gpsdata->fix.latitude;
    lon = gpsdata->fix.longitude;
    
    if(gpsdata->fix.mode >= 2) {
        cout << lat << "\t" << lon << endl;
    } else {
        cout << "N/A" << "\t" << "N/A" << endl;
    
}

void information(struct gps_data_t *gpsdata) {
    
    bool use;
    short prn;
    short elevate;
    short azimuth;
    double SNR;
    
    azimuth = gpsdata->azimuth[0];
    use = gpsdata->used[0];
    prn = gpsdata->PRN[0];
    elevate = gpsdata->elevation[0];
    SNR = gpsdata->ss[0];
    
    cout << "azimuth: " << azimuth << endl;
    cout << "used: " << use << endl;
    cout << "prn: " <<prn << endl;
    cout << "elevation: " << elevate << endl;
    cout << "SNR: " <<SNR << endl;
}
