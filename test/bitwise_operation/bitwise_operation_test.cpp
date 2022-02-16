#include <gtest/gtest.h>
#include "bitwise_operation/bitwise_operation.h"

namespace leetcode {
namespace test {

using namespace bit;

TEST(BitwiseOperationTest, HammingWeightTest) {
    HammingWeight solution;

    EXPECT_EQ(solution.Solution1(0b00000000000000000000000000001011), 3);
    EXPECT_EQ(solution.Solution1(0b00000000000000000000000010000000), 1);
    EXPECT_EQ(solution.Solution1(0b11111111111111111111111111111101), 31);
    EXPECT_EQ(solution.Solution1(0b11111111111111111111111111111111), 32);

    EXPECT_EQ(solution.Solution2(0b00000000000000000000000000001011), 3);
    EXPECT_EQ(solution.Solution2(0b00000000000000000000000010000000), 1);
    EXPECT_EQ(solution.Solution2(0b11111111111111111111111111111101), 31);
    EXPECT_EQ(solution.Solution2(0b11111111111111111111111111111111), 32);

    EXPECT_EQ(solution.Solution3(0b00000000000000000000000000001011), 3);
    EXPECT_EQ(solution.Solution3(0b00000000000000000000000010000000), 1);
    EXPECT_EQ(solution.Solution3(0b11111111111111111111111111111101), 31);
    EXPECT_EQ(solution.Solution3(0b11111111111111111111111111111111), 32);
}

} // namespace test
} // namespace leetcode
