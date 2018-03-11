#include <net/client.hpp>

#include <unistd.h>
#include <iostream>

#include <logger/logger.hpp>

void usage()
{
  std::cout << "Usage: dominus-client [OPTIONS]" << std::endl;
  std::cout << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << std::endl;
  std::cout << "  -i=192.168.1.30       IP of Dominus Server" << std::endl;
  std::cout << "  -p=8081               Port of Dominus Server" << std::endl;
  std::cout << "  -c=\"GPIO:12:1\"        Command to execute" << std::endl;
  std::cout << "  -h                    Help" << std::endl;
}

int main( int argc, char * argv[] )
{
  std::string host;
  std::string command;
  int port = -1;
  char c;

  while( ( c = getopt (argc, argv, "i:p:c:h") ) != -1 )
  {
    switch(c)
    {
      case 'p':
        if(optarg)
          port = atoi(optarg);
        break;

      case 'i':
        if(optarg)
          host = optarg;
        break;

      case 'c':
        if(optarg)
          command = optarg;
        break;

      case 'h':
        usage();
        return EXIT_SUCCESS;

      default:
        std::cerr << "Invalid usage. See -h for help." << std::endl;
        return EXIT_FAILURE;
    }
  }

  if ( host.empty() || command.empty() || port == -1 )
  {
    usage();
    return EXIT_FAILURE;
  }

  Logger::debug( "[dominus-client] Starting Dominus client." );

  Client client(host, port);
  client.connect();
  client.send( command );
  client.close();

  return EXIT_SUCCESS;
}
