#include "temperature_sensor.h"
using namespace DS18B20;
using namespace Display;

#include "doctest.h"

#include <cassert>
#include <cstdio>
#include <cstring>

#include <string>
#include <iostream>
#include <strstream>
#include <iomanip>
using namespace std;
// #include <array>

// a.  Initialize the DS18B20 to be configurable for 9, 10, 11 or 12-bit resolution
// b.  Read ROM
// c.  Check ROM CRC value
// d.  On a LCD display print out ROM's Family Code and Serial number values
Temperature_sensor::Temperature_sensor(Lcd& lcd_, Ds1820& sensor_):
lcd{&lcd_},
sensor{&sensor_}
{  
    const ROM_t rom_data = sensor->read_rom();
    const uint8_t crc = sensor->calculate_CRC((uint8_t*)&rom_data, 7);

    if(rom_data.rom_code.crc != crc){
        // TODO : work out how to fail?
        // should we have a return code?
        return;
    }

    CHECK(rom_data.rom_code.family_code == 0x28);

    // char buff[40] = {};
    // sprintf(buff, "Family code: 0x%02X", rom_data.rom_code.family_code);

    strstream family_code; // dynamic buffer
    family_code << "Family code: 0x" << hex << static_cast<uint32_t>(rom_data.rom_code.family_code) << ends;

    int count = lcd->display(family_code.str());  
    if(count == -1) {
        // LCD display error
        return;
    }

    // buff.fill(0);
    // const int num = sprintf(buff, "Serial Number: ");
    // for (uint32_t i = 6, offset = 0; i != 0; --i) {
    //     int xnum = sprintf((buff+(num+offset)), "%02X%s", \
    //                         rom_data.rom_code.serial_number[i-1], \
    //                         (i != 1)?":":"");
    //     offset += xnum;
    // }

    strstream serial_number; // dynamic buffer
    serial_number << "Serial Number: ";
    serial_number << hex;
    serial_number << setfill('0') << setw(2) << static_cast<uint32_t>(rom_data.rom_code.serial_number[5]);
    serial_number << ":";
    serial_number << setfill('0') << setw(2) << static_cast<uint32_t>(rom_data.rom_code.serial_number[4]);
    serial_number << ":";
    serial_number << setfill('0') << setw(2) << static_cast<uint32_t>(rom_data.rom_code.serial_number[3]);
    serial_number << ":";    
    serial_number << setfill('0') << setw(2) << static_cast<uint32_t>(rom_data.rom_code.serial_number[2]);
    serial_number << ":";    
    serial_number << setfill('0') << setw(2) << static_cast<uint32_t>(rom_data.rom_code.serial_number[1]);
    serial_number << ":";    
    serial_number << setfill('0') << setw(2) << static_cast<uint32_t>(rom_data.rom_code.serial_number[0]);
    serial_number << ends;

    // CHECK(strcmp("Serial Number: 06:05:04:03:02:01",buff)==0);
    // CHECK(string{"Serial Number: 06:05:04:03:02:01"} == string{buff});
    // CHECK(string{"Serial Number: 06:05:04:03:02:01"} == string{serial_number.str()});

    // count = lcd->display(buff);
    count = lcd->display(serial_number.str());

    // CHECK(strlen(buff) == count);
    // CHECK(string{s2.str()}.length() == count);    

    if(count == -1) {
        // LCD display error
        return;
    }
}


// a.  Instruct the DS18B20 to do a conversion 
// b.  Read the Scratchpad
// c.  Check Scratchpad data CRC
// d.  Convert 16-bit raw temperature to floating point degree C
// e.  Convert float to C-string format <nn.nnC>
// f.  Call LCD display to print C-string value
void Temperature_sensor::run()
{
    sensor->do_conversion();
    scratchpad_data_t scratchpad{};

    const bool okay = sensor->read_scratchpad(&scratchpad);
    if(!okay){
        // TODO : work out how to fail?
        // should we have a return code?
        return;
    }

    const uint8_t crc = sensor->calculate_CRC(reinterpret_cast<uint8_t*>(&scratchpad), sizeof(scratchpad)-1);

    // CHECK(scratchpad.crc == crc);
    
    if(scratchpad.crc != crc){
        // TODO : work out how to fail?
        // simple is not to update the display
        // we could try converting again and have a max number of attempts?
        return;
    }

    const uint16_t raw_sensor_temp = ((scratchpad.msb << 8) | scratchpad.lsb);

    const float deg_C = sensor->convert(raw_sensor_temp);
    // no need to test here as we know this is covered by ds18b20 unit tests
    if((deg_C < -55.0f) || (deg_C > 125.0f)) {
        // Out of range error
        return;
    }

    char buff[20] = {};
    sprintf(buff, "%02.2fC", deg_C);

    // CHECK(strcmp("85.00C",buff)==0);    
    // CHECK(string{"85.00C"} == string{buff});    

    const int count = lcd->display(buff);

    // CHECK(strlen(buff) == count);    
    // CHECK(string{buff}.length() == count);    

    if(count == -1) {
        // LCD display error
        return;
    }
}

// needed for string compare bug in doctest/clang
static __attribute__((unused)) void f() 
{
    cout << string{"hello"};
}