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
 
#include <stdio.h>
#include <stdlib.h>
#define PORT 23
#include <iostream> 
 
 
int main(int argc, char* argv[])
{
    char* ip="127.0.0.1";
    char* buffer="allumer";
    if (argc != 5) { // Check the value of argc. If not enough parameters have been passed, inform user and exit.
        std::cout << "Usage is -i <ip> -m <msg>\n"; // Inform the user on how to use the program
        exit(0);
    }
    const char * options = "i:m:";
    int option;
    while((option = getopt(argc, argv, options)) != -1)
    {
        switch(option)
        {
            case 'i':
	        ip = optarg;       // If the -i option is set, then ip takes the value of optarg (next inline 'block')
                break;

            case 'm':
                buffer = optarg;   // If the -m option is set, then buffer takes the value of optarg (next inline 'block')
                break;

            case '?':
                fprintf(stderr, "Invalid option %c\n", optopt);
                exit(EXIT_FAILURE);
        }
    }

    int erreur = 0;
    int sock_err;
      
    SOCKET sock;
    SOCKADDR_IN sin;
 
    if(!erreur)
    {
        /* Création de la socket */
        sock = socket(AF_INET, SOCK_STREAM, 0);
 
        /* Configuration de la connexion */
        sin.sin_addr.s_addr = inet_addr(ip);
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);
 
        /* Si le client arrive à se connecter */
        if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
	{
            printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
	    sock_err = send(sock, buffer, 32, 0);
 
            if(sock_err != SOCKET_ERROR)
                printf("Chaine envoyée : %s\n", buffer);
            else
                printf("Erreur de transmission\n");
	}
        else
            printf("Impossible de se connecter\n");
 
        /* On ferme la socket précédemment ouverte */
        closesocket(sock);
 
    }
 
    return EXIT_SUCCESS;
}
