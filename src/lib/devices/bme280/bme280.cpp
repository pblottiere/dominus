#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>

#include <logger/logger.hpp>

#include "bme280.hpp"

BME280::BME280( const int id, const std::string &port )
  : Device( Device::BME280, id )
  , _port( port )
  , _address( 0x77 )
  , _temp_calib_value( 0.0 )
{
  Logger::debug("[bme280] Configuration:");
  Logger::debug("[bme280]   - id: " + std::to_string( id ));
  Logger::debug("[bme280]   - port: " + port);
}

std::string BME280::port() const
{
  return _port;
}

void BME280::setCalibrationValueTemperature( const float calib_value )
{
  _temp_calib_value = calib_value;
}

bool BME280::get( Data::THP &thp ) const
{
  // https://github.com/ControlEverythingCommunity/BME280
  //
  Logger::debug("[bme280] Reading data...");

  thp = {-1, -1, -1};

  // open fd descriptor
  int fd;
  char bus[BUFSIZ];
  sprintf(bus, "/dev/%s", _port.c_str());

  if((fd = open(bus, O_RDWR)) < 0)
  {
    Logger::error( "[bme280] Failed to open the bus." );
    return true;
  }

  // get I2C device
  ioctl(fd, I2C_SLAVE, _address);

  // read 24 bytes of data from register(0x88)
  unsigned char reg[1] = {0x88};
  write(fd, reg, 1);
  char b1[24] = {0};

  if(read(fd, b1, 24) != 24)
  {
    Logger::error( "[bme280] Input/Output error." );
    close(fd);
    return true;
  }

  // temperature coefficients
  int dig_T1 = (b1[0] + b1[1] * 256);
  int dig_T2 = (b1[2] + b1[3] * 256);
  if(dig_T2 > 32767)
  {
    dig_T2 -= 65536;
  }
  int dig_T3 = (b1[4] + b1[5] * 256);
  if(dig_T3 > 32767)
  {
    dig_T3 -= 65536;
  }

  // pressure coefficents
  int dig_P1 = (b1[6] + b1[7] * 256);
  int dig_P2 = (b1[8] + b1[9] * 256);
  if(dig_P2 > 32767)
  {
    dig_P2 -= 65536;
  }
  int dig_P3 = (b1[10] + b1[11] * 256);
  if(dig_P3 > 32767)
  {
    dig_P3 -= 65536;
  }
  int dig_P4 = (b1[12] + b1[13] * 256);
  if(dig_P4 > 32767)
  {
    dig_P4 -= 65536;
  }
  int dig_P5 = (b1[14] + b1[15] * 256);
  if(dig_P5 > 32767)
  {
    dig_P5 -= 65536;
  }
  int dig_P6 = (b1[16] + b1[17] * 256);
  if(dig_P6 > 32767)
  {
    dig_P6 -= 65536;
  }
  int dig_P7 = (b1[18] + b1[19] * 256);
  if(dig_P7 > 32767)
  {
    dig_P7 -= 65536;
  }
  int dig_P8 = (b1[20] + b1[21] * 256);
  if(dig_P8 > 32767)
  {
    dig_P8 -= 65536;
  }
  int dig_P9 = (b1[22] + b1[23] * 256);
  if(dig_P9 > 32767)
  {
    dig_P9 -= 65536;
  }

  // read 1 byte of data from register(0xA1)
  reg[0] = 0xA1;
  write(fd, reg, 1);
  char data[8] = {0};
  read(fd, data, 1);
  int dig_H1 = data[0];

  // Read 7 bytes of data from register(0xE1)
  reg[0] = 0xE1;
  write(fd, reg, 1);
  read(fd, b1, 7);

  // Convert the data
  // humidity coefficents
  int dig_H2 = (b1[0] + b1[1] * 256);
  if(dig_H2 > 32767)
  {
    dig_H2 -= 65536;
  }
  int dig_H3 = b1[2] & 0xFF ;
  int dig_H4 = (b1[3] * 16 + (b1[4] & 0xF));
  if(dig_H4 > 32767)
  {
    dig_H4 -= 65536;
  }
  int dig_H5 = (b1[4] / 16) + (b1[5] * 16);
  if(dig_H5 > 32767)
  {
    dig_H5 -= 65536;
  }
  int dig_H6 = b1[6];
  if(dig_H6 > 127)
  {
    dig_H6 -= 256;
  }

  // Select control humidity register(0xF2)
  // Humidity over sampling rate = 1(0x01)
  char config[2] = {0};
  config[0] = 0xF2;
  config[1] = 0x01;
  write(fd, config, 2);
  // Select control measurement register(0xF4)
  // Normal mode, temp and pressure over sampling rate = 1(0x27)
  config[0] = 0xF4;
  config[1] = 0x27;
  write(fd, config, 2);
  // Select config register(0xF5)
  // Stand_by time = 1000 ms(0xA0)
  config[0] = 0xF5;
  config[1] = 0xA0;
  write(fd, config, 2);

  // Read 8 bytes of data from register(0xF7)
  // pressure msb1, pressure msb, pressure lsb, temp msb1, temp msb, temp lsb, humidity lsb, humidity msb
  reg[0] = 0xF7;
  write(fd, reg, 1);
  read(fd, data, 8);

  // Convert pressure and temperature data to 19-bits
  long adc_p = ((long)(data[0] * 65536 + ((long)(data[1] * 256) + (long)(data[2] & 0xF0)))) / 16;
  long adc_t = ((long)(data[3] * 65536 + ((long)(data[4] * 256) + (long)(data[5] & 0xF0)))) / 16;
  // Convert the humidity data
  long adc_h = (data[6] * 256 + data[7]);

  // Temperature offset calculations
  float var1 = (((float)adc_t) / 16384.0 - ((float)dig_T1) / 1024.0) * ((float)dig_T2);
  float var2 = ((((float)adc_t) / 131072.0 - ((float)dig_T1) / 8192.0) *
      (((float)adc_t)/131072.0 - ((float)dig_T1)/8192.0)) * ((float)dig_T3);
  float t_fine = (long)(var1 + var2);
  float cTemp = (var1 + var2) / 5120.0;
  float fTemp = cTemp * 1.8 + 32;

  // Pressure offset calculations
  var1 = ((float)t_fine / 2.0) - 64000.0;
  var2 = var1 * var1 * ((float)dig_P6) / 32768.0;
  var2 = var2 + var1 * ((float)dig_P5) * 2.0;
  var2 = (var2 / 4.0) + (((float)dig_P4) * 65536.0);
  var1 = (((float) dig_P3) * var1 * var1 / 524288.0 + ((float) dig_P2) * var1) / 524288.0;
  var1 = (1.0 + var1 / 32768.0) * ((float)dig_P1);
  float p = 1048576.0 - (float)adc_p;
  p = (p - (var2 / 4096.0)) * 6250.0 / var1;
  var1 = ((float) dig_P9) * p * p / 2147483648.0;
  var2 = p * ((float) dig_P8) / 32768.0;
  float pressure = (p + (var1 + var2 + ((float)dig_P7)) / 16.0) / 100;

  // Humidity offset calculations
  float var_H = (((float)t_fine) - 76800.0);
  var_H = (adc_h - (dig_H4 * 64.0 + dig_H5 / 16384.0 * var_H)) * (dig_H2 / 65536.0 * (1.0 + dig_H6 / 67108864.0 * var_H * (1.0 + dig_H3 / 67108864.0 * var_H)));
  float humidity = var_H * (1.0 -  dig_H1 * var_H / 524288.0);
  if(humidity > 100.0)
  {
    humidity = 100.0;
  }
  else if(humidity < 0.0)
  {
    humidity = 0.0;
  }

  thp.humidity = humidity;
  thp.pressure = pressure;
  thp.temperature = cTemp + _temp_calib_value;

  if ( _temp_calib_value != 0.0 )
  {
    const std::string msg = "[bme280] Calibrate temperature: " + std::to_string(cTemp) + " -> " + std::to_string(thp.temperature);
    Logger::debug(msg);
  }

  close(fd);

  return false;
}
