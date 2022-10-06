#include "02_pancakes.hpp"

namespace hyped::workshop {

PancakesEatenBy mostPancakesEaten(const std::vector<PancakesEatenBy> all_pancakes_eaten)
{
  PancakesEatenBy highest = all_pancakes_eaten[0];

  for (int i = 0; i < all_pancakes_eaten.size(); i++) {
    if (all_pancakes_eaten[i].num_pancakes_eaten > highest.num_pancakes_eaten) {
      highest = all_pancakes_eaten[i];
    }
  }

  return highest;
}

std::vector<PancakesEatenBy> moreThanNPancakesEaten(
  const std::vector<PancakesEatenBy> all_pancakes_eaten, const int n)
{
  std::vector<PancakesEatenBy> eatenMoreThan;
  for (int i = 0; i < all_pancakes_eaten.size(); i++) {
    if (all_pancakes_eaten[i].num_pancakes_eaten > n) {
      eatenMoreThan.push_back(all_pancakes_eaten[i]);
    }
  }

  return eatenMoreThan;
}

}  // namespace hyped::workshop