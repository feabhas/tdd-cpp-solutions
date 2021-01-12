#include "gtest/gtest.h"

#include "display_stub.h"
#include "ds1820.h"

#include "temperature_sensor.h"

//
// Fixture
class Stub_test_fixture : public ::testing::Test {
protected:
  Stub_test_fixture()          = default;
  virtual ~Stub_test_fixture() = default;

  // stub objects
  Sensor::Ds1820        sensor{};
  Display::Display_stub display{};
  // Unit-Under-Test
  Temperature_sensor test_obj{ display, sensor };
};

TEST_F(Stub_test_fixture, test_initialisation)
{
  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(Stub_test_fixture, test_basic_algorithm)
{
  test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}

//
// As Fixture with initialisation
class Stub_test_run : public ::testing::Test {
protected:
  Stub_test_run() { test_obj.initialize(); };
  virtual ~Stub_test_run() = default;

  // stub objects
  Sensor::Ds1820        sensor{};
  Display::Display_stub display{};
  // Unit-Under-Test
  Temperature_sensor test_obj{ display, sensor };
};

TEST_F(Stub_test_run, test_basic_algorithm)
{
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}