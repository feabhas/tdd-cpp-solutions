/** @file temperature_sensor.h
    \brief API for the abstracted Temperature Sensor module.
*/
#ifndef _TEMPERATURE_SENSOR_H
#define _TEMPERATURE_SENSOR_H

namespace Sensor
{
  class Ds1820;
}

namespace Display
{
  class IDisplay;
}

class Temperature_sensor {
public:
  enum class status { ok, sensor_failure, display_failure };
  Temperature_sensor(Display::IDisplay&, Sensor::Ds1820&);
  ~Temperature_sensor() = default;
  /*! \fn void Temperture_sensor::initialize()
  \brief Perform initialization of the sensor and display
  \return whether the initialization was successful.
  */
  status initialize();
  /*! \fn void Temperture_sensor::run()
  \brief Perform the reading of the raw temperature sensor and displays the
  value \return whether the reading and conversion of the temperature was
  successful.
    */
  status run();

private:
  Display::IDisplay* display{};
  Sensor::Ds1820*    sensor{};
};

#endif // _TEMPERATURE_SENSOR_H
