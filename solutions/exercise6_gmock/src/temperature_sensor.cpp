#include "temperature_sensor.h"

#include "IDisplay.h"
#include "ISensor.h"
using namespace Sensor;
using namespace Display;

#include <cstdio>
#include <cstring>

#include <iomanip>
#include <iostream>
#include <string>
#include <strstream>
using namespace std;

Temperature_sensor::Temperature_sensor(IDisplay& IDisplay_, ISensor& sensor_) :
  display{ &IDisplay_ }, sensor{ &sensor_ }
{
}

// a.  Initialize the DS18B20 to be configurable for 9, 10, 11 or 12-bit
// resolution b.  Read ROM c.  assert ROM CRC value d.  On a IDisplay display
// print out ROM's Family Code and Serial number values
Temperature_sensor::status Temperature_sensor::initialize()
{
  int count = display->display(sensor->family_code().c_str());
  if (count == -1) {
    return status::display_failure;
  }

  count = display->display(sensor->serial_number().c_str());

  if (count == -1) {
    // display display error
    return status::display_failure;
  }
  return status::ok;
}

Temperature_sensor::status Temperature_sensor::run()
{
  const float deg_C = sensor->lastest_reading();
  if ((deg_C < -55.0f) || (deg_C > 125.0f)) {
    // Out of range error
    return status::sensor_failure;
  }

  char buff[20] = {};
  sprintf(buff, "%02.2fC", deg_C);

  const int count = display->display(buff);

  if (count == -1) {
    return status::display_failure;
  }
  return status::ok;
}
