#include <gtest/gtest.h>
#include "tree/binary_tree.h"

namespace leetcode {
namespace test {

using namespace tree;

TEST(BinaryTreeTest, PreorderTraversalTest) {
    PreorderTraversal solution;

    std::vector<std::vector<std::string>> s_trees{
        {"1","null","2","3"},
        {},
        {"1"},
        { "0","1","2","3","4","5","6","7","8","9"}
    };

    std::vector<std::vector<int>> results{
        { 1,2,3 },
        { },
        { 1 },
        { 0,1,3,7,8,4,9,2,5,6 }
    };

    std::vector<TreeNode *> roots;
    for (auto &str_tree : s_trees) {
        TreeNode *root = NewTree(str_tree);
        roots.emplace_back(root);
    }

    EXPECT_EQ(solution.Solution1(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution1(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution1(roots[2]), results[2]);
    EXPECT_EQ(solution.Solution1(roots[3]), results[3]);

    EXPECT_EQ(solution.Solution2(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution2(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution2(roots[2]), results[2]);
    EXPECT_EQ(solution.Solution2(roots[3]), results[3]);

    EXPECT_EQ(solution.Solution3(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution3(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution3(roots[2]), results[2]);
    EXPECT_EQ(solution.Solution3(roots[3]), results[3]);

    for (auto root : roots) {
        DeleteTree(root);
    }
}

TEST(BinaryTreeTest, InorderTraversalTest) {
    InorderTraversal solution;
    std::vector<std::vector<std::string>> s_trees{
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
    for (auto &str_tree : s_trees) {
        TreeNode *root = NewTree(str_tree);
        roots.emplace_back(root);
    }

    EXPECT_EQ(solution.Solution1(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution1(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution1(roots[2]), results[2]);
    EXPECT_EQ(solution.Solution1(roots[3]), results[3]);

    EXPECT_EQ(solution.Solution2(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution2(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution2(roots[2]), results[2]);
    EXPECT_EQ(solution.Solution2(roots[3]), results[3]);

    EXPECT_EQ(solution.Solution3(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution3(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution3(roots[2]), results[2]);
    EXPECT_EQ(solution.Solution3(roots[3]), results[3]);

    for (auto root : roots) {
        DeleteTree(root);
    }
}

TEST(BinaryTreeTest, PostorderTraversalTest) {
    PostorderTraversal solution;

    std::vector<std::vector<std::string>> s_trees{
        { "1","2","3" },
        { "1","null","2","3"},
        {},
        { "1" },
        { "0","1","2","3","4","5","6","7","8","9"}
    };

    std::vector<std::vector<int>> results{
        { 2,3,1 },
        { 3,2,1 },
        { },
        { 1 },
        { 7,8,3,9,4,1,5,6,2,0 },
    };

    std::vector<TreeNode *> roots;
    for (auto &str_tree : s_trees) {
        TreeNode *root = NewTree(str_tree);
        roots.emplace_back(root);
    }

    EXPECT_EQ(solution.Solution1(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution1(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution1(roots[2]), results[2]);
    EXPECT_EQ(solution.Solution1(roots[3]), results[3]);

    EXPECT_EQ(solution.Solution2(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution2(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution2(roots[2]), results[2]);
    EXPECT_EQ(solution.Solution2(roots[3]), results[3]);

    EXPECT_EQ(solution.Solution3(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution3(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution3(roots[2]), results[2]);
    EXPECT_EQ(solution.Solution3(roots[3]), results[3]);

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

TEST(BinaryTreeTest, UpsideDownBinaryTreeTest) {
    UpsideDownBinaryTree solution;
    IsSameTree judge;

    std::vector<std::vector<std::string>> sp{
        { "1","2","3","4","5" },
        { },
        { "1" },
        { "1","2","3","4","5","null","null","6","7","null","null","8","9" },
    };

    std::vector<std::vector<std::string>> sq{
        { "4","5","2","null","null","3","1" },
        { },
        { "1" },
        { "8","9","6","null","null","7","4","null","null","5","2","null","null","3","1" },
    };

    std::vector<TreeNode *> roots0, roots1;
    for (int i = 0; i < sp.size(); ++i) {
        roots0.emplace_back(NewTree(sp[i]));
        roots1.emplace_back(NewTree(sq[i]));
    }

    for (int i = 0; i < sp.size(); ++i) {
        roots0[i] = solution.Solution1(roots0[i]);
    }

    EXPECT_TRUE(judge.Solution1(roots0[0], roots1[0]));
    EXPECT_TRUE(judge.Solution1(roots0[1], roots1[1]));
    EXPECT_TRUE(judge.Solution1(roots0[2], roots1[2]));
    

    for (int i = 0; i < sp.size(); ++i) {
        DeleteTree(roots0[i]);
        DeleteTree(roots1[i]);
    }
}

TEST(BinaryTreeTest, InvertTreeTest) {
    InvertTree solution;
    IsSameTree judge;

    std::vector<std::vector<std::string>> sp{
        { "4","2","7","1","3","6","9" },
        { "2","1","3" },
        { },
    };

    std::vector<std::vector<std::string>> sq{
        { "4","7","2","9","6","3","1" },
        { "2","3","1" },
        {}
    };

    std::vector<TreeNode *> roots1, roots2, roots3;
    for (int i = 0; i < sp.size(); ++i) {
        roots1.emplace_back(NewTree(sp[i]));
        roots2.emplace_back(NewTree(sp[i]));
        roots3.emplace_back(NewTree(sq[i]));
    }

    EXPECT_TRUE(judge.Solution1(solution.Solution1(roots1[0]), roots3[0]));
    EXPECT_TRUE(judge.Solution1(solution.Solution1(roots1[1]), roots3[1]));
    EXPECT_TRUE(judge.Solution1(solution.Solution1(roots1[2]), roots3[2]));

    EXPECT_TRUE(judge.Solution1(solution.Solution2(roots2[0]), roots3[0]));
    EXPECT_TRUE(judge.Solution1(solution.Solution2(roots2[1]), roots3[1]));
    EXPECT_TRUE(judge.Solution1(solution.Solution2(roots2[2]), roots3[2]));

    for (int i = 0; i < sp.size(); ++i) {
        DeleteTree(roots1[i]);
        DeleteTree(roots2[i]);
        DeleteTree(roots3[i]);
    }
}

TEST(BinaryTreeTest, BinaryTreePathsTest) {
    BinaryTreePaths solution;

    std::vector<std::vector<std::string>> s_trees{
        {"1","2","3","null","5"},
        {"1"},
        {"1","2","3","4","5","6","7","8","9"}
    };

    std::vector<std::vector<std::string>> results1{
        {"1->2->5","1->3"},
        {"1"},
        {"1->2->4->8","1->2->4->9","1->2->5","1->3->6","1->3->7"},
    };

    std::vector<std::vector<std::string>> results2{
        {"1->3", "1->2->5"},
        {"1"},
        {"1->2->5","1->3->6","1->3->7","1->2->4->8","1->2->4->9"},
    };

    std::vector<TreeNode *> roots;
    for (auto &s_tree : s_trees) {
        roots.emplace_back(NewTree(s_tree));
    }

    EXPECT_EQ(solution.Solution1(roots[0]), results1[0]);
    EXPECT_EQ(solution.Solution1(roots[1]), results1[1]);
    EXPECT_EQ(solution.Solution1(roots[2]), results1[2]);

    EXPECT_EQ(solution.Solution2(roots[0]), results2[0]);
    EXPECT_EQ(solution.Solution2(roots[1]), results2[1]);
    EXPECT_EQ(solution.Solution2(roots[2]), results2[2]);

    for (TreeNode *root : roots) {
        DeleteTree(root);
    }
}

} // namespace test
} // namespace leetcode
