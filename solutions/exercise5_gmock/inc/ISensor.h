/** @file ISesnor.h
    \brief API for the ISesnor Interface.
*/
#ifndef _ISENSOR_H
#define _ISENSOR_H

#include <string>

namespace Sensor
{
  class ISensor {
  public:
    virtual std::string family_code()     = 0;
    virtual std::string serial_number()   = 0;
    virtual float       lastest_reading() = 0;
    virtual ~ISensor()                    = default;
  };
} // namespace

#endif // _ISENSOR_H
