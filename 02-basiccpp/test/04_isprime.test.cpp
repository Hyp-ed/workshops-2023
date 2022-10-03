#include <04_isprime.hpp>
#include <gtest/gtest.h>

namespace hyped::test {

TEST(IsPrime, Zero)
{
  EXPECT_FALSE(workshop::isPrime(0));
}

TEST(IsPrime, One)
{
  EXPECT_FALSE(workshop::isPrime(1));
}

TEST(IsPrime, Two)
{
  EXPECT_TRUE(workshop::isPrime(2));
}

TEST(IsPrime, Three)
{
  EXPECT_TRUE(workshop::isPrime(3));
}

TEST(IsPrime, Four)
{
  EXPECT_FALSE(workshop::isPrime(4));
}

TEST(IsPrime, Five)
{
  EXPECT_TRUE(workshop::isPrime(5));
}

TEST(IsPrime, Seven)
{
  EXPECT_TRUE(workshop::isPrime(7));
}

TEST(IsPrime, TwentyThree)
{
  EXPECT_TRUE(workshop::isPrime(23));
}

TEST(IsPrime, TwentyFour)
{
  EXPECT_FALSE(workshop::isPrime(24));
}

TEST(IsPrime, OneOneNineThree)
{
  EXPECT_TRUE(workshop::isPrime(1193));
}

}  // namespace hyped::test