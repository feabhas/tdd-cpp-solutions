#include "temperature_sensor.h"

#include "IDisplay.h"
#include "ds1820.h"
using namespace Sensor;
using namespace Display;

#include <cstdio>
#include <cstring>

#include <iomanip>
#include <iostream>
#include <string>
#include <strstream>
using namespace std;

Temperature_sensor::Temperature_sensor(IDisplay& IDisplay_, Ds1820& sensor_) :
  display{ &IDisplay_ }, sensor{ &sensor_ }
{
}

// a.  Initialize the DS18B20 to be configurable for 9, 10, 11 or 12-bit
// resolution b.  Read ROM c.  assert ROM CRC value d.  On a IDisplay display
// print out ROM's Family Code and Serial number values
Temperature_sensor::status Temperature_sensor::initialize()
{
  const ROM_t   rom_data = sensor->read_rom();
  const uint8_t crc =
    sensor->calculate_CRC(reinterpret_cast<const uint8_t*>(&rom_data), 7);

  if (rom_data.rom_code.crc != crc) {
    return status::sensor_failure;
  }

  if (rom_data.rom_code.family_code != 0x28) {
    return status::sensor_failure;
  }

  strstream family_code{}; // dynamic buffer
  family_code << "Family code: 0x" << hex
              << static_cast<uint32_t>(rom_data.rom_code.family_code) << ends;

  int count = display->display(family_code.str());
  if (count == -1) {
    // display display error
    return status::display_failure;
  }

  strstream serial_number{}; // dynamic buffer
  serial_number << "Serial Number: ";
  serial_number << hex;
  serial_number << setfill('0') << setw(2)
                << static_cast<uint32_t>(rom_data.rom_code.serial_number[5]);
  serial_number << ":";
  serial_number << setfill('0') << setw(2)
                << static_cast<uint32_t>(rom_data.rom_code.serial_number[4]);
  serial_number << ":";
  serial_number << setfill('0') << setw(2)
                << static_cast<uint32_t>(rom_data.rom_code.serial_number[3]);
  serial_number << ":";
  serial_number << setfill('0') << setw(2)
                << static_cast<uint32_t>(rom_data.rom_code.serial_number[2]);
  serial_number << ":";
  serial_number << setfill('0') << setw(2)
                << static_cast<uint32_t>(rom_data.rom_code.serial_number[1]);
  serial_number << ":";
  serial_number << setfill('0') << setw(2)
                << static_cast<uint32_t>(rom_data.rom_code.serial_number[0]);
  serial_number << ends;

  count = display->display(serial_number.str());

  if (count == -1) {
    // display display error
    return status::display_failure;
  }
  return status::ok;
}

// a.  Instruct the DS18B20 to do a conversion
// b.  Read the Scratchpad
// c.  assert Scratchpad data CRC
// d.  Convert 16-bit raw temperature to floating point degree C
// e.  Convert float to C-string format <nn.nnC>
// f.  Call display display to print C-string value
Temperature_sensor::status Temperature_sensor::run()
{
  sensor->do_conversion();
  scratchpad_data_t scratchpad{};

  const bool okay = sensor->read_scratchpad(&scratchpad);
  if (!okay) {
    return status::sensor_failure;
  }

  const uint8_t crc = sensor->calculate_CRC(
    reinterpret_cast<const uint8_t*>(&scratchpad), sizeof(scratchpad) - 1);

  if (scratchpad.crc != crc) {
    return status::sensor_failure;
  }

  const uint16_t raw_sensor_temp = ((scratchpad.msb << 8) | scratchpad.lsb);

  const float deg_C = sensor->convert(raw_sensor_temp);
  if ((deg_C < -55.0f) || (deg_C > 125.0f)) {
    // Out of range error
    return status::sensor_failure;
  }

  char buff[20] = {};
  sprintf(buff, "%02.2fC", deg_C);

  const int count = display->display(buff);

  if (count == -1) {
    // display display error
    return status::display_failure;
  }
  return status::ok;
}
