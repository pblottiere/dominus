#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netdb.h>
#include <arpa/inet.h>

int tcp_server;

struct sockaddr_in adr;
socklen_t lgadresse;


int init_server(int port)
{
	int socket_RV;

	if ((socket_RV = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket RV failure");
		exit(1);
	}

	adr.sin_family = AF_INET;
	adr.sin_port = htons(port);
	adr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(socket_RV, (struct sockaddr *) &adr, sizeof(adr))==-1)
	{
		perror("Binding failure");
		exit(1);
	}			

	if (listen(socket_RV,1)==-1)
	{
		perror("Listening failure");
		exit(1);
	}

    return socket_RV;
}

char get_command_from_client(int tcp_server)
{
    int socket_service;
    socket_service = accept(tcp_server,(struct sockaddr *)&adr, &lgadresse);

    // Listening
    char msg[256];
    int read_total = 0;
    int read_size = 0;
    while ((read_size = recv(socket_service, msg, 256, read_total)) > 0)
    {
        read_total += read_size;
    }
    
    close(socket_service);
    
    return msg[0];
}



