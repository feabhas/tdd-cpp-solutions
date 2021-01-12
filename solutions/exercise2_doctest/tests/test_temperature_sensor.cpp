#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "display_stub.h"
#include "ds1820.h"


#include "temperature_sensor.h"

TEST_CASE("testing basic algorithm")
{
  Sensor::Ds1820 sensor{};
  Display::Display_stub display{};

  Temperature_sensor test_obj{ display, sensor };

  SUBCASE("initialise")
  {
    auto status = test_obj.initialize();
    CHECK(status == Temperature_sensor::status::ok);

    SUBCASE("run main algorithm")
    {
      auto status = test_obj.run();
      CHECK(status == Temperature_sensor::status::ok);
    }
  }
}
