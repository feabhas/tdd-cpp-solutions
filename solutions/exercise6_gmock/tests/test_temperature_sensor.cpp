#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Return;
using ::testing::_;
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::StartsWith;
using ::testing::ContainsRegex;

#include "IDisplay.h"
#include "Sensor_Adaptor.h"
#include "temperature_sensor.h"

class mock_display : public Display::IDisplay {
public:
  MOCK_METHOD1(display, int(const char* str));
};

class Mock_tests : public ::testing::Test {
protected:
  Mock_tests()          = default;
  virtual ~Mock_tests() = default;

  // stub object
  Sensor::Sensor_Adaptor sensor{};
  // Create our mock object(s)
  StrictMock<mock_display> display{};
};

TEST_F(Mock_tests, test_initialisation)
{
  EXPECT_CALL(display, display(_)).Times(2);

  Temperature_sensor test_obj{ display, sensor };

  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(Mock_tests, test_init_display_1st_failure)
{
  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));

  Temperature_sensor test_obj{ display, sensor };

  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(Mock_tests, test_init_display_2nd_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(display, display(_)).WillOnce(Return(0));
  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));

  Temperature_sensor test_obj{ display, sensor };

  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(Mock_tests, test_run_display_no_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(display, display(_)).Times(3).WillRepeatedly(Return(0));

  Temperature_sensor test_obj{ display, sensor };

  test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(Mock_tests, test_init_display_3nd_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(display, display(_)).WillOnce(Return(0));
  EXPECT_CALL(display, display(_)).WillOnce(Return(0));
  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));

  Temperature_sensor test_obj{ display, sensor };

  test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(Mock_tests, test_init_display_param_check)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(display, display(StartsWith("Family code: 0x")))
    .WillOnce(Return(0));
  EXPECT_CALL(display, display(StartsWith("Serial Number:")))
    .WillOnce(Return(0));
  EXPECT_CALL(display, display(ContainsRegex("..\\...C"))).WillOnce(Return(0));

  Temperature_sensor test_obj{ display, sensor };

  test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}

//==============================================================

class mock_sensor : public Sensor::ISensor {
public:
  MOCK_METHOD0(family_code,  std::string());
  MOCK_METHOD0(serial_number,  std::string());
  MOCK_METHOD0(lastest_reading, float());
};

class full_Mock_tests : public ::testing::Test {
protected:
  full_Mock_tests()          = default;
  virtual ~full_Mock_tests() = default;

  // Create our mock object(s)
  StrictMock<mock_display> display{};
  StrictMock<mock_sensor>  sensor{};
};

TEST_F(full_Mock_tests, test_initialisation)
{
  EXPECT_CALL(sensor, family_code())
      .WillOnce(Return("Family code: 0x28"));
  EXPECT_CALL(sensor, serial_number())
      .WillOnce(Return("Serial Number:00:00:00:00:00"));

  EXPECT_CALL(display, display(_)).Times(2);

  Temperature_sensor test_obj{ display, sensor };

  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(full_Mock_tests, test_init_display_1st_failure)
{
  EXPECT_CALL(sensor, family_code()).WillOnce(Return("Family code: 0x28"));

  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));

  Temperature_sensor test_obj{ display, sensor };

  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(full_Mock_tests, test_init_display_2nd_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(sensor, family_code()).WillOnce(Return("Family code: 0x28"));
  EXPECT_CALL(display, display(_)).WillOnce(Return(0));
  EXPECT_CALL(sensor, serial_number())
    .WillOnce(Return("Serial Number:00:00:00:00:00"));
  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));

  Temperature_sensor test_obj{ display, sensor };

  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(full_Mock_tests, test_run_display_no_failure)
{
  ::testing::InSequence strict_sequence;

    EXPECT_CALL(sensor, family_code())
      .WillOnce(Return("Family code: 0x28"));

    EXPECT_CALL(display, display(_))
      .WillOnce(Return(0));

    EXPECT_CALL(sensor, serial_number())
      .WillOnce(Return("Serial Number:00:00:00:00:00"));

    EXPECT_CALL(display, display(_))
      .WillOnce(Return(0));

    EXPECT_CALL(sensor, lastest_reading())
      .WillOnce(Return(25.0f));

    EXPECT_CALL(display, display(_)).WillOnce(Return(0));
    Temperature_sensor test_obj{ display, sensor };

    test_obj.initialize();
    auto status = test_obj.run();
    ASSERT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(full_Mock_tests, test_init_display_3nd_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(sensor, family_code()).WillOnce(Return("Family code: 0x28"));

  EXPECT_CALL(display, display(_)).WillOnce(Return(0));

  EXPECT_CALL(sensor, serial_number())
    .WillOnce(Return("Serial Number:00:00:00:00:00"));

  EXPECT_CALL(display, display(_)).WillOnce(Return(0));

  EXPECT_CALL(sensor, lastest_reading()).WillOnce(Return(25.0f));
  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));

  Temperature_sensor test_obj{ display, sensor };

  test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(full_Mock_tests, test_init_display_param_check)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(sensor, family_code())
    .WillOnce(Return("Family code: 0x28"));
  EXPECT_CALL(display, display(StartsWith("Family code: 0x")))
    .WillOnce(Return(0));

  EXPECT_CALL(sensor, serial_number())
    .WillOnce(Return("Serial Number:00:00:00:00:00"));
  EXPECT_CALL(display, display(StartsWith("Serial Number:")))
    .WillOnce(Return(0));

  EXPECT_CALL(sensor, lastest_reading())
    .WillOnce(Return(25.0f));
  EXPECT_CALL(display, display(ContainsRegex("..\\...C"))).WillOnce(Return(0));

  Temperature_sensor test_obj{ display, sensor };

  test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}
