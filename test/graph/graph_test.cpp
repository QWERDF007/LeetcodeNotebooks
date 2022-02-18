#include <gtest/gtest.h>
#include "graph/graph.h"

namespace leetcode {
namespace test {

using namespace graph;

TEST(GraphTest, FindCenterTest) {
    FindCenter solution;

    std::vector<std::vector<std::vector<int>>> edges{
        { {1,2},{2,3},{4,2} },
        { {1,2},{5,1},{1,3},{1,4} },
    };

    EXPECT_EQ(solution.Solution1(edges[0]), 2);
    EXPECT_EQ(solution.Solution1(edges[1]), 1);

    EXPECT_EQ(solution.Solution2(edges[0]), 2);
    EXPECT_EQ(solution.Solution2(edges[1]), 1);

    EXPECT_EQ(solution.Solution3(edges[0]), 2);
    EXPECT_EQ(solution.Solution3(edges[1]), 1);
}

} // namespace test
} // namespace leetcode
