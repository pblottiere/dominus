CC=~/buildroot-2017.08/output/host/bin/arm-linux-gcc # Change here the path to the compiler

default: all

serveur.o: switchOnOff.h
    
all: serveur.o client.o switchOnOff.o
	$(CC) -o dominus_client client.o
	$(CC) -o dominus_serveur serveur.o switchOnOff.o

switchOnOff.o: switchOnOff.c switchOnOff.h
	$(CC) -c switchOnOff.c

client.o: client.c
	$(CC) -c client.c

serveur.o: serveur.c
	$(CC) -c serveur.c

clean:
	rm *.o 
