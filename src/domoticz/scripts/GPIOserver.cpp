#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
 
#include <iostream>
#include <errno.h>
#include <signal.h>
#include "GPIOClass.h"

#include <stdio.h>
#include <stdlib.h>
#define PORT 23
 
using namespace std; 
 
int main(int argc,char* argv[])
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

    int erreur = 0;
    char buffer[32]=""; 
    /* Socket et contexte d'adressage du serveur */
    SOCKADDR_IN sin;
    SOCKET sock;
    socklen_t recsize = sizeof(sin);
    
    /* Socket et contexte d'adressage du client */
    SOCKADDR_IN csin;
    SOCKET csock;
    socklen_t crecsize = sizeof(csin);
    
    int sock_err;
    
    
    if(!erreur)
    {
        /* Création d'une socket */
        sock = socket(AF_INET, SOCK_STREAM, 0);
        
        /* Si la socket est valide */
        if(sock != INVALID_SOCKET)
        {
            printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);
            
            /* Configuration */
            sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
            sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
            sin.sin_port = htons(PORT);               /* Listage du port */
            sock_err = bind(sock, (SOCKADDR*)&sin, recsize);
            
	    /*démarrage des GPIO*/
	    GPIOClass* gpio17 = new GPIOClass(nbr);
	    gpio17->export_gpio();
	    gpio17->setdir_gpio("out");
	    
            /* Si la socket fonctionne */
            if(sock_err != SOCKET_ERROR)
            {
                while(buffer[0] != 'o')
		{
		/* Démarrage du listage (mode server) */
                sock_err = listen(sock, 5);
                printf("Listage du port %d...\n", PORT);
                
                /* Si la socket fonctionne */
                if(sock_err != SOCKET_ERROR)
                {
                    /* Attente pendant laquelle le client se connecte */
                    printf("Patientez pendant que le client se connecte sur le port %d...\n", PORT);
                    csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
                    printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
                    
		    sock_err=recv(csock,buffer,32,0);
		    if(sock_err != SOCKET_ERROR)
                    {
			printf("Recu : %s\n", buffer);
			if(buffer[0] == 'a')
			{
			    gpio17->setval_gpio("1");
			    printf("gpio on");
			}
			else
			{
			    gpio17->setval_gpio("0");
		            printf("gpio off");
			}
		    }	

		}
                else
                    perror("listen");
		}
            }

            else
                perror("bind");
            
            /* Fermeture de la socket client et de la socket serveur */
            printf("Fermeture de la socket client\n");
            closesocket(csock);
            printf("Fermeture de la socket serveur\n");
            closesocket(sock);
            printf("Fermeture du serveur terminée\n");
        }
        else
            perror("socket");
        
    }
    
    return EXIT_SUCCESS;
}
