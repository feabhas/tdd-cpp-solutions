#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::ContainsRegex;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StartsWith;
using ::testing::StrictMock;

#include "IDisplay.h"
#include "ds1820.h"
#include "temperature_sensor.h"

class mock_display : public Display::IDisplay {
public:
  MOCK_METHOD1(display, int(const char* str));
};

class Mock_tests_initialise : public ::testing::Test {
protected:
  Mock_tests_initialise()          = default;
  virtual ~Mock_tests_initialise() = default;

  // stub object
  Sensor::Ds1820 sensor{};
  // Create our mock object(s)
  // NiceMock<mock_display> display{};
  StrictMock<mock_display> display{};

  Temperature_sensor test_obj{ display, sensor };
};

TEST_F(Mock_tests_initialise, test_initialisation)
{
  EXPECT_CALL(display, display(_)).Times(2);

  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(Mock_tests_initialise, test_init_display_1st_failure)
{
  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));

  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(Mock_tests_initialise, test_init_display_2nd_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(display, display(_)).WillOnce(Return(0));
  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));

  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

class Mock_tests_run : public ::testing::Test {
protected:
  Mock_tests_run()
  {
    // EXPECT_CALL(display, display(_))
    //   .Times(2); // only needed if StrictMock used
    EXPECT_CALL(display, display(StartsWith("Family code: 0x")))
      .WillOnce(Return(0));
    EXPECT_CALL(display, display(StartsWith("Serial Number:")))
      .WillOnce(Return(0));

    test_obj.initialize();
  }

  // stub object
  Sensor::Ds1820 sensor{};
  // Create our mock object(s)
  // NiceMock<mock_display> display{};
  StrictMock<mock_display> display{};

  Temperature_sensor test_obj{ display, sensor };
};

TEST_F(Mock_tests_run, test_run_display_no_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(display, display(_)).Times(1).WillRepeatedly(Return(0));

  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(Mock_tests_run, test_init_display_3nd_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));

  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(Mock_tests_run, test_init_display_param_check)
{
  ::testing::InSequence strict_sequence;

  // EXPECT_CALL(display, display(StartsWith("Family code: 0x")))
  //   .WillOnce(Return(0));
  // EXPECT_CALL(display, display(StartsWith("Serial Number:")))
  //   .WillOnce(Return(0));
  EXPECT_CALL(display, display(ContainsRegex("..\\...C"))).WillOnce(Return(0));

  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}
