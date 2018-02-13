#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "../lib/gpio/gpio_switch.h"
#include "../lib/tcp/tcp_server.h"

int tcp_server;

void signals_handler(int signal_number)
{
    close(tcp_server);
	fflush(stdout);
	printf("Dominus server stopped\n");
    exit(1);
}


int set_gpio(char* pin, char* value)
{
    if (setGPIOValue(pin, value) == EXIT_FAILURE) 
    {
        if (initGPIO(pin) == EXIT_FAILURE) 
        {
            return EXIT_FAILURE;
        }
        if (setGPIODirection(pin, "out") == EXIT_FAILURE) 
        {
            return EXIT_FAILURE;
        }
        if (setGPIOValue(pin, value) == EXIT_FAILURE) 
        {
           return EXIT_FAILURE;
        }         
    }
    return EXIT_SUCCESS;
}


int main (int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Error, missing arguments\n");
        printf("Convention: \n");
        printf("./main port pin\n");
        return EXIT_FAILURE;
    } else
    {
	    // SIGACTION
        struct sigaction action;

        action.sa_handler = signals_handler;
        sigemptyset(& (action.sa_mask));

        sigaction(SIGQUIT, & action, NULL);
        sigaction(SIGINT, & action, NULL);
        // END SIGACTION
        
        // Initialize the server on given port
        tcp_server = init_server(atoi(argv[1])); 

        printf("Dominus server started\n");
        int gpio;
        do
        {
			// Wait for command from the client
	        char value = get_command_from_client(tcp_server);

	        // Assign the command value to the gpio
	        gpio = set_gpio(argv[2], &value);
	        printf("GPIO %s set to %c\n", argv[2], value);
        } while (gpio == EXIT_SUCCESS);

        return EXIT_FAILURE;
    }
}



