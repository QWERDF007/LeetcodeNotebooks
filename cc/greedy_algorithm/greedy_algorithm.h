#pragma once

#include <vector>
#include "leetcode_solution.h"

namespace leetcode {
namespace greedy {

void GreedyAlgorithmSolution(int pid);

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

} // namespace greedy
} // namespace leetcode
