#pragma once

#include <string>

namespace leetcode {

class LeetcodeSolution {
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
     * @return 
     */
    virtual std::string Link() = 0;

    /**
     * @brief 解决方案
     * 
     * @return std::string 
     */
    virtual std::string Solution() = 0;

    /**
     * @brief 性能测试
     * 
     */
    virtual void Benchmark() = 0;
};

/**
 * @brief 问题类型
 * 
 */
enum ProblemType {
    ARRAY = 1,
    LINKED_LIST,
};

/**
 * @brief 题目号，对应leetcode上的题目
 * 
 */
enum SolutionsId {
    TWO_SUM = 1,
    ADD_TWO_NUMBERS = 2,
    REMOVE_DUPLICATES = 26,
    MISSING_NUMBER = 268,
};
    
} // namespace leetcode


