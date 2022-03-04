| :tiger:                                        | :cat:                                                      | :dog:                                      | :dragon:                       |
| ---------------------------------------------- | ---------------------------------------------------------- | ------------------------------------------ | ------------------------------ |
| 144. [二叉树的前序遍历](#二叉树的前序遍历)     | 94.[二叉树的中序遍历](#二叉树的中序遍历)                   | 145. [二叉树的后序遍历](#二叉树的后序遍历) | 100. [相同的树](#相同的树)     |
| 110. [平衡二叉树](#平衡二叉树)                 | 111. [二叉树的最小深度](#二叉树的最小深度)                 | 112. [路径总和](#路径总和)                 | 226. [翻转二叉树](#翻转二叉树) |
| 156. [上下翻转二叉树](#上下翻转二叉树)         | 235. [二叉搜索树的最近公共祖先](#二叉搜索树的最近公共祖先) | 257. [二叉树的所有路径](#二叉树的所有路径) | 404. [左叶子之和](#左叶子之和) |
| 501. [二叉搜索树中的众数](#二叉搜索树中的众数) | 563. [二叉树的坡度](#二叉树的坡度)                         |                                            |                                |



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

# 二叉树的前序遍历

- [链接](https://leetcode-cn.com/problems/binary-tree-preorder-traversal/)
- [code](../cc/tree/binary_tree.h)

>给你二叉树的根节点 root，返回它节点值的前序遍历。

## 递归

先序遍历即有限访问根节点，然后访问左子树，最后访问右子树，访问子树时以相同的顺序访问。

**复杂度分析：**

- 时间复杂度：$O(n)$，递归遍历全部节点时间
- 空间复杂度：$O(h)$，递归堆栈空间，h 为树的高度，平均情况下 $O(\log n)$，最坏情况下 $O(n)$

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        preorder(root, res);
        return res;
    }

    void preorder(TreeNode *root, vector<int> &res) {
        if (root == nullptr) {
            return;
        }
        res.emplace_back(root->val);
        preorder(root->left, res);
        preorder(root->right, res);
    }
};
```

## 迭代

递归隐式地维护了一个栈，使用迭代方法，在迭代的过程中显示地模拟这个栈。其他和递归遍历一样。

**复杂度分析：**

- 时间复杂度：$O(n)$，迭代遍历全部节点时间
- 空间复杂度：$O(n)$，迭代模拟递归遍历全部节点空间

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode *> stk;
        TreeNode *cur = root;
        while (cur != nullptr || !stk.empty()) {
            while (cur != nullptr) {
                res.emplace_back(cur->val);
                stk.emplace(cur);
                cur = cur->left;
            }
            cur = stk.top();
            stk.pop();
            cur = cur->right;
        }
        return res;
    }
};
```

## Morris

Morris 遍历算法是另一种遍历二叉树的方法，它能将非递归的中序遍历空间复杂度降为 O(1)。

算法整体步骤如下（假设当前节点为 cur）：

- 如果 `cur` 无左节点，即 `cur->left == nullptr`，将 `cur` 的值加入结果，访问 `cur` 的右节点，即 `cur = cur->right`。
- 如果 `cur` 有左节点，则找到 `cur` 左子树上最右的节点（即左子树中序遍历的最后一个节点，`cur` 在中序遍历中的前驱节点），记为 `predecessor`。根据 `predecessor` 的右节点是否为空，进行如下操作：
  - 如果 `predecessor` 的右节点为空，则将其右节点指向 `cur`，将 `cur` 的值加入结果，然后访问 `cur` 的左节点，即 `cur = cur->left`。
  - 如果 `predecessor` 的右节点不为空，则此时其右节点指向 `cur`，说明已经遍历完 `cur` 的左子树，将 `predecessor` 的右节点置空，即 `predecessor->right = nullptr`，然后访问 `cur` 的右节点，即 `cur = cur->right`。
- 重复上述操作，直到访问完整棵树。

其实整个过程我们就多做一步：假设当前遍历到的节点为 cur，将 cur 的左子树中最右边的节点的右孩子指向 cur，这样在左子树遍历完成后我们通过这个指向走回了 cur，且能通过这个指向知晓我们已经遍历完成了左子树，而不用再通过栈来维护，省去了栈的空间复杂度。

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode *cur = root, *predecessor = nullptr;
        while (cur) {
            if (cur->left) {
                predecessor = cur->left;
                // 找到 cur 中序遍历的前驱节点，即准备输出 cur 的前一个节点
                while (predecessor->right && predecessor->right != cur) {
                    predecessor = predecessor->right;
                }
                // 第一次遍历到前驱，前驱节点的右节点指向 cur
                if (predecessor->right == nullptr) {
                    res.emplace_back(cur->val);
                    predecessor->right = cur;
                    cur = cur->left;
                } 
                // 第二次遍历到前驱，说明左子树遍历完了
                else {
                    predecessor->right = nullptr;
                    cur = cur->right;
                }
            } else {
                res.emplace_back(cur->val);
                cur = cur->right;
            }
        }
        return res;
    }
};
```

# 二叉树的中序遍历

- [链接](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)
- [code](../cc/tree/binary_tree.h)

> 给定一个二叉树的根节点 root，返回它的中序遍历。


## 递归

中序遍历即优先访问左子树，然后访问根，最后访问右子树的遍历方式，访问子树时以相同的顺序访问。

**注意：** 递归终止条件是当前节点为空。

**复杂度分析**：

- 时间复杂度：$O(n)$，递归遍历全部节点时间
- 空间复杂度：$O(h)$，递归堆栈空间，h 为树的高度，平均情况下 $O(\log n)$，最坏情况下 $O(n)$

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

- 时间复杂度：$O(n)$，迭代全部节点时间
- 空间复杂度：$O(n)$，迭代模拟递归栈所需空间，需要迭代全部节点

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

## Morris

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

# 二叉树的后序遍历

- [链接](https://leetcode-cn.com/problems/binary-tree-postorder-traversal/)
- [code](../cc/tree/binary_tree.h)

> 给你一棵二叉树的根节点 root，返回其节点值的后序遍历。

## 递归

后序遍历即先访问左子树，然后访问右子树，最后访问根节点的顺序，访问子树以相同的顺序访问。

**复杂度分析：**

- 时间复杂度：$O(n)$，递归遍历全部节点时间
- 空间复杂度：$O(h)$，递归堆栈空间，h 为树的高度，平均情况下 $O(\log n)$，最坏情况下 $O(n)$

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        postorder(root, res);
        return res;
    }

    void postorder(TreeNode* root, vector<int> &res) {
        if (root == nullptr) {
            return;
        }
        postorder(root->left, res);
        postorder(root->right, res);
        res.emplace_back(root->val);
    }
};
```

## 迭代

递归隐式地维护了一个栈，使用迭代方法，在迭代的过程中显示地模拟这个栈。其他和递归遍历一样。

**复杂度分析：**

- 时间复杂度：$O(n)$，迭代全部节点时间
- 空间复杂度：$O(n)$，迭代全部节点所需空间

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode *> stk;
        TreeNode *cur = root, *prev = nullptr;
        while (cur != nullptr || !stk.empty()) {
            while (cur != nullptr) {
                stk.emplace(cur);
                cur = cur->left;
            }
            cur = stk.top();
            stk.pop();
            // 右子树为空或已经处理完则加入根节点，避免死循环
            if (cur->right == nullptr || cur->right == prev) {
                res.emplace_back(cur->val);
                prev = cur;
                cur = nullptr;
            } else {
                stk.emplace(cur);
                cur = cur->right;
            }
        }
        return res;
    }
};
```

## Morris

分析看 leetcode 题解

**复杂度分析：**

- 时间复杂度：$O(n)$，其中 n 是二叉树的节点数。没有左子树的节点只被访问一次，有左子树的节点被访问两次
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode *cur = root, *predecessor = nullptr;
        while (cur) {
            predecessor = cur->left;
            if (predecessor) {
                while (predecessor->right && predecessor->right != cur) {
                    predecessor = predecessor->right;
                }
                // 第一次访问到 cur 的中序遍历的前驱
                if (predecessor->right == nullptr) {
                    predecessor->right = cur;
                    cur = cur->left;
                    continue;
                } 
                // 左子树访问完
                else {
                    predecessor->right = nullptr;
                    AddPath(cur->left, res);
                    //cur = cur->right;
                }
            } 
            cur = cur->right;
        }
        AddPath(root, res);
        return res;
    }

    void AddPath(TreeNode *root, vector<int> &res) {
        int count = 0;
        while (root) {
            ++count;
            res.emplace_back(root->val);
            root = root->right;
        }
        reverse(res.end() - count, res.end());
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

- [链接](https://leetcode-cn.com/problems/balanced-binary-tree/)
- [code](../cc/tree/binary_tree.h)

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

# 二叉树的最小深度

- [链接](https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/)
- [code]((../cc/tree/binary_tree.h))

> 给定一个二叉树，找出其最小深度。
>
> 最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
>
> 说明：叶子节点是指没有子节点的节点。

## 深度优先搜索

对于每个非叶子节点，分别计算其左右子树的最小叶子节点深度，可以用递归来计算。

**复杂度分析**：

- 时间复杂度：$O(n)$，n 是节点数，最差情况下每个节点都要访问一次
- 空间复杂度：$O(h)$，h 是二叉树高度，最差情况二叉树呈链状，高度为 n，空间复杂度 $O(n)$，平均情况下树的高度为与节点数的对数正相关，空间复杂度 $O(\log n)$

```c++
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        } else if (root->left == nullptr && root->right == nullptr) {
            return 1;
        } else if (root->left == nullptr) {
            return minDepth(root->right) + 1;
        } else if (root->right == nullptr) {
            return minDepth(root->left) + 1;
        } else {
            return min(minDepth(root->left), minDepth(root->right)) + 1;
        }
    }
};
```

## 广度优先搜索

可以借助队列来层序遍历二叉树，寻找叶子节点，直接返回这个叶子节点的深度。广度优先搜索保证最先搜索到的叶子节点的深度一定最小。

**注意：** 虽然算法理论时间复杂度 $O(n)$，但队列操作时间对算法影响较大

**复杂度分析：**

- 时间复杂度：$O(n)$，最差情况下每个节点都需访问
- 空间复杂度：$O(n)$，队列所需空间

```c++
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int depth = 1;
        queue<TreeNode *> que;
        que.emplace(root);
        while (!que.empty()) {
            int n = que.size();
            for (int i = 0; i < n; ++i) {
                TreeNode *cur = que.front();
                que.pop();
                if (cur->left == nullptr && cur->right == nullptr) {
                    return depth;
                }
                if (cur->left) {
                    que.emplace(cur->left);
                }
                if (cur->right) {
                    que.emplace(cur->right);
                }
            }
            ++depth;
        }
        return depth;
    }
};
```

# 路径总和

- [链接]()
- [code]((../cc/tree/binary_tree.h))

> 给你二叉树的根节点 root 和一个表示目标和的整数 targetSum。
>
> 判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和 targetSum。
>
> 如果存在，返回 true；否则，返回 false。
>
> 叶子节点是指没有子节点的节点。

## 深度优先搜索

问题是求根节点到叶子节点的路径上所有节点的总和是否等于目标和，直接递归求和较难，可以将大问题转换为一个小问题：是否存在从当前节点的子节点到叶子节点的路径，满足其路径和为 `sum - val`，不难发现这满足递归的性质，若当前节点是叶子节点则直接判断 `sum == val`。

**复杂度分析：**

- 时间复杂度：$O(n)$，每个节点都需要访问一次
- 空间复杂度：$O(h)$，h 为二叉树高度，最差情况下二叉树呈链状，高度为 n

```c++
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            return false;
        } else if (!root->left && !root->right) {
            return root->val == targetSum;
        } else {
            return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
        }
    }
};
```

## 广度优先搜索

可以使用队列记录根节点到当前节点的路径和。使用两个队列分别存储要遍历的节点和根节点到这些节点的路径和，也可以使用一个队列和 pair 存储。

**注意：** 实际测试 pair 比双队列耗时稍微多一些。

**复杂度分析**：

- 时间复杂度：$O(n)$，遍历全部节点时间
- 空间复杂度：$O(n)$，队列存储时间

```c++
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) {
            return false;
        }
        queue<TreeNode *> que_tree;
        queue<int> que_sum;
        que_tree.emplace(root);
        que_sum.emplace(0);
        while (!que_tree.empty()) {
            TreeNode *cur = que_tree.front();
            int sum = que_sum.front() + cur->val;
            que_tree.pop();
            que_sum.pop();
            if (!cur->left && !cur->right && sum == targetSum) {
                return true;
            }
            if (cur->left) {
                que_tree.emplace(cur->left);
                que_sum.emplace(sum);
            }
            if (cur->right) {
                que_tree.emplace(cur->right);
                que_sum.emplace(sum);
            }
        }
        return false;
    }
};
```

# 翻转二叉树

- [链接](https://leetcode-cn.com/problems/invert-binary-tree/)
- [code]((../cc/tree/binary_tree.h))

> 给你一棵二叉树的根节点 root，翻转这棵二叉树，并返回其根节点。

## 深度优先搜索

翻转二叉树，从根节点开始，递归地对树进行遍历，翻转左右子树，对于子树也同样翻转其左右子树，最后当前根节点的左右子树即可。

**复杂度分析：**

- 时间复杂度：$O(n)$，递归遍历全部节点时间
- 空间复杂度：$O(h)$，递归堆栈空间，h 为二叉树高度，平均情况下 $O(\log n)$，最差情况下 $O(n)$

```c++
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode *left = invertTree(root->left);
        TreeNode *right = invertTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
};
```

## 广度优先搜索

使用队列来层序遍历二叉树节点，并交换其左右子树。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历全部节点时间
- 空间复杂度：$O(n)$，队列存储空间

```c++
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        queue<TreeNode *> que;
        que.emplace(root);
        while (!que.empty()) {
            TreeNode *cur = que.front();
            que.pop();
            TreeNode *tmp = cur->left;
            cur->left = cur->right;
            cur->right = tmp;
            if (cur->left) {
                que.emplace(cur->left);
            }
            if (cur->right) {
                que.emplace(cur->right);
            }
        }
        return root;
    }
};
```



# 上下翻转二叉树

- 链接
- [code]((../cc/tree/binary_tree.h))

> 给你一个二叉树的根节点 root，请你将此二叉树上下翻转，并返回新的根节点。
>
> 你可以按下面的步骤翻转一棵二叉树：
>
> 1. 原来的左子节点变成新的根节点
> 2. 原来的根节点变成新的右子节点
> 3. 原来的右子节点变成新的左子节点
>
> 上面的步骤逐层进行。题目数据保证每个右节点都有一个同级节点（即共享同一父节点的左节点）且不存在子节点。

## 层遍历

由题意分析可得，该二叉树只会向左生长，只需遍历各层最左节点，将原父节点变为其的右子节点，原右节点变为其的左子节点即可完成翻转，可以将根节点当作前一层的最左节点，其父节点 `father` 和父节点的右节点 `right` 均为 `nullptr`。

**复杂度分析**：

- 时间复杂度：$O(h)$，h 为二叉树高度，本题的二叉树树只会向左生长
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        TreeNode *right = nullptr, *father = nullptr;
        while (root) {
            // 记录当前节点的左子节点，待下一次遍历
            TreeNode *left = root->left;
            // 更新当前节点左节点为父节点的右节点
            root->left = right;
            // 记录当前节点的右子节点
            right = root->right;
            // 更新当前节点的右子节点为原父节点
            root->right = father;
            // 记录当前节点作为下一个待遍历节点的父节点
            father = root;
            root = left;
            // 最终 root=nullptr ，father 指向翻转后的二叉树的根节点
        }
        return father;
    }
};
```



# 二叉搜索树的最近公共祖先

- [链接](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree/)
- [code]((../cc/tree/binary_tree.h))

> 给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
>
> 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

## 递归

注意到题目所给的是二叉搜索树，其性质为比根节点小的节点都在根节点左边，比根节点大的节点都在根节点右边，子树也满足该性质。因此可以判断 p 和 q 是否位于当前节点的同一侧，不是则当前节点为 p 和 q 的最近公共祖先，否则访问同一侧的子树。

**复杂度分析：**

- 时间复杂度：$O(n)$，递归遍历时间，最差情况下有一半节点被访问
- 空间复杂度：$O(h)$，h 为二叉树高度

```c++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (p->val < root->val && q->val < root->val) {
            return lowestCommonAncestor(root->left, p, q);
        } else if (p->val > root->val && q->val > root->val) {
            return lowestCommonAncestor(root->right, p, q);
        } else {
            return root;
        }
    }
};
```



## 遍历

根据二叉搜索树的性质，遍历获取根节点到 p 和 q 的路径，比较条路径，当出现不同时，则该节点为 p 和 q 的最近公共祖先。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历获取路径时间 $O(n)$，比较路径不同时间 $O(n)$
- 空间复杂度：$O(n)$

```c++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode *> p_path = getPath(root, p);
        vector<TreeNode *> q_path = getPath(root, q);
        int n = p_path.size(), m = q_path.size();
        TreeNode *ancestor = nullptr;
        for (int i = 0; i < n && i < m; ++i) {
            if (p_path[i] == q_path[i]) {
                ancestor = p_path[i];
            } else {
                break;
            }
        }
        return ancestor;
    }

    std::vector<TreeNode *> getPath(TreeNode *root, TreeNode *target) {
        vector<TreeNode *> path;
        TreeNode *cur = root;
        while (cur && cur->val != target->val) {
            path.emplace_back(cur);
            if (target->val < cur->val) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        path.emplace_back(cur);
        return path;
    }
};
```



# 二叉树的所有路径

- [链接](https://leetcode-cn.com/problems/binary-tree-paths/)
- [code]((../cc/tree/binary_tree.h))

> 给你一个二叉树的根节点 root，按任意顺序，返回所有从根节点到叶子节点的路径。
>
> 叶子节点是指没有子节点的节点。

## 深度优先搜索

使用深度优先搜索遍历二叉树，需要考虑当前节点是否叶子节点：

- 如果当前当前节点不是叶子节点，则在当前路径末尾加入该节点，并继续递归遍历该节点的左右节点
- 如果当前节点是叶子节点，则在当前路径末尾添加该节点，并将该路径加入答案

**复杂度分析：**

- 时间复杂度：$O(n^2)$，递归遍历 n 个节点时间 $O(n)$，每个节点只被访问一次，每一次会对 `path` 拷贝，拷贝时间 $O(n)$，故总时间复杂度 $O(n^2)$
- 空间复杂度：$O(h^2)$，递归所需空间 $O(h)$，h 为二叉树高度，每次遍历需要拷贝一个根节点到当前节点路径的 `path ` 空间，故总空间复杂度 $O(h^2)$

```c++
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> paths;
        treePaths(root, paths, "");
        return paths;
    }

    void treePaths(TreeNode *root, vector<string> &paths, string path) {
        if (root) {
            path += to_string(root->val);
            if (root->left == nullptr && root->right == nullptr) {
                paths.emplace_back(path);
            } else {
                path += "->";
                treePaths(root->left, paths, path);
                treePaths(root->right, paths, path);
            }
        }
    }
};
```

## 广度优先搜索

使用队列来层序遍历二叉树和维护到当前节点的路径，遇到叶子节点，则在当前路径末尾加入该节点，并加入答案；遇到非叶子节点，则在当前路径末尾加入该节点，并将该节点左右节点加入到队列中，将当前路径加入到队列中。

**复杂度分析：**

- 时间复杂度：$O(n^2)$，遍历 n 个节点时间 $O(n)$，拷贝 `path` 时间 $O(n)$
- 空间复杂度：$O(n^2)$ ?，队列存储 n 个节点空间 $O(n)$， n 个路径空间 $O(n)$，根节点到当前节点路径 `path` 空间 $O(n)$

```c++
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> paths;
        if (root == nullptr) {
            return paths;
        }
        queue<TreeNode *> que_node;
        queue<string> que_path;
        que_node.emplace(root);
        que_path.emplace("");
        while (!que_node.empty()) {
            TreeNode *cur = que_node.front();
            string path = que_path.front();
            que_node.pop();
            que_path.pop();
            path += to_string(cur->val);
            if (cur->left == nullptr && cur->right == nullptr) {
                paths.emplace_back(path);
            } else {
                path += "->";
                if (cur->left) {
                    que_node.emplace(cur->left);
                    que_path.emplace(path);
                }
                if (cur->right) {
                    que_node.emplace(cur->right);
                    que_path.emplace(path);
                }
            }
        }
        return paths;
    }
};
```



# 左叶子之和

- [链接](https://leetcode-cn.com/problems/sum-of-left-leaves/)
- [code]((../cc/tree/binary_tree.h))

> 给定二叉树的根节点 root，返回所有左叶子之和。

## 深度优先搜索

遍历节点到 node，如果它的左子节点是一个叶子节点，那么将它的左子节点的值加入答案。

自底向上看，当最底层的子树计算完左叶子节点之和后，可以向上抽象成一棵新的树，树的子节点之值为其左叶子节点之和，逐层向上抽象。因此可以通过递归完成累加。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历全部节点时间
- 空间复杂度：$O(h)$，h 为二叉树高度

```c++
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        int ans = 0;
        if (root->left) {
            ans = isLeafNode(root->left) ? root->left->val : sumOfLeftLeaves(root->left);
        }
        if (root->right && !isLeafNode(root->right)) {
            ans += sumOfLeftLeaves(root->right);
        }
        return ans;
    }

    bool isLeafNode(TreeNode *node) {
        return !node->left && !node->right;
    }
};
```

## 广度优先搜索

通过队列模拟递归遍历，遇到左叶子节点将值累加至答案。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历全部节点时间
- 空间复杂度：$O(n)$，队列存储全部节点空间

```c++
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        
        queue<TreeNode *> q;
        q.emplace(root);
        int ans = 0;
        while (!q.empty()) {
            TreeNode *cur = q.front();
            q.pop();
            if (cur->left) {
                if (isLeafNode(cur->left)) {
                    ans += cur->left->val;
                } else {
                    q.emplace(cur->left);
                }
            }
            if (cur->right && !isLeafNode(cur->right)) {
                q.emplace(cur->right);
            }
        }
        return ans;
    }

    bool isLeafNode(TreeNode *node) {
        return !node->left && !node->right;
    }
};
```



# 二叉搜索树中的众数

- [链接]()
- [code]((../cc/tree/binary_tree.h))

> 给你一个含重复值的二叉搜索树（BST）的根节点 root，找出并返回 BST 中的所有众数（即，出现频率最高的元素）。
>
> 如果树中有不止一个众数，可以按任意顺序返回。
>
> 假定 BST 满足如下定义：
>
> - 结点左子树中所含节点的值小于等于当前节点的值
> - 结点右子树中所含节点的值大于等于当前节点的值
> - 左子树和右子树都是二叉搜索树

## 哈希表

根据二叉搜索树的性质可知，对这棵树的中序遍历出来的结果将是一个有序的序列，因此可以先获取这棵树的中序遍历，再遍历，用哈希表来统计出现次数，最后再找到出现次数最多的元素加入结果即可。

**注意： ** 哈希表操作时间复杂度理论为 $O(1)$，但对算法时间影响较大

**复杂度分析：**

- 时间复杂度：$O(n)$，中序遍历时间 $O(n)$，遍历有序序列统计出现次数时间 $O(n)$，获取出现次数最多的元素时间 $O(n)$
- 空间复杂度：$O(n)$，存储有序序列空间 $O(n)$，哈希表存储空间 $O(n)$

```c++
class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        unordered_map<int, int> map;
        vector<int> nums, ans;
        inorder(root, nums);
        int max_count = 0;
        for (int num : nums) {
            ++map[num];
            if (map[num] > max_count) {
                max_count = map[num];
            }
        }
        for (auto &element : map) {
            if (element.second == max_count) {
                ans.emplace_back(element.first);
            }
        }
        return ans;
    }

    void inorder(TreeNode *root, vector<int> &nums) {
        if (root == nullptr) {
            return;
        }
        inorder(root->left, nums);
        nums.emplace_back(root->val);
        inorder(root->right, nums);
    }
};
```

## 递归

可以在中序遍历的递归过程中更新结果，用 num 表示当前数字，base 表示正在统计的数字，count 表示当前数字出现次数，max_count 表示众数出现次数，用 ans 记录众数，首先更新 base 和 count：

- `num == base`，count 自增 1
- `num != base`，count 重置为 1，并更新 `base = num`

再更新 max_count：

- `count > max_count`，表示 base 不是众数，更新 `max_count = count`，`base = num`，清空 ans，并加入当前数字 num
- `count == max_count`，表示 base 在目前看是众数，加入到结果 ans 中

**复杂度分析：**

- 时间复杂度：$O(n)$，递归遍历节点时间 $O(n)$，更新结果时间 $O(1)$
- 空间复杂度：$O(1)$，题目说明递归的隐式调用栈不算开销

```c++
class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        int base = 1e-5 - 1, count = 0, max_count = 0;
        vector<int> ans;
        inorder(root, count, max_count, base, ans);
        return ans;
    }

    void inorder(TreeNode *root, int &count, int &max_count, int &base, std::vector<int> &ans) {
        if (!root) {
            return;
        }
        inorder(root->left, count, max_count, base, ans);
        update(root->val, count, max_count, base, ans);
        inorder(root->right, count, max_count, base, ans);
    }

    void update(int num, int &count, int &max_count, int &base, std::vector<int> &ans) {
        if (num == base) {
            ++count;
        } else {
            count = 1;
            base = num;
        }

        if (count == max_count) {
            ans.emplace_back(num);
        } else if (count > max_count) {
            max_count = count;
            ans = std::vector<int>({ base });
        }
    }
};
```

## 迭代

利用堆栈手动模拟递归中序遍历，其他和递归方法一样。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历节点时间 $O(n)$，更新结果时间 $O(1)$
- 空间复杂度：$O(n)$，显示维护调用堆栈空间 $O(n)$

```c++
class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        int base = 1e-5 - 1, count = 0, max_count = 0;
        vector<int> ans;
        if (!root) {
            return ans;
        }
        stack<TreeNode *> stk;
        TreeNode *cur = root;
        while (cur || !stk.empty()) {
            while (cur) {
                stk.emplace(cur);
                cur = cur->left;
            }
            cur = stk.top();
            stk.pop();
            update(cur->val, count, max_count, base, ans);
            cur = cur->right;
        }
        return ans;
    }

    void update(int num, int &count, int &max_count, int &base, std::vector<int> &ans) {
        if (num == base) {
            ++count;
        } else {
            count = 1;
            base = num;
        }

        if (count == max_count) {
            ans.emplace_back(num);
        } else if (count > max_count) {
            max_count = count;
            ans = std::vector<int>({ base });
        }
    }
};
```



# 二叉树的坡度

- [链接](https://leetcode-cn.com/problems/binary-tree-tilt/)
- [code]((../cc/tree/binary_tree.h))

> 给你一个二叉树的根节点 root，计算并返回整个树的坡度。
>
> 一个树的节点的坡度定义即为，该节点左子树的节点之和和右子树节点之和的差的绝对值。
>
> 如果没有左子树的话，左子树的节点之和为 0；没有右子树的话也是一样。空结点的坡度是 0。
>
> 整个树的坡度就是其所有节点的坡度之和。

## 深度优先搜索

根据题意，累计二叉树中所有节点的左子树之和右子树之和的差的绝对值。可以使用深度优先搜索，遍历每个节点时，累加其左子树节点之和与右子树节点之和的差的绝对值，并返回以其为根节点的树的节点之和。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历全部节点时间
- 空间复杂度：$O(h)$，递归堆栈空间，h 为二叉树的高度

```c++
class Solution {
public:
    int findTilt(TreeNode* root) {
        int ans = 0;
        dfs(root, ans);
        return ans;
    }

    int dfs(TreeNode *root, int &ans) {
        if (root == nullptr) {
            return 0;
        }
        int left_sum = dfs(root->left, ans);
        int right_sum = dfs(root->right, ans);
        ans += abs(left_sum - right_sum);
        return root->val + left_sum + right_sum;
    }
};
```

