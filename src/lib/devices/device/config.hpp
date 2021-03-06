#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <list>
#include "device.hpp"

class Config
{
  public:
    Config();

    bool read( const std::string &filename );

    std::string domoticz_host() const;

    int domoticz_port() const;

    int port() const;

    std::string name() const;

    int interval() const;

    std::string interface() const;

    std::list<Device*> devices() const;

    std::string ip() const;

  private:
    void init();

    int _port;
    int _interval;
    std::string _net_if;
    std::string _name;
    std::string _domoticz_host;
    int _domoticz_port;
    std::list<Device*> _devices;
};

#endif
