#ifndef DHT11_HPP
#define DHT11_HPP

#include <devices/gpio/gpio.hpp>
#include <devices/device/data.hpp>

class DHT11 : public GPIO
{
    public:
        DHT11( int id, int port );

        bool get( Data::TH &th ) const;

    private:
        const int _maxtimings;
};

#endif
