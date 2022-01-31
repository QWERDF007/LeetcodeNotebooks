#include <gtest/gtest.h>
#include "array/array.h"

namespace leetcode {
namespace array {

TEST(TwoSumTest, TwoSunSolution) {
    TwoSum solution;
    
    std::vector<std::vector<int>> nums({
        { 2,7,11,15 },
        { 3,2,4 },
        { 3,3 },
        { 2,7,11,15,12,15,67,45,66,11,22,44,978,123,95 },
    });

    std::vector<int> targets({
        9,
        6,
        6,
        24,
    });

    std::vector<std::vector<int>> results({ 
        { 0,1 },
        { 1,2 },
        { 0,1 },
        { 0,10 },
    });

    EXPECT_EQ(solution.Solution1(nums[0], targets[0]), results[0]);
    EXPECT_EQ(solution.Solution1(nums[1], targets[1]), results[1]);
    EXPECT_EQ(solution.Solution1(nums[2], targets[2]), results[2]);
    EXPECT_EQ(solution.Solution1(nums[3], targets[3]), results[3]);

    EXPECT_EQ(solution.Solution2(nums[0], targets[0]), results[0]);
    EXPECT_EQ(solution.Solution2(nums[1], targets[1]), results[1]);
    EXPECT_EQ(solution.Solution2(nums[2], targets[2]), results[2]);
    EXPECT_EQ(solution.Solution2(nums[3], targets[3]), results[3]);
}

};
};


