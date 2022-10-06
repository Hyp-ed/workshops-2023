#include "01_temperatures.hpp"

namespace hyped::workshop {

double celsiusToKelvin(const double celsius)
{
  double kelvin = celsius + 273.15;
  return kelvin;
}

double celsiusToFahrenheit(const double celsius)
{
  double fahr = (celsius * (9 / 5)) + 32;
  return fahr;
}

}  // namespace hyped::workshop