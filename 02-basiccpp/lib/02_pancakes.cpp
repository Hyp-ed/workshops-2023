#include "02_pancakes.hpp"

namespace hyped::workshop {

bool compfunc(PancakesEatenBy a, PancakesEatenBy b)
{
  return a.num_pancakes_eaten < b.num_pancakes_eaten;
}
PancakesEatenBy mostPancakesEaten(const std::vector<PancakesEatenBy> all_pancakes_eaten)
{
  PancakesEatenBy maxIsAKnob = all_pancakes_eaten.at(0);

  for (size_t i = 1; i < all_pancakes_eaten.size(); i++) {
    if (all_pancakes_eaten.at(i).num_pancakes_eaten >= maxIsAKnob.num_pancakes_eaten) {
      maxIsAKnob = all_pancakes_eaten.at(i);
    }
  }
  return maxIsAKnob;
}

std::vector<PancakesEatenBy> moreThanNPancakesEaten(
  const std::vector<PancakesEatenBy> all_pancakes_eaten, const int n)
{
  std::vector<PancakesEatenBy> maxPancakeOverload3000;
  for (PancakesEatenBy currentVal : all_pancakes_eaten) {
    if (currentVal.num_pancakes_eaten > n) { maxPancakeOverload3000.push_back(currentVal); }
  }
  return maxPancakeOverload3000;
}

}  // namespace hyped::workshop