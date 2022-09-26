#pragma once

#include <stdio.h>
#include <cstdlib>

namespace hyped::utils {

namespace {
}

#define NO_COPY_ASSIGN(T)                                                                          \
  T(const T &) = delete;                                                                           \
  void operator=(const T &) = delete;

#define ASSERT(COND)                                                                               \
  do {                                                                                             \
    if (!(COND)) {                                                                                 \
      printf("%s:%d: error: EXPECTED %s\n", __FILE__, __LINE__, #COND);                            \
      abort();                                                                                     \
    }                                                                                              \
  } while (0)

template<bool>
class StaticAssert;
template<>
class StaticAssert<true> {
};
#define STATIC_ASSERT(COND) (StaticAssert<(COND) != 0>())

}  // namespace hyped::utils