GCC = /root/buildroot-2017.08-compiled/output/host/bin/arm-linux-gcc
SONAME = libgpio.so
SERVER = dominus0_server
CLIENT = dominus1_client


## ALL:
############################
all: init gpio client server


## HELP:
############################
help:
	@( \
	echo ;\
	echo "    === Makefile for the dominus server ===                         ";\
	echo ;\
	echo "make        : Default action...                                     ";\
	echo "              Generates all the code in the 'bin' folder            ";\
	echo ;\
	echo "make init   : Generates the fs-tree                                 ";\
	echo ;\
	echo "make client : Generates only the client and its config-file in the  ";\
	echo "              bin folder                                            ";\
	echo ;\
	echo "make server : Generates only the server and its config-file in the  ";\
	echo "              bin folder                                            ";\
	echo ;\
	echo "make gpio   : Generates only the 'libgpio.so' file in the 'include' ";\
	echo "              folder                                                ";\
	echo ;\
	echo "make test   : Generates a tiny test-program to check my gpio lib, in";\
	echo "              in the 'bin' folder                                   ";\
	echo ;\
	echo "make clean  : Cleans everything to have an embeded source code      ";\
	echo ;\
	)


## INIT:
############################
init:
	mkdir -p bin lib include


## CLIENT:
############################
client:
	$(GCC) -Wall src/client.c -o bin/$(CLIENT)
	cp src/client.conf bin/client.conf


## SERVER:
############################
server:
	$(GCC) -Wall src/server.c -o bin/$(SERVER) -I include/ -L lib/ -lgpio
	cp src/server.conf bin/server.conf


## GPIO:
############################
gpio: init
	$(GCC) -g -c -fPIC src/lib/gpio/gpio.c -o src/lib/gpio/gpio.o
	$(GCC) -g -shared -Wl,-soname,$(SONAME) -o src/lib/gpio/$(SONAME) src/lib/gpio/gpio.o
	cp src/lib/gpio/gpio.h include/
	mv src/lib/gpio/$(SONAME) lib/


## TEST:
############################
test:
	$(GCC) -Wall src/lib/gpio/gpio.c include/gpio.h src/lib/gpio/test.c -o bin/test


## CLEAN:
############################
clean:
	rm -rf bin lib include
	rm src/lib/gpio/gpio.o