#include <algorithm>
#include <gtest/gtest.h>
#include "tree/tree.h"

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
        TreeNode *root = NewBinaryTree(str_tree);
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
        DeleteBinaryTree(root);
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
        TreeNode *root = NewBinaryTree(str_tree);
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
        DeleteBinaryTree(root);
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
        TreeNode *root = NewBinaryTree(str_tree);
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
        DeleteBinaryTree(root);
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
        TreeNode *root = NewBinaryTree(s);
        p.emplace_back(root);
    }
    for (auto &s : sq) {
        TreeNode *root = NewBinaryTree(s);
        q.emplace_back(root);
    }

    EXPECT_TRUE(solution.Solution1(p[0], q[0]));
    EXPECT_FALSE(solution.Solution1(p[1], q[1]));
    EXPECT_FALSE(solution.Solution1(p[2], q[2]));

    EXPECT_TRUE(solution.Solution2(p[0], q[0]));
    EXPECT_FALSE(solution.Solution2(p[1], q[1]));
    EXPECT_FALSE(solution.Solution2(p[2], q[2]));

    for (auto root : p) {
        DeleteBinaryTree(root);
    }
    for (auto root : q) {
        DeleteBinaryTree(root);
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
        roots.emplace_back(NewBinaryTree(s));
    }

    EXPECT_TRUE(solution.Solution1(roots[0]));
    EXPECT_FALSE(solution.Solution1(roots[1]));
    EXPECT_TRUE(solution.Solution1(roots[2]));

    EXPECT_TRUE(solution.Solution2(roots[0]));
    EXPECT_FALSE(solution.Solution2(roots[1]));
    EXPECT_TRUE(solution.Solution2(roots[2]));

    for (auto root : roots) {
        DeleteBinaryTree(root);
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
        roots.emplace_back(NewBinaryTree(s));
    }

    EXPECT_EQ(solution.Solution1(roots[0]), 2);
    EXPECT_EQ(solution.Solution1(roots[1]), 5);

    EXPECT_EQ(solution.Solution2(roots[0]), 2);
    EXPECT_EQ(solution.Solution2(roots[1]), 5);

    for (auto root : roots) {
        DeleteBinaryTree(root);
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
        roots.emplace_back(NewBinaryTree(s));
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
        DeleteBinaryTree(root);
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
        roots0.emplace_back(NewBinaryTree(sp[i]));
        roots1.emplace_back(NewBinaryTree(sq[i]));
    }

    for (int i = 0; i < sp.size(); ++i) {
        roots0[i] = solution.Solution1(roots0[i]);
    }

    EXPECT_TRUE(judge.Solution1(roots0[0], roots1[0]));
    EXPECT_TRUE(judge.Solution1(roots0[1], roots1[1]));
    EXPECT_TRUE(judge.Solution1(roots0[2], roots1[2]));
    

    for (int i = 0; i < sp.size(); ++i) {
        DeleteBinaryTree(roots0[i]);
        DeleteBinaryTree(roots1[i]);
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
        roots1.emplace_back(NewBinaryTree(sp[i]));
        roots2.emplace_back(NewBinaryTree(sp[i]));
        roots3.emplace_back(NewBinaryTree(sq[i]));
    }

    EXPECT_TRUE(judge.Solution1(solution.Solution1(roots1[0]), roots3[0]));
    EXPECT_TRUE(judge.Solution1(solution.Solution1(roots1[1]), roots3[1]));
    EXPECT_TRUE(judge.Solution1(solution.Solution1(roots1[2]), roots3[2]));

    EXPECT_TRUE(judge.Solution1(solution.Solution2(roots2[0]), roots3[0]));
    EXPECT_TRUE(judge.Solution1(solution.Solution2(roots2[1]), roots3[1]));
    EXPECT_TRUE(judge.Solution1(solution.Solution2(roots2[2]), roots3[2]));

    for (int i = 0; i < sp.size(); ++i) {
        DeleteBinaryTree(roots1[i]);
        DeleteBinaryTree(roots2[i]);
        DeleteBinaryTree(roots3[i]);
    }
}

TEST(BinaryTreeTest, LowestCommonAncestorTest) {
    LowestCommonAncestor solution;

    std::vector<std::vector<std::string>> s_trees{
        { "6","2","8","0","4","7","9","null","null","3","5" },
        { "6","2","8","0","4","7","9","null","null","3","5" },
        { "2","1" },
        { "28","12","45","4","24","35","47","2","9","14","25","31","42","46","48","0","3","8","11","13","20",
          "null","26","30","33","41","43","null","null","null","49","null","1","null","null","7","null","10",
          "null","null","null","17","22","null","27","29","null","32","34","36","null","null","44","null","null",
          "null","null","6","null","null","null","16","18","21","23","null","null","null","null","null","null",
          "null","null","null","37","null","null","5","null","15","null","null","19","null","null","null","null",
          "null","40","null","null","null","null","null","null","39","null","38" },
    };

    std::vector<int> p{
        2, 2, 2, 1
    };

    std::vector<int> q{
        8, 4, 1, 23
    };

    std::vector<int> results{
        6, 2, 2, 12
    };

    std::vector<TreeNode *> roots, p_nodes, q_nodes;
    for (auto &s_tree : s_trees) {
        roots.emplace_back(NewBinaryTree(s_tree));
    }
    for (int v : p) {
        p_nodes.emplace_back(new TreeNode(v));
    }
    for (int v : q) {
        q_nodes.emplace_back(new TreeNode(v));
    }

    EXPECT_EQ(solution.Solution1(roots[0], p_nodes[0], q_nodes[0])->val, results[0]);
    EXPECT_EQ(solution.Solution1(roots[1], p_nodes[1], q_nodes[1])->val, results[1]);
    EXPECT_EQ(solution.Solution1(roots[2], p_nodes[2], q_nodes[2])->val, results[2]);
    EXPECT_EQ(solution.Solution1(roots[3], p_nodes[3], q_nodes[3])->val, results[3]);

    EXPECT_EQ(solution.Solution2(roots[0], p_nodes[0], q_nodes[0])->val, results[0]);
    EXPECT_EQ(solution.Solution2(roots[1], p_nodes[1], q_nodes[1])->val, results[1]);
    EXPECT_EQ(solution.Solution2(roots[2], p_nodes[2], q_nodes[2])->val, results[2]);
    EXPECT_EQ(solution.Solution2(roots[3], p_nodes[3], q_nodes[3])->val, results[3]);

    for (TreeNode *root : roots) {
        DeleteBinaryTree(root);
    }
    for (TreeNode *node : p_nodes) {
        delete node;
    }
    for (TreeNode *node : q_nodes) {
        delete node;
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
        roots.emplace_back(NewBinaryTree(s_tree));
    }

    EXPECT_EQ(solution.Solution1(roots[0]), results1[0]);
    EXPECT_EQ(solution.Solution1(roots[1]), results1[1]);
    EXPECT_EQ(solution.Solution1(roots[2]), results1[2]);

    EXPECT_EQ(solution.Solution2(roots[0]), results2[0]);
    EXPECT_EQ(solution.Solution2(roots[1]), results2[1]);
    EXPECT_EQ(solution.Solution2(roots[2]), results2[2]);

    for (TreeNode *root : roots) {
        DeleteBinaryTree(root);
    }
}

TEST(BinaryTreeTest, SumOfLeftLeavesTest) {
    SumOfLeftLeaves solution;
    std::vector<std::vector<std::string>> s_trees{
        { "3","9","20","null","null","15","7" },
        { "1" },
    };

    std::vector<int> results{
        24, 0,
    };

    std::vector<TreeNode *> roots;

    for (auto &s_tree : s_trees) {
        roots.emplace_back(NewBinaryTree(s_tree));
    }

    EXPECT_EQ(solution.Solution1(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution1(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution2(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution2(roots[1]), results[1]);

    for (TreeNode *root : roots) {
        DeleteBinaryTree(root);
    }
}

TEST(BinaryTreeTest, FindModeTest) {
    FindMode solution;
    std::vector<std::vector<std::string>> s_trees{
        { "1","null","2","2" },
        { "0" },
        { "2","null","3","null","4","null","5","null","6" },
    };

    std::vector<std::vector<int>> results{
        { 2 },
        { 0 },
        { 2,3,4,5,6 },
    };

    std::vector<TreeNode *> roots;
    for (auto &s_tree : s_trees) {
        roots.emplace_back(NewBinaryTree(s_tree));
    }
    
    std::vector<std::vector<int>> solution1_ans, solution2_ans, solution3_ans;
    for (TreeNode *root : roots) {
        solution1_ans.emplace_back(solution.Solution1(root));
        solution2_ans.emplace_back(solution.Solution2(root));
        solution3_ans.emplace_back(solution.Solution3(root));
    }

    for (auto &vec : solution1_ans) {
        std::sort(vec.begin(), vec.end());
    }

    for (auto &vec : solution2_ans) {
        std::sort(vec.begin(), vec.end());
    }

    for (auto &vec : solution3_ans) {
        std::sort(vec.begin(), vec.end());
    }

    EXPECT_EQ(solution1_ans[0], results[0]);
    EXPECT_EQ(solution1_ans[1], results[1]);
    EXPECT_EQ(solution1_ans[2], results[2]);

    EXPECT_EQ(solution2_ans[0], results[0]);
    EXPECT_EQ(solution2_ans[1], results[1]);
    EXPECT_EQ(solution2_ans[2], results[2]);

    EXPECT_EQ(solution3_ans[0], results[0]);
    EXPECT_EQ(solution3_ans[1], results[1]);
    EXPECT_EQ(solution3_ans[2], results[2]);

    for (TreeNode *root : roots) {
        DeleteBinaryTree(root);
    }
}

TEST(BinaryTreeTest, FindTiltTest) {
    FindTilt solution;

    std::vector<std::vector<std::string>> s_trees{
        { "1","2","3" },
        { "4","2","9","3","5","null","7" },
        { "21","7","14","1","1","2","2","3","3" },
    };

    std::vector<int> results{
        1, 15, 9,
    };

    std::vector<TreeNode *> roots;
    for (auto &s_tree : s_trees) {
        roots.emplace_back(NewBinaryTree(s_tree));
    }

    EXPECT_EQ(solution.Solution1(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution1(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution1(roots[2]), results[2]);

    for (TreeNode *root : roots) {
        DeleteBinaryTree(root);
    }
}

TEST(BinaryTreeTest, IsSubtreeTest) {
    IsSubtree solution;

    std::vector<std::vector<std::string>> s_trees1{
        { "3","4","5","1","2" },
        { "3","4","5","1","2","null","null","null","null","0" },
        { "1","1" },
        { "3","4","5","1","2" },
    };

    std::vector<std::vector<std::string>> s_trees2{
        { "4","1","2" },
        { "4","1","2" },
        { "1" },
        { "4","1","2","1" },
    };

    std::vector<TreeNode *> roots, subroots;
    for (int i = 0; i < s_trees1.size(); ++i) {
        roots.emplace_back(NewBinaryTree(s_trees1[i]));
        subroots.emplace_back(NewBinaryTree(s_trees2[i]));
    }

    EXPECT_TRUE(solution.Solution1(roots[0], subroots[0]));
    EXPECT_FALSE(solution.Solution1(roots[1], subroots[1]));
    EXPECT_TRUE(solution.Solution1(roots[2], subroots[2]));
    EXPECT_FALSE(solution.Solution1(roots[3], subroots[3]));

    EXPECT_TRUE(solution.Solution2(roots[0], subroots[0]));
    EXPECT_FALSE(solution.Solution2(roots[1], subroots[1]));
    EXPECT_TRUE(solution.Solution2(roots[2], subroots[2]));
    EXPECT_FALSE(solution.Solution2(roots[3], subroots[3]));

    EXPECT_TRUE(solution.Solution3(roots[0], subroots[0]));
    EXPECT_FALSE(solution.Solution3(roots[1], subroots[1]));
    EXPECT_TRUE(solution.Solution3(roots[2], subroots[2]));
    EXPECT_FALSE(solution.Solution3(roots[3], subroots[3]));

    for (int i = 0; i < s_trees1.size(); ++i) {
        DeleteBinaryTree(roots[i]);
        DeleteBinaryTree(subroots[i]);
    }
}

TEST(NAryTreeTest, PreorderTest) {
    Preorder solution;

    std::vector<std::vector<std::string>> s_trees{
        { "1","null","3","2","4","null","5","6" },
        { "1","null","2","3","4","5","null","null","6","7","null","8","null","9","10","null","null","11","null","12","null","13","null","null","14" },
    };

    std::vector<std::vector<int>> results{
        { 1,3,5,6,2,4 },
        { 1,2,3,6,7,11,14,4,8,12,5,9,13,10 },
    };
    std::vector<Node *> roots;
    for (auto &s_tree : s_trees) {
        roots.emplace_back(NewNAryTree(s_tree));
    }

    EXPECT_EQ(solution.Solution1(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution1(roots[1]), results[1]);

    EXPECT_EQ(solution.Solution2(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution2(roots[1]), results[1]);

    EXPECT_EQ(solution.Solution3(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution3(roots[1]), results[1]);

    for (Node *root : roots) {
        DeleteNAryTree(root);
    }
}

TEST(NAryTreeTest, PostorderTest) {
    Postorder solution;

    std::vector<std::vector<std::string>> s_trees{
        { "1","null","3","2","4","null","5","6" },
        { "1","null","2","3","4","5","null","null","6","7","null","8","null","9","10","null","null","11","null","12","null","13","null","null","14" },
    };

    std::vector<Node *> roots;
    for (auto &s_tree : s_trees) {
        roots.emplace_back(NewNAryTree(s_tree));
    }

    std::vector<std::vector<int>> results{
        { 5,6,3,2,4,1 },
        { 2,6,14,11,7,3,12,8,4,13,9,10,5,1 },
    };

    EXPECT_EQ(solution.Solution1(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution1(roots[1]), results[1]);

    EXPECT_EQ(solution.Solution2(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution2(roots[1]), results[1]);

    EXPECT_EQ(solution.Solution3(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution3(roots[1]), results[1]);

    EXPECT_EQ(solution.Solution4(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution4(roots[1]), results[1]);

    for (Node *root : roots) {
        DeleteNAryTree(root);
    }
}

TEST(BinaryTreeTest, Tree2StrTest) {
    Tree2Str solution;

    std::vector<std::vector<std::string>> s_trees{
        { "1","2","3","4" },
        { "1","2","3","null","4" },
    };

    std::vector<std::string> results{
        "1(2(4))(3)",
        "1(2()(4))(3)",
    };

    std::vector<TreeNode *> roots;
    for (auto &s_tree : s_trees) {
        roots.emplace_back(NewBinaryTree(s_tree));
    }

    EXPECT_EQ(solution.Solution1(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution1(roots[1]), results[1]);

    EXPECT_EQ(solution.Solution2(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution2(roots[1]), results[1]);

    for (TreeNode *root : roots) {
        DeleteBinaryTree(root);
    }
}


TEST(BinaryTreeTest, AverageOfLevelsTest) {
    AverageOfLevels solution;
    std::vector<std::vector<std::string>> s_trees{
        { "3","9","20","null","null","15","7" },
        { "3","9","20","15","7" },
    };

    std::vector<std::vector<double>> results{
        { 3.00000,14.50000,11.00000 },
        { 3.00000,14.50000,11.00000 },
    };

    std::vector<TreeNode *> roots;
    for (auto &s_tree : s_trees) {
        roots.emplace_back(NewBinaryTree(s_tree));
    }

    EXPECT_EQ(solution.Solution1(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution1(roots[1]), results[1]);

    EXPECT_EQ(solution.Solution2(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution2(roots[1]), results[1]);

    for (TreeNode *root : roots) {
        DeleteBinaryTree(root);
    }
}

TEST(BinaryTreeTest, FindTargetTest) {
    FindTarget solution;
    std::vector<std::vector<std::string>> s_trees{
        { "5","3","6","2","4","null","7" },
        { "5","3","6","2","4","null","7" },
        { "2","null","3" },
        { "1" },
    };

    std::vector<int> targets{
        9, 28, 6, 2
    };

    std::vector<TreeNode *> roots;
    for (auto &s_tree : s_trees) {
        roots.emplace_back(NewBinaryTree(s_tree));
    }

    EXPECT_TRUE(solution.Solution1(roots[0], targets[0]));
    EXPECT_FALSE(solution.Solution1(roots[1], targets[1]));
    EXPECT_FALSE(solution.Solution1(roots[2], targets[2]));
    EXPECT_FALSE(solution.Solution1(roots[3], targets[3]));

    EXPECT_TRUE(solution.Solution2(roots[0], targets[0]));
    EXPECT_FALSE(solution.Solution2(roots[1], targets[1]));
    EXPECT_FALSE(solution.Solution2(roots[2], targets[2]));
    EXPECT_FALSE(solution.Solution2(roots[3], targets[3]));

    EXPECT_TRUE(solution.Solution3(roots[0], targets[0]));
    EXPECT_FALSE(solution.Solution3(roots[1], targets[1]));
    EXPECT_FALSE(solution.Solution3(roots[2], targets[2]));
    EXPECT_FALSE(solution.Solution3(roots[3], targets[3]));

    for (TreeNode *root : roots) {
        DeleteBinaryTree(root);
    }
}

TEST(BinaryTreeTest, FindSecondMinimumValueTest) {
    FindSecondMinimumValue solution;

    std::vector<std::vector<std::string>> s_trees{
        { "2","2","5","null","null","5","7" },
        { "2","2","2 "},
        { "5","8","5" },
        { "1","1","3","1","1","3","4","3","1","1","1","3","8","4","8","3","3","1","6","2","1" },
        { "2","2","2147483647" },
        
    };

    std::vector<int> results{
        5, -1, 8, 2, 2147483647,
    };

    std::vector<TreeNode *> roots;
    for (auto &s_tree : s_trees) {
        roots.emplace_back(NewBinaryTree(s_tree));
    }

    EXPECT_EQ(solution.Solution1(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution1(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution1(roots[2]), results[2]);
    EXPECT_EQ(solution.Solution1(roots[3]), results[3]);
    EXPECT_EQ(solution.Solution1(roots[4]), results[4]);

    EXPECT_EQ(solution.Solution2(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution2(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution2(roots[2]), results[2]);
    EXPECT_EQ(solution.Solution2(roots[3]), results[3]);
    EXPECT_EQ(solution.Solution2(roots[4]), results[4]);

    EXPECT_EQ(solution.Solution3(roots[0]), results[0]);
    EXPECT_EQ(solution.Solution3(roots[1]), results[1]);
    EXPECT_EQ(solution.Solution3(roots[2]), results[2]);
    EXPECT_EQ(solution.Solution3(roots[3]), results[3]);
    EXPECT_EQ(solution.Solution3(roots[4]), results[4]);

    for (TreeNode *root : roots) {
        DeleteBinaryTree(root);
    }
}

} // namespace test
} // namespace leetcode
