#_GPS Reader_
Below is a set of instructions for running the Raspberry Pi GPS locator application.

###Part 1: Installing and running the GPSD Client<br />
1.	Open the command line on the raspberry pi<br />
2.	Type and run the below command to install GPSD:<br />
    $ sudo apt-get install gpsd gpsd-clients python-gps <br />
3.	After installing GPSD, run the below command to start it<br />
    $ sudo gpsd /dev/ttyUSB0 -F -n /var/run/gpsd.sock <br />
    
###Part 2: Cloning the Git Repository<br />
1.	Open the raspberry pi’s command prompt in the folder you would like the GPS tracking program to be installed.<br />
2.	Type in the below command to clone the git repository into the selected folder from step 1.<br />
    $ git clone https://github.com/jacobfrank4/gpsReader.git<br />

###Part 3: Running the GPS Tracking Software<br />
1.	From inside the project folder, run the below command to create the executable file.<br />
    $ make<br />
2.	Once the project has been built, run the below command to run the executable<br />
    $./dcgps<br />
3.	Once the file is run, you should see the GPS data printed to the screen as in the example below.<br />
 
###_Troubleshooting_<br />
####If git is not installed on the raspberry pi<br />
1.	Run the below command to install git<br />
    $ sudo apt-get install git-all<br />
2.	After installing git, return to part 2 and clone the repository<br />

####If the operating system is Raspbian Jessie or later<br />
1.	To run GPSD on the operating system Raspbian Jessie or later, the gpsd.socket system service must be disabled. Run the below commands to stop and disable this system service.<br />
    $ sudo systemctl stop gpsd.socket<br />
    $ sudo systemctl disable gpsd.socket<br />
2.	After running the above commands, rerun the command in step 3 of part 1 to initialize GPSD<br />

####If any of the programs are out of date<br />
1.	Run the below command to update the software on the Raspberry pi<br />
    $ sudo apt-get update<br />
2.	After running the above command, rerun step 3 of part 1.<br />
