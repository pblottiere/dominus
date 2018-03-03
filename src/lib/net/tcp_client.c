#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netdb.h>
#include <arpa/inet.h>

int socket_RV;

void connect_to_server(char* IP, int port)
{
	struct sockaddr_in adr;

	if ((socket_RV = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
		perror("Socket RV failure");
		exit(1);
	}
	
	adr.sin_addr.s_addr = inet_addr(IP);
	adr.sin_family = AF_INET;
	adr.sin_port = htons(port);

	if ( connect(socket_RV,(struct sockaddr *)&adr, sizeof(adr))==-1 )
	{
		perror("Connection failure");
		exit(1);
	}
}

void send_remote_message(char* IP, int port, char* message)
{
    // Server host
    connect_to_server(IP, port);

	// Sending msg
	send(socket_RV, message, strlen(message), 0);

    // Closing Socket
    close(socket_RV);
}



