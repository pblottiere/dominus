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

    enum Lib
    {
      SYSFS,
      WIRING_PI
    };

    GPIO( int id, int port, const std::string &name = "gpio", Lib lib = Lib::SYSFS );
    GPIO( int port, const std::string &name = "gpio", Lib lib = Lib::SYSFS );

    int port() const;

    int value() const;
    bool setValue( int status ) const;

    Direction direction() const;
    bool setDirection( Direction direction ) const;

  protected:
    const int _port;

  private:
    void initSysfs();
    int valueSysfs() const;
    bool setValueSysfs( int status ) const;
    Direction directionSysfs() const;
    bool setDirectionSysfs( Direction direction ) const;

    void initWiringPi() const;
    int valueWiringPi() const;
    bool setValueWiringPi( int status ) const;
    Direction directionWiringPi() const;
    bool setDirectionWiringPi( Direction direction ) const;

    bool _valid;
    std::string _path;
    const Lib _lib;
    const std::string _name;
};

#endif
