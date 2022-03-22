#pragma once

#include <vector>
#include "leetcode_solution.h"

namespace leetcode {
namespace greedy {

void GreedyAlgorithmSolution(SolutionsId pid);

/**
 * @brief 455. 分发饼干
 * 
 */
class FindContentChildren : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 排序+贪心算法
     * 时间复杂度：O(nlogn+mlogm)
     * 空间复杂度：O(logn+logm)
     * @param g 胃口值数组
     * @param s 饼干尺寸数组
     * @return int 被满足的孩子最大数量
     */
    int Solution1(std::vector<int> &g, std::vector<int> &s);
};

/**
 * @brief 969. 煎饼排序
 * 
 */
class PancakeSort : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;
    
    /**
     * @brief 贪心
     * 时间复杂度：O(n^2)
     * 空间复杂度：O(1)
     * @param arr 煎饼排序的数组
     * @return std::vector<int> 排序后的数组
     */
    std::vector<int> Solution1(std::vector<int> &arr);

    void Pancake(std::vector<int> &arr, std::vector<int> &indices);
};


/**
 * @brief 2038. 如果相邻两个颜色均相同则删除当前颜色
 * 
 */
class WinnerOfGame : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 贪心
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param colors AB 颜色片段
     * @return true 
     * @return false 
     */
    bool Solution1(std::string colors);
};

} // namespace greedy
} // namespace leetcode
