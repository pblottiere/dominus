#ifndef GPIO_H
#define GPIO_H


/* #################################### */
/* ##            PROTOTYPES          ## */
/* #################################### */

/**
 * Writing on the GPIO
 * 
 * @param gpio: int containing the number of the GPIO (<= 27)
 * @param state: int containing the expected state of the GPIO: '0' for Off and '1' for On.
 */
int write_gpio(int, int);


/**
 * Initialization of the GPIO
 * 
 * @param gpio: int containing the number of the GPIO (<= 27)
 * @param state: int containing '0' if Output or '1' if Input 
 */
int init_gpio(int, int);


/**
 * Closing the GPIO
 * 
 * @param gpio: int containing the number of the GPIO (<= 27)
 */
int destroy_gpio(int);


#endif