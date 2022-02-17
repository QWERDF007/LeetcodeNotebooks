#include <gtest/gtest.h>
#include "dynamic_programming/dynamic_programming.h"

namespace leetcode {
namespace test {

using namespace dp;

TEST(DynamicProgrammingTest, KnightProbabilityTest) {
    KnightProbability solution;

    EXPECT_EQ(solution.Solution1(3, 2, 0, 0), 0.0625);
    EXPECT_EQ(solution.Solution1(1, 0, 0, 0), 1.00000);
}

} // namespace test
} // namespace leetcode
