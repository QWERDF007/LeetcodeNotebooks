#pragma once

#include <string>

namespace leetcode
{

enum ProblemType {
    ARRAY = 1,
    LINKED_LIST,
};

enum SolutionsId {
    TWO_SUM = 1,
    ADD_TWO_NUMBERS,
};

class LeetcodeSolution
{
public:
    /**
     * @brief leetcode 题目
     *
     * @return std::string 题目
     */
    virtual std::string Title() = 0;

    /**
     * @brief leetcode 题目问题描述
     * 
     * @return std::string 问题描述
     */
    virtual std::string Problem() = 0;

    /**
     * @brief 链接
     *
     * @return 链接
     */
    virtual std::string Link() = 0;

    /**
     * @brief leetcode 解决方案
     * 
     */
    virtual std::string Solution() = 0;

    /**
     * @brief 评估 solution 的性能
     * 
     * @return std::string 性能报告
     */
    virtual std::string Benchmark() = 0;
};
    
} // namespace leetcode


