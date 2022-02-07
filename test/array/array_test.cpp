#include <gtest/gtest.h>
#include <unordered_set>
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

TEST(NumArrayTest, LeetcodeTest) {
    int n = 1000;
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = i + 1;
    }

    NumArray solution(nums);

    std::vector<int> left{
        0,
        0,
        50,
        999,
    };

    std::vector<int> right{
        0,
        10,
        100,
        999,
    };

    std::vector<int> results{
        1,
        66,
        3876,
        1000,
    };

    EXPECT_EQ(solution.sumRange1(left[0], right[0]), results[0]);
    EXPECT_EQ(solution.sumRange1(left[1], right[1]), results[1]);
    EXPECT_EQ(solution.sumRange1(left[2], right[2]), results[2]);
    EXPECT_EQ(solution.sumRange1(left[3], right[3]), results[3]);

    EXPECT_EQ(solution.sumRange2(left[0], right[0]), results[0]);
    EXPECT_EQ(solution.sumRange2(left[1], right[1]), results[1]);
    EXPECT_EQ(solution.sumRange2(left[2], right[2]), results[2]);
    EXPECT_EQ(solution.sumRange2(left[3], right[3]), results[3]);
}

std::unordered_set<int> VectorToSet(std::vector<int>& nums) {
    return std::unordered_set<int>(nums.begin(), nums.end());
}

TEST(IntersectionTest, LeetcodeTest) {
    Intersection solution;
    std::vector<std::vector<int>> nums1{
        { 1,2,2,1 },
        { 4,9,5 },
    };

    std::vector<std::vector<int>> nums2{
        { 2,2 },
        { 9,4,9,8,4 },
    };

    std::vector<std::vector<int>> results{
        { 2 },
        { 9,4 },
    };

    EXPECT_EQ(VectorToSet(solution.Solution1(nums1[0], nums2[0])), VectorToSet(results[0]));
    EXPECT_EQ(VectorToSet(solution.Solution1(nums1[1], nums2[1])), VectorToSet(results[1]));

    EXPECT_EQ(VectorToSet(solution.Solution2(nums1[0], nums2[0])), VectorToSet(results[0]));
    EXPECT_EQ(VectorToSet(solution.Solution2(nums1[1], nums2[1])), VectorToSet(results[1]));
}

} // namespace test
} // namespace leetcode


