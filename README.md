# gpsReader
Below is a set of instructions for running the Raspberry Pi GPS locator application.

Part 1: Installing and running the GPSD Client
1.	Open the command line on the raspberry pi
2.	Type and run the below command to install GPSD:
    $ sudo apt-get install gpsd gpsd-clients python-gps 
3.	After installing GPSD, run the below command to start it
    $ sudo gpsd /dev/ttyUSB0 -F -n /var/run/gpsd.sock 
    
Part 2: Cloning the Git Repository
1.	Open the raspberry pi’s command prompt in the folder you would like the GPS tracking program to be installed. 
2.	Type in the below command to clone the git repository into the selected folder from step 1.
    $ git clone https://github.com/jacobfrank4/gpsReader.git

Part 3: Running the GPS Tracking Software
1.	From inside the project folder, run the below command to create the executable file.
    $ make
2.	Once the project has been built, run the below command to run the executable
    $./dcgps
3.	Once the file is run, you should see the GPS data printed to the screen as in the example below.
 
Troubleshooting
If git is not installed on the raspberry pi
1.	Run the below command to install git
    $ sudo apt-get install git-all
2.	After installing git, return to part 2 and clone the repository

If the operating system is Raspbian Jessie or later
1.	To run GPSD on the operating system Raspbian Jessie or later, the gpsd.socket system service must be disabled. Run the below commands to stop and disable this system service.
    $ sudo systemctl stop gpsd.socket
    $ sudo systemctl disable gpsd.socket
2.	After running the above commands, rerun the command in step 3 of part 1 to initialize GPSD

If any of the programs are out of date
1.	Run the below command to update the software on the Raspberry pi
    $ sudo apt-get update
2.	After running the above command, rerun step 3 of part 1.
