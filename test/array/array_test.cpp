#include <gtest/gtest.h>
#include "array/array.h"

namespace leetcode {
namespace test {

using namespace array;

TEST(TwoSumTest, LeetcodeTest) {
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

TEST(RemoveDuplicatesTest, LeetcodeTest) {
    RemoveDuplicates solution;
    std::vector<std::vector<int>> nums({
        {},
        { 1,1,2 },
        { 0,0,1,1,1,2,2,3,3,4 },
        { 0,0,1,1,1,2,2,3,3,4,5,5,7,8,9,9,9,10,10,11 },
    });

    std::vector<int> results({
        0,
        2,
        5,
        11,
    });

    EXPECT_EQ(solution.Solution1(nums[0]), results[0]);
    EXPECT_EQ(solution.Solution1(nums[1]), results[1]);
    EXPECT_EQ(solution.Solution1(nums[2]), results[2]);
    EXPECT_EQ(solution.Solution1(nums[3]), results[3]);

    EXPECT_EQ(solution.Solution2(nums[0]), results[0]);
    EXPECT_EQ(solution.Solution2(nums[1]), results[1]);
    EXPECT_EQ(solution.Solution2(nums[2]), results[2]);
    EXPECT_EQ(solution.Solution2(nums[3]), results[3]);
}

TEST(MissingNumberTest, LeetcodeTest) {
    MissingNumber solution;
    std::vector<std::vector<int>> nums({
        { 3,0,1 },
        { 0,1 },
        { 9,6,4,2,3,5,7,0,1 },
    });

    std::vector<int> results({
        2,
        2,
        8,
    });

    EXPECT_EQ(solution.Solution1(nums[0]), results[0]);
    EXPECT_EQ(solution.Solution1(nums[1]), results[1]);
    EXPECT_EQ(solution.Solution1(nums[2]), results[2]);

    EXPECT_EQ(solution.Solution2(nums[0]), results[0]);
    EXPECT_EQ(solution.Solution2(nums[1]), results[1]);
    EXPECT_EQ(solution.Solution2(nums[2]), results[2]);

    EXPECT_EQ(solution.Solution3(nums[0]), results[0]);
    EXPECT_EQ(solution.Solution3(nums[1]), results[1]);
    EXPECT_EQ(solution.Solution3(nums[2]), results[2]);

    EXPECT_EQ(solution.Solution4(nums[0]), results[0]);
    EXPECT_EQ(solution.Solution4(nums[1]), results[1]);
    EXPECT_EQ(solution.Solution4(nums[2]), results[2]);
}

} // namespace test
} // namespace leetcode


