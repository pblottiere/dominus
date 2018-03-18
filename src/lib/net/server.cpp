#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <iostream>

#include <logger/logger.hpp>

#include "server.hpp"

Server::Server( const int port )
    : _port( port )
    , _socket( -1 )
{
    Logger::debug( "[server] Configuration:" );
    Logger::debug( "[server]   - port: " + std::to_string( port ) );
}

Server::~Server()
{
    if ( _socket >= 0 )
    {
        close(_socket);
    }
}

bool Server::bind()
{
    if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        Logger::error( "[server] Socket failure." );
        return true;
    }

    _sockaddr.sin_family = AF_INET;
    _sockaddr.sin_port = htons(_port);
    _sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (::bind(_socket, (struct sockaddr *) &_sockaddr, sizeof(_sockaddr))==-1)
    {
        Logger::error( "[server] Binding failure." );
        return true;
    }

    if (listen(_socket, 1)==-1)
    {
        Logger::error( "[server] Listening failure." );
        return true;
    }

    // prepare set of file descriptors
    FD_ZERO (&_read_set);

    FD_ZERO (&_active_set);
    FD_SET (_socket, &_active_set);

    return false;
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
        Logger::error( "[server] Select failure" );
        return true;
    }

    if (FD_ISSET (_socket, &_read_set))
    {
        char buf[BUFSIZ];
        int nbytes = 0;
        socklen_t size = sizeof(_sockaddr);
        int s = accept(_socket, (struct sockaddr *)&_sockaddr, &size);

        if( (nbytes = read(s, buf , BUFSIZ)) < 0)
        {
            Logger::error( "[server] Read failure" );
            return true;
        }

        message = buf;
        message.resize(nbytes);

        close(s);
    }

    return false;
}
