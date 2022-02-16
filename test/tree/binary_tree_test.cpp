#include <gtest/gtest.h>
#include "tree/binary_tree.h"

namespace leetcode {
namespace test {

using namespace tree;

TEST(BinaryTreeTest, InorderTraversalTest) {
    InorderTraversal solution;
    std::vector<std::vector<std::string>> str_trees{
        { "1","null","2","3"},
        {},
        { "1" },
        { "0","1","2","3","4","5","6","7","8","9"}
    };
    std::vector<std::vector<int>> results{
        { 1,3,2 },
        {},
        { 1 },
        { 7,3,8,1,9,4,0,5,2,6 },
    };

    std::vector<TreeNode *> roots;
    for (auto &str_tree : str_trees) {
        TreeNode *root = NewTree(str_tree);
        roots.emplace_back(root);
    }

    EXPECT_EQ(solution.Solution1(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution1(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution1(roots[2]), results[2]);

    EXPECT_EQ(solution.Solution2(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution2(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution2(roots[2]), results[2]);

    EXPECT_EQ(solution.Solution3(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution3(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution3(roots[2]), results[2]);

    for (auto root : roots) {
        DeleteTree(root);
    }
}

} // namespace test
} // namespace leetcode
