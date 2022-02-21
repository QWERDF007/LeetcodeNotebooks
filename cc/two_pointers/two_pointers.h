#pragma once

#include <vector>
#include "leetcode_solution.h"

namespace leetcode {
namespace tp {

void TwoPointersSolution(int pid);

class PushDominoes : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    std::string Solution1(std::string dominoes);

    std::string Solution2(std::string dominoes);
};

} // namespace tp
} // namespace leetcode
