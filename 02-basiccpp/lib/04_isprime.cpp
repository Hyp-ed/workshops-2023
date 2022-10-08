#include "04_isprime.hpp"

namespace hyped::workshop {
bool isPrime(int n)
{
  if (n == 2) { return true; }
  if (n % 2 == 0 || n == 1) { return false; }
  for (int i = 3; i < n; i = i + 2) {
    if (n % i == 0) { return false; }
  }
  return true;
}
}  // namespace hyped::workshop