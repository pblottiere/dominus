BUILDROOT_HOME=/root/buildroot-2017.08
CC=$(BUILDROOT_HOME)/output/host/usr/bin/arm-linux-g++
CFLAGS=-fpermissive -Wall

all:
	mkdir -p build
	g++ -fpermissive -Wall GPIOclient.cpp -o build/client
	g++ -fpermissive -Wall GPIOClass.cpp GPIOserver.cpp -o build/server

v2:
	mkdir -p build
	g++ -fpermissive -Wall GPIOClass.cpp GPIOon.cpp -o build/gpion
	g++ -fpermissive -Wall GPIOClass.cpp GPIOoff.cpp -o build/gpioff

lib:
	g++ -fpermissive -fPIC -shared GPIOClass.cpp -o libshared.so
	g++ -L. -lshared -o build/server GPIOserver.cpp

crossv2:
	mkdir -p build
	$(CC) $(CFLAGS) GPIOClass.cpp GPIOon.cpp -o build/gpion
	$(CC) $(CFLAGS) GPIOClass.cpp GPIOoff.cpp -o build/gpioff
crossv4:
	mkdir -p build
	$(CC) $(CFLAGS) GPIOClass.cpp GPIOserver.cpp -o build/server
	$(CC) $(CFLAGS) GPIOclient.cpp -o build/client

clean:
	rm -r ./build



