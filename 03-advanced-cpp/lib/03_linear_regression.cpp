#include "03_linear_regression.hpp"

namespace hyped::workshop {

Point calculateMean(const std::vector<Point> &sample)
{
  Point sum = {0, 0};
  for (const auto &p : sample) {
    sum.x += p.x;
    sum.y += p.y;
  }
  const double d = static_cast<double>(sample.size());
  return {sum.x / d, sum.y / d};
}

LinearModel linearRegression(const std::vector<Point> &sample)
{
  const Point mean = calculateMean(sample);
  double sum1      = 0;
  double sum2      = 0;
  for (const auto &p : sample) {
    sum1 += (p.x - mean.x) * (p.y - mean.y);
    sum2 += (p.x - mean.x) * (p.x - mean.x);
  }
  const double beta1 = sum1 / sum2;
  const double beta0 = mean.y - beta1 * mean.x;
  return {beta0, beta1};
}

}  // namespace hyped::workshop
