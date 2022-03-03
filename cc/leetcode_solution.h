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
    DYNAMIC_PROGRAMMING = 4,
    MATH = 5,
    GREEDY_ALGORITHM,
    LINKED_LIST,
    BITWISE_OPERATION,
    BINARY_TREE,
    TWO_POINTERS,
    GRAPH,
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
    INORDER_TRAVERSAL = 94,
    IS_SAME_TREE = 100,
    IS_BALANCED = 110,
    MIN_DEPTH = 111,
    HAS_PATH_SUM = 112,
    PREORDER_TRAVERSAL = 144,
    POSTORDER_TRAVERSAL = 145,
    UPSIDE_DOWN_BINARY_TREE = 156,
    FIND_MISSING_RANGES = 163,
    CONVERT_TO_TITLE = 168,
    HAMMING_WEIGHT = 191,
    IS_HAPPY = 202,
    INVERT_TREE = 226,
    LOWEST_COMMON_ANCESTOR = 235,
    BINARY_TREE_PATHS = 257,
    ADD_DIGITS = 258,
    MISSING_NUMBER = 268,
    NUM_ARRAY = 303,
    INTERSECTION = 349,
    INTERSECT = 350,
    SUM_OF_LEFT_LEAVES = 404,
    LONGEST_PALINDROME = 409,
    THIRD_MAX = 414,
    FIND_DISAPPEARED_NUMBERS = 448,
    MIN_MOVES = 453,
    FIND_CONTENT_CHILDREN = 455,
    FIND_MODE = 501,
    SINGLE_NON_DUPLICATE = 540,
    COMPLEX_NUMBER_MULTIPLY = 537,
    KNIGHT_PROBABILITY = 688,
    IS_ONE_BIT_CHARACTER = 717,
    PUSH_DOMINOES = 838,
    REVERSE_ONLY_LETTERS = 917,
    PANCAKE_SORT = 969,
    COMMON_CHARS = 1002,
    MAX_NUMBER_OF_BALLONS = 1189,
    LUCKY_NUMBERS = 1380,
    MAX_POWER = 1446,
    FIND_BALL = 1706,
    FIND_CENTER = 1791,
    SECOND_HIGHEST = 1796,
    MINIMUM_DIFFERENCE = 1984,
    MAXIMUM_DIFFERENCE = 2016,
};
    
} // namespace leetcode


