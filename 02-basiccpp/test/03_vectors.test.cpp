#include <03_vectors.hpp>
#include <gtest/gtest.h>

namespace hyped::test {

TEST(SumTest, handlesEmpty)
{
  const std::vector<double> v;
  ASSERT_EQ(0, workshop::sum(v));
  ASSERT_EQ(0, workshop::absoluteSum(v));
  ASSERT_EQ(0, workshop::countNegatives(v));
  ASSERT_EQ(0, workshop::average(v));
}

TEST(SumTest, handlesAllNonNegative)
{
  const std::vector<double> v = {1, 2, 4, 8, 16};
  ASSERT_EQ(31, workshop::sum(v));
  ASSERT_EQ(31, workshop::absoluteSum(v));
  ASSERT_EQ(0, workshop::countNegatives(v));
  ASSERT_EQ(6.2, workshop::average(v));
}

TEST(SumTest, handlesAllNegative)
{
  const std::vector<double> v = {-1, -2, -4, -8, -16};
  ASSERT_EQ(-31, workshop::sum(v));
  ASSERT_EQ(31, workshop::absoluteSum(v));
  ASSERT_EQ(5, workshop::countNegatives(v));
  ASSERT_EQ(-6.2, workshop::average(v));
}

TEST(SumTest, handlesMixedSigns)
{
  const std::vector<double> v = {-1, -2, -4, -8, 16};
  ASSERT_EQ(1, workshop::sum(v));
  ASSERT_EQ(31, workshop::absoluteSum(v));
  ASSERT_EQ(4, workshop::countNegatives(v));
  ASSERT_EQ(0.2, workshop::average(v));
}
}  // namespace hyped::test