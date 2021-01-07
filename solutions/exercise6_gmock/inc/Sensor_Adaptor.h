/**
 * @file Sensor_Adaptor.h
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
#ifndef _Sensor_Adaptor_h_
#define _Sensor_Adaptor_h_

#include "ISensor.h"
#include "ds1820.h"

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
}

#endif