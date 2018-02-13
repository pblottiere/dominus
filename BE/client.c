#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <string.h>
#define MAXTEXT 100

int main(int argc, char *argv[])
{
  int sock;
  int port;
  struct hostent * hote;
  struct sockaddr_in adr;

  if (argc!=5)
  {
    fprintf(stderr,"Usage : %s <MACHINE> <PORT-NUMBER> <GPIO_NUMBER> <VALUE_TO_WRITE>\n", argv[0]);
    exit(1);
  }

  char *gpio_number = argv[3];
  char *value = argv[4];

  if ((sock=socket(AF_INET, SOCK_STREAM, 0)) ==-1)
  {
    perror("socket rendez-vous");
    exit(1);
  }
  
  hote=gethostbyname(argv[1]);
  port=atoi(argv[2]);

  adr.sin_family=AF_INET;
  adr.sin_port=htons(port);
  bcopy(hote->h_addr, &adr.sin_addr.s_addr, hote->h_length);

  if (connect(sock, (struct sockaddr *)&adr, sizeof(adr))==-1)
  {
    perror("connect");
    exit(1);
  }

  char c[MAXTEXT];
  sprintf(c, "%s %s\n", gpio_number, value);

  // send the gpio_number and the value to the socket
  write(sock, &c, MAXTEXT);


  return 0;
}

