#include <stdio.h>
#include <stdlib.h>

// External library:
#include "gpio.h"


/* #################################### */
/* ##               MAIN             ## */
/* #################################### */
int main() {	
	printf("Begining of the program !\n");
	int gpioLedNumber = 17;

	// Initialization of the GPIO:
	init_gpio(gpioLedNumber, 0);
	printf("=> End of function 'init_gpio'!\n");

	// Writing:
	write_gpio(gpioLedNumber, 1);
	printf("=> End of function 'write_gpio'!\n");

	// To let some time pass:
	printf("=> Starting to lose some time!\n");
	int i;
	for (i = 0; i < 1500000; i ++) {
		printf("");
	}
	printf("=> End of losing some time!\n");

	//Destroying the GPIO:
	destroy_gpio(gpioLedNumber);
	printf("=> End of function 'destroy_gpio'!\n");

	return 0;
}
