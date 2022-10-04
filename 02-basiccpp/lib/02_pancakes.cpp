#include "02_pancakes.hpp"

namespace hyped::workshop {

PancakesEatenBy mostPancakesEaten(const std::vector<PancakesEatenBy> all_pancakes_eaten)
{
  int maxPancakes = 0;
  PancakesEatenBy max;
  for(int i  = 0;i<all_pancakes_eaten.length();i++){
    if(all_pancakes_eaten[i].num_pancakes_eaten > maxPancakes){
      maxPancakes = all_pancakes_eaten[i].num_pancakes_eaten;
      max = all_pancakes_eaten[i];
    }
  }
  return max;

}

std::vector<PancakesEatenBy> moreThanNPancakesEaten(
  const std::vector<PancakesEatenBy> all_pancakes_eaten, const int n)
{
  std::vector<PancakesEatenBy> output;
  for(int i =0;i<all_pancakes_eaten.length();i++){
    if(all_pancakes_eaten[i].num_pancakes_eaten > n){
      output.push(all_pancakes_eaten[i]);
    }
  }

  return output;
}

}  // namespace hyped::workshop