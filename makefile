CC=g++
CFLAGS=-c -Wall -W -pedantic
CLIB= -lgps

dcgps: dcgps.o gps-utils.o gpsprint.o
		$(CC) -o dcgps dcgps.o gps-utils.o gpsprint.o $(CLIB)

clean:
	rm -f *.o core.* dcgps
dcgps.o:
	$(CC) $(CFLAGS) dcgps.cpp
gps-utils.o:
	$(CC) $(CFLAGS) gps-utils.cpp
gpsprint.0:
	$(CC) $(CFLAGS) gpsprint.cpp