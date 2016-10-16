//gpsprint.cpp
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

void gps_data(struct gps_data_t *gpsdata) {
    time(gpsdata);
    location(gpsdata);
    information(gpsdata);
}
void time(struct gps_data_t *gpsdata) {
    time_t gpsTime;
    gpsTime = (time_t) gpsdata->fix.time;
    cout << ctime(&gpsTime) << "  ";
}

void location(struct gps_data_t *gpsdata) {
    
    double lat;
    double lon;
    lat = gpsdata->fix.latitude;
    lon = gpsdata->fix.longitude;
    
    if(gpsdata->fix.mode >= 2) {
        if(lat < 0 && lon >= 0) {
          cout << abs(lat) << "S" << "\t" << lon << "E" << endl;
        } else if(lat < 0 && lon <0) {
            cout << abs(lat) << "S" << "\t" << abs(lon) << "W" << endl;
        } else if (lat >=0 && lon < 0) {
            cout << lat << "N" << "\t" << abs(lon) << "W" << endl;
        } else {
            cout << lat << "N" << "\t" << lon << "E" << endl;
        }
        
    }
    
}

void information(struct gps_data_t *gpsdata) {
    
    
    if(gpsdata->satellites_visible !=0) {
        for(int i = 0; i < gpsdata->satellites_visible; i++) {
            cout << "PRN: " + gpsdata->PRN[i] << "\t";
            cout << "Elevation: " + gpsdata->elevation[i] << "\t";
            cout << "Azimuth: " + gpsdata->azimuth[i] << "\t";
            cout << "SNR: " + gpsdata->ss[i] << "\t";
            if(gpsdata->used[i]) {
                cout << "Used: " << "Y" << endl;
            } else {
                cout << "Used: " << "N" << endl;
            }
        }
    }
}
