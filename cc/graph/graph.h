#pragma once

#include <vector>
#include "leetcode_solution.h"


namespace leetcode {
namespace graph {

void GraphSolution(int pid);

class FindCenter : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 寻找出现在两条边的节点
     * 时间复杂度：O(1)
     * 空间复杂度：O(1)
     * @param edges 星型图的边
     * @return int 星形图中心
     */
    int Solution1(std::vector<std::vector<int>> &edges);

    /**
     * @brief 计算节点的度
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param edges 星型图的边
     * @return int 星型图的中心
     */
    int Solution2(std::vector<std::vector<int>> &edges);

    /**
     * @brief 统计节点出现次数
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param edges 星型图的边
     * @return int 星型图的中心
     */
    int Solution3(std::vector<std::vector<int>> &edges);
};

} // namespace graph
} // namespace leetcode
