#include <gtest/gtest.h>
#include "greedy_algorithm/greedy_algorithm.h"

namespace leetcode {
namespace test {

using namespace greedy;

TEST(GreedyAlgorithmTest, FindContentChildrenTest) {
    FindContentChildren solution;
    std::vector<std::vector<int>> g{
        { 1,2,3 },
        { 1,2 },
    };

    std::vector<std::vector<int>> s{
        { 1,1 },
        { 1,2,3 }
    };

    std::vector<int> targets{
        1,2,
    };

    EXPECT_EQ(solution.Solution1(g[0], s[0]), targets[0]);
    EXPECT_EQ(solution.Solution1(g[1], s[1]), targets[1]);
}

} // namespace test
} // namespace leetcode
