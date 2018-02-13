#ifndef gpio_switch_h__
#define gpio_switch_h__
 
int initGPIO(char* gpioId);
int setGPIODirection(char* gpioId, char* direction);
int setGPIOValue(char* gpioId, char* value);
 
#endif  // gpio_switch_h__

