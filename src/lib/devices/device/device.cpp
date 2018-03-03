#include "device.hpp"

Device::Device( const Type type, const int id)
  : _id( id )
  , _type( type )
{
};

Device::Type Device::type() const
{
  return _type;
}

int Device::id() const
{
  return _id;
}
