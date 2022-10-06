#include "04_isprime.hpp"

namespace hyped::workshop {
bool isPrime(int n)
{
  bool prime = true;
  if (n < 2) { return false; }
  for (int i = 2; i < n; i++) {
    if (n % i == 0) {
      prime = false;
      break;
    }
  };
  return prime;
}
}  // namespace hyped::workshop