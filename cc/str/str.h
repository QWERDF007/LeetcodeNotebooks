#pragma once

#include <string>
#include <unordered_map>

#include "leetcode_solution.h"

namespace leetcode {
namespace str {


/**
 * @brief 字符串题目入口
 *
 * @param pid 字符串题目id
 */
void StrSolution(SolutionsId pid);


class RomanToInt : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 暴力求解，列出所有情况
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param s 
     * @return int 
     */
    int Solution1(std::string s);

    /**
     * @brief 动态数组
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param s 
     * @return int 
     */
    int Solution2(std::string s);

    /**
     * @brief 哈希表
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param s 
     * @return int 
     */
    int Solution3(std::string s);

    std::unordered_map<char, int> symbols_value_{
        {'I',1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000}
    };
};

class AddBinary : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 列竖式(模拟)
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param a 
     * @param b 
     * @return std::string a + b 的二进制结果
     */
    std::string Solution1(std::string a, std::string b);

    /**
     * @brief 列竖式(位运算)
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param a 
     * @param b 
     * @return std::string a + b 的二进制结果
     */
    std::string Solution2(std::string a, std::string b);
};

class ConvertToTitle : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    std::string Solution1(int columnNumber);

    std::string Solution2(int columnNumber);
};

class LongestPalindrome : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 数组统计
     * 时间复杂度：O(n)
     * 空间复杂度：O(k)，k=52
     * @param s 
     * @return int 最长回文串长度
     */
    int Solution1(std::string s);

    /**
     * @brief 哈希表统计
     * 时间复杂度：O(n)
     * 空间复杂度：O(k)，k 为字符串中不重复的字符数
     * @param s 
     * @return int 最长回文串长度
     */
    int Solution2(std::string s);
};

/**
 * @brief 599. 两个列表的最小索引总和
 * 
 */
class FindRestaurant : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;
    
    /**
     * @brief 暴力搜索
     * 时间复杂度：O(nm)
     * 空间复杂度：O(1)
     * @param list1 餐厅列表
     * @param list2 餐厅列表
     * @return std::vector<std::string> 共同喜爱的餐厅
     */
    std::vector<std::string> Solution1(std::vector<std::string> &list1, std::vector<std::string> &list2);

    /**
     * @brief 哈希表
     * 时间复杂度：O(n+m)
     * 空间复杂度：O(min(n,m))
     * @param list1 餐厅列表
     * @param list2 餐厅列表
     * @return std::vector<std::string> 共同喜爱的餐厅
     */
    std::vector<std::string> Solution2(std::vector<std::string> &list1, std::vector<std::string> &list2);
};

class CommonChars : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 统计
     * 时间复杂度：O(n(m+k))
     * 空间复杂度：O(k)
     * @param words 字符串数组
     * @return std::vector<std::string> 共用字符
     */
    std::vector<std::string> Solution1(std::vector<std::string> &words);
};

class MaxNumberOfBallons : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 统计
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param text 用来拼凑的字符串
     * @return int 单词 balloon 的数量
     */
    int Solution1(std::string text);
};

class MaxPower : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 双指针
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param s
     * @return int 「能量」
     */
    int Solution1(std::string s);
};

class SecondHighest : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 有限变量遍历
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param s 
     * @return int 第二大的数
     */
    int Solution1(std::string s);

    /**
     * @brief 有序集合
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param s 
     * @return int 第二大的数
     */
    int Solution2(std::string s);

    /**
     * @brief 排序
     * 时间复杂度：O(nlogn)
     * 空间复杂度：O(n)
     * @param s 
     * @return int 第二大的数
     */
    int Solution3(std::string s);
};


class PlatesBetweenCandles : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 前缀和
     * 时间复杂度：O(n+q)
     * 空间复杂度：O(n)
     * @param s 蜡烛盘子字符串
     * @param queries 查询端点
     * @return std::vector<int> 查询端点中蜡烛的数量
     */
    std::vector<int> Solution1(std::string s, std::vector<std::vector<int>> &queries);

    /**
     * @brief 实时计算
     * 时间复杂度：O(qm)
     * 空间复杂度：O(1)
     * @param s 蜡烛盘子字符串
     * @param queries 查询端点
     * @return std::vector<int> 查询端点中蜡烛的数量
     */
    std::vector<int> Solution2(std::string s, std::vector<std::vector<int>> &queries);
};

} // namespace str
} // namespace leetcode 