#include "02_pancakes.hpp"

namespace hyped::workshop {

PancakesEatenBy mostPancakesEaten(const std::vector<PancakesEatenBy> all_pancakes_eaten)
{
  PancakesEatenBy largest = all_pancakes_eaten[0];
  for (PancakesEatenBy i : all_pancakes_eaten) {
    if (i.num_pancakes_eaten > largest.num_pancakes_eaten) { largest = i; }
  }

  return largest;
}

std::vector<PancakesEatenBy> moreThanNPancakesEaten(
  const std::vector<PancakesEatenBy> all_pancakes_eaten, const int n)
{
  std::vector<PancakesEatenBy> largerThanN;
  for (PancakesEatenBy i : all_pancakes_eaten) {
    if (i.num_pancakes_eaten > n) { largerThanN.push_back(i); }
  }

  return largerThanN;
}

}  // namespace hyped::workshop