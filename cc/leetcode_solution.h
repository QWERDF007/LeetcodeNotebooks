#pragma once

#include <string>

namespace leetcode
{

enum SolutionsId {
    TWO_SUM = 1,
    ADD_TWO_NUMBERS,
};

class LeetcodeSolution
{
public:
    /**
     * @brief leetcode 题目问题描述
     * 
     * @return std::string 问题描述
     */
    virtual std::string problem() = 0;

    /**
     * @brief leetcode 解决方案
     * 
     */
    virtual void solution() = 0;

    /**
     * @brief 评估 solution 的性能
     * 
     * @return std::string 性能报告
     */
    virtual std::string benchmark() = 0;
};
    
} // namespace leetcode


