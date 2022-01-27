#pragma once

#include <iostream>
#include "leetcode_solution.h"

namespace leetcode {
namespace array{

void ArraySolution(int pid);

class TwoSum : public LeetcodeSolution {
public:
    std::string problem() override;

    void solution() override;

    std::string benchmark() override;

    void _benchmark();
};

} // namespace array
} // namespace leetcode
