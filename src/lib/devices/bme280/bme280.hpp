#ifndef BME280_HPP
#define BME280_HPP

#include <devices/device/device.hpp>
#include <devices/device/data.hpp>

class BME280 : public Device
{
  public:
    BME280( const int id, const std::string &port );

    // example: "i2c-1" to read "/dev/i2c-1"
    std::string port() const;

    void setCalibrationValueTemperature( const float calib_value );

    bool get( Data::THP &thp ) const;

  private:
    const std::string _port;
    const char _address;
    float _temp_calib_value;
};

#endif
