#include "config.hpp"
#include <libconfig.h++>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <iostream>
#include <stdlib.h>
#include <devices/bme280/bme280.hpp>

Config::Config()
{
  init();
}

std::string Config::domoticz_host() const
{
  return _domoticz_host;
}

std::string Config::name() const
{
  return _name;
}

int Config::port() const
{
  return _port;
}

int Config::domoticz_port() const
{
  return _domoticz_port;
}

std::list<Device*> Config::devices() const
{
  return _devices;
}

int Config::interval() const
{
  return _interval;
}

void Config::summary() const
{
  std::cout << "Dominus:" << std::endl;
  std::cout << "  - " << _name << std::endl;
  std::cout << "  - " << _net_if << std::endl;
  std::cout << "  - " << _port << std::endl;
  std::cout << "  - " << _interval << std::endl;
  std::cout << "Domoticz:" << std::endl;
  std::cout << "  - " << _domoticz_host << std::endl;
  std::cout << "  - " << _domoticz_port << std::endl;
}

bool Config::read( const std::string &filename )
{
  init();

  libconfig::Config cfg;

  // read file
  try
  {
    cfg.readFile(filename.c_str());
  }
  catch(const libconfig::FileIOException &fioex)
  {
    std::cerr << "I/O error while reading file." << std::endl;
    return(EXIT_FAILURE);
  }
  catch(const libconfig::ParseException &pex)
  {
    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError() << std::endl;
    return EXIT_FAILURE;
  }

  // get mandatory parameters
  try
  {
    cfg.lookupValue("name", _name);
    cfg.lookupValue("port", _port);
    cfg.lookupValue("interval", _interval);
    cfg.lookupValue("interface", _net_if);
  }
  catch(const libconfig::SettingNotFoundException &nfex)
  {
    std::cerr << "A mandatory parameter is lacking." << std::endl;
    return EXIT_FAILURE;
  }

  // get devices
  const libconfig::Setting& root = cfg.getRoot();

  try
  {
    const libconfig::Setting &domo = root["domoticz"];

    domo.lookupValue("host", _domoticz_host);
    domo.lookupValue("port", _domoticz_port);
  }
  catch(const libconfig::SettingNotFoundException &nfex)
  {
    std::cerr << "Failed to read domoticz configuration." << std::endl;
    return EXIT_FAILURE;
  }

  try
  {
    const libconfig::Setting &devs = root["devices"];
    const int count = devs.getLength();

    for(int i = 0; i < count; ++i)
    {
      const libconfig::Setting &dev = devs[i];
      int dev_id;
      int dev_type;

      dev.lookupValue("type", dev_type);
      dev.lookupValue("id", dev_id);

      switch( dev_type )
      {
        case Device::BME280:
          std::string i2c_port;
          dev.lookupValue("port", i2c_port);
          BME280 *bme280 = new BME280( dev_id, i2c_port );
          _devices.push_front( bme280 );
          break;
      }
    }
  }
  catch(const libconfig::SettingNotFoundException &nfex)
  {
    std::cerr << "Failed to read devices configuration." << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void Config::init()
{
  _devices.clear();
  _name.clear();
  _port = -1;
  _net_if.clear();
  _domoticz_host.clear();
  _domoticz_port = -1;
  _interval = -1;
}

std::string Config::ip() const
{
  struct ifaddrs *ifap, *ifa;
  struct sockaddr_in *sa;
  std::string ip;

  getifaddrs (&ifap);
  for (ifa = ifap; ifa; ifa = ifa->ifa_next)
  {
    if ( (ifa->ifa_addr->sa_family==AF_INET) && (_net_if.compare( ifa->ifa_name ) == 0) )
    {
      sa = (struct sockaddr_in *) ifa->ifa_addr;
      ip = inet_ntoa(sa->sin_addr);
    }
  }

  freeifaddrs(ifap);
}
