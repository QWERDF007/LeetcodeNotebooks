#include <gtest/gtest.h>
#include "str/str.h"

namespace leetcode {
namespace test {

using namespace str;

TEST(RomanToIntTest, LeetcodeTest) {
    RomanToInt solution;

    std::vector<std::string> strs{
        "III",
        "LVIII",
        "MCMXCIV",
        "MMMDCCCLXXXVIII",
    };

    std::vector<int> results{
        3,
        58,
        1994,
        3888,
    };

    EXPECT_EQ(solution.Solution1(strs[0]), results[0]);
    EXPECT_EQ(solution.Solution1(strs[1]), results[1]);
    EXPECT_EQ(solution.Solution1(strs[2]), results[2]);
    EXPECT_EQ(solution.Solution1(strs[3]), results[3]);

    EXPECT_EQ(solution.Solution2(strs[0]), results[0]);
    EXPECT_EQ(solution.Solution2(strs[1]), results[1]);
    EXPECT_EQ(solution.Solution2(strs[2]), results[2]);
    EXPECT_EQ(solution.Solution2(strs[3]), results[3]);

    EXPECT_EQ(solution.Solution3(strs[0]), results[0]);
    EXPECT_EQ(solution.Solution3(strs[1]), results[1]);
    EXPECT_EQ(solution.Solution3(strs[2]), results[2]);
    EXPECT_EQ(solution.Solution3(strs[3]), results[3]);
}

} // namespace test
} // namespace leetcode
