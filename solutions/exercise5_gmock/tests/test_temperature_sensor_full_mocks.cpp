#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::ContainsRegex;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StartsWith;
using ::testing::StrictMock;

#include "IDisplay.h"
#include "Sensor_Adaptor.h"
#include "temperature_sensor.h"

class mock_display : public Display::IDisplay {
public:
  MOCK_METHOD1(display, int(const char* str));
};

//==============================================================

class mock_sensor : public Sensor::ISensor {
public:
  MOCK_METHOD0(family_code, std::string());
  MOCK_METHOD0(serial_number, std::string());
  MOCK_METHOD0(lastest_reading, float());
};

class full_Mock_tests_init : public ::testing::Test {
protected:
  full_Mock_tests_init()          = default;
  virtual ~full_Mock_tests_init() = default;

  // Create our mock object(s)
  StrictMock<mock_display> display{};
  StrictMock<mock_sensor>  sensor{};
  Temperature_sensor       test_obj{ display, sensor };
};

TEST_F(full_Mock_tests_init, test_initialisation)
{
  EXPECT_CALL(sensor, family_code()).WillOnce(Return("Family code: 0x28"));
  EXPECT_CALL(sensor, serial_number())
    .WillOnce(Return("Serial Number:00:00:00:00:00"));
  EXPECT_CALL(display, display(_)).Times(2);
  auto status = test_obj.initialize();
  EXPECT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(full_Mock_tests_init, test_init_display_1st_failure)
{
  EXPECT_CALL(sensor, family_code()).WillOnce(Return("Family code: 0x28"));
  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));
  auto status = test_obj.initialize();
  EXPECT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(full_Mock_tests_init, test_init_display_2nd_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(sensor, family_code()).WillOnce(Return("Family code: 0x28"));
  EXPECT_CALL(display, display(_)).WillOnce(Return(0));
  EXPECT_CALL(sensor, serial_number())
    .WillOnce(Return("Serial Number:00:00:00:00:00"));
  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));
  auto status = test_obj.initialize();
  EXPECT_EQ(status, Temperature_sensor::status::display_failure);
}

//=========================================================

class full_Mock_tests_run : public ::testing::Test {
protected:
  full_Mock_tests_run()
  {
    EXPECT_CALL(sensor, family_code()).WillOnce(Return("Family code: 0x28"));
    EXPECT_CALL(display, display(StartsWith("Family code: 0x")))
      .WillOnce(Return(0));

    EXPECT_CALL(sensor, serial_number())
      .WillOnce(Return("Serial Number:00:00:00:00:00"));
    EXPECT_CALL(display, display(StartsWith("Serial Number:")))
      .WillOnce(Return(0));
    test_obj.initialize();
  }

  //   Create our mock object(s)
  //   NiceMock<mock_display> display{};
  //   NiceMock<mock_sensor>  sensor{};
  StrictMock<mock_display> display{};
  StrictMock<mock_sensor>  sensor{};
  Temperature_sensor       test_obj{ display, sensor };
};

TEST_F(full_Mock_tests_run, test_run_display_no_failure)
{
  ::testing::InSequence strict_sequence;
  EXPECT_CALL(sensor, lastest_reading()).WillOnce(Return(25.0f));
  EXPECT_CALL(display, display(_)).WillOnce(Return(0));
  auto status = test_obj.run();
  EXPECT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(full_Mock_tests_run, test_run_display_failure)
{
  ::testing::InSequence strict_sequence;
  EXPECT_CALL(sensor, lastest_reading()).WillOnce(Return(25.0f));
  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));
  auto status = test_obj.run();
  EXPECT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(full_Mock_tests_run, test_run_display_param_check)
{
  ::testing::InSequence strict_sequence;
  EXPECT_CALL(sensor, lastest_reading()).WillOnce(Return(25.0f));
  EXPECT_CALL(display, display(ContainsRegex("..\\...C"))).WillOnce(Return(0));
  auto status = test_obj.run();
  EXPECT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(full_Mock_tests_run, test_run_sensor_failure)
{
  ::testing::InSequence strict_sequence;
  EXPECT_CALL(sensor, lastest_reading()).WillOnce(Return(200.0f));
  auto status = test_obj.run();
  EXPECT_EQ(status, Temperature_sensor::status::sensor_failure);
}