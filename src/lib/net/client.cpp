#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>

#include <logger/logger.hpp>

#include "client.hpp"

Client::Client( const std::string &ip, const int port )
    : _port( port )
    , _ip( ip )
    , _socket( -1 )
{
    Logger::debug( "[client] Configuration:" );
    Logger::debug( "[client]   - ip: " + ip );
    Logger::debug( "[client]   - port: " + std::to_string( port ) );
}

bool Client::connect()
{
    struct sockaddr_in adr;

    if ( (_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
        std::cerr << "Socket failure" << std::endl;
        return false;
    }

    adr.sin_addr.s_addr = inet_addr(_ip.c_str());
    adr.sin_family = AF_INET;
    adr.sin_port = htons(_port);

    if ( ::connect(_socket,(struct sockaddr *)&adr, sizeof(adr))==-1 )
    {
        std::cerr << "Connection failure" << std::endl;
        return false;
    }

    return true;
}

bool Client::send( const std::string &message )
{
    if ( _socket )
    {
        return ::send(_socket, message.c_str(), message.size(), 0);
    }

    return -1;
}

bool Client::close()
{
    return ::close( _socket );
}
