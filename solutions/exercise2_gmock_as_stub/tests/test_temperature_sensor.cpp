#include "gmock/gmock.h"
#include "gtest/gtest.h"
using ::testing::_;
using testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::Return;

#include "IDisplay.h"
#include "ds1820.h"  // cannot mock as non-virtual interface

#include "temperature_sensor.h"

class Display_stub : public Display::IDisplay {
public:
  // Nice_Mock<> will return 0
  MOCK_METHOD(int, display, (const char* str));
};

class Stub_test : public ::testing::Test {
protected:
  Stub_test()          = default;
  virtual ~Stub_test() = default;
  // Create a stub object
  NiceMock<Display_stub> display_stub{};

  // concrete stub
  Sensor::Ds1820 sensor{};
  // Unit-Under-Test
  Temperature_sensor test_obj{ display_stub, sensor };
};


TEST_F(Stub_test, test_initialisation)
{
  // if we wanted to return anything other than 0
  // EXPECT_CALL(display_stub, display(_)).Times(AnyNumber()).WillOnce(Return(0));
  // EXPECT_CALL(display_stub, display(_)).Times(AnyNumber()).WillOnce(Return(0));
  // or implicit behaviour
  // EXPECT_CALL(display_stub,display(_)).WillRepeatedly(Return(0));
  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(Stub_test, test_basic_algorithm)
{
  // EXPECT_CALL(display_stub,display(_)).WillRepeatedly(Return(0));
  test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}