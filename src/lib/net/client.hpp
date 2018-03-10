#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
    public:
        Client( const std::string &ip, const int port );

        bool connect();

        int port() const;

        std::string ip() const;

        bool send( const std::string &message );

        bool close();

    private:
        const int _port;
        const std::string _ip;
        int _socket;
};

#endif

