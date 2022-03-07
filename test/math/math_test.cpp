#include <gtest/gtest.h>
#include <climits>
#include "math/leetcode_math.h"

namespace leetcode {
namespace test {

using namespace math;

TEST(MathTest, IsPalindromeTest) {
    IsPalindrome solution;

    EXPECT_TRUE(solution.Solution1(121));
    EXPECT_FALSE(solution.Solution1(-121));
    EXPECT_FALSE(solution.Solution1(-101));
    EXPECT_FALSE(solution.Solution1(10));

    EXPECT_TRUE(solution.Solution2(121));
    EXPECT_FALSE(solution.Solution2(-121));
    EXPECT_FALSE(solution.Solution2(-101));
    EXPECT_FALSE(solution.Solution2(10));

    EXPECT_TRUE(solution.Solution3(121));
    EXPECT_FALSE(solution.Solution3(-121));
    EXPECT_FALSE(solution.Solution3(-101));
    EXPECT_FALSE(solution.Solution3(10));

    EXPECT_TRUE(solution.Solution4(121));
    EXPECT_FALSE(solution.Solution4(-121));
    EXPECT_FALSE(solution.Solution4(-101));
    EXPECT_FALSE(solution.Solution4(10));
}

TEST(MathTest, MySqrtTest) {
    MySqrt solution;

    EXPECT_EQ(solution.Solution1(0), 0);
    EXPECT_EQ(solution.Solution1(4), 2);
    EXPECT_EQ(solution.Solution1(8), 2);
    EXPECT_EQ(solution.Solution1(123336), 351);

    EXPECT_EQ(solution.Solution2(0), 0);
    EXPECT_EQ(solution.Solution2(4), 2);
    EXPECT_EQ(solution.Solution2(8), 2);
    EXPECT_EQ(solution.Solution2(123336), 351);

    EXPECT_EQ(solution.Solution3(0), 0);
    EXPECT_EQ(solution.Solution3(4), 2);
    EXPECT_EQ(solution.Solution3(8), 2);
    EXPECT_EQ(solution.Solution3(123336), 351);

    EXPECT_EQ(solution.Solution4(0), 0);
    EXPECT_EQ(solution.Solution4(4), 2);
    EXPECT_EQ(solution.Solution4(8), 2);
    EXPECT_EQ(solution.Solution4(123336), 351);
}

TEST(MathTest, IsHappyTest) {
    IsHappy solution;

    EXPECT_TRUE(solution.Solution1(19));
    EXPECT_TRUE(solution.Solution2(19));
    EXPECT_TRUE(solution.Solution3(19));
    
    EXPECT_FALSE(solution.Solution1(2));
    EXPECT_FALSE(solution.Solution2(2));
    EXPECT_FALSE(solution.Solution3(2));

    EXPECT_FALSE(solution.Solution1(INT_MAX));
    EXPECT_FALSE(solution.Solution2(INT_MAX));
    EXPECT_FALSE(solution.Solution3(INT_MAX));
}

TEST(MathTest, AddDigitsTest) {
    AddDigits solution;
    std::vector<int> nums{
        38, 0,
    };
    std::vector<int> results{
        2, 0
    };

    EXPECT_EQ(solution.Solution1(nums[0]), results[0]);
    EXPECT_EQ(solution.Solution1(nums[1]), results[1]);

    EXPECT_EQ(solution.Solution2(nums[0]), results[0]);
    EXPECT_EQ(solution.Solution2(nums[1]), results[1]);

    EXPECT_EQ(solution.Solution3(nums[0]), results[0]);
    EXPECT_EQ(solution.Solution3(nums[1]), results[1]);
}

TEST(MathTest, ConvertToBase7Test) {
    ConvertToBase7 solution;

    std::vector<int> nums{
        100, -7, 0,
    };

    std::vector<std::string> results{
        "202", "-10", "0",
    };

    EXPECT_EQ(solution.Solution1(nums[0]), results[0]);
    EXPECT_EQ(solution.Solution1(nums[1]), results[1]);
    EXPECT_EQ(solution.Solution1(nums[2]), results[2]);
}

TEST(MathTest, ComplexNumberMultiplyTest) {
    ComplexNumberMultiply solution;

    EXPECT_EQ(solution.Solution1("0+0i", "0+0i"), "0+0i");
    EXPECT_EQ(solution.Solution1("1+1i", "1+1i"), "0+2i");
    EXPECT_EQ(solution.Solution1("1+1i", "1+-1i"), "2+0i");
    EXPECT_EQ(solution.Solution1("100+100i", "100+-100i"), "20000+0i");

    EXPECT_EQ(solution.Solution2("0+0i", "0+0i"), "0+0i");
    EXPECT_EQ(solution.Solution2("1+1i", "1+1i"), "0+2i");
    EXPECT_EQ(solution.Solution2("1+1i", "1+-1i"), "2+0i");
    EXPECT_EQ(solution.Solution2("100+100i", "100+-100i"), "20000+0i");
}

} // namespace test
} // namespace leetcode 