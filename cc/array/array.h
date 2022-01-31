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

    std::string Solution() override;

    std::string Benchmark() override;
    
    /**
     * @brief 两数之和：暴力枚举
     * 时间复杂度：O(n^2)
     * 空间复杂度：O(1)
     * @param nums 
     * @param target 
     * @return std::vector<int> 
     */
    std::vector<int> Solution1(std::vector<int>& nums, int target);

    /**
     * @brief 两数之和：哈希表
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param nums 
     * @param target 
     * @return std::vector<int> 
     */
    std::vector<int> Solution2(std::vector<int>& nums, int target);
};

} // namespace array
} // namespace leetcode
