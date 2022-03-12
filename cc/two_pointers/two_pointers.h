#pragma once

#include <vector>
#include "leetcode_solution.h"

namespace leetcode {
namespace tp {

void TwoPointersSolution(SolutionsId pid);

class PushDominoes : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 双指针模拟
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param dominoes 多米诺骨牌的初始状态
     * @return std::string 多米诺骨牌的最终状态
     */
    std::string Solution1(std::string dominoes);
    
    /**
     * @brief 广度优先搜索 (BFS)
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param dominoes 多米诺骨牌的初始状态
     * @return std::string 多米诺骨牌的最终状态
     */
    std::string Solution2(std::string dominoes);
};

class ReverseOnlyLetters : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 双指针 (就地)
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param s 待反转的字符串
     * @return std::string 反转后的字符串
     */
    std::string Solution1(std::string s);

    /**
     * @brief 双指针
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param s 待反转的字符串
     * @return std::string 反转后的字符串
     */
    std::string Solution2(std::string s);
};

} // namespace tp
} // namespace leetcode
