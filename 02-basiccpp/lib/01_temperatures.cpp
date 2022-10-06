#include "01_temperatures.hpp"

namespace hyped::workshop {

double celsiusToKelvin(const double celsius)
{
  double K = celsius + 273.15;
  return K;
}

double celsiusToFahrenheit(const double celsius)
{
  double F = celsius * 9 / 5 + 32;
  return F;
}

}  // namespace hyped::workshop