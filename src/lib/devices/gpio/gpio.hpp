#ifndef GPIO_HPP
#define GPIO_HPP

#include "devices/device/device.hpp"

class GPIO : public Device
{
  public:
    enum Direction
    {
      IN,
      OUT
    };

    GPIO( const int id, const int port );
    GPIO( const int port );

    int port() const;

    int value() const;
    int setValue( const int status );

    Direction direction() const;
    int setDirection( const Direction direction );

  private:
    bool _valid;
    std::string _path;
    const int _port;
};

#endif
