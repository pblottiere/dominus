#include <domoticz/domoticz.hpp>
#include <devices/bme280/bme280.hpp>
#include <devices/device/config.hpp>
#include <net/server.hpp>
#include <logger/logger.hpp>

#include <unistd.h>
#include <iostream>

void usage()
{
  std::cout << "Usage: dominus-server [OPTIONS]" << std::endl;
  std::cout << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << std::endl;
  std::cout << "  -c=dominus.cfg        Configuration file" << std::endl;
  std::cout << "  -h                    Help" << std::endl;
}

int main( int argc, char * argv[] )
{
  std::string filename;
  char c;
  bool done = false;

  while( !done && ( c = getopt (argc, argv, "c:h") ) != -1 )
  {
    switch(c)
    {
      case 'c':
        if(optarg)
          filename = optarg;
        break;

      case 'h':
        usage();
        return EXIT_SUCCESS;

      default:
        done = true;
        break;
    }
  }

  if ( filename.empty() )
  {
    usage();
    return EXIT_FAILURE;
  }

  Logger::debug( "[dominus-server] Starting Dominus server." );

  Config config;

  if ( config.read( filename ) )
  {
    Logger::error( "[dominus-server] Error during configuration file reading." );
    return EXIT_FAILURE;
  }

  Logger::debug( "[dominus-server] Configuration:" );
  Logger::debug( "[dominus-server]   - name: " + config.name() );
  Logger::debug( "[dominus-server]   - interface: " + config.interface() );
  Logger::debug( "[dominus-server]   - ip: " + config.ip() );
  Logger::debug( "[dominus-server]   - interval: " + std::to_string(config.interval()) + " secs" );

  std::list<Device*> devices = config.devices();
  Domoticz domo( config.domoticz_host(), config.domoticz_port() );
  Server server( config.port() );
  server.bind();

  std::string command;
  while(1)
  {
    if ( server.wait( config.interval(), command ) == EXIT_SUCCESS )
    {
      if ( ! command.empty() )
      {
        std::cout << "COMMAND: " << command << std::endl;
      }
      else
      {
        for ( auto it = devices.begin(); it != devices.end(); it++)
        {
          switch( (*it)->type() )
          {
            case Device::BME280:
              BME280 *bme280 = dynamic_cast<BME280 *>(*it);
              Data::THP thp;

              if ( ! bme280->get( thp ) )
              {
                domo.update_temp_hum( bme280->id(), thp.temperature, thp.humidity );
              }
              break;
          }
        }
      }
    }
  }

  return EXIT_SUCCESS;
}
