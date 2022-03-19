#include <gtest/gtest.h>
#include "dynamic_programming/dynamic_programming.h"

namespace leetcode {
namespace test {

using namespace dp;

TEST(DynamicProgrammingTest, NumTreesTest) {
    NumTrees solution;
    std::vector<int> n{
        3, 1, 19
    };

    std::vector<int> results{
        5, 1, 1767263190,
    };

    EXPECT_EQ(solution.Solution1(n[0]), results[0]);
    EXPECT_EQ(solution.Solution1(n[1]), results[1]);
    EXPECT_EQ(solution.Solution1(n[2]), results[2]);

    EXPECT_EQ(solution.Solution2(n[0]), results[0]);
    EXPECT_EQ(solution.Solution2(n[1]), results[1]);
    EXPECT_EQ(solution.Solution2(n[2]), results[2]);
}

TEST(DynamicProgrammingTest, KnightProbabilityTest) {
    KnightProbability solution;

    EXPECT_EQ(solution.Solution1(3, 2, 0, 0), 0.0625);
    EXPECT_EQ(solution.Solution1(1, 0, 0, 0), 1.00000);
}

} // namespace test
} // namespace leetcode
