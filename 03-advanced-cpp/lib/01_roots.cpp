#include "01_roots.hpp"

#include <cmath>

namespace hyped::workshop {

QuadraticPolynomial::QuadraticPolynomial(const double a, const double b, const double c)
{
  //add checks to pass the first test
  a_ = a;
  b_ = b;
  c_ = c;
}

bool QuadraticPolynomial::isRoot(const double x) const
{
  double y = (a_ * x * x) + (b_ * x) + (c_);
  return std::abs(y) < kTolerance;
}

std::unordered_set<double> QuadraticPolynomial::realRoots() const
{
  return std::unordered_set<double>();
}

}  // namespace hyped::workshop
