#include <net/client.hpp>

#include <unistd.h>
#include <iostream>

int main( int argc, char * argv[] )
{
  std::string host;
  std::string command;
  int port;
  char c;

  while( ( c = getopt (argc, argv, "h:p:c:") ) != -1 )
  {
    switch(c)
    {
      case 'p':
        if(optarg)
          port = atoi(optarg);
        break;
      case 'h':
        if(optarg)
          host = optarg;
        break;
      case 'c':
        if(optarg)
          command = optarg;
        break;
    }
  }

  Client client(host, port);
  client.connect();
  client.send( command );
  client.close();
}
