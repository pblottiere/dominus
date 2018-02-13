#include <stdio.h>
#include <stdlib.h>

// External library:
#include "gpio.h"


/* #################################### */
/* ##            FUNCTIONS           ## */
/* #################################### */
/**
 * Writing on the GPIO
 * 
 * @param gpio: int containing the number of the GPIO
 * @param state: int containing the expected state of the GPIO: '0' for Off and '1' for On.
 * 
 * TODO: add tests of success of faillure for the creation of the files
 *       check if the folders/files exists before trying to create them
 *       add true error messages
 *       add true return signals
 */
int write_gpio(int gpioNumber, int state) {
	if (gpioNumber <= 27) {
		// Changing the state:
		// 		Changing the state of the gpio:
		int maxSize = 29;
		char path[maxSize];
		snprintf(path, maxSize, "/sys/class/gpio/gpio%d/value", gpioNumber);

		FILE *GPIO_VALUE = fopen(path, "w");
		if (state == 1) {
			fprintf(GPIO_VALUE, "1");
		}
		else if (state == 0) {
			fprintf(GPIO_VALUE, "0");
		}
		else {
			printf("Error in 'write_gpio' from gpio.h/c: 'state' needs to be equal to 0 (=Output) or 1 (=Input)!\n");
		}
		fclose(GPIO_VALUE);

		//printf("The GPIO_%ds's value is %d \n", gpioNumber, state);
		return 0;
	}
	else {
		printf("Error in 'write_gpio' from gpio.h/c: 'gpioNumber' needs to be <= 27!\n");
		return 1;
	}
}


/**
 * Initialization of the GPIO
 * 
 * @param gpio: int containing the number of the GPIO
 * @param state: int containing '0' if Output or '1' if Input 
 *
 * TODO: add tests of success of faillure for the creation of the files
 *       check if the folders/files exists before trying to create them
 *       add true error messages
 *       add true return signals
 */
int init_gpio(int gpioNumber, int inOut) {
	if (gpioNumber <= 27) {
		// Creation:
		// 		Defining the gpio:
		FILE *GPIO_CREATION = fopen("/sys/class/gpio/export", "w");
		char nb[3];
		snprintf(nb, 3, "%d", gpioNumber);  // cast
		fprintf(GPIO_CREATION, nb);
		fclose(GPIO_CREATION);
		//printf("--> GPIO created!\n");


		// Setting-up the type state of the gpio (input or output)
		// 		- Storing the path of the gpio for future writing:
		int maxSize = 33;
		char stateFile[maxSize];
		snprintf(stateFile, maxSize, "/sys/class/gpio/gpio%d/direction", gpioNumber);

		// 		- Setting-up the gpio:
		FILE *GPIO_STATE = fopen(stateFile, "w");
		if (inOut == 1) {
			fprintf(GPIO_STATE, "In");
	 		//printf("The GPIO_%d is created as an Input !\n", gpioNumber);
	
			fclose(GPIO_STATE);

			// Turning off the GPIO:
			write_gpio(gpioNumber, 0);
			return 0;
		}
		else if (inOut == 0) {
			fprintf(GPIO_STATE, "out");
			//printf("The GPIO_%d is created as an Output !\n", gpioNumber);

			fclose(GPIO_STATE);

			// Turning off the GPIO:
			write_gpio(gpioNumber, 0);
			return 0;
		}
		else {
			printf("Error in 'init_gpio' from gpio.h/c: 'inOut' needs to be equal to 0 (=Output) or 1 (=Input)!\n");
			fclose(GPIO_STATE);
			return 1;
		}
	}
	else {
		printf("Error in 'init_gpio' from gpio.h/c: 'gpioNumber' needs to be <= 27!\n");
		return 1;
	}
}


/**
 * Closing the GPIO
 * 
 * @param gpio: int containing the number of the GPIO
 *
 * TODO: add tests of success of faillure for the creation of the files
 *       check if the folders/files exists before trying to create them
 *       add true error messages
 *       add true return signals
 */
int destroy_gpio(int gpioNumber) {
	if (gpioNumber <= 27) {
		// Turning off the GPIO:
		write_gpio(gpioNumber, 0);
		//printf("--> GPIO stoped!\n");

		// Closing:
	 	// 		Closing the gpio:
	 	FILE *GPIO_DESTRUCTION = fopen("/sys/class/gpio/unexport", "w");
	 	char nb[3];
		snprintf(nb, 3, "%d", gpioNumber);  // cast
	 	fprintf(GPIO_DESTRUCTION, nb);
	 	fclose(GPIO_DESTRUCTION);

	 	//printf("The GPIO_%d was closed !\n", gpioNumber);
	 	return 0;
	}
	else {
		printf("Error in 'destroy_gpio' from gpio.h/c: 'gpioNumber' needs to be <= 27!\n");
		return 1;
	}
}
