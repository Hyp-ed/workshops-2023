#include "03_vectors.hpp"

#include <cmath>

namespace hyped::workshop {

double sum(const std::vector<double> v)
{
  double sum = 0.0;
  for (int i = 0; i < v.size(); i++) {
    sum = sum + v[i];
  }
  return sum;
}

double absoluteSum(const std::vector<double> v)
{
  double sum = 0.0;
  for (int i = 0; i < v.size(); i++) {
    sum = sum + abs(v[i]);
  }
  return sum;
}

double average(const std::vector<double> v)
{
  if (v.size() == 0) { return 0.0; }
  double sumOutput = sum(v);
  return sumOutput / v.size();
}

unsigned countNegatives(const std::vector<double> v)
{
  unsigned negatives = 0.0;
  for (int i = 0; i < v.size(); i++) {
    if (v[i] < 0) { negatives = negatives + 1; }
  }
  return negatives;
}

}  // namespace hyped::workshop
