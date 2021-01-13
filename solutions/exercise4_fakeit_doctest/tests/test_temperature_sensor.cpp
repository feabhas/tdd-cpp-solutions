#pragma GCC diagnostic ignored "-Wnon-virtual-dtor" // for fakeIt

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "fakeit.hpp"
using namespace fakeit;

#include <regex>

#include "IDisplay.h"
#include "ds1820.h"
#include "temperature_sensor.h"

TEST_CASE("testing basic algorithm")
{
  Mock<Display::IDisplay> mock_display{};
  // When(Method(mock, display)).Return(0,0,0);
  // When(Method(mock, display)).AlwaysReturn(0);
  // When(Method(mock, display)).AlwaysReturn();
  // Method(mock, display) = 0;
  // When(Method(mock, display)).AlwaysDo([](auto str){ return 0; });
  // or...
  Fake(Method(mock_display, display));

  Sensor::Ds1820 sensor{};
  auto&          display_ref = mock_display.get();

  Temperature_sensor test_obj{ display_ref, sensor };
  SUBCASE("initialisation")
  {
    SUBCASE("normal behaviour")
    {
      // When(Method(mock_display, display)).Return(0, 0);
      When(Method(mock_display, display).Matching([](auto& p) -> bool {
        return std::string_view{ "Family code: 0x28" } == std::string_view{ p };
      }))
        .Return(0);
      When(Method(mock_display, display).Matching([](auto& p) -> bool {
        std::string_view match_str{ "Serial Number: " };
        return match_str == std::string_view{ p }.substr(0, match_str.length());
      }))
        .Return(0);
      auto status = test_obj.initialize();
      CHECK(status == Temperature_sensor::status::ok);
      Verify(Method(mock_display, display)).Exactly(2);

      SUBCASE("display first call failure")
      {
        When(Method(mock_display, display)).Return(-1);

        auto status = test_obj.initialize();
        CHECK(status == Temperature_sensor::status::display_failure);
      }

      SUBCASE("display second call failure")
      {
        When(Method(mock_display, display)).Return(0, -1);

        auto status = test_obj.initialize();
        CHECK(status == Temperature_sensor::status::display_failure);
      }
    }
  }

  SUBCASE("run failure test")
  {
    test_obj.initialize();

    SUBCASE("normal_behaviour")
    {
      When(Method(mock_display, display)).Return(0);
      auto status = test_obj.run();
      CHECK(status == Temperature_sensor::status::ok);
      Verify(Method(mock_display, display)).Exactly(3);
    }

    SUBCASE("display_failure")
    {
      When(Method(mock_display, display)).Return(-1);
      auto status = test_obj.run();
      CHECK(status == Temperature_sensor::status::display_failure);
    }

    SUBCASE("display_param_check")
    {
      // match temperature of the form 00.00C
      When(Method(mock_display, display).Matching([](auto& p) -> bool {
        return regex_match(p, std::regex{ R"(\d\d.\d\dC)" });
      }))
        .Return(0);

      auto status = test_obj.run();
      CHECK(status == Temperature_sensor::status::ok);
    }
  }
}