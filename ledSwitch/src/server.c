#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>

// External library:
#include "gpio.h"

int gpioLedNumber = 17,
    newsockfd;


void error(char *);

void signals_handler(int signal_number);

int main(int argc, char *argv[]) {

    // Reading conf from the file 'server.conf':
    FILE* fileData = fopen ("/opt/dominus/server.conf","r");
    if (fileData == NULL) {
        printf ("ERROR: no 'server.conf' file found!\n");
        exit(1);
    }

    int ierr,
        port_no;
    ierr = fscanf (fileData,"%d", &(port_no));
    if (ierr != 1) {
        printf ("ERROR: the file is empty\n");
        exit(1);
    }
    //printf("Socket read\n");
    
    fclose (fileData);

    init_gpio(gpioLedNumber, 0);
    // To catch ctrl + C:
    struct sigaction action;
    action.sa_handler = signals_handler;
    sigemptyset(& (action.sa_mask));
    action.sa_flags = 0;
    sigaction(SIGINT, & action, NULL);

    int sockfd,
        //cli_size,
        bindfd,
        readfd,
        //writefd,
        listenfd;

    unsigned int serv_size;
    
    char sbuffer[256];
    char *p;
    p = &sbuffer[0];

    struct sockaddr_in serv_addr, cli_addr;

    //creating sever side socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        error("Server side listening Socket could not be created!\n");
    }


    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family =  AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    //binding socket
    bindfd = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if  (bindfd == -1) {
        error("Failed to bind server side socket!\n");
    }

    //listening for incoming connections
    listenfd = listen(sockfd, 5);
    if (listenfd == -1) {
        error("Failed to lisen to incoming connections!\n");
    }

    serv_size = sizeof(serv_addr);
    //cli_size = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &serv_size);
    if (newsockfd == -1) {
        error("Failed to accept connections from client!\n");
    }

    //printf("Server received connections from %s\n", (char *)inet_ntoa(cli_addr.sin_addr)); 

    while(1)
    {   
        bzero(p, sizeof(sbuffer));
        readfd = read(newsockfd, p, sizeof(sbuffer));
        if (readfd == -1) {
            error("Sorry. Unable to read message from client!\n");
        }
        /*if (sbuffer[0] == 'q') {
            break;
        }*/
        //printf("Message Received: ");
        if (strcmp(sbuffer, "light_on") == 0) {
            write_gpio(gpioLedNumber, 1);
	    printf("GPIO Number %d, turned on\n", gpioLedNumber);
        }
        else if (strcmp(sbuffer, "light_off") == 0) {
            write_gpio(gpioLedNumber, 0);
	    printf("GPIO Number %d, turned off\n", gpioLedNumber);
        }
        //puts(sbuffer);
    
        /*bzero(p,  sizeof(sbuffer));
        printf("\nEnter Your Message for client: ");
        gets(sbuffer);
        writefd = write(newsockfd, p, sizeof(sbuffer));
        if (writefd == -1)
            error("Sorry. Message Could not be sent to client.\n");
        printf("Congratulations! Message has been sent to client.\n");  */
    }       
    close(newsockfd);
    destroy_gpio(gpioLedNumber);
    sleep(1);
    return 0;   
}


//-----------------------------------------------------------------------------
void error(char *msg) {
    perror(msg);
    exit(1);
}

void signals_handler(int signal_number) {
    printf("Signal catched.\n");
    close(newsockfd);
    destroy_gpio(gpioLedNumber);
    sleep(1);
    exit(EXIT_SUCCESS);
}
