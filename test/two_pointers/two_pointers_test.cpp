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

} // namespace test
} // namespace leetcode
