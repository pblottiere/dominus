#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "GPIOClass.h"

using namespace std;

int main(int argc, char* argv[])
{

	char* nbr="17";
        if (argc != 3){
            std::cout << "Usage is -g <GPIO> \n";
            exit(0);
        }
        const char * options = "g:";
        int option;
        while((option = getopt(argc, argv, options)) != -1){
            switch(option){
                case 'g':
                    nbr = optarg;
                    break;
                case '?':
                    fprintf(stderr, "Invalid option %c\n", optopt);
                    exit(EXIT_FAILURE);
                }
        }

	GPIOClass* gpio4 = new GPIOClass(nbr); //create new GPIO object to be attached to  GPIO4
	gpio4->export_gpio(); //export GPIO4

	cout << " GPIO pins exported" << endl;

	gpio4->setdir_gpio("off"); //GPIO4 set to output

	cout << " Set GPIO pin directions" << endl;


    	gpio4->setval_gpio("0"); // turn LED ON

   	cout << " Turning it off" << endl;

	cout << "Exiting....." << endl;
	return 0;
}
