#include <cmath>

#include <01_temperatures.hpp>
#include <gtest/gtest.h>

namespace hyped::test {

TEST(Temperatures, ZeroCelsius)
{
  ASSERT_DOUBLE_EQ(273.15, workshop::celsiusToKelvin(0.0));
  ASSERT_DOUBLE_EQ(32.0, workshop::celsiusToFahrenheit(0.0));
}

TEST(Temperatures, OneHundredCelsius)
{
  ASSERT_DOUBLE_EQ(373.15, workshop::celsiusToKelvin(100.0));
  ASSERT_DOUBLE_EQ(212.0, workshop::celsiusToFahrenheit(100.0));
}

TEST(Temperatures, NegativeOneHundredCelsius)
{
  ASSERT_DOUBLE_EQ(173.15, workshop::celsiusToKelvin(-100.0));
  ASSERT_DOUBLE_EQ(-148.0, workshop::celsiusToFahrenheit(-100.0));
}

TEST(Temperatures, celsiusToFarenheit)
{
  ASSERT_DOUBLE_EQ(156.2, workshop::celsiusToFahrenheit(69.0));
  ASSERT_DOUBLE_EQ(210.2, workshop::celsiusToFahrenheit(99.0));
  ASSERT_DOUBLE_EQ(248.0, workshop::celsiusToFahrenheit(120.0));
}

TEST(Temperatures, celsiusToKelvin)
{
  ASSERT_DOUBLE_EQ(342.15, workshop::celsiusToKelvin(69.0));
  ASSERT_DOUBLE_EQ(372.15, workshop::celsiusToKelvin(99.0));
  ASSERT_DOUBLE_EQ(393.15, workshop::celsiusToKelvin(120.0));
}

}  // namespace hyped::test