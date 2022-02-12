#include <gtest/gtest.h>
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

} // namespace test
} // namespace leetcode 