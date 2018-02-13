#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "../lib/tcp/tcp_client.h"


int main (int argc, char* argv[])
{
    if (argc != 4) 
    {
        printf("Error, missing arguments\n");
        printf("Convention: \n");
        printf("./main ip port message\n");
        return EXIT_FAILURE;
    } else 
    {
        // Create the client on given port, IP and send the message
        send_remote_message(argv[1], atoi(argv[2]), argv[3]);

        return EXIT_SUCCESS;
    }
}


