#pragma once

#include <vector>
#include <string>
#include "leetcode_solution.h"

namespace leetcode {
namespace tree {

void BinaryTreeSolution(int pid);

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * @brief 递归，二叉树先(根)序遍历，根 -> 左 -> 右，递归遍历
 * 
 * @tparam T 二叉树结点值类型
 * @param root 二叉树根结点
 * @param res 二叉树先序遍历结果
 */
template <typename T>
void PreOrderTraversal(TreeNode *root, std::vector<T> &res);

/**
 * @brief 递归，二叉树中(根)序遍历，左 -> 根 -> 右
 * 
 * @tparam T 二叉树结点值类型
 * @param root 二叉树根结点
 * @param res 二叉树中序遍历结果
 */
template <typename T>
void InOrderTraversal(TreeNode *root, std::vector<T> &res);

/**
 * @brief 递归，二叉树后(根)序遍历，左 -> 右 -> 根
 * 
 * @tparam T 二叉树结点值类型
 * @param root 二叉树根结点
 * @param res 二叉树后序遍历结果
 */
template <typename T>
void PostOrderTraversal(TreeNode *root, std::vector<T> &res);

/**
 * @brief 层序遍历
 *
 * @param root 二叉树根结点
 * @param res 二叉树层序遍历结果
 */
void LevelOrderTraversal(TreeNode *root, std::vector<int> &res);

int TreeHeight(TreeNode *root);

/**
 * @brief 从字符串数组层序生成二叉树，"null" 表示该结点为空，
 * 数组中只包含数字和null
 * @param tree 二叉树字符串数组
 * @return TreeNode* 二叉树根结点
 */
TreeNode *NewTree(std::vector<std::string> &tree);

/**
 * @brief 递归，后序遍历方式释放二叉树，左 -> 右 -> 根
 * 
 * @param root 二叉树根结点
 */
void DeleteTree(TreeNode *root);

class PreorderTraversal : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;
    
    /**
     * @brief 递归前序遍历
     * 时间复杂度：O(n)
     * 空间复杂度：O(h)
     * @param root 二叉树根节点
     * @return std::vector<int> 前序遍历结果 
     */
    std::vector<int> Solution1(TreeNode *root);

    /**
     * @brief 迭代前序遍历，模拟递归
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param root 二叉树根节点
     * @return std::vector<int> 前序遍历结果
     */
    std::vector<int> Solution2(TreeNode *root);

    /**
     * @brief Morris 前序遍历
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param root 二叉树根节点
     * @return std::vector<int> 前序遍历结果
     */
    std::vector<int> Solution3(TreeNode *root);
};

class InorderTraversal : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 递归中序遍历
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param root 二叉树根节点
     * @return std::vector<int> 中序遍历结果
     */
    std::vector<int> Solution1(TreeNode *root);

    /**
     * @brief 迭代中序遍历，stack 模拟递归
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param root 二叉树根节点
     * @return std::vector<int> 中序遍历结果
     */
    std::vector<int> Solution2(TreeNode *root);

    /**
     * @brief Morris 中序遍历
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param root 二叉树根节点
     * @return std::vector<int> 中序遍历结果
     */
    std::vector<int> Solution3(TreeNode *root);
};

class PostorderTraversal : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 递归后序遍历
     * 时间复杂度：O(n)
     * 空间复杂度：O(h)
     * @param root 二叉树根节点
     * @return std::vector<int> 后序遍历结果
     */
    std::vector<int> Solution1(TreeNode *root);

    /**
     * @brief 迭代后序遍历
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param root 二叉树根节点
     * @return std::vector<int> 后序遍历结果
     */
    std::vector<int> Solution2(TreeNode *root);

    /**
     * @brief Morris 后序遍历
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param root 二叉树根节点
     * @return std::vector<int> 后序遍历结果
     */
    std::vector<int> Solution3(TreeNode *root);

private:
    void AddPath(TreeNode *root, std::vector<int> &res);
};

class IsSameTree : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 深度优先搜索 (DFS)
     * 时间复杂度：O(min(n,m))
     * 空间复杂度：O(min(n,m))
     * @param p 待比较二叉树
     * @param q 待比较二叉树
     * @return true 
     * @return false 
     */
    bool Solution1(TreeNode *p, TreeNode *q);

    /**
     * @brief 广度优先搜索 (BFS)
     * 时间复杂度：O(min(n,m))
     * 空间复杂度：O(min(n,m))
     * @param p 待比较二叉树
     * @param q 待比较二叉树
     * @return true 
     * @return false 
     */
    bool Solution2(TreeNode *p, TreeNode *q);
};

class IsBalanced : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 自顶向下递归
     * 时间复杂度：O(n^2)
     * 空间复杂度：O(n)
     * @param root 二叉树根节点
     * @return true 
     * @return false 
     */
    bool Solution1(TreeNode *root);

    /**
     * @brief 自底向上递归
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param root 二叉树根节点
     * @return true 
     * @return false 
     */
    bool Solution2(TreeNode *root);

private:
    int Height(TreeNode *root);
};

class MinDepth : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 深度优先搜索 (DFS)
     * 时间复杂度：O(n)
     * 空间复杂度：O(h)
     * @param root 二叉树根节点
     * @return int 最小深度
     */
    int Solution1(TreeNode *root);

    /**
     * @brief 广度优先搜索 (BFS)
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param root 二叉树根节点
     * @return int 最小深度
     */
    int Solution2(TreeNode *root);
};

class UpsideDownBinaryTree : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 层序遍历
     * 时间复杂度：O(h)
     * 空间复杂度：O(1)
     * @param root 二叉树根节点
     * @return TreeNode* 翻转后的二叉树根节点
     */
    TreeNode *Solution1(TreeNode *root);
};

class HasPathSum : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 深度优先搜索 (DFS)
     * 时间复杂度：O(n)
     * 空间复杂度：O(h)
     * @param root 二叉树根节点
     * @param targetSum 目标和
     * @return true 
     * @return false 
     */
    bool Solution1(TreeNode *root, int targetSum);

    /**
     * @brief 广度优先搜索 (BFS) + pair
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param root 二叉树根节点
     * @param targetSum 目标和
     * @return true 
     * @return false 
     */
    bool Solution2(TreeNode *root, int targetSum);

    /**
     * @brief 广度优先搜索 (BFS) + 双队列
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param root 二叉树根节点
     * @param targetSum 目标和
     * @return true 
     * @return false 
     */
    bool Solution3(TreeNode *root, int targetSum);
};

class InvertTree : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 深度优先搜索 (DFS)
     * 时间：O(n)
     * 空间：O(h)
     * @param root 二叉树根节点
     * @return TreeNode* 翻转后的二叉树的根节点
     */
    TreeNode *Solution1(TreeNode *root);

    /**
     * @brief 广度优先搜索 (BFS)
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param root 二叉树根节点
     * @return TreeNode* 翻转后的二叉树的根节点
     */
    TreeNode *Solution2(TreeNode *root);
};


class LowestCommonAncestor : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 遍历
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param root 二叉搜索树根节点
     * @param p root 的节点
     * @param q root 的节点
     * @return TreeNode* 最近公共祖先
     */
    TreeNode *Solution1(TreeNode *root, TreeNode *p, TreeNode *q);

    /**
     * @brief 递归
     * 时间复杂度：O(n)
     * 空间复杂度：O(h)
     * @param root 二叉搜索树根节点
     * @param p root 的节点
     * @param q root 的节点
     * @return TreeNode* 最近公共祖先
     */
    TreeNode *Solution2(TreeNode *root, TreeNode *p, TreeNode *q);

private:
    /**
     * @brief 获取到二叉搜索树根节点到目标节点的路径
     * 
     * @param root 二叉搜索树根节点
     * @param target 目标节点
     * @return std::vector<TreeNode *> 根节点到目标节点的路径
     */
    std::vector<TreeNode *> GetPath(TreeNode *root, TreeNode *target);
};

class BinaryTreePaths : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 深度优先搜索 (DFS)
     * 时间复杂度：O(n^2)
     * 空间复杂度：O(h^2)
     * @param root 二叉树根节点
     * @return std::vector<std::string> 根节点到全部叶子节点的字符串路径
     */
    std::vector<std::string> Solution1(TreeNode *root);

    /**
     * @brief 广度优先搜索 (BFS)
     * 时间复杂度：O(n^2)
     * 空间复杂度：O(n^2)
     * @param root 二叉树根节点
     * @return std::vector<std::string> 根节点到全部叶子节点字符串的路径
     */
    std::vector<std::string> Solution2(TreeNode *root);

private:
    /**
     * @brief 深度优先搜索获取根节点到叶子节点的路径
     * 
     * @param root 二叉树根节点
     * @param paths 根节点到全部叶子节点的字符串路径
     * @param path 到当前节点的父节点的字符串路径
     */
    void TreePaths(TreeNode *root, std::vector<std::string> &paths, std::string path);
};

class SumOfLeftLeaves : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 深度优先搜索 (DFS)
     * 时间复杂度：O(n)
     * 空间复杂度：O(h)
     * @param root 二叉树根节点
     * @return int 左叶子节点之和
     */
    int Solution1(TreeNode *root);

    /**
     * @brief 广度优先搜索 (DFS)
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param root 二叉树根节点
     * @return int 左叶子节点之和
     */
    int Solution2(TreeNode *root);

private:
    /**
     * @brief 判断是否叶子节点
     * 
     * @param node 二叉树节点
     * @return true 
     * @return false 
     */
    bool IsLeafNode(TreeNode *node);
};

class FindMode : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 哈希表
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param root 二叉搜索树根节点
     * @return std::vector<int> 众数
     */
    std::vector<int> Solution1(TreeNode *root);

    /**
     * @brief 递归
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param root 二叉搜索树根节点
     * @return std::vector<int> 众数
     */
    std::vector<int> Solution2(TreeNode *root);

    /**
     * @brief 迭代
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param root 二叉搜索树根节点
     * @return std::vector<int> 众数
     */
    std::vector<int> Solution3(TreeNode *root);

private:
    /**
     * @brief 中序遍历更新众数
     * 
     * @param root 二叉搜索树根节点
     * @param count base 的出现次数
     * @param max_count 最大出现次数
     * @param base 当前统计的元素
     * @param ans 众数
     */
    void Inorder(TreeNode *root, int &count, int &max_count, int &base, std::vector<int> &ans);

    /**
     * @brief 更新众数
     * 
     * @param num 当前元素
     * @param count 当前元素出现次数
     * @param max_count 最大出现次数
     * @param base 当前统计的元素
     * @param ans 众数
     */
    void Update(int num, int &count, int &max_count, int &base, std::vector<int> &ans);
};

class FindTilt : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;
};

} // namespace tree
} // namespace leetcode
