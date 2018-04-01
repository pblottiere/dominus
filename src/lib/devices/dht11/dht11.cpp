#include "dht11.hpp"
#include <logger/logger.hpp>
#include <wiringPi.h>

DHT11::DHT11( int id, int port )
    : GPIO( id, port, "dht11", GPIO::WIRING_PI )
    , _maxtimings( 85 )
{
    _type = Device::DHT11;
    setDirection(GPIO::IN);
}

bool DHT11::get( Data::TH &th ) const
{
    // see
    // https://github.com/sunfounder/Sunfounder_SensorKit_C_code_for_RaspberryPi

    bool rc = false;

    uint8_t laststate = HIGH;
    uint8_t counter = 0;
    uint8_t j = 0, i;
    float f; // fahrenheit

    int dht11_dat[5] = { 0, 0, 0, 0, 0 };
    dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

    // pull pin down for 18 milliseconds
    pinMode(_port, OUTPUT);
    digitalWrite(_port, LOW);
    delay(18);

    // then pull it up for 40 microseconds
    digitalWrite(_port, HIGH);
    delayMicroseconds(40);

    // prepare to read the pin
    pinMode(_port, INPUT);

    // detect change and read data
    for ( i=0; i< _maxtimings; i++)
    {
        counter = 0;
        while (digitalRead(_port) == laststate)
        {
            counter++;
            delayMicroseconds(1);
            if (counter == 255) {
                break;
            }
        }
        laststate = digitalRead(_port);

        if (counter == 255) break;

        // ignore first 3 transitions
        if ((i >= 4) && (i%2 == 0)) {
            // shove each bit into the storage bytes
            dht11_dat[j/8] <<= 1;
            if (counter > 16)
                dht11_dat[j/8] |= 1;
            j++;
        }
    }

    // check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
    // print it out if data is good
    if ((j >= 40) &&
            (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF)) ) {
        // f = dht11_dat[2] * 9. / 5. + 32;

        char hum[256];
        sprintf(hum, "%d.%d", dht11_dat[0], dht11_dat[1]);

        char temp[256];
        sprintf(temp, "%d.%d", dht11_dat[2], dht11_dat[3]);

        th.humidity = atof(hum);
        th.temperature = atof(temp);
    }
    else
    {
        Logger::error("[dht11] Invalid data.");
        rc = true;
    }

    return rc;
}
