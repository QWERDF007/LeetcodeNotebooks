#include <gtest/gtest.h>
#include "two_pointers/two_pointers.h"

namespace leetcode {
namespace test {

using namespace tp;

TEST(TwoPointersTest, PushDominoesTest) {
    PushDominoes solution;

    EXPECT_EQ(solution.Solution1("RR..LL"), "RRRLLL");
    EXPECT_EQ(solution.Solution1("RR.L"), "RR.L");
    EXPECT_EQ(solution.Solution1(".L.R...LR..L.."), "LL.RR.LLRRLL..");

    EXPECT_EQ(solution.Solution2("RR..LL"), "RRRLLL");
    EXPECT_EQ(solution.Solution2("RR.L"), "RR.L");
    EXPECT_EQ(solution.Solution2(".L.R...LR..L.."), "LL.RR.LLRRLL..");
}

TEST(TwoPointersTest, ReverseOnlyLettersTest) {
    ReverseOnlyLetters solution;
    
    EXPECT_EQ(solution.Solution1("ab-cd"), "dc-ba");
    EXPECT_EQ(solution.Solution1("a-bC-dEf-ghIj"), "j-Ih-gfE-dCba");
    EXPECT_EQ(solution.Solution1("Test1ng-Leet=code-Q!"), "Qedo1ct-eeLg=ntse-T!");

    EXPECT_EQ(solution.Solution2("ab-cd"), "dc-ba");
    EXPECT_EQ(solution.Solution2("a-bC-dEf-ghIj"), "j-Ih-gfE-dCba");
    EXPECT_EQ(solution.Solution2("Test1ng-Leet=code-Q!"), "Qedo1ct-eeLg=ntse-T!");
}

} // namespace test
} // namespace leetcode
