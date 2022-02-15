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
    STR = 2,
    MATH = 5,
    LINKED_LIST,
    BITWISE_OPERATION,
};

/**
 * @brief 题目号，对应leetcode上的题目
 * 
 */
enum SolutionsId {
    TWO_SUM = 1,
    ADD_TWO_NUMBERS = 2,
    IS_PALINDROME = 9,
    ROMAN_TO_INT = 13,
    REMOVE_DUPLICATES = 26,
    ADD_BINARY = 67,
    MY_SQRT = 69,
    CONVERT_TO_TITLE = 168,
    HAMMING_WEIGHT = 191,
    IS_HAPPY = 202,
    MISSING_NUMBER = 268,
    NUM_ARRAY = 303,
    INTERSECTION = 349,
    INTERSECT = 350,
    THIRD_MAX = 414,
    FIND_DISAPPEARED_NUMBERS = 448,
    MIN_MOVES = 453,
    SINGLE_NON_DUPLICATE = 540,
    MAX_NUMBER_OF_BALLONS = 1189,
    LUCKY_NUMBERS = 1380,
    MAX_POWER = 1446,
    SECOND_HIGHEST = 1796,
    MINIMUM_DIFFERENCE = 1984,
};
    
} // namespace leetcode


