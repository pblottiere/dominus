#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <string>

class Device
{
  public:
    enum Type
    {
      BME280 = 0,
      GPIO = 1,
      UNKNOWN = 50
    };

    Device( Type type, const int id );
    virtual ~Device();

    Type type() const;

    int id() const;

  protected:
    const int _id;
    const Type _type;
};

#endif
