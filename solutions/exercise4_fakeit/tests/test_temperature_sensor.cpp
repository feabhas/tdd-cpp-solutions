#pragma GCC diagnostic ignored "-Wnon-virtual-dtor" // for fakeIt

#include "gtest/gtest.h"

#include "fakeit.hpp"
using namespace fakeit;

#include <regex>

#include "IDisplay.h"
#include "ds1820.h"
#include "temperature_sensor.h"

class Mock_tests_initialise : public ::testing::Test {
protected:
  Mock_tests_initialise() : test_obj{ mock_display.get(), sensor } {}
  virtual ~Mock_tests_initialise() = default;

  // stub object
  Sensor::Ds1820 sensor{};
  // Create our mock object(s)
  Mock<Display::IDisplay> mock_display{};
  // UUT
  Temperature_sensor test_obj;
};

TEST_F(Mock_tests_initialise, normal_behaviour)
{
  When(Method(mock_display, display)).Return(0, 0);
  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
  Verify(Method(mock_display, display)).Exactly(2);
}

TEST_F(Mock_tests_initialise, normal_behaviour_with_param_check)
{
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
  ASSERT_EQ(status, Temperature_sensor::status::ok);
  Verify(Method(mock_display, display)).Exactly(2);
}

TEST_F(Mock_tests_initialise, display_1st_failure)
{
  When(Method(mock_display, display)).Return(-1);

  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(Mock_tests_initialise, display_2nd_failure)
{
  When(Method(mock_display, display)).Return(0, -1);

  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

class Mock_tests_run : public ::testing::Test {
protected:
  Mock_tests_run() : test_obj{ mock_display.get(), sensor } {}

  void SetUp() override
  {
    Fake(Method(mock_display, display));
    test_obj.initialize();
  }

  // stub object
  Sensor::Ds1820 sensor{};
  // Create our mock object(s)
  Mock<Display::IDisplay> mock_display{};
  // UUT
  Temperature_sensor test_obj;
};

TEST_F(Mock_tests_run, normal_behaviour)
{
  When(Method(mock_display, display)).Return(0);
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
  Verify(Method(mock_display, display)).Exactly(3);
}

TEST_F(Mock_tests_run, display_failure)
{
  When(Method(mock_display, display)).Return(-1);
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(Mock_tests_run, display_param_check)
{
  // match temperature of the form 00.00C
  When(Method(mock_display, display).Matching([](auto& p) -> bool {
    return regex_match(p, std::regex{ R"(\d\d.\d\dC)" });
  }))
    .Return(0);

  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}