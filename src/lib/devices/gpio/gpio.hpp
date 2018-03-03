#ifndef GPIO_HPP
#define GPIO_HPP

#include "devices/device/device.hpp"

class GPIO : public Device
{
  enum Direction
  {
    IN,
    OUT
  };

  public:
    GPIO( const int id, const int port );

    int port() const;

    int value() const;
    void setValue( const int status );

    Direction direction() const;
    void setDirection( const Direction direction );

  private:
    bool _valid;
    const int _port;
};

#endif
