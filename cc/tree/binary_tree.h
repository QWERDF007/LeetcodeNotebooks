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

} // namespace tree
} // namespace leetcode
