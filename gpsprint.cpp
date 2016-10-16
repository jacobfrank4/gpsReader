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
	cout << "before time call" << endl;
    time(gpsdata);
	cout << "after time call" << endl;
	cout << "before location call" << endl;
    location(gpsdata);
	cout << "after location call" << endl;
	cout << "before information call" << endl;
    information(gpsdata);
	cout << "after information call" << endl;
}
void time(struct gps_data_t *gpsdata) {
	cout << "beginning of time method" << endl;
    time_t gpsTime;
    gpsTime = (time_t) gpsdata->fix.time;
    cout << localtime(&gpsTime) << endl;
	cout << "end of time method" << endl;
}

void location(struct gps_data_t *gpsdata) {
    
    double lat;
    double lon;
    
    lat = gpsdata->fix.latitude;
    lon = gpsdata->fix.longitude;
    cout << "latitude" << lat << endl;
    cout << "longitude" << lon << endl;
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
