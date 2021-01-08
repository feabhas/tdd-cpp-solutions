/**
 * @file ds1820.cpp
 * @author Feabhas Limited (training@feabhas.com)
 * @brief
 * @version 0.1
 * @date 2019-02-22
 *
 * @copyright Copyright (c) 2019
 *
 * @custom
 * DISCLAIMER
 * Feabhas is furnishing this item 'as is'. Feabhas does not provide any
 * warranty of the item whatsoever, whether express, implied, or statutory,
 * including, but not limited to, any warranty of merchantability or fitness
 * for a particular purpose or any warranty that the contents of the item will
 * be error-free.
 * In no respect shall Feabhas incur any liability for any damages, including,
 * but limited to, direct, indirect, special, or consequential damages arising
 * out of, resulting from, or any way connected to the use of the item, whether
 * or not based upon warranty, contract, tort, or otherwise; whether or not
 * injury was sustained by persons or property or otherwise; and whether or not
 * loss was sustained from, or arose out of, the results of, the item, or any
 * services that may be provided by Feabhas.
 */
#include "ISensor.h"
#include "ds1820.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <strstream>
using namespace std;

namespace Sensor
{
  class Sensor_Adaptor : public ISensor {
  public:
    Sensor_Adaptor()  = default;
    ~Sensor_Adaptor() = default;
    std::string family_code() override;
    std::string serial_number() override;
    float       lastest_reading() override;

  private:
    Ds1820 concrete_sensor{};
    ROM_t  rom_data{};
  };

  std::string Sensor_Adaptor::family_code()
  {
    rom_data          = concrete_sensor.read_rom();
    const uint8_t crc = concrete_sensor.calculate_CRC(
      reinterpret_cast<const uint8_t*>(&rom_data), 7);

    if (rom_data.rom_code.crc != crc) {
      // return status::sensor_failure;
      return std::string{};
    }

    if (rom_data.rom_code.family_code != 0x28) {
      // return status::sensor_failure;
      return std::string{};
    }

    strstream code{}; // dynamic buffer
    code << "Family code: 0x" << hex
         << static_cast<uint32_t>(rom_data.rom_code.family_code) << ends;
    return code.str();
  }

  std::string Sensor_Adaptor::serial_number()
  {
    strstream number{}; // dynamic buffer
    number << "Serial Number: ";
    number << hex;
    number << setfill('0') << setw(2)
           << static_cast<uint32_t>(rom_data.rom_code.serial_number[5]);
    number << ":";
    number << setfill('0') << setw(2)
           << static_cast<uint32_t>(rom_data.rom_code.serial_number[4]);
    number << ":";
    number << setfill('0') << setw(2)
           << static_cast<uint32_t>(rom_data.rom_code.serial_number[3]);
    number << ":";
    number << setfill('0') << setw(2)
           << static_cast<uint32_t>(rom_data.rom_code.serial_number[2]);
    number << ":";
    number << setfill('0') << setw(2)
           << static_cast<uint32_t>(rom_data.rom_code.serial_number[1]);
    number << ":";
    number << setfill('0') << setw(2)
           << static_cast<uint32_t>(rom_data.rom_code.serial_number[0]);
    number << ends;

    return number.str();
  }

  float Sensor_Adaptor::lastest_reading()
  {
    concrete_sensor.do_conversion();
    scratchpad_data_t scratchpad{};

    const bool okay = concrete_sensor.read_scratchpad(&scratchpad);
    if (!okay) {
      // return status::sensor_failure;
    }

    const uint8_t crc = concrete_sensor.calculate_CRC(
      reinterpret_cast<const uint8_t*>(&scratchpad), sizeof(scratchpad) - 1);

    if (scratchpad.crc != crc) {
      // return status::sensor_failure;
    }

    const uint16_t raw_sensor_temp = ((scratchpad.msb << 8) | scratchpad.lsb);

    return concrete_sensor.convert(raw_sensor_temp);
  }

} // namespace Sensor