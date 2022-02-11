#include <gtest/gtest.h>
#include "math/leetcode_math.h"

namespace leetcode {
namespace test {

using namespace math;

TEST(IsPalindromeTest, LeetcodeTest) {
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

} // namespace test
} // namespace leetcode 