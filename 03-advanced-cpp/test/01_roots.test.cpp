#include <01_roots.hpp>
#include <gtest/gtest.h>

namespace hyped::test {

TEST(RootTest, zeroCoefficients)
{
  EXPECT_ANY_THROW(workshop::QuadraticPolynomial p(0, 0, 0));
  EXPECT_ANY_THROW(workshop::QuadraticPolynomial p(0, 1, 1));
  EXPECT_NO_THROW(workshop::QuadraticPolynomial(1, 0, 0));
}

TEST(RootTest, twoSolutions)
{
  const workshop::QuadraticPolynomial p(1, 0, -1);
  ASSERT_TRUE(p.isRoot(-1.0));
  ASSERT_TRUE(p.isRoot(1.0));
  const auto roots = p.realRoots();
  ASSERT_EQ(roots.size(), 2);
  for (const double x : roots) {
    ASSERT_TRUE(p.isRoot(x));
  }
}

TEST(RootTest, oneSolution)
{
  const workshop::QuadraticPolynomial p(1, 0, 0);
  ASSERT_TRUE(p.isRoot(0));
  const auto roots = p.realRoots();
  ASSERT_EQ(roots.size(), 1);
  for (const auto x : roots) {
    ASSERT_TRUE(p.isRoot(x));
  }
}

TEST(RootTest, noSolutions)
{
  const workshop::QuadraticPolynomial p(1, 0, 1);
  const auto roots = p.realRoots();
  ASSERT_TRUE(roots.empty());
}

TEST(RootTest, construction)
{
  const workshop::QuadraticPolynomial p(1, 0, 0);
  const workshop::QuadraticPolynomial q(1, 0, -1);
  ASSERT_EQ(p, p);
  ASSERT_NE(p, q);
}

}  // namespace hyped::test
