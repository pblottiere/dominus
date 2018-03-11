#include <domoticz/domoticz.hpp>
#include <devices/bme280/bme280.hpp>
#include <devices/device/config.hpp>
#include <net/server.hpp>
#include <logger/logger.hpp>

#include <unistd.h>
#include <iostream>

int main( int argc, char * argv[] )
{
  Logger::debug( "[dominus-server] Starting Dominus server." );
  std::string filename;
  char c;

  while( ( c = getopt (argc, argv, "c:") ) != -1 )
  {
    switch(c)
    {
      case 'c':
        if(optarg)
          filename = optarg;
        break;
    }
  }

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
