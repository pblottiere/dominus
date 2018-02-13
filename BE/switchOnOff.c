#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "switchOnOff.h"

int switch_gpio(char *gpio_number, char *value) {

	// Create the gpio folder if it doesn't exist yet.
	char gpio_path[255];
	sprintf(gpio_path, "/sys/class/gpio/gpio%s", gpio_number);

	struct stat st = {0};

	if (stat(gpio_path, &st) == -1)	{	
		FILE *fp_gpio_path;
		fp_gpio_path = fopen("/sys/class/gpio/export", "w");
		fputs(gpio_number, fp_gpio_path);
		fclose(fp_gpio_path);
	}

	// Set the direction to "out" if it's not the case.
	char gpio_direction_path[255];
	sprintf(gpio_direction_path, "%s/direction", gpio_path);

	FILE *fp_direction_path;
	fp_direction_path = fopen(gpio_direction_path, "r+");
	char *current_value;
	fread(&current_value, sizeof(char), 1, fp_direction_path);
	if (*current_value != 'o') {
		fputs("out", fp_direction_path);
	}
	fclose(fp_direction_path);

	// Write the wished value.
	char gpio_value_path[255];
	sprintf(gpio_value_path, "%s/value", gpio_path);

	FILE *fp;
	fp = fopen(gpio_value_path, "w");
	fputs(value, fp);
	fclose(fp);

	return 0;
}
