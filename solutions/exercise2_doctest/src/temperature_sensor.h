/** @file temperature_sensor.h 
    \brief API for the abstracted Temperature Sensor module.
*/
#ifndef _TEMPERATURE_SENSOR_H
#define _TEMPERATURE_SENSOR_H

#include "ds1820.h"
#include "lcd.h"

class Temperature_sensor {
public:
  Temperature_sensor(Display::Lcd& lcd_, DS18B20::Ds1820& sensor_);
  ~Temperature_sensor() = default;
  /*! \fn void Temperture_sensor::run(void)
    \brief Perform the reading of the raw temperature sensor and displays the value
    */ 
    void run();
private:
    Display::Lcd* lcd;
    DS18B20::Ds1820* sensor;
};

#endif // _TEMPERATURE_SENSOR_H
