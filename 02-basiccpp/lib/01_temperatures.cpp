#include "01_temperatures.hpp"

namespace hyped::workshop {

double celsiusToKelvin(const double celsius)
{
  return celsius + 273.15;
}

double celsiusToFahrenheit(const double celsius)
{
  return ((celsius * 9.0) / (5.0) + 32.0);
}

}  // namespace hyped::workshop