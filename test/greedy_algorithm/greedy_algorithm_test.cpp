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

TEST(GreedyAlgorithmTest, PancakeSortTest) {
    PancakeSort solution;

    std::vector<std::vector<int>> arrs{
        { 3,2,4,1 },
        { 1,2,3 },
    };

    std::vector<std::vector<int>> arrs_to_pancake = arrs;

    std::vector<std::vector<int>> results{
        { 1,2,3,4 },
        { 1,2,3 },
    };

    std::vector<std::vector<int>> panake_indices;
    panake_indices.emplace_back(solution.Solution1(arrs[0]));
    panake_indices.emplace_back(solution.Solution1(arrs[1]));

    std::vector<int> pancake_times(arrs.size());
    pancake_times[0] = panake_indices[0].size();
    pancake_times[1] = panake_indices[1].size();

    solution.Pancake(arrs_to_pancake[0], panake_indices[0]);
    solution.Pancake(arrs_to_pancake[1], panake_indices[1]);

    EXPECT_EQ(arrs_to_pancake[0], results[0]);
    EXPECT_EQ(arrs_to_pancake[1], results[1]);
    EXPECT_LE(pancake_times[0], 10 * arrs[0].size());
    EXPECT_LE(pancake_times[1], 10 * arrs[1].size());
}

} // namespace test
} // namespace leetcode
