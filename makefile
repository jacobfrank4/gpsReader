CC=g++
CFLAGS=-c -std=c++11 -Wall -W -pedantic
CLIB= -lgps -pthread

dcgps: dcgps.o gps-utils.o gpsprint.o
		$(CC) -o dcgps dcgps.o gps-utils.o gpsprint.o $(CLIB)

clean:
	rm -f *.o core.* dcgps
dcgps.o:
	$(CC) $(CFLAGS) dcgps.cpp
gps-utils.o:
	$(CC) $(CFLAGS) gps-utils.cpp
gpsprint.o:
	$(CC) $(CFLAGS) gpsprint.cpp