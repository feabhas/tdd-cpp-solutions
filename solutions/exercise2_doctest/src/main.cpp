#include <iostream>

#include "ds1820.h"
#include "lcd.h"
#include "temperature_sensor.h"
using namespace DS18B20;
using namespace Display;

int main()
{
  std::cout << "starting main...\n";
  DS18B20::Ds1820 sensor{};
  Display::Lcd    display{};

  Temperature_sensor test_obj{ display, sensor };

  test_obj.run();
  std::cout << "main complete...\n";
}
