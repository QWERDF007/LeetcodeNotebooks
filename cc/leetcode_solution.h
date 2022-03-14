#pragma once

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

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
enum class ProblemType {
    ARRAY = 1,
    STR = 2,
    DYNAMIC_PROGRAMMING = 4,
    MATH = 5,
    GREEDY_ALGORITHM,
    LINKED_LIST,
    BITWISE_OPERATION,
    TREE,
    TWO_POINTERS,
    GRAPH,
};

/**
 * @brief ProblemType 到字符串的映射
 * 
 */
const std::map<ProblemType, std::string> kTypeToStr{
    { ProblemType::ARRAY, "ARRAY" },
    { ProblemType::STR, "STR" },
    { ProblemType::DYNAMIC_PROGRAMMING, "DYNAMIC_PROGRAMMING" },
    { ProblemType::MATH, "MATH" },
    { ProblemType::GREEDY_ALGORITHM, "GREEDY_ALGORITHM" },
    { ProblemType::LINKED_LIST, "LINKED_LIST" },
    { ProblemType::BITWISE_OPERATION, "BITWISE_OPERATION" },
    { ProblemType::TREE, "TREE" },
    { ProblemType::TWO_POINTERS, "TWO_POINTERS" },
    { ProblemType::GRAPH, "GRAPH" },
};

/**
 * @brief 题目号，对应leetcode上的题目
 * 
 */
enum class SolutionsId {
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
    CONVERT_TO_BASE_7 = 504,
    SINGLE_NON_DUPLICATE = 540,
    COMPLEX_NUMBER_MULTIPLY = 537,
    FIND_TILT = 563,
    IS_SUBTREE = 572,
    PREORDER = 589,
    POSTORDER = 590,
    FIND_RESTAURANT = 599,
    TREE_2_STR = 606,
    AVERAGE_OF_LEVELS = 637,
    FIND_TARGET = 653,
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
    PLATES_BETWEEN_CANDLES = 2055,
};

/**
 * @brief pid 到 type 的映射
 * 
 */
const std::map<SolutionsId, ProblemType> kPidToType{
    { SolutionsId::TWO_SUM, ProblemType::ARRAY },
    { SolutionsId::ADD_TWO_NUMBERS, ProblemType::LINKED_LIST },
    { SolutionsId::IS_PALINDROME, ProblemType::MATH },
    { SolutionsId::ROMAN_TO_INT, ProblemType::STR },
    { SolutionsId::REMOVE_DUPLICATES, ProblemType::ARRAY },
    { SolutionsId::ADD_BINARY, ProblemType::STR },
    { SolutionsId::MY_SQRT, ProblemType::MATH },
    { SolutionsId::INORDER_TRAVERSAL, ProblemType::TREE },
    { SolutionsId::IS_SAME_TREE, ProblemType::TREE },
    { SolutionsId::IS_BALANCED, ProblemType::TREE },
    { SolutionsId::MIN_DEPTH, ProblemType::TREE },
    { SolutionsId::HAS_PATH_SUM, ProblemType::TREE },
    { SolutionsId::PREORDER_TRAVERSAL, ProblemType::TREE },
    { SolutionsId::POSTORDER_TRAVERSAL, ProblemType::TREE },
    { SolutionsId::UPSIDE_DOWN_BINARY_TREE, ProblemType::TREE },
    { SolutionsId::FIND_MISSING_RANGES, ProblemType::ARRAY },
    { SolutionsId::CONVERT_TO_TITLE, ProblemType::STR },
    { SolutionsId::HAMMING_WEIGHT, ProblemType::BITWISE_OPERATION },
    { SolutionsId::IS_HAPPY, ProblemType::MATH },
    { SolutionsId::INVERT_TREE, ProblemType::TREE },
    { SolutionsId::LOWEST_COMMON_ANCESTOR, ProblemType::TREE },
    { SolutionsId::BINARY_TREE_PATHS, ProblemType::TREE },
    { SolutionsId::ADD_DIGITS, ProblemType::MATH },
    { SolutionsId::MISSING_NUMBER, ProblemType::ARRAY },
    { SolutionsId::NUM_ARRAY, ProblemType::ARRAY },
    { SolutionsId::INTERSECTION, ProblemType::ARRAY },
    { SolutionsId::INTERSECT, ProblemType::ARRAY },
    { SolutionsId::SUM_OF_LEFT_LEAVES, ProblemType::TREE },
    { SolutionsId::LONGEST_PALINDROME, ProblemType::STR },
    { SolutionsId::THIRD_MAX, ProblemType::ARRAY },
    { SolutionsId::FIND_DISAPPEARED_NUMBERS, ProblemType::ARRAY },
    { SolutionsId::MIN_MOVES, ProblemType::ARRAY },
    { SolutionsId::FIND_CONTENT_CHILDREN, ProblemType::GREEDY_ALGORITHM },
    { SolutionsId::FIND_MODE, ProblemType::TREE },
    { SolutionsId::CONVERT_TO_BASE_7, ProblemType::MATH },
    { SolutionsId::SINGLE_NON_DUPLICATE, ProblemType::ARRAY },
    { SolutionsId::COMPLEX_NUMBER_MULTIPLY, ProblemType::MATH },
    { SolutionsId::FIND_TILT, ProblemType::TREE },
    { SolutionsId::IS_SUBTREE, ProblemType::TREE },
    { SolutionsId::PREORDER, ProblemType::TREE },
    { SolutionsId::POSTORDER, ProblemType::TREE },
    { SolutionsId::FIND_RESTAURANT, ProblemType::STR },
    { SolutionsId::TREE_2_STR, ProblemType::TREE },
    { SolutionsId::AVERAGE_OF_LEVELS, ProblemType::TREE },
    { SolutionsId::FIND_TARGET, ProblemType::TREE },
    { SolutionsId::KNIGHT_PROBABILITY, ProblemType::DYNAMIC_PROGRAMMING },
    { SolutionsId::IS_ONE_BIT_CHARACTER, ProblemType::ARRAY },
    { SolutionsId::PUSH_DOMINOES, ProblemType::TWO_POINTERS },
    { SolutionsId::REVERSE_ONLY_LETTERS, ProblemType::TWO_POINTERS },
    { SolutionsId::PANCAKE_SORT, ProblemType::GREEDY_ALGORITHM },
    { SolutionsId::COMMON_CHARS, ProblemType::STR },
    { SolutionsId::MAX_NUMBER_OF_BALLONS, ProblemType::STR },
    { SolutionsId::LUCKY_NUMBERS, ProblemType::ARRAY },
    { SolutionsId::MAX_POWER, ProblemType::STR },
    { SolutionsId::FIND_BALL, ProblemType::ARRAY },
    { SolutionsId::FIND_CENTER, ProblemType::GRAPH },
    { SolutionsId::SECOND_HIGHEST, ProblemType::STR },
    { SolutionsId::MINIMUM_DIFFERENCE, ProblemType::ARRAY },
    { SolutionsId::MAXIMUM_DIFFERENCE, ProblemType::ARRAY },
    { SolutionsId::PLATES_BETWEEN_CANDLES, ProblemType::STR },
};

/**
 * @brief 重载 cout，输出 SolutionsId
 * 利用 inline 修饰，可以避免头文件被多重引用时的重复定义
 * @param os 输出流
 * @param obj SolutionsId 枚举类
 * @return std::ostream& 输出流 
 */
inline std::ostream &operator << (std::ostream &os, const SolutionsId obj) {
    os << static_cast<std::underlying_type<SolutionsId>::type>(obj);
    return os;
}

/**
 * @brief 重载 cout，输出 ProblemType
 * 利用 inline 修饰，可以避免头文件被多重引用时的重复定义
 * @param os 输出流
 * @param obj ProblemType 枚举类
 * @return std::ostream& 输出流
 */
inline std::ostream &operator << (std::ostream &os, const ProblemType obj) {
    os << static_cast<std::underlying_type<ProblemType>::type>(obj);
    return os;
}


} // namespace leetcode


