#include "03_vectors.hpp"

#include <cmath>

#include <numeric>

#include <bits/stdc++.h>

namespace hyped::workshop {

double sum(const std::vector<double> v)
{
  // double var = 0;
  // for (size_t i = 0; i < v.size(); i++) {
  //   var += v.at(i);
  // }
  // return var;
  return reduce(v.begin(), v.end(), 0);
}

double absoluteSum(const std::vector<double> v)
{
  double var = 0;
  for (size_t i = 0; i < v.size(); i++) {
    var += abs(v.at(i));
  }
  return var;
}

double average(const std::vector<double> v)
{
  if (v.size() == 0) return 0;
  return sum(v) / v.size();
}

unsigned countNegatives(const std::vector<double> v)
{
  unsigned counter = 0;
  for (size_t i = 0; i < v.size(); i++) {
    if (v.at(i) < 0) counter++;
  }
  return counter;
}

}  // namespace hyped::workshop
