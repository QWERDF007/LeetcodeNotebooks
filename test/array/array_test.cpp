#include <gtest/gtest.h>
#include "array/array.h"

namespace leetcode {
namespace array {

TEST(TwoSumTest, Positive) {
    TwoSum sol;
    int target = 9;
    std::vector<int> inputs({ 2,7,11,15 }), res({ 0, 1 });
    EXPECT_EQ(sol.Solution1(inputs, target), res);
}

};
};


