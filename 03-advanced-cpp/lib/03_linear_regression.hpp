#pragma once

#include <vector>

namespace hyped::workshop {

struct LinearModel {
  double intercept;
  double slope;
};

struct Point {
  double x;
  double y;
};

Point calculateMean(const std::vector<Point> &sample);

LinearModel linearRegression(const std::vector<Point> &sample);

}  // namespace hyped::workshop
