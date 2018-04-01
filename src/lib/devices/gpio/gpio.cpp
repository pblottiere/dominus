#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "gpio.hpp"
#include <logger/logger.hpp>
#include <config.h>

#ifdef WIRINGPI
#include <wiringPi.h>
#endif

GPIO::GPIO( const int id, const int port, const std::string &name, const Lib lib )
    : Device( Device::GPIO, id )
    , _port( port )
    , _lib( lib )
    , _name( name )
{
    Logger::debug("[" + _name + "] Configuration:");
    Logger::debug("[" + _name + "]   - id: " + std::to_string( id ));
    Logger::debug("[" + _name + "]   - port: " + std::to_string( _port) );

    switch( _lib )
    {
        case Lib::SYSFS:
            initSysfs();
            Logger::debug("[" + _name + "]   - lib: SYSFS");
            break;
        case Lib::WIRING_PI:
            initWiringPi();
            Logger::debug("[" + _name + "]   - lib: WIRINGPI");
            break;
        default:
            break;
    }
}

GPIO::GPIO( const int port, const std::string &name, const Lib lib )
    : GPIO( -1, port, name, lib )
{
}

int GPIO::value() const
{
    int value = -1;

    switch( _lib )
    {
        case Lib::SYSFS:
            value = valueSysfs();
            break;
        case Lib::WIRING_PI:
            value = valueWiringPi();
            break;
        default:
            break;
    }

    return value;
}

bool GPIO::setValue( const int status ) const
{
    bool rc = true;

    switch( _lib )
    {
        case Lib::SYSFS:
            rc = setValueSysfs( status );
            break;
        case Lib::WIRING_PI:
            rc = setValueWiringPi( status );
        default:
            break;
    }

    return rc;
}

GPIO::Direction GPIO::direction() const
{
    GPIO::Direction dir = GPIO::OUT;

    switch( _lib )
    {
        case Lib::SYSFS:
            dir = directionSysfs();
            break;
        case Lib::WIRING_PI:
            dir = directionWiringPi();
            break;
        default:
            break;
    }

    return dir;
}

bool GPIO::setDirection( const Direction direction ) const
{
    bool rc = true;

    switch( _lib )
    {
        case Lib::SYSFS:
            rc = setDirectionSysfs( direction );
            break;
        case Lib::WIRING_PI:
            rc = setDirectionWiringPi( direction );
            break;
        default:
            break;
    }

    return rc;
}

void GPIO::initSysfs()
{
    int fd;
    if ((fd = open("/sys/class/gpio/export", O_WRONLY)) >= 0)
    {
        const std::string sport = std::to_string(_port);
        write(fd, sport.c_str(), sport.size());
        close(fd);

        _valid = true;

        _path = "/sys/class/gpio/gpio" + std::to_string(_port) + "/";
    }
    else
    {
        _valid = false;
    }
}

int GPIO::valueSysfs() const
{
    return -1;
}

bool GPIO::setValueSysfs( const int status ) const
{
    int fd;
    const std::string path = _path + "value";
    if ((fd = open(path.c_str(), O_WRONLY)) < 0)
    {
        Logger::error("[" + _name + "] Error when opening file");
        return 1;
    }

    const std::string value = std::to_string( status );

    Logger::debug("[" + _name + "] Set value " + value);

    write(fd, value.c_str(), value.size());
    close(fd);

    return 0;
}

GPIO::Direction GPIO::directionSysfs() const
{
    return GPIO::OUT;
}

bool GPIO::setDirectionSysfs( Direction direction ) const
{
    int fd;
    const std::string path = _path + "direction";
    if ((fd = open(path.c_str(), O_WRONLY)) < 0)
    {
        Logger::error("[" + _name + "] Error when opening file");
        return 1;
    }

    std::string dir = "in";
    if ( direction == GPIO::Direction::OUT )
    {
        dir = "out";
    }

    Logger::debug("[" + _name + "] Set direction " + dir);;

    write(fd, dir.c_str(), dir.size());
    close(fd);

    return 0;
}

void GPIO::initWiringPi() const
{
#ifdef WIRINGPI
    wiringPiSetup();
#endif
}

int GPIO::valueWiringPi() const
{
    return -1;
}

bool GPIO::setValueWiringPi( const int status ) const
{
#ifdef WIRINGPI
    if ( status <= 0 )
        digitalWrite(_port, LOW);
    else
        digitalWrite(_port, HIGH);
#endif

    return false;
}

GPIO::Direction GPIO::directionWiringPi() const
{
    return GPIO::OUT;
}

bool GPIO::setDirectionWiringPi( const Direction direction ) const
{
#ifdef WIRINGPI
    if ( direction == GPIO::OUT )
        pinMode (_port, OUTPUT) ;
    else
        pinMode (_port, INPUT) ;
#endif

    return false;
}
