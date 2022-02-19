| :tiger:                                  | :cat:                      | :dog:                          | :dragon: |
| ---------------------------------------- | -------------------------- | ------------------------------ | -------- |
| 94.[二叉树的中序遍历](#二叉树的中序遍历) | 100. [相同的树](#相同的树) | 110. [平衡二叉树](#平衡二叉树) |          |

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
  - 如果 `predecessor` 的右节点不为空，则此时其右节点指向 `cur`，说明已经遍历完 `cur` 的左子树，将 `cur` 的值加入结果，将 `predecessor` 的右节点置空，即 `predecessor->right = nullptr`，然后访问 `cur` 的右节点，即 `cur = cur->right`。
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

# 相同的树

- [链接](https://leetcode-cn.com/problems/same-tree/)
- [code](../cc/tree/binary_tree.h)

> 给你两棵二叉树的根节点 p 和 q，编写一个函数来检验这两棵树是否相同。
>
> 如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。

## 深度优先搜索

使用深度优先搜索判断两棵树是否相等，即先序遍历两棵二叉树，判断对应节点是否相同。若两个树都为空，则两棵二叉树相等；若只有且只有其中一个为空，则两棵二叉树不同。若两棵树都不为空，则首先判断它们根节点的值是否相同，若不同则两颗树不同；若相同则再分别判断两棵树的左子树是否相同，以及右子树是否相同。这是一个递归的过程。

**复杂度分析**：

- 时间复杂度：$O(\min(n,m))$，对两个二叉树进行深度优先搜索时，只有两个树的对应节点都不为空时才会访问到该节点，因此被访问的节点数量不会超过较小的二叉树的节点数。
- 空间复杂度：$O(\min(n,m))$，递归调用层数最大不会超过较小的二叉树的节点数。

```c++
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr) {
            return true;
        } else if (p == nullptr || q == nullptr || p->val != q->val) {
            return false;
        } else {
            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        }
    }
};
```

## 广度优先搜索

使用广度优先搜索判断两棵树是否相等，即层序遍历两棵二叉树，判断对应节点是否相同。构建一个队列，将两棵树根节点加入队列中。每次从队列中取出两个节点作为 p 和 q，判断是否相同，若不相同则两棵树不同；若相同，则将 p 和 q 的左节点加入队列，再将 p 和 q 的右节点加入队列。重复上述过程，直到队列为空，则说明两棵树相同。

**注意：** BFS 理论时间复杂度与 DFS 相同，但队列操作时间耗时对算法影响较大。

**复杂度分析：**

- 时间复杂度：$O(\min(n,m))$，只有两棵树节点不为空才会访问到该节点，因此访问节点数量不会超过较小的二叉树的节点数。
- 空间复杂度：$O(\min(n,m))$，队列中节点数量最大不会超过较小二叉树的节点数。

```c++
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        queue<TreeNode *> cmp_queue;
        cmp_queue.push(p);
        cmp_queue.push(q);
        while (!cmp_queue.empty()) {
            p = cmp_queue.front();
            cmp_queue.pop();
            q = cmp_queue.front();
            cmp_queue.pop();
            if (p == nullptr && q == nullptr) {
                continue;
            } else if (p == nullptr || q == nullptr || p->val != q->val) {
                return false;
            } else {
                cmp_queue.push(p->left);
                cmp_queue.push(q->left);

                cmp_queue.push(p->right);
                cmp_queue.push(q->right);
            }
        }
        return true;
    }
};
```

# 平衡二叉树

- 链接
- code

> 给定一个二叉树，判断它是否是高度平衡的二叉树。
>
> 本题中，一棵高度平衡二叉树定义为：
>
> - 一个二叉树每个节点的左右两个子树的高度差的绝对值不超过 1。

## 自顶向下递归

根据定义，一棵二叉树是平衡二叉树，当且仅当其所有子树都是平衡二叉树，因此可以使用递归的方式判断二叉树是不是平衡二叉树。

定义高度函数 **height**，用于计算二叉树的任意节点 p 的高度：
$$
height(p) =\left\{
\begin{aligned}
& 0, & p \neq nullptr \\
& \max(height(p.left), height(p.right))+1, & p = nullptr\\
\end{aligned}
\right.
$$
有了计算高度的函数，可以类似先序遍历判断二叉树是否平衡二叉树，具体做法是，判断根节点的左右节点高度差是否超过 1，若不超过 1，再分别递归判断左右节点是否平衡二叉树，这是一个自顶向下的递归过程。

**注意：** 自顶向下递归过程中存在大量重复计算，每次判断当前节点是否平衡二叉树时，都需计算一次当前节点的左右子树的全部节点。

复杂度分析：

- 时间复杂度：$O(n^2)$，需要判断 n 节点，且判断每个节点是否平衡二叉树都需重新计算一次该节点下的全部节点，最坏情况下，二叉树形成链式结构，高度为 n；
- 空间复杂度：$O(n)$，递归所需堆栈空间，最差情况下需要递归 n 次

```c++
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        return abs(height(root->left) - height(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }

    int height(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        } else {
            return max(height(root->left), height(root->right)) + 1;
        }
    }
};
```

## 自底向上递归

自顶向下递归，每个节点会被重复计算高度，如果使用自底向上递归，则每个节点只需计算一次，具体做法类似后序遍历，对于遍历到的节点，先递归地判断其左右子树是否平衡，再判断以当前节点为根的子树是否平衡。如果一棵树是平衡的，就返回它的高度（高度一定非负），否则返回 - 1。如果存在一棵子树不平衡，则整个二叉树不平衡。

**复杂度分析：**

- 时间复杂度：$O(n)$，每个节点需要计算一次高度，最差情况下要计算全部节点的高度
- 空间复杂度：$O(n)$，递归计算所需堆栈空间，最差情况下需要递归 n 次计算全部节点高度

```c++
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return height(root) >= 0;
    }

    int height(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        } 
        int left_height = height(root->left);
        int right_height = height(root->right);
        if (left_height < 0 || right_height < 0 || abs(left_height - right_height) > 1) {
            return -1;
        } else {
            return max(left_height, right_height) + 1;
        }
    }
};
```



