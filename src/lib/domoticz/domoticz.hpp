#ifndef DOMOTICZ_HPP
#define DOMOTICZ_HPP

#include <string>
#include <curl/curl.h>

class Domoticz
{
  public:
    Domoticz( const std::string &host, const int port );

    bool update_temp_hum( const int device, const float temp,
                          const float hum );

  private:
    bool send( const std::string &message );

    std::string _host;
    int _port;
};

#endif
