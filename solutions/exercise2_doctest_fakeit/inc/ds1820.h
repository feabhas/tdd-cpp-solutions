/**
 * @file ds1820.h
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
#ifndef _ds1820_h_
#define _ds1820_h_

#include <cstdint>

/*! \struct ds18b20_scratchpad_data_t
    \brief Structure for storing the returned DS18B20 scratchpad data.
*/
namespace Sensor
{
  struct scratchpad_data_t
  {
    uint8_t lsb;         //!< least-significant byte of temperature
    uint8_t msb;         //!< most-significant byte of temperature
    uint8_t Th;          //!< High alarm trigger value
    uint8_t Tl;          //!< Low alarm trigger value
    uint8_t config_reg;  //!< Configuration register
    uint8_t reserved[3]; //!< reserved
    uint8_t crc;         //!< Cyclic Redundancy Check
  };

  /*! \union ds18b20_ROM_t
      \brief Union for storing the ROM values

      The 64-bytes of data can either byte access or struct access.
  */
  union ROM_t
  {
    struct
    {
      uint8_t family_code;      //!< Family code (```0x28```)
      uint8_t serial_number[6]; //!< Serial number (```00:00:00:00:00:00```)
      uint8_t crc;              //!< Cyclic Redundancy Check
    } rom_code;
    uint8_t bytes[8]; //!< raw byte access of 64-bits of data
  };

  class Ds1820 {
  public:
    /**
     *  Defines the DS18B20 Temperature Sensor Resolution
     */
    enum class Resolution : std::uint16_t {
      R9  = static_cast<std::uint16_t>(~1U), /**<  9-bit Resolution */
      R10 = static_cast<std::uint16_t>(~3U), /**< 10-bit Resolution */
      R11 = static_cast<std::uint16_t>(~7U), /**< 11-bit Resolution */
      R12 = static_cast<std::uint16_t>(~0U)  /**< 12-bit Resolution */
    };

    explicit Ds1820(Resolution resolution = Resolution::R12);

    ~Ds1820() = default;

    /*! \fn float Ds1820::convert(std::uint16_t digital)
      \brief Converts the signed 12.4 fixed point representation to degC.
      \param[in] digital The 16-bit raw temperature reading in signed 12.4
      \return The temperature converted to degrees Centigrade.
    */
    float convert(std::uint16_t reading);
    /*! \fn Ds18b20::ROM_t ds18b20_read_rom()
      \brief Read ROM
      \return 64-bits of data as type ```DS18B20::ROM_t```
    */
    ROM_t read_rom();
    /*! \fn void Ds18b20::do_conversion()
        \brief Initiate Temperature Conversion - blocks until conversion
       complete
    */
    void do_conversion();
    /*! \fn bool Ds18b20::read_scratchpad(ds18b20_scratchpad_data_t * const
       data) \brief Reads the DS18B20 Scratchpad data \param data[out] the
       current contents pf the device scartchpad \return ```true``` if read
       successful
    */
    bool read_scratchpad(scratchpad_data_t* const data);
    /*! \fn uint8_t Ds18b20::calculate_CRC(const uint8_t* data, uint32_t
       num_of_bytes) \brief Compute CRC using CRC = X^8 + X^5 + X^4 + 1 \param
       data[in] takes N-bytes of data \param num_of_bytes[in] the number of
       bytes for the CRC to use in calculation \return CRC value
    */
    uint8_t calculate_CRC(const uint8_t* const data, uint32_t num_of_bytes);

  private:
    Resolution mask;
  };

} // namespace
#endif /* _ds1820_h_ */
