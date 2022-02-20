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

TEST(BinaryTreeTest, IsSameTreeTest) {
    IsSameTree solution;

    std::vector<std::vector<std::string>> sp{
        { "1","2","3" },
        { "1","2" },
        { "1","2","1" },
    };

    std::vector<std::vector<std::string>> sq{
        { "1","2","3" },
        { "1","null","2" },
        { "1","1","2" },
    };

    std::vector<TreeNode *> p, q;

    for (auto &s : sp) {
        TreeNode *root = NewTree(s);
        p.emplace_back(root);
    }
    for (auto &s : sq) {
        TreeNode *root = NewTree(s);
        q.emplace_back(root);
    }

    EXPECT_TRUE(solution.Solution1(p[0], q[0]));
    EXPECT_FALSE(solution.Solution1(p[1], q[1]));
    EXPECT_FALSE(solution.Solution1(p[2], q[2]));

    EXPECT_TRUE(solution.Solution2(p[0], q[0]));
    EXPECT_FALSE(solution.Solution2(p[1], q[1]));
    EXPECT_FALSE(solution.Solution2(p[2], q[2]));

    for (auto root : p) {
        DeleteTree(root);
    }
    for (auto root : q) {
        DeleteTree(root);
    }
}

TEST(BinaryTreeTest, IsBalancedTest) {
    IsBalanced solution;

    std::vector<std::vector<std::string>> s_trees{
        {"3","9","20","null","null","15","7"},
        {"1","2","2","3","3","null","null","4","4"},
        {}
    };

    std::vector<TreeNode *> roots;
    for (auto &s : s_trees) {
        roots.emplace_back(NewTree(s));
    }

    EXPECT_TRUE(solution.Solution1(roots[0]));
    EXPECT_FALSE(solution.Solution1(roots[1]));
    EXPECT_TRUE(solution.Solution1(roots[2]));

    EXPECT_TRUE(solution.Solution2(roots[0]));
    EXPECT_FALSE(solution.Solution2(roots[1]));
    EXPECT_TRUE(solution.Solution2(roots[2]));

    for (auto root : roots) {
        DeleteTree(root);
    }
}

TEST(BinaryTreeTest, MinDepthTest) {
    MinDepth solution;

    std::vector<std::vector<std::string>> s_trees{
        { "3","9","20","null","null","15","7" },
        { "2","null","3","null","4","null","5","null","6" },
    };
    std::vector<TreeNode *> roots;
    for (auto &s : s_trees) {
        roots.emplace_back(NewTree(s));
    }

    EXPECT_EQ(solution.Solution1(roots[0]), 2);
    EXPECT_EQ(solution.Solution1(roots[1]), 5);

    EXPECT_EQ(solution.Solution2(roots[0]), 2);
    EXPECT_EQ(solution.Solution2(roots[1]), 5);

    for (auto root : roots) {
        DeleteTree(root);
    }
}

TEST(BinaryTreeTest, HasPathSumTest) {
    HasPathSum solution;
    std::vector<std::vector<std::string>> s_trees{
        {"5","4","8","11","null","13","4","7","2","null","null","null","1"},
        {"1","2","3"},
        { },
    };
    std::vector<TreeNode *> roots;
    for (auto &s : s_trees) {
        roots.emplace_back(NewTree(s));
    }

    EXPECT_TRUE(solution.Solution1(roots[0], 22));
    EXPECT_TRUE(solution.Solution2(roots[0], 22));
    EXPECT_TRUE(solution.Solution3(roots[0], 22));

    EXPECT_FALSE(solution.Solution1(roots[1], 5));
    EXPECT_FALSE(solution.Solution2(roots[1], 5));
    EXPECT_FALSE(solution.Solution3(roots[1], 5));

    EXPECT_FALSE(solution.Solution1(roots[2], 0));
    EXPECT_FALSE(solution.Solution2(roots[2], 0));
    EXPECT_FALSE(solution.Solution3(roots[2], 0));

    for (TreeNode *root : roots) {
        DeleteTree(root);
    }
}

} // namespace test
} // namespace leetcode
