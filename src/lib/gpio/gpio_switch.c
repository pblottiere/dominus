#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "gpio_switch.h"


int initGPIO(char* gpioId) {
    int exportFile;
    if ((exportFile = open("/sys/class/gpio/export", O_WRONLY)) < 0){
        return EXIT_FAILURE;
    }
    write(exportFile, gpioId, strlen(gpioId));
    close(exportFile);
    return EXIT_SUCCESS;
}

int setGPIODirection(char* gpioId, char* direction) {
    char directionPath[256];
    sprintf(directionPath, "/sys/class/gpio/gpio%s/direction", gpioId);
    int directionFile;
    if ((directionFile = open(directionPath, O_WRONLY)) < 0) {
        return EXIT_FAILURE;
    }
    write(directionFile, direction, strlen(direction));
    close(directionFile);
    return EXIT_SUCCESS;
}

int setGPIOValue(char* gpioId, char* value) {
    char valuePath[256];
    sprintf(valuePath, "/sys/class/gpio/gpio%s/value", gpioId);
    int valueFile;
    if ((valueFile = open(valuePath, O_WRONLY)) < 0) {
        return EXIT_FAILURE;
    }
    write(valueFile, value, strlen(value));
    close(valueFile);
    return EXIT_SUCCESS;
}

int main (int argc, char* argv[]){
    if (argc < 3) {
        printf("Error, missing arguments\n");
        printf("Convention: \n");
        printf("./gpio_switch pin value\n");
        return EXIT_SUCCESS;
    } else {
        if (setGPIOValue(argv[1], argv[2]) == EXIT_FAILURE) {
            if (initGPIO(argv[1]) == EXIT_FAILURE) {
                return EXIT_FAILURE;
            }
            if (setGPIODirection(argv[1], "out") == EXIT_FAILURE) {
                return EXIT_FAILURE;
            }
            if (setGPIOValue(argv[1], argv[2]) == EXIT_FAILURE) {
               return EXIT_FAILURE;
            }         
        }
        return EXIT_SUCCESS;
    }
}
