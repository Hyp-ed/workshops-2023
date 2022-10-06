#pragma once
#include <algorithm>
#include <string>
#include <vector>

namespace hyped::workshop {

struct Person {
  std::string name;
  unsigned age;
};

void sortByAge(std::vector<Person> &persons);

}  // namespace hyped::workshop
