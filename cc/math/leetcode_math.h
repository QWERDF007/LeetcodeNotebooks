#pragma once

#include "leetcode_solution.h"

namespace leetcode {
namespace math {

void MathSolution(int pid);

class IsPalindrome : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 转字符串+双指针
     * 时间复杂度：O(log n)
     * 空间复杂度：O(1)
     * @param x 
     * @return true 
     * @return false 
     */
    bool Solution1(int x);

    /**
     * @brief 反转一半数字
     * 时间复杂度：O(log n)
     * 空间复杂度：O(1)
     * @param x 
     * @return true 
     * @return false 
     */
    bool Solution2(int x);

    /**
     * @brief 双指针
     * 时间复杂度：O(log n)
     * 空间复杂度：O(1)
     * @param x 
     * @return true 
     * @return false 
     */
    bool Solution3(int x);

    /**
     * @brief 转字符串+反转字符串
     * 时间复杂度：O(logn)
     * 空间复杂度：O(1)
     * @param x 
     * @return true 
     * @return false 
     */
    bool Solution4(int x);
};

class MySqrt : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    int Solution1(int x);

    int Solution2(int x);

    int Solution3(int x);

    int Solution4(int x);
};

} // namespace math
} // namespace leetcode
