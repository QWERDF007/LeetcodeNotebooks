#pragma once

#include <cstdint>
#include "leetcode_solution.h"

namespace leetcode {
namespace bit {

void BitwiseOperationSolution(SolutionsId pid);

class HammingWeight : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 左移
     * 时间复杂度：O(n)，n 为最高位 1 的位置
     * 空间复杂度：O(1)
     * @param n 
     * @return int 
     */
    int Solution1(uint32_t n);

    /**
     * @brief 右移
     * 时间复杂度：O(n)，n 为最高位 1 的位置
     * 空间复杂度：O(1)
     * @param n 
     * @return int 
     */
    int Solution2(uint32_t n);

    /**
     * @brief n-1
     * 时间复杂度：O(n)，n 为 1 的个数
     * 空间复杂度：O(1)
     * @param n 
     * @return int 
     */
    int Solution3(uint32_t n);
};

} // namespace bit
} // namespace leetcode
