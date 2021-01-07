#include <memory>

#include "doctest.h"
#include "ds1820.h"
using namespace DS18B20;

// TEST_CASE("testing power on reset value") {
//     uint16_t reading = 0x0550;
//     Ds1820 test_obj{};
//     CHECK(doctest::Approx(85.0f) == test_obj.convert(reading));
// }

// TEST_CASE("testing max value") {
//     uint16_t reading = 0x07D0;
//     Ds1820 test_obj{};
//     CHECK(doctest::Approx(125.0f).epsilon(0.05) == test_obj.convert(reading));
// }

class DS1820_Temperature_Sensor {
public:
  DS1820_Temperature_Sensor() : test_obj{ std::make_unique<Ds1820>() } {}

protected:
  std::unique_ptr<Ds1820> test_obj;
};

TEST_CASE_FIXTURE(DS1820_Temperature_Sensor, "power on reset")
{
  CHECK(doctest::Approx(85.0f).epsilon(0.05) == test_obj->convert(0x0550));        
}

TEST_CASE_FIXTURE(DS1820_Temperature_Sensor, "zero")
{
  CHECK(doctest::Approx(0.0f).epsilon(0.05) == test_obj->convert(0x0000));        
}

TEST_CASE("ds18b20 Temperature Sensor (R12)") {
    Ds1820 test_obj{};  // R12
    uint16_t reading{};

    SUBCASE("power on reset") {
        reading = 0x0550;
        CHECK(doctest::Approx(85.0f).epsilon(0.05) == test_obj.convert(reading));        
    }

    SUBCASE("zero")
    {
      int16_t raw    = 0x0000;
      float   actual = test_obj.convert(raw);
      CHECK(doctest::Approx(0.0f).epsilon(0.05) == actual);
    }

    SUBCASE("most valid positive")
    {
      int16_t raw    = 0x07D0;
      float   actual = test_obj.convert(raw);
      CHECK(doctest::Approx(125.0f).epsilon(0.05) == actual);
    }

    SUBCASE("most valid negative")
    {
      int16_t raw    = 0xFC90;
      float   actual = test_obj.convert(raw);
      CHECK(doctest::Approx(-55.0f).epsilon(0.05) == actual);
    }

    SUBCASE("smallest fraction")
    {
      int16_t raw    = 0x0001;
      float   actual = test_obj.convert(raw);
      CHECK(doctest::Approx(0.0625f).epsilon(0.05) == actual);
    }

    SUBCASE("one eighth fraction")
    {
      int16_t raw    = 0x0002;
      float   actual = test_obj.convert(raw);
      CHECK(doctest::Approx(0.125f).epsilon(0.05) == actual);
    }

    SUBCASE("one quarter fraction")
    {
      int16_t raw    = 0x0004;
      float   actual = test_obj.convert(raw);
      CHECK(doctest::Approx(0.25f).epsilon(0.05) == actual);
    }

    // What should be the outcome of anything > +125C ?
    SUBCASE("max positive")
    {
      int16_t raw    = 0x7FFF;
      float   actual = test_obj.convert(raw);
      CHECK(doctest::Approx(125.0f).epsilon(0.05) == actual);
    }

    // What should be the outcome of anything < -55C ?
    SUBCASE("max negative")
    {
      int16_t raw    = 0x8000;
      float   actual = test_obj.convert(raw);
      CHECK(doctest::Approx(-55.0f).epsilon(0.05) == actual);
    }
}

TEST_CASE("ds18b20 smallest fraction (R9")
{
  int16_t raw  = 0x000F;
  Ds1820 test_obj{Ds1820::Resolution::R9};
  float actual = test_obj.convert(raw);
  CHECK(doctest::Approx(0.875f).epsilon(0.05) == actual);
}

TEST_CASE("ds18b20 one eighth fraction R10")
{
  int16_t raw  = 0x000F;
  Ds1820 test_obj{Ds1820::Resolution::R10};
  float actual = test_obj.convert(raw);
  CHECK(doctest::Approx(0.75f).epsilon(0.05) == actual);
}

TEST_CASE("ds18b20 one quarter fraction R11")
{
  int16_t raw  = 0x000F;
  Ds1820 test_obj{Ds1820::Resolution::R11};
  float actual = test_obj.convert(raw);
  CHECK(doctest::Approx(0.5f).epsilon(0.05) == actual);
}
