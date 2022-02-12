#include <gtest/gtest.h>
#include "str/str.h"

namespace leetcode {
namespace test {

using namespace str;

TEST(StrTest, RomanToIntTest) {
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

TEST(StrTest, AddBinaryTest) {
    AddBinary solution;

    std::vector<std::string> a{
        "11",
        "1010",
        "10100000100100110110010000010101111011011001101110111111111101000000101111001110001111100001101",
    };

    std::vector<std::string> b{
        "1",
        "1011",
        "110101001011101110001111100110001010100001101011101010000011011011001011101111001100000011011110011",
    };

    std::vector<std::string> results{
        "100",
        "10101",
        "110111101100010011000101110110100000011101000101011001000011011000001100011110011010010011000000000",
    };

    EXPECT_EQ(solution.Solution1(a[0], b[0]), results[0]);
    EXPECT_EQ(solution.Solution1(a[1], b[1]), results[1]);
    EXPECT_EQ(solution.Solution1(a[2], b[2]), results[2]);

    EXPECT_EQ(solution.Solution2(a[0], b[0]), results[0]);
    EXPECT_EQ(solution.Solution2(a[1], b[1]), results[1]);
    EXPECT_EQ(solution.Solution2(a[2], b[2]), results[2]);
}

TEST(StrTest, ConvertToTitleTest) {
    ConvertToTitle solution;

    EXPECT_EQ(solution.Solution1(1), "A");
    EXPECT_EQ(solution.Solution1(28), "AB");
    EXPECT_EQ(solution.Solution1(52), "AZ");
    EXPECT_EQ(solution.Solution1(701), "ZY");

    EXPECT_EQ(solution.Solution2(1), "A");
    EXPECT_EQ(solution.Solution2(28), "AB");
    EXPECT_EQ(solution.Solution2(52), "AZ");
    EXPECT_EQ(solution.Solution2(701), "ZY");
}

TEST(StrTest, SecondHighestTest) {
    SecondHighest solution;

    EXPECT_EQ(solution.Solution1("dfa12321afd"), 2);
    EXPECT_EQ(solution.Solution1("abc1111"), -1);
    EXPECT_EQ(solution.Solution1("ck077"), 0);

    EXPECT_EQ(solution.Solution2("dfa12321afd"), 2);
    EXPECT_EQ(solution.Solution2("abc1111"), -1);
    EXPECT_EQ(solution.Solution2("ck077"), 0);

    EXPECT_EQ(solution.Solution3("dfa12321afd"), 2);
    EXPECT_EQ(solution.Solution3("abc1111"), -1);
    EXPECT_EQ(solution.Solution3("ck077"), 0);
}

TEST(StrTest, MaxPowerTest) {
    MaxPower solution;

    EXPECT_EQ(solution.Solution1("leetcode"), 2);
    EXPECT_EQ(solution.Solution1("abbcccddddeeeeedcba"), 5);
    EXPECT_EQ(solution.Solution1("triplepillooooow"), 5);
    EXPECT_EQ(solution.Solution1("hooraaaaaaaaaaay"), 11);
    EXPECT_EQ(solution.Solution1("tourist"), 1);
}

} // namespace test
} // namespace leetcode
