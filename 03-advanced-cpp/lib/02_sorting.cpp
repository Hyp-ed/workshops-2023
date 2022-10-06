#include "02_sorting.hpp"

#include <algorithm>

namespace hyped::workshop {

void sortByAge(std::vector<Person> &persons)
{
  std::sort(persons.begin(), persons.end(),
            [](const Person &lhs, const Person &rhs) { return lhs.age < rhs.age; });
}

}  // namespace hyped::workshop
