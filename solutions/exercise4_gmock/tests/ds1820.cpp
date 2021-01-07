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
#include "ds1820.h"

namespace Sensor
{
  Ds1820::Ds1820(Resolution resolution) : mask{ resolution } {};

  float Ds1820::convert(uint16_t digital)
  {
    digital &= static_cast<uint16_t>(mask);
    int16_t s_digital = digital;
    return s_digital / 16.0f;
  }

  ROM_t Ds1820::read_rom()
  {
    ROM_t data = {
      0x28,
      { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6 },
      0x00,
    }; //!OCLINT
    return data;
  }

  void Ds1820::do_conversion() {}

  bool Ds1820::read_scratchpad(scratchpad_data_t* const data)
  {
    // default values
    data->lsb = 0x50;
    data->msb = 0x05;
    data->crc = 0;
    return true;
  }

  uint8_t Ds1820::calculate_CRC(const uint8_t* data, uint32_t num_of_bytes)
  {
    (void)data;
    (void)num_of_bytes;
    return 0;
  }

} // namespace