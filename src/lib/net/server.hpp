#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <arpa/inet.h>

class Server
{
    public:
        Server( const int port );

        bool bind();

        bool wait( const int timeout, std::string &message );

        bool receive( std::string &message );

    private:
        const int _port;
        struct sockaddr_in _sockaddr;
        socklen_t _socklen;
        int _socket;
        fd_set _active_set;
        fd_set _read_set;
};

#endif
