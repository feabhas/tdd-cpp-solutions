#pragma GCC diagnostic ignored "-Wnon-virtual-dtor" // for fakeIt

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "fakeit.hpp"
using namespace fakeit;

// #include "display_stub.h"
#include "IDisplay.h"
#include "ds1820.h"

#include "temperature_sensor.h"

TEST_CASE("testing basic algorithm")
{
  Mock<Display::IDisplay> mock{};
  // When(Method(mock, display)).Return(0,0,0);
  // When(Method(mock, display)).AlwaysReturn(0);
  // When(Method(mock, display)).AlwaysReturn();
  // Method(mock, display) = 0;
  // When(Method(mock, display)).AlwaysDo([](auto str){ return 0; });
  // or...
  Fake(Method(mock, display));

  Sensor::Ds1820 sensor{};
  auto&          display = mock.get();

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
