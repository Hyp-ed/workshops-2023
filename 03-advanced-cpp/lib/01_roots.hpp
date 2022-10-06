#pragma once

#include <optional>

#include <unordered_set>

namespace hyped::workshop {

/**
 * Represents a quadratic polynomial of the form
 *
 * a * x * x + b * x + c = 0.
 */
class QuadraticPolynomial {
 private:
  double a_;
  double b_;
  double c_;

  static constexpr double kTolerance = 0.0001;

 public:
  /* New quadratic with real coefficients a, b, and c where a != 0*/
  QuadraticPolynomial(const double a, const double b, const double c);

  /* True iff x is a root to the polynomial */
  bool isRoot(const double x) const;

  /* Returns zero, one or two real roots */
  std::unordered_set<double> realRoots() const;

  /* Representation of this quadratic polynomial as an std::tuple */
  auto key() const { return std::tie(a_, b_, c_); }

  /* Equality operator to compare to quadratics */
  bool operator==(const QuadraticPolynomial &rhs) const { return key() == rhs.key(); }

  /* Inequality operator to compare to quadratics */
  bool operator!=(const QuadraticPolynomial &rhs) const { return !(*this == rhs); }
};

}  // namespace hyped::workshop
