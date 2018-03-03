#include <cstdio>
#include <iostream>

#include "domoticz.hpp"

Domoticz::Domoticz( const std::string &host, const int port )
  : _host( host )
  , _port( port )
{
}

bool Domoticz::update_temp_hum( const int device, const float temp,
                                const float hum )
{
  // https://www.domoticz.com/wiki/Domoticz_API/JSON_URL%27s#Temperature.2Fhumidity
  char update[BUFSIZ];

  int hum_status = 0;
  if ( (hum > 45.5) && ( hum < 65.0 ) )
  {
    hum_status = 1; // comfortable
  }
  else if ( hum < 45.5 )
  {
    hum_status = 2; // dry
  }
  else // > 65.0
  {
    hum_status = 3; // wet
  }

  sprintf(update,
          "type=command&param=udevice&idx=%d&nvalue=0&svalue=%0.1f;%0.1f;%d",
          device, temp, hum, hum_status);

  return send(update);
}

bool Domoticz::send( const std::string &data )
{
  char message[BUFSIZ];
  sprintf(message, "%s:%d/json.htm?%s", _host.c_str(), _port, data.c_str());

  CURLcode res;
  curl_global_init(CURL_GLOBAL_ALL);
  CURL *curl = curl_easy_init();

  std::cout << message << std::endl;

  if ( curl )
  {
    curl_easy_setopt(curl, CURLOPT_URL, message);
    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
    {
      fprintf(stderr, "curl_easy_perform() failed: %s (%s)\n",
          curl_easy_strerror(res), message);
      return EXIT_FAILURE;
    }

    curl_easy_cleanup(curl);
  }
  else
  {
    curl_global_cleanup();
    fprintf(stderr, "Failed to init CURL");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
