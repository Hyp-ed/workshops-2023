#include "01_temperatures.hpp"

namespace hyped::workshop {

double celsiusToKelvin(const double celsius)
{
  double f = celsius + 273.15;
  return f;
}

double celsiusToFahrenheit(const double celsius)
{
  return celsius * 9 / 5 + 32;
}

}  // namespace hyped::workshop