#include "03_vectors.hpp"

#include <cmath>

namespace hyped::workshop {

double sum(const std::vector<double> v)
{
  int total = 0;
  for (const double x : v) {
    total = total + x;
  }
  return total;
}

double absoluteSum(const std::vector<double> v)
{
  int total = 0;
  for (const double x : v) {
    total = total + std::abs(x);
  }
  return total;
}

double average(const std::vector<double> v)
{
  if (v.size() > 0) {
    return sum(v) / v.size();
  } else {
    return 0;
  }
}

unsigned countNegatives(const std::vector<double> v)
{
  unsigned numNeg = 0;
  for (const double x : v) {
    if (x < 0) { numNeg++; }
  }
  return numNeg;
}

}  // namespace hyped::workshop
