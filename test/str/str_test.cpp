#include <gtest/gtest.h>
#include <algorithm>
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

TEST(StrTest, LongestPalindromeTest) {
    LongestPalindrome solution;

    EXPECT_EQ(solution.Solution1("abccccdd"), 7);
    EXPECT_EQ(solution.Solution1("a"), 1);
    EXPECT_EQ(solution.Solution1("bb"), 2);

    EXPECT_EQ(solution.Solution2("abccccdd"), 7);
    EXPECT_EQ(solution.Solution2("a"), 1);
    EXPECT_EQ(solution.Solution2("bb"), 2);
}

TEST(StrTest, FindRestaurantTest) {
    FindRestaurant solution;
    
    std::vector<std::vector<std::string>> list1{
        { "Shogun","Tapioca Express","Burger King","KFC" },
        { "Shogun","Tapioca Express","Burger King","KFC" },
        { "Shogun","Burger King","Tapioca Express","KFC" },
    };

    std::vector<std::vector<std::string>> list2{
        { "Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun" },
        { "KFC","Shogun","Burger King" },
        { "Burger King","Shogun","KFC" },
    };

    std::vector<std::vector<std::string>> results{
        { "Shogun" },
        { "Shogun" },
        { "Burger King","Shogun" },
    };

    std::vector<std::vector<std::string>> s1_ans, s2_ans;
    for (int i = 0; i < list1.size(); ++i) {
        s1_ans.emplace_back(solution.Solution1(list1[i], list2[i]));
        s2_ans.emplace_back(solution.Solution2(list1[i], list2[i]));
    }
    for (int i = 0; i < list1.size(); ++i) {
        std::sort(s1_ans[i].begin(), s1_ans[i].end());
        std::sort(s2_ans[i].begin(), s2_ans[i].end());
    }

    EXPECT_EQ(s1_ans[0], results[0]);
    EXPECT_EQ(s1_ans[1], results[1]);
    EXPECT_EQ(s1_ans[2], results[2]);

    EXPECT_EQ(s2_ans[0], results[0]);
    EXPECT_EQ(s2_ans[1], results[1]);
    EXPECT_EQ(s2_ans[2], results[2]);
}

TEST(StrTest, CommonCharsTest) {
    CommonChars solution;

    std::vector<std::vector<std::string>> words{
        { "bella","label","roller" },
        { "cool","lock","cook" },
    };

    std::vector<std::vector<std::string>> results{
        { "e", "l", "l" },
        { "c", "o" },
    };

    // 需要对结果字符串排序再比较
    EXPECT_EQ(solution.Solution1(words[0]), results[0]);
    EXPECT_EQ(solution.Solution1(words[1]), results[1]);
}

TEST(StrTest, MaxNumberOfBallonsTest) {
    MaxNumberOfBallons solution;

    EXPECT_EQ(solution.Solution1("nlaebolko"), 1);
    EXPECT_EQ(solution.Solution1("loonbalxballpoon"), 2);
    EXPECT_EQ(solution.Solution1("leetcode"), 0);
}

TEST(StrTest, MaxPowerTest) {
    MaxPower solution;

    EXPECT_EQ(solution.Solution1("leetcode"), 2);
    EXPECT_EQ(solution.Solution1("abbcccddddeeeeedcba"), 5);
    EXPECT_EQ(solution.Solution1("triplepillooooow"), 5);
    EXPECT_EQ(solution.Solution1("hooraaaaaaaaaaay"), 11);
    EXPECT_EQ(solution.Solution1("tourist"), 1);
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

TEST(StrTest, PlatesBetweenCandlesTest) {
    PlatesBetweenCandles solution;
    std::vector<std::string> strs{
        "**|**|***|",
        "***|**|*****|**||**|*",
    };
    
    std::vector<std::vector<std::vector<int>>> queries{
        { {2,5},{5,9} },
        { {1,17},{4,5},{14,17},{5,11},{15,16} },
    };

    std::vector<std::vector<int>> results{
        { 2,3 },
        { 9,0,0,0,0 },
    };

    EXPECT_EQ(solution.Solution1(strs[0], queries[0]), results[0]);
    EXPECT_EQ(solution.Solution1(strs[1], queries[1]), results[1]);

    EXPECT_EQ(solution.Solution2(strs[0], queries[0]), results[0]);
    EXPECT_EQ(solution.Solution2(strs[1], queries[1]), results[1]);
}

} // namespace test
} // namespace leetcode
