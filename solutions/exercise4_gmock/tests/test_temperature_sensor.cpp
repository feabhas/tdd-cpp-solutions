#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Return;
using ::testing::_;
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::StartsWith;
using ::testing::ContainsRegex;

#include "IDisplay.h"
#include "ds1820.h"
#include "temperature_sensor.h"

class mock_display : public Display::IDisplay {
public:
  MOCK_METHOD1(display, int (const char* str));
};

class Mock_tests : public ::testing::Test {
protected:
  Mock_tests()          = default;
  virtual ~Mock_tests() = default;

  // stub object
  Sensor::Ds1820 sensor{};
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

  EXPECT_CALL(display, display(StartsWith("Family code: 0x"))).WillOnce(Return(0));
  EXPECT_CALL(display, display(StartsWith("Serial Number:"))).WillOnce(Return(0));
  EXPECT_CALL(display, display(ContainsRegex("..\\...C"))).WillOnce(Return(0));

  Temperature_sensor test_obj{ display, sensor };

  test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}
