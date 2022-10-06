#include "03_vectors.hpp"

#include <cmath>

#include <iostream>

namespace hyped::workshop {

double sum(const std::vector<double> v)
{
  double sum = 0;
  for (double i : v) {
    sum += i;
  }
  return sum;
}

double absoluteSum(const std::vector<double> v)
{
  double sum = 0;
  for (double i : v) {
    sum += fabs(i);
  }
  // abs dosen't accept?
  return sum;
}

double average(const std::vector<double> v)
{
  if (v.size() == 0) { return 0; }
  double s = sum(v);

  return s / v.size();
}

unsigned countNegatives(const std::vector<double> v)
{
  int count = 0;
  for (double i : v) {
    if (i < 0) { count++; }
  }

  return count;
}

}  // namespace hyped::workshop
