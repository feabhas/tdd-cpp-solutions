#include "doctest.h"

#include "ds1820.h"
#include "lcd.h"
using namespace DS18B20;
using namespace Display;

#include "temperature_sensor.h"

TEST_CASE("testing basic algorithm") {
    DS18B20::Ds1820 sensor{};
    Display::Lcd    display{};

    Temperature_sensor test_obj { display, sensor };

    SUBCASE("run main algorithm") {
        test_obj.run();
    }

}
