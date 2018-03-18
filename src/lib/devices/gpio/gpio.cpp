#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "gpio.hpp"
#include <logger/logger.hpp>

GPIO::GPIO( const int id, const int port )
    : Device( Device::GPIO, id )
    , _port( port )
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

    Logger::debug("[gpio] Configuration:");
    Logger::debug("[gpio]   - id: " + std::to_string( id ));
    Logger::debug("[gpio]   - port: " + std::to_string( _port) );
}

GPIO::GPIO( const int port )
    : GPIO( -1, port )
{
}

int GPIO::value() const
{
    return 0; // TODO
}

int GPIO::setValue( const int status )
{
    int fd;
    const std::string path = _path + "value";
    if ((fd = open(path.c_str(), O_WRONLY)) < 0)
    {
        Logger::error("[gpio] Error when opening file");
        return 1;
    }

    const std::string value = std::to_string( status );

    Logger::debug("[gpio] Set value " + value);

    write(fd, value.c_str(), value.size());
    close(fd);

    return 0;
}

GPIO::Direction GPIO::direction() const
{
    return GPIO::IN; // TODO
}

int GPIO::setDirection( const Direction direction )
{
    int fd;
    const std::string path = _path + "direction";
    if ((fd = open(path.c_str(), O_WRONLY)) < 0)
    {
        Logger::error("[gpio] Error when opening file");
        return 1;
    }

    std::string dir = "in";
    if ( direction == GPIO::Direction::OUT )
    {
        dir = "out";
    }

    Logger::debug("[gpio] Set direction " + dir);;

    write(fd, dir.c_str(), dir.size());
    close(fd);

    return 0;
}
