| :tiger:                                  | :cat: | :dog: | :dragon: |
| ---------------------------------------- | ----- | ----- | -------- |
| 94.[二叉树的中序遍历](#二叉树的中序遍历) |       |       |          |

# 二叉树的中序遍历

- [链接](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)
- [code](../cc/tree/binary_tree.h)

> 给定一个二叉树的根节点 root，返回它的中序遍历。

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
```

## 递归

中序遍历即优先访问左子树，然后访问根，最后访问右子树的遍历方式，访问子树时以相同的顺序访问。

**注意：** 递归终止条件是当前节点为空。

**复杂度分析**：

- 时间复杂度：$O(n)$，递归遍历每个节点所需时间
- 空间复杂度：$O(n)$，递归堆栈空间，需要递归遍历全部节点

```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> values;
        inorder(root, values);
        return values;
    }

    void inorder(TreeNode *node, vector<int> &values) {
        if (!node) {
            return;
        }
        inorder(node->left, values);
        values.emplace_back(node->val);
        inorder(node->right, values);
    }
};
```

## 迭代

递归隐式地维护了一个栈，使用迭代方法，在迭代的过程中显示地模拟这个栈。其他和递归遍历一样。

**复杂度分析**：

- 时间复杂度：O(n)，迭代每个节点所需时间
- 空间复杂度：O(n)，迭代模拟递归栈所需空间，需要迭代全部节点

```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode *> stk;
        TreeNode *cur = root;
        while (cur != nullptr || !stk.empty()) {
            while (cur != nullptr) {
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top();
            stk.pop();
            res.emplace_back(cur->val);
            cur = cur->right;
        }
        return res;
    }
};
```

## Miorris

Morris 遍历算法是另一种遍历二叉树的方法，它能将非递归的中序遍历空间复杂度降为 O(1)。

算法整体步骤如下（假设当前节点为 cur）：

- 如果 `cur` 无左节点，即 `cur->left == nullptr`，将 `cur` 的值加入结果，访问 `cur` 的右节点，即 `cur = cur->right`。
- 如果 `cur` 有左节点，则找到 `cur` 左子树上最右的节点（即左子树中序遍历的最后一个节点，`cur` 在中序遍历中的前驱节点），记为 `predecessor`。根据 `predecessor` 的右节点是否为空，进行如下操作：
  - 如果 `predecessor` 的右节点为空，则将其右节点指向 `cur`，然后访问 `cur` 的左节点，即 `cur = cur->left`。
  - 如果 `predecessor` 的右节点不为空，则此时其右节点指向 `cur`，说明已经遍历完 `cur` 的左子树，将 `predecessor` 置空，将 `cur` 的值加入结果，访问 `cur` 的右节点，即 `cur = cur->right`。
- 重复上述操作，直到访问完整棵树。

其实整个过程我们就多做一步：假设当前遍历到的节点为 cur，将 cur 的左子树中最右边的节点的右孩子指向 cur，这样在左子树遍历完成后我们通过这个指向走回了 cur，且能通过这个指向知晓我们已经遍历完成了左子树，而不用再通过栈来维护，省去了栈的空间复杂度。

**复杂度分析：**

- 时间复杂度：$O(n)$，Morris 遍历中，每个节点会被访问两次，时间 $O(2n) = O(n)$
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode *predecessor = nullptr;
        TreeNode *cur = root;
        while (cur != nullptr) {
            if (cur->left != nullptr) {
                // predecessor 节点就是当前 cur 节点向左走一步，然后一直向右走至无法走为止
                predecessor = cur->left;
                while (predecessor->right != nullptr && predecessor->right != cur) {
                    predecessor = predecessor->right;
                }
                // 让 predecessor 的右指针指向 cur，继续遍历左子树
                if (predecessor->right == nullptr) {
                    predecessor->right = cur;
                    cur = cur->left;
                }
                // 说明左子树已经访问完了，我们需要断开链接
                else {
                    res.push_back(cur->val);
                    predecessor->right = nullptr;
                    cur = cur->right;
                }
            }
            // 如果没有左孩子，则直接访问右孩子
            else {
                res.push_back(cur->val);
                cur = cur->right;
            }
        }
        return res;
    }
};
```

