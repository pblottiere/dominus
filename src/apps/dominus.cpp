#include <domoticz/domoticz.hpp>
#include <devices/bme280/bme280.hpp>
#include <devices/device/config.hpp>
#include <unistd.h>
#include <iostream>

int main( int argc, char * argv[] )
{
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

  if ( ! config.read( filename ) )
  {
    config.summary();

    std::list<Device*> devices = config.devices();
    Domoticz domo( config.domoticz_host(), config.domoticz_port() );

    while(1)
    {
      for ( auto it = devices.begin(); it != devices.end(); it++)
      {
        switch( (*it)->type() )
        {
          case Device::BME280:
            BME280 *bme280 = dynamic_cast<BME280 *>(*it);
            Data::THP thp = bme280->get();

            if ( thp.temperature != -1 && thp.humidity != -1 )
            {
              domo.update_temp_hum( bme280->id(), thp.temperature, thp.humidity );
            }
            break;
        }
      }

      sleep(config.interval());
    }
  }

  return 0;
}
