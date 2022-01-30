#pragma once

#include <iostream>
#include <vector>

#include "leetcode_solution.h"

namespace leetcode {
namespace array{

void ArraySolution(int pid);

class TwoSum : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    void Solution() override;

    std::string Benchmark() override;

    std::vector<int> Solution1(std::vector<int>& nums, int target);
};

} // namespace array
} // namespace leetcode
