#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>

#include "server.hpp"

Server::Server( const int port )
    : _port( port )
    , _socket( -1 )
{
}

bool Server::bind()
{
    if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        std::cerr << "Socket RV failure" << std::endl;
        return false;
    }

    _sockaddr.sin_family = AF_INET;
    _sockaddr.sin_port = htons(_port);
    _sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (::bind(_socket, (struct sockaddr *) &_sockaddr, sizeof(_sockaddr))==-1)
    {
        std::cerr << "Binding failure" << std::endl;
        return false;
    }

    if (listen(_socket, 1)==-1)
    {
        std::cerr << "Listening failure" << std::endl;
        return false;
    }

    // prepare set of file descriptors
    FD_ZERO (&_read_set);

    FD_ZERO (&_active_set);
    FD_SET (_socket, &_active_set);

    return true;
}

bool Server::wait( const int secs, std::string &message )
{
    message.clear();
    _read_set = _active_set;

    struct timeval timeout;
    timeout.tv_sec = secs;
    timeout.tv_usec = 0;

    if (select (_socket+1, &_read_set, NULL, NULL, &timeout) < 0)
    {
        std::cerr << "select" << std::endl;
        return EXIT_FAILURE;
    }

    if (FD_ISSET (_socket, &_read_set))
    {
        char buf[BUFSIZ];
        int nbytes = 0;
        socklen_t size = sizeof(_sockaddr);
        int s = accept(_socket, (struct sockaddr *)&_sockaddr, &size);

        if( (nbytes = read(s, buf , BUFSIZ)) < 0)
        {
            std::cerr << "recv failure" << std::endl;
            return false;
        }

        message = buf;
        message.resize(nbytes);

        close(s);
    }

    return EXIT_SUCCESS;
}
