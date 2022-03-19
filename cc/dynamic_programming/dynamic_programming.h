#pragma once

#include <vector>
#include "leetcode_solution.h"

namespace leetcode {
namespace dp {

void DynamicProgrammingSolution(SolutionsId pid);

/**
 * @brief 96. 不同的二叉搜索树
 * 
 */
class NumTrees : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 动态规划
     * 时间复杂度：O(n^2)
     * 空间复杂度：O(n)
     * @param n 
     * @return int 符合条件的二叉搜索树的种数
     */
    int Solution1(int n);

    /**
     * @brief 数学，卡特兰数
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param n 
     * @return int 符合条件的二叉搜索树的种数
     */
    int Solution2(int n);
};

/**
 * @brief 688. 骑士在棋盘上的概率
 * 
 */
class KnightProbability : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;
    
    /**
     * @brief 动态规划
     * 时间复杂度：O(kn^2)
     * 空间复杂度：O(kn^2)
     * @param n 棋盘大小
     * @param k 移动次数
     * @param row 初始行位置
     * @param column 初始列位置
     * @return double 移动 k 次后停留在棋盘上的概率
     */
    double Solution1(int n, int k, int row, int column);
private:
    std::vector<std::vector<int>> dirs_ = {
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}
    };
};

} // namespace dp
} // namespace leetcode
