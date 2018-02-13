#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include <signal.h>
#include <unistd.h>

int sockfd;


void error(char *);

void signals_handler(int signal_number);



int main(int argc, char *argv[]) {

    // Reading conf from the file 'client.conf':
	FILE* fileData = fopen ("/opt/dominus/client.conf","r");
	if (fileData == NULL) {
		printf ("ERROR: no data 'client.conf' file found!\n");
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

	char ip[20];
	ierr = fscanf (fileData,"%s", ip);
	if (ierr != 1) {
		printf ("ERROR: the file is empty\n");
		exit(1);
	}
	//printf("ip read\n");
	
	fclose (fileData);

    // To catch ctrl + C:
    struct sigaction action;
    action.sa_handler = signals_handler;
    sigemptyset(& (action.sa_mask));
    action.sa_flags = 0;
    sigaction(SIGINT, & action, NULL);


	int connectfd, 
	    //readfd, 
	    writefd;

	char mess[256],
	     saved[256];
	saved[0] = '\0';
	char *ptr = &mess[0];

	struct sockaddr_in serv_addr;
	struct hostent *he;

	he = gethostbyname(ip);
	if (he == NULL) {
	    error("No Such Host!\n");
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) {
	    error("Sorry. Socket could not be created!\n");
	}

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr = *((struct in_addr *)he->h_addr);  

	connectfd = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (connectfd == -1) {
	    error("Sorry. Could not connect to server.\n");
	}



	while(1)
	{   
	    bzero(ptr, sizeof(mess));
	    //printf("\nEnter message for Server: \n");
	    //gets(mess);

		FILE* fileData = fopen ("/tmp/light.dat","r");
		if (fileData == NULL) {
			printf ("ERROR: no data '/tmp/light.dat' file found!\n");
			exit(1);
		}

		int ierr;
		ierr = fscanf (fileData,"%s", mess);
		if (ierr != 1) {
			printf ("ERROR: the file is empty\n");
			exit(1);
		}
	    
		fclose (fileData);
		if (strcmp(mess, saved) != 0) {
			writefd = write(sockfd, ptr, sizeof(mess));
	    	strcpy(saved, mess);  // keep last data
	    }
	    /*if (mess[0] == 'q') {
	    	break;
	    }*/
	    if (writefd == -1) {
	        error("Sorry. Could not send message to Server.");
	    }

	    //printf("Congratulations! Server Successfully Received your message.\n");    

	    /*bzero(ptr, sizeof(mess));
	    readfd = read(sockfd, ptr, sizeof(mess));
	    if (readfd == -1)
	        error("Sorry. Message from server could not be read.\n");

	    printf("Message Received: ");
	    puts(mess);*/
	    sleep(10);
	}
	close(sockfd);
	sleep(1);
	return 0;
}



//-----------------------------------------------------------------------------
void error(char *msg) {
	perror(msg);
	exit(1);
}


void signals_handler(int signal_number)
{
    printf("Signal catched.\n");
    close(sockfd);
    sleep(1);
    exit(EXIT_SUCCESS);
}
