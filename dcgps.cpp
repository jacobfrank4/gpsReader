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
-- REVISIONS:
-- Jacob Frank: Oct 17, 2016: Updated main function to include a help menu
--
-- DESIGNERS: Jacob Frank & Justen DePourcq
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
#include "headers/dcgps.h"

using namespace std;
void startThread(gpsmm& gps);
void readGPS(gpsmm gps);

int main(int argc, char* argv[]) {

    //Display help menu for the user if they type '-h' or '--help' as a command line argument
    if(argc > 1) {
        string arg1 = argv[1];
        cout << argv[1] << endl;
        if (arg1 == "-h" || arg1 =="--help") {
            cout << "Installing the GPSD client" << endl;
            cout << "1)Type and run the below command to install GPSD" << endl;
            cout << "    $sudo apt-get install gpsd gpsd-clients python-gps" << endl;
            cout << "2)run the below command to start GPSD" << endl;
            cout << "    $sudo gpsd /dev/ttyUSB0 -F -n /var/run/gpsd.sock" << endl << endl;

            cout << "Running the GPS Tracking Software" << endl;
            cout << "1)run the below command to create the executable file" << endl;
            cout << "    $make" << endl;
            cout << "2)run the below command to run the executable" << endl;
            cout << "    $./dcgps" << endl << endl;

            cout << "Troubleshooting" << endl;
            cout << "If the operating system is Raspbian Jessie or later" << endl;
            cout << "1) To run GPSD on the operating system Raspbian Jessie or later, the gpsd.socket system " <<
            "service must be disabled. Run the below commands to stop and disable this system service." << endl;
            cout << "    $sudo systemctl stop gpsd.socket" << endl;
            cout << "    $sudo systemctl disable gpsd.socket\n" << endl;
            cout << "If any of the programs are out of date" << endl;
            cout << "1) Run the below command to update the software on the Raspberry pi" << endl;
            cout << "    $sudo apt-get update" << endl;
        } else {
            cout << "Did you mean '-h' or '--help'?" << endl;
        }
        return 0;
    }

    gpsmm gpsStruct("localhost", DEFAULT_GPSD_PORT);

    if(gpsStruct.stream(WATCH_ENABLE|WATCH_JSON) == NULL) {
        cerr << "No GPSD Running. \n";
        return 1;
    }
    WINDOW * win;
    if ( (win = initscr()) == NULL ) {
        fputs("Could not initialize screen.", stderr);
        exit(EXIT_FAILURE);
    }
    //Passes the gpsmm to the read function for interpreting of the stallite gps data
    readGPS(gpsStruct);
}
