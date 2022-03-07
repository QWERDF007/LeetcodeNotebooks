#pragma once

#include <unordered_set>
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
     * 时间复杂度：O(log n)
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

    /**
     * @brief 暴力解法
     * 时间复杂度：O(x^{1/2})
     * 空间复杂度：O(1)
     * @param x 
     * @return int 
     */
    int Solution1(int x);

    /**
     * @brief 二分查找
     * 时间复杂度：O(log x)
     * 空间复杂度：O(1)
     * @param x 
     * @return int 
     */
    int Solution2(int x);

    /**
     * @brief 牛顿迭代
     * 时间复杂度：O(log x)
     * 空间复杂度：O(1)
     * @param x 
     * @return int 
     */
    int Solution3(int x);

    /**
     * @brief 数学替换
     * 时间复杂度：O(1)
     * 空间复杂度：O(1)
     * @param x 
     * @return int 
     */
    int Solution4(int x);
};

class IsHappy : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 哈希集合
     * 时间复杂度：O(log n)
     * 空间复杂度：O(log n)
     * @param n 
     * @return true 
     * @return false 
     */
    bool Solution1(int n);

    /**
     * @brief 快慢指针
     * 时间复杂度：O(log n)
     * 空间复杂度：O(1)
     * @param n 
     * @return true 
     * @return false 
     */
    bool Solution2(int n);

    /**
     * @brief 数学分析
     * 时间复杂度：O(log n)
     * 空间复杂度：O(1)
     * @param n 
     * @return true 
     * @return false 
     */
    bool Solution3(int n);

private:
    int GetNext(int n);

    std::unordered_set<int> cycle_nums_{ 4, 16, 37, 58, 89, 145, 42, 20 };
};


class AddDigits : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 递归
     * 时间复杂度：O(log n)
     * 空间复杂度：O(log n)
     * @param num 
     * @return int 数根
     */
    int Solution1(int num);

    /**
     * @brief 循环
     * 时间复杂度：O(log n)
     * 空间复杂度：O(1)
     * @param num 
     * @return int 数根
     */
    int Solution2(int num);

    /**
     * @brief 数学
     * 时间复杂度：O(1)
     * 空间复杂度：O(1)
     * @param num 
     * @return int 数根
     */
    int Solution3(int num);
};

class ConvertToBase7 : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 倒推+迭代
     * 时间复杂度：O(log |num|)
     * 空间复杂度：O(1)
     * @param num 10进制数
     * @return std::string 7进制字符串
     */
    std::string Solution1(int num);
};


class ComplexNumberMultiply : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 遍历
     * 时间复杂度：O(n+m)
     * 空间复杂度：O(1)
     * @param num1 字符串复数
     * @param num2 字符串复数
     * @return std::string 复数相乘结果
     */
    std::string Solution1(std::string num1, std::string num2);

    /**
     * @brief 正则匹配
     * 时间复杂度：O(n+m)
     * 空间复杂度：O(1)
     * @param num1 字符串复数
     * @param num2 字符串复数
     * @return std::string 复数相乘结果
     */
    std::string Solution2(std::string num1, std::string num2);
};

} // namespace math
} // namespace leetcode
