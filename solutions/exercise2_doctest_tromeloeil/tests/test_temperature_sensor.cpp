#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "trompeloeil.hpp"
using trompeloeil::_;

#include "IDisplay.h"
#include "ds1820.h"

#include "temperature_sensor.h"

class Display_fake : public trompeloeil::mock_interface<Display::IDisplay> {
public:
  IMPLEMENT_MOCK1(display);
};

//
// Alternative form
//
// class Display_fake : Display::IDisplay {
// public:
//   MAKE_MOCK1(display, int(const char*), override);
// };

TEST_CASE("testing basic algorithm")
{
  Sensor::Ds1820  fake_sensor{};
  Display_fake fake_display{};
  ALLOW_CALL(fake_display, display(_)).RETURN(0);

  Temperature_sensor test_obj{ fake_display, fake_sensor };

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
