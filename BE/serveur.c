#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <signal.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include "switchOnOff.h"

#define MAXTEXT 100

int socket_RV = 0;

void signals_handler(int signal_number)
{
  printf("Signal catched.\n");
  close(socket_RV);
  printf("Socket closed.\n");
  exit(EXIT_SUCCESS);
}


int main(int argc, char * argv[])
{
  // signals handler to close properly the socket on CTRL-C
  struct sigaction action;
  action.sa_handler = signals_handler;
  sigemptyset(& (action.sa_mask));
  action.sa_flags = 0;
  sigaction(SIGINT, & action, NULL);

  int socket_service;
  int port;
  char nom[30];
  struct sockaddr_in adr, adresse;
  socklen_t lgadresse;
  if (argc!=2)
  {
    fprintf(stderr,"Usage : %s port-number", argv[0]);
    exit(1);
  }

  port = atoi(argv[1]);


  if ((socket_RV=socket(AF_INET, SOCK_STREAM, 0)) ==-1)
  {
    perror("socket rendez-vous");
    exit(1);
  }

  if (gethostname(nom, 30)==-1)
  {
    perror("Qui suis-je ?");
    exit(1);
  }
 
  adr.sin_family=AF_INET;
  adr.sin_port=htons(port);
  adr.sin_addr.s_addr = htonl(INADDR_ANY);

  
  if (bind(socket_RV, (struct sockaddr *) &adr, sizeof(adr))==-1)
  {
    perror("bind");
    exit(1);
  }


  if (listen(socket_RV,1)==-1)
  {
    perror("listen");
    exit(1);
  }


  while (1) {

    socket_service=accept(socket_RV, (struct sockaddr *)&adresse, &lgadresse);
    

    char *chat =  (char*)malloc(MAXTEXT);

    printf("Client is connected\n");

    read(socket_service, chat, MAXTEXT);

    char *p = chat;
    char *gpio_number = p;
    char *lastSpace;

    // Parsing with the space characters
    while(*p != '\0')
    {
        if (*p == ' ')
            lastSpace = p;
        p++;
    }

    // Replace the last space in the line with a NUL
    *lastSpace = '\0';

    // Advance past the NUL to the first character of the number field
    lastSpace++;

    char *value = lastSpace;
    // call the function that actually change the LED value
    switch_gpio(gpio_number, value);
  
    close(socket_service);
  }

  return 0;
}



