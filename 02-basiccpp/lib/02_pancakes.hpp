#pragma once

#include <string>
#include <vector>

namespace hyped::workshop {

struct PancakesEatenBy {
  std::string name;
  int num_pancakes_eaten;
};

PancakesEatenBy mostPancakesEaten(const std::vector<PancakesEatenBy> all_pancakes_eaten);

std::vector<PancakesEatenBy> moreThanNPancakesEaten(
  const std::vector<PancakesEatenBy> all_pancakes_eaten, const int n);

std::vector<PancakesEatenBy> nMostPancakesEaten(
  const std::vector<PancakesEatenBy> all_pancakes_eaten, const int n);

}  // namespace hyped::workshop