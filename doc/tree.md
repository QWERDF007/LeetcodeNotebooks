| :tiger:                                                | :cat:                                                      | :dog:                                              | :dragon:                                        |
| ------------------------------------------------------ | ---------------------------------------------------------- | -------------------------------------------------- | ----------------------------------------------- |
| 144. [二叉树的前序遍历](#二叉树的前序遍历)             | 94.[二叉树的中序遍历](#二叉树的中序遍历)                   | 145. [二叉树的后序遍历](#二叉树的后序遍历)         | 95. [不同的二叉搜索树 II](#不同的二叉搜索树 II) |
|                                                        |                                                            |                                                    | 99. [恢复二叉搜索树](#恢复二叉搜索树)           |
| 100. [相同的树](#相同的树)                             | 103. [二叉树的锯齿形层序遍历](#二叉树的锯齿形层序遍历)     |                                                    |                                                 |
|                                                        |                                                            |                                                    |                                                 |
| 110. [平衡二叉树](#平衡二叉树)                         | 111. [二叉树的最小深度](#二叉树的最小深度)                 | 112. [路径总和](#路径总和)                         | 226. [翻转二叉树](#翻转二叉树)                  |
| 156. [上下翻转二叉树](#上下翻转二叉树)                 | 235. [二叉搜索树的最近公共祖先](#二叉搜索树的最近公共祖先) | 257. [二叉树的所有路径](#二叉树的所有路径)         | 404. [左叶子之和](#左叶子之和)                  |
| 501. [二叉搜索树中的众数](#二叉搜索树中的众数)         | 563. [二叉树的坡度](#二叉树的坡度)                         | 572. [另一棵树的子树](#另一棵树的子树)             | 589. [N叉树的前序遍历](#N叉树的前序遍历)        |
| 590. [N叉树的后序遍历](#N叉树的后序遍历)               |                                                            | 606. [根据二叉树创建字符串](#根据二叉树创建字符串) | 637. [二叉树的层平均值](#二叉树的层平均值)      |
| 653. [两数之和 IV - 输入 BST](#两数之和 IV - 输入 BST) | 671. [二叉树中第二小的节点](#二叉树中第二小的节点)         | 700. [二叉搜索树中的搜索](#二叉搜索树中的搜索)     |                                                 |
|                                                        |                                                            |                                                    |                                                 |



# 二叉树的定义

```c++
struct TreeNode {
	int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
```

# N叉树的定义

```c++
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
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
- 空间复杂度：$O(h)$，迭代模拟递归空间

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
- 空间复杂度：$O(h)$，迭代模拟递归栈所需空间

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
- 空间复杂度：$O(h)$，迭代全部节点所需空间

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



# 不同的二叉搜索树 II

- [链接](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/)
- [code](../cc/tree/binary_tree.h)

> 给你一个整数 n，请你生成并返回所有由 n 个节点组成且节点值从 1 到 n 互不相同的不同二叉搜索树。可以按任意顺序返回答案。

## 回溯

二叉搜索树的性质是根节点的值大于左子树所有节点的值，小于右子树所有节点的值，且左子树和右子树也同样为二叉搜索树。因此可以在生成所有可行的二叉搜索树时，假设序列长度为 n，当前节点值为 i，则左子树的节点值的集合为 [1 ... i-1]，右子树的节点值的集合为 [i+1 ... n]。而左右子树的生成相较于原问题是一个序列长度缩小的子问题，可以用回溯的方法来解决。

定义 `generateTrees(int start, int end)` 为生成当前值的集合为 [start, end] 所有可行的二叉搜索树，枚举集合中的 i 为当前二叉树的根节点，那么序列划分为了 [start, i-1] 和 [i+1, end] 两部分，递归调用这两部分，即 `generateTrees(start, i-1)` 和 `generateTrees(i+1, end)`，获得所有可行的左子树和右子树，最后从左子树和右子树中分别任意选一棵，拼接到当前的根节点上即可得到一棵完整的二叉搜索树，将其放入结果。

递归调用的入口为 `generateTrees(1, n)`，出口为 `start > end`，返回空节点。

**复杂度分析：**

- 时间复杂度：$O(\frac{4^n}{n^{1/2}})$，复杂度取决于可行的二叉搜索树的个数，对于 n 个点生成的二叉搜索树数量等价于数学上第 n 个**卡特兰数**，用 $G_n$ 表示。生成一棵二叉搜索树需要时间 $O(n)$，一共有 $G_n$ 棵二叉搜索树，而卡特兰数以 $\frac{4^n}{n^{3/2}}$ 增长，所以总时间 $O(\frac{4^n}{n^{1/2}})$
- 空间复杂度：$O(\frac{4^n}{n^{1/2}})$，n 个点生成的二叉搜索树有 $G_n$ 棵，每棵有 n 个节点，因此存储的空间需要 $O(nG_n) = O(\frac{4^n}{n^{1/2}})$ ，递归空间需要 $O(n)$

```c++
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n <= 0) {
            return {};
        }
        return generateTrees(1, n);
    }

    vector<TreeNode*> generateTrees(int start, int end) {
        if (start > end) {
            return { nullptr };
        }
        vector<TreeNode *> all_trees;
        for (int i = start; i <= end; ++i) {
            vector<TreeNode*> left_trees = generateTrees(start, i-1);
            vector<TreeNode*> right_trees = generateTrees(i+1, end);
            for (TreeNode *left : left_trees) {
                for (TreeNode *right : right_trees) {
                    TreeNode *cur = new TreeNode(i);
                    cur->left = left;
                    cur->right = right;
                    all_trees.emplace_back(cur);
                }
            }
        }
        return all_trees;
    }
};
```



# 恢复二叉搜索树

- [链接](https://leetcode-cn.com/problems/recover-binary-search-tree/)
- [code](../cc/tree/binary_tree.h)

> 给你二叉搜索树的根节点 root，该树中的恰好两个节点的值被错误地交换。请在不改变其结构的情况下，恢复这棵树。

## 显示遍历

二叉搜索树的中序遍历得到的结果是一个递增有序序列。对序列进行遍历，寻找两个错误节点的值，若遇到相邻两个值不满足 $a_{n} < a_{n+1}$，则说明找到了错误的节点。需要注意的是两次找到的节点所取的位置不同，第一次遇到不满足 $a_{n} < a_{n+1}$ 的值时需要取 $a_{n}$ 作为错误节点，而第二次遇到需要取 $a_{n+1}$ 作为错误节点。假设有一个递增序列 a = {1,2,3,4,5,6,7}，假如有两个不相邻的节点被交换，例如 2 和 6 被交换，得到交换后的序列 a = {1,6,3,4,5,2,7}，此序列中有两个不满足 $a_n < a_{n+1}$ 条件的，分别是 6 > 3 和 5 > 2，明显可知第一个错误节点 6，而第二个错误节点是 2。

具体实现时，可以用两个变量 x, y 分别记录错误节点的位置，将 x, y 初值设为 -1，若 $a_{n+1} > a_n$，且 `x == -1`，则将 $a_n$ 所在位置赋予 x；若 `x != -1`，说明已经找到了第一个，则将 $a_{n+1}$ 的位置赋予 y，结束遍历，返回序列中 x, y 对应的值。重新遍历二叉树，交换两个错误节点的值。

**复杂度分析：**

- 时间复杂度：$O(n)$，中序遍历时间 $O(n)$，遍历序列时间 $O(n)$，遍历树恢复节点时间 $O(n)$
- 空间复杂度：$O(n)$，递归调用空间 $O(h)$，存储序列空间 $O(n)$

```c++
class Solution {
public:
    void recoverTree(TreeNode* root) {
        vector<int> nums;
        inorder(root, nums);
        int num1, num2;
        findTwoSwapped(nums, num1, num2);
        recover(root, 2, num1, num2);
    }

    void inorder(TreeNode *root, vector<int> &nums) {
        if (root == nullptr) {
            return;
        }
        inorder(root->left, nums);
        nums.emplace_back(root->val);
        inorder(root->right, nums);
    }

    void findTwoSwapped(vector<int> &nums, int &num1, int &num2) {
        int n = nums.size();
        int index1 = -1, index2 = -1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[i-1]) {
                index2 = i;
                if (index1 == -1) {
                    index1 = i - 1;
                } else {
                    break;
                }
            }
        }
        num1 = nums[index1];
        num2 = nums[index2];
    }

    void recover(TreeNode *root, int count, int num1, int num2) {
        if (root == nullptr) {
            return;
        }
        if (root->val == num1 || root->val == num2) {
            root->val = root->val == num1 ? num2 : num1;
            if (--count == 0) {
                return;
            }
        }
        recover(root->left, count, num1, num2);
        recover(root->right, count, num1, num2);
    }
};
```

## 隐式迭代遍历

寻找错误节点只需要关心相邻两个节点的大小关系是否满足 $a_n < a_{n+1}$，因此可以在中序遍历过程中，使用 pred 记录是一个节点，并用两个变量 x，y 记录错误节点，遍历完后交换两个错误节点的值即可。使用堆栈来显示模拟递归调用。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历全部节点时间 $O(n)$，交换两个节点时间 $O(1)$
- 空间复杂度：$O(h)$，模拟递归调用空间 $O(h)$, h 为二叉树高度

```c++
class Solution {
public:
    void recoverTree(TreeNode* root) {
        stack<TreeNode *> stk;
        TreeNode *cur = root;
        TreeNode *pred = nullptr;
        TreeNode *x = nullptr;
        TreeNode *y = nullptr;
        while (!stk.empty() || cur) {
            while (cur) {
                stk.emplace(cur);
                cur = cur->left;
            }
            cur = stk.top();
            stk.pop();
            if (pred && pred->val > cur->val) {
                y = cur;
                if (x == nullptr) {
                    x = pred;
                } else {
                    break;
                }
            }
            pred = cur;
            cur = cur->right;
        }
        swap(x->val, y->val);
    }
};
```

## 隐式递归遍历

同上，但是使用递归。

**注意：** 递归调用传入参数的 pred、x、y 需要以引用的方式传入，否则会在递归回溯时，恢复现场导致并未成功记录 pred、x 和 y。

**复杂度分析：**

- 时间复杂度：$O(n)$，递归遍历全部节点
- 空间复杂度：$O(h)$，递归调用空间，h 为二叉树高度

```c++
class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode *pred = nullptr;
        TreeNode *x = nullptr;
        TreeNode *y = nullptr;
        inorder(root, pred, x, y);
        swap(x->val, y->val);
    }

    void inorder(TreeNode *root, TreeNode* &pred, TreeNode* &x, TreeNode* &y) {
        if (root == nullptr) {
            return;
        }
        inorder(root->left, pred, x, y);
        if (pred && pred->val > root->val) {
            y = root;
            if (x == nullptr) {
                x = pred;
            } else {
                return;
            }
        }
        pred = root;
        inorder(root->right, pred, x, y);
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



# 二叉树的锯齿形层序遍历

- [链接](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/)
- [code](../cc/tree/binary_tree.h)

> 给你二叉树的根节点 root，返回其节点值的锯齿形层序遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

## 双端队列

使用广度优先搜索遍历二叉树得到层序遍历结果，要先从左往右，再从右往左交替输出结果，可以使用双端队列的数据结构来维护当前层节点值的输出的顺序。具体实现时，维护一个 `isReversed` 来记录当前层顺序是从左往右，还是从右往左：

- true：从右往左顺序，将层遍历结果依次加入到双端队列的头部
- false：从左往右顺序，将层遍历结果依次加入到双端队列的尾部

最后将每层遍历的结果加入到结果数组中。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历全部节点时间
- 空间复杂度：$O(n)$，存储节点队列和层序结果的双端队列空间

```c++
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == nullptr) {
            return ans;
        }
        queue<TreeNode *> q;
        q.emplace(root);
        bool isReversed = false;
        while (!q.empty()) {
            int n = q.size();
            deque<int> layer;
            for (int i = 0; i < n; ++i) {
                TreeNode *cur = q.front();
                q.pop();
                if (isReversed) {
                    layer.emplace_front(cur->val);
                } else {
                    layer.emplace_back(cur->val);
                }
                if (cur->left) {
                    q.emplace(cur->left);
                }
                if (cur->right) {
                    q.emplace(cur->right);
                }
            }
            isReversed = !isReversed;
            ans.emplace_back(vector<int>{layer.begin(), layer.end()});
        }
        return ans;
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
- 空间复杂度：$O(h)$，h 为二叉树高度，递归计算所需堆栈空间，最差情况下需要递归 n 次计算全部节点高度

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
- 空间复杂度：$O(n)$，存储 p 和 q 的路径空间

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
- 空间复杂度：$O(h)$，h 为二叉树高度，显示维护调用堆栈空间 $O(h)$

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



# 另一棵树的子树

- [链接](https://leetcode-cn.com/problems/subtree-of-another-tree/)
- [code]((../cc/tree/binary_tree.h))

> 给你两棵二叉树 root 和 subRoot。检验 root 中是否包含和 subRoot 具有相同结构和节点值的子树。如果存在，返回 true；否则，返回 false。
>
> 二叉树 tree 的一棵子树包括 tree 的某个节点和这个节点的所有后代节点。tree 也可以看做它自身的一棵子树。

## 深度优先搜索匹配

遍历每个节点，判断以这个节点为根节点的子树是否和目标树相等。

**复杂度分析：**

- 时间复杂度：$O(nm)$，n 为 root 的节点树，m 为 subRoot 的节点树，对于 root 的每个子树，都要和 subRoot 比较一次，比较一次时间 $O(m)$
- 空间复杂度：$O(\max(h_n,h_m))$，h 为二叉树高度，递归调用空间

```c++
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (root == nullptr) {
            return false;
        } else {
            return isSameTree(root, subRoot) || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
        }
    }

    bool isSameTree(TreeNode *root, TreeNode *subRoot) {
        if (root == nullptr && subRoot == nullptr) {
            return true;
        } else if (root == nullptr || subRoot == nullptr || root->val != subRoot->val) {
            return false;
        } else {
            return isSameTree(root->left, subRoot->left) && isSameTree(root->right, subRoot->right);
        }
    }
};
```

## 先序遍历序列串匹配

对两棵树深度优先搜索，获取对应的序列，然后看 root 所对应的序列中是否能匹配到 subRoot 所对应的序列。遍历获取序列，需要对左右节点为空的情况添加两个不在节点值范围的值。再使用暴力匹配或者其他匹配算法，例如 KMP。

**复杂度分析：**

- 时间复杂度：$O(n+m)$，先序遍历时间 $O(n+m)$，KMP 匹配时间 $O(n+m)$，暴力匹配时间则为 $O(nm)$
- 空间复杂度：$O(n+m)$，存储 root 序列和 subRoot 序列所需空间

```c++
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        vector<int> root_vec, subRoot_vec;
        int lnull = INT_MIN, rnull = INT_MAX;
        inorder(root, lnull, rnull, root_vec);
        inorder(subRoot, lnull, rnull, subRoot_vec);
        return kmp(root_vec, subRoot_vec);
    }

    void inorder(TreeNode *root, int lnull, int rnull, vector<int> &res) {
        if (root == nullptr) {
            return;
        }
        res.emplace_back(root->val);
        if (root->left) {
            inorder(root->left, lnull, rnull, res);
        } else {
            res.emplace_back(lnull);
        }
        if (root->right) {
            inorder(root->right, lnull, rnull, res);
        } else {
            res.emplace_back(rnull);
        }
    }

    bool kmp(vector<int> &nums, vector<int>& sub) {
        int n = nums.size(), m = sub.size();
        vector<int> fail(m, -1);
        for (int i = 1, j = -1; i < m; ++i) {
            while (j != -1 && sub[i] != sub[j + 1]) {
                j = fail[j];
            }
            if (sub[i] == sub[j + 1]) {
                ++j;
            }
            fail[i] = j;
        }
        for (int i = 0, j = -1; i < n; ++i) {
            while (j != -1 && nums[i] != sub[j + 1]) {
                j = fail[j];
            }
            if (nums[i] == sub[j + 1]) {
                ++j;
            }
            if (j == m - 1) {
                return true;
            }
        }
        return false;
    }
};
```

## 树哈希

考虑将每个子树都映射成一个唯一的数，如果 subRoot 对应的数和 root 中任意的一个子树对应的数相等，则 subRoot 是 root 的一棵子树。可以定义哈希函数：
$$
f_o = v_o + 31 \cdot f_l \cdot p(s_l) + 179 \cdot f_r \cdot p(s_r)
$$
$f_x$ 表示节点 x 的哈希值，$s_x$ 表示节点 x 对应子树大小，$v_x$ 表示节点 x 的 `val`，$p(n)$ 表示第 n 个素数，o 表示当前节点，l 和 r 分别表示左右孩子。上式表示为节点 o 的哈希值，等于这个节点的 `val` 加上 31 倍左子树的哈希值乘以第 $s_l$ 个素数，再加上 179 倍右子树的哈希值乘以第 $s_r$ 个素数。这里的 31 和 179 为左右子树的权值，可以为任意两个不同的值。

详见[力扣题解](https://leetcode-cn.com/problems/subtree-of-another-tree/solution/ling-yi-ge-shu-de-zi-shu-by-leetcode-solution/)

**复杂度分析：**

- 时间复杂度：$O(\arg \pi (max(n,m)))$
- 空间复杂度：$O(\arg \pi (max(n,m)))$

```c++
class Solution {
public:
    struct Status {
        int f, s; // f 为哈希值，s 为子树大小
        Status(int f_ = 0, int s_ = 0) : f(f_), s(s_) {}
    };

    static constexpr int MAX_N = 1000 + 5;
    static constexpr int MOD = int(1e9) + 7;

    bool vis[MAX_N] = { 0 };
    int p[MAX_N], tot;

    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (root == nullptr) {
            return false;
        }
        getPrime();
        unordered_map<TreeNode *, Status> root_hash, subroot_hash;
        treeHash(root, root_hash);
        treeHash(subRoot, subroot_hash);
        int target = subroot_hash[subRoot].f;
        for (const auto &[k, v] : root_hash) {
            if (v.f == target) {
                return true;
            }
        }
        return false;
    }

    void treeHash(TreeNode *root, unordered_map<TreeNode *, Status> &hash) {
        if (root == nullptr) {
            return;
        }
        // 对树进行哈希，h(root) = root.val + 31 * h(root.left) + 179 * h(root.right)
        hash[root] = Status(root->val, 1);
        if (root->left) {
            treeHash(root->left, hash);
            hash[root].s += hash[root->left].s;
            hash[root].f = (hash[root].f + (31LL * hash[root->left].f + p[hash[root->left].s]) % MOD) % MOD;
        }
        if (root->right) {
            treeHash(root->right, hash);
            hash[root].s += hash[root->right].s;
            hash[root].f = (hash[root].f + (179LL * hash[root->right].f + p[hash[root->right].s]) % MOD) % MOD;
        }
    }

    void getPrime() {
        vis[0] = vis[1] = 1;
        tot = 0;
        for (int i = 2; i < MAX_N; ++i) {
            if (!vis[i])
                p[++tot] = i;
            for (int j = 1; j <= tot && i * p[j] < MAX_N; ++j) {
                vis[i * p[j]] = 1;
                if (i % p[j] == 0)
                    break;
            }
        }
    }
};
```



# N叉树的前序遍历

- [链接](https://leetcode-cn.com/problems/n-ary-tree-preorder-traversal/)
- [code]((../cc/tree/binary_tree.h))

> 给定一个 n 叉树的根节点 root，返回其节点值的前序遍历。
>
> n 叉树在输入中按层序遍历进行序列化表示，每组子节点由空值 null 分隔（请参见示例）。

## 递归

N 叉树的前序遍历递归与二叉树的前序遍历递归思路一样，先访问根节点，再访问子节点即可。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历全部节点时间
- 空间复杂度：$O(h)$，h 为 n 叉树高度

```c++
class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> ans;
        preorder(root, ans);
        return ans;
    }

    void preorder(Node* root, vector<int> &nums) {
        if (root == nullptr) {
            return;
        }
        nums.emplace_back(root->val);
        for (Node *child : root->children) {
            preorder(child, nums);
        }
    }
};
```

## 迭代

可以用堆栈模拟递归调用，但是从子节点返回父节点时，需要跳过已经访问过的子节点，访问未访问过的子节点，可以使用哈希表记录当前节点已经访问过的子节点。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历全部节点时间
- 空间复杂度：$O(h)$，堆栈模拟递归调用空间 $O(h)$，存储已访问过的子节点 $O(h)$

```c++
class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> ans;
        if (root == nullptr) {
            return ans;
        }
        unordered_map<Node *, int> cnt;
        stack<Node *> stk;
        Node *cur = root;
        while (!stk.empty() || cur) {
            while (cur) {
                ans.emplace_back(cur->val);
                stk.emplace(cur);
                if (cur->children.size() > 0) {
                    cnt[cur] = 0;
                    cur = cur->children[0]; // 访问第一个孩子
                } else {
                    cur = nullptr;
                }
            }
            cur = stk.top();
            int index = (cnt.count(cur) ? cnt[cur] : -1) + 1; // 访问下一个孩子
            if (index < cur->children.size()) {
                cnt[cur] = index;
                cur = cur->children[index];
            } else {
                stk.pop();
                cnt.erase(cur);
                cur = nullptr;
            }
        }
        return ans;
    }
};
```

## 迭代优化

利用栈先进后出的特性，从右向左依次将子节点入栈，这样出栈时即可保证从左往右遍历每棵子树，还可以避免记录每个节点的子节点访问数量。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历全部节点时间
- 空间复杂度：$O(h)$，堆栈模拟递归调用空间

```c++
class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> ans;
        if (root == nullptr) {
            return ans;
        }
        stack<Node *> stk;
        stk.emplace(root); 
        while (!stk.empty()){
            Node *cur = stk.top();
            stk.pop();
            ans.emplace_back(cur->val);
            // 从右往左将子节点入栈，每层的最左的子节点会在堆栈顶部
            for (auto it = cur->children.rbegin(); it != cur->children.rend(); ++it) {
                stk.emplace(*it);
            }
        }
        return ans;
    }
};
```



# N叉树的后序遍历

- [链接](https://leetcode-cn.com/problems/n-ary-tree-postorder-traversal/)
- [code]((../cc/tree/binary_tree.h))

> 给定一个 n 叉树的根节点 root ，返回其节点值的后序遍历。
>
> n 叉树在输入中按层序遍历进行序列化表示，每组子节点由空值 null 分隔（请参见示例）。

## 递归

N 叉树的后续遍历递归思路与二叉树的一样，先访问子节点，再访问根节点即可。

**复杂度分析：**

- 时间复杂度：$O(n)$，递归遍历全部节点时间
- 空间复杂度：$O(h)$，h 为 n 叉树高度，递归调用堆栈空间

```c++
class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> ans;
        postorder(root, ans);
        return ans;
    }

    void postorder(Node *root, vector<int> &res) {
        if (root == nullptr) {
            return;
        }
        for (Node *child : root->children) {
            postorder(child, res);
        }
        res.emplace_back(root->val);
    }
};
```

## 迭代

可以模拟递归中栈的调用，在后序遍历中从左向右遍历每个子树，再访问根节点。遍历时需要记录当前节点访问过的子节点，当全部子节点访问完后，再访问当前节点，访问完后将当前节点后出栈。

**复杂度分析：**

- 时间复杂度：$O(n)$，需要遍历全部节点
- 空间复杂度：$O(h)$，堆栈模拟存储全部节点空间 $O(h)$，存储节点已经访问过的子节点空间 $O(h)$

```c++

class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> ans;
        if (root == nullptr) {
            return ans;
        }
        stack<Node *> stk;
        unordered_map<Node *, int> cnt;
        Node *cur = root;
        while (cur || !stk.empty()) {
            while (cur) {
                stk.emplace(cur);
                if (cur->children.size() > 0) { // 访问第一个子节点
                    cnt[cur] = 0;
                    cur = cur->children[0];
                } else {
                    cur = nullptr;
                }
            }
            cur = stk.top();
            int index = (cnt.count(cur) ? cnt[cur] : -1) + 1;
            if (index < cur->children.size()) { // 访问下一个子节点
                cnt[cur] = index;
                cur = cur->children[index];
            } else { // 已经访问完全部子节点
                ans.emplace_back(cur->val);
                stk.pop();
                cnt.erase(cur);
                cur = nullptr;
            }
        }
        return ans;
    }
};
```

## 迭代优化

迭代时，可以从右向左地将子节点入栈，出栈时最左的子节点就在栈顶，不需要记录当前节点访问到第几个子节点，但需要记录是否已经访问过当前节点的子节点，可以用一个哈希表来维护。

**复杂度分析：**

- 时间复杂度：$O(n)$，需要遍历全部节点
- 空间复杂度：$O(h)$，堆栈空间 $O(h)$，存储已经访问过子节点的节点的哈希表空间 $O(h)$

```c++
class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> ans;
        if (root == nullptr) {
            return ans;
        }
        stack<Node *> stk;
        unordered_set<Node *> visited;
        stk.emplace(root);
        while (!stk.empty()) {
            Node *cur = stk.top();
            // 当前节点是叶子节点或已经访问过其子节点
            if (cur->children.size() == 0 || visited.count(cur)) {
                ans.emplace_back(cur->val);
                stk.pop();
            } else {
                // 反向，从右向左将子节点入栈，出栈时栈顶为最左的子节点
                for (auto it = cur->children.rbegin(); it != cur->children.rend(); ++it) {
                    stk.emplace(*it);
                }
                visited.emplace(cur);
            }
        }
        return ans;
    }
};
```

## 伪先序遍历反转

先访问当前节点，再从左往右将当前节点的子节点入栈，出栈时最右子节点在栈顶，然后访问子节点，最后将结果反转，即可得到后序遍历结果。这样和先序遍历有点类似，但在访问子节点时，是按从右往左的方向访问子节点。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历全部节点时间 $O(n)$，反转结果时间 $O(n)$
- 空间复杂度：$O(h)$，h 为 n 叉树高度，模拟堆栈空间 $O(h)$

```c++
class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> ans;
        if (root == nullptr) {
            return ans;
        }
        stack<Node *> stk;
        stk.emplace(root);
        while (!stk.empty()) {
            Node *cur = stk.top();
            stk.pop();
            ans.emplace_back(cur->val);
            for (Node *child : cur->children) {
                stk.emplace(child);
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```



# 根据二叉树创建字符串

- [链接](https://leetcode-cn.com/problems/construct-string-from-binary-tree/)
- [code]((../cc/tree/binary_tree.h))

> 你需要采用前序遍历的方式，将一个二叉树转换成一个由括号和整数组成的字符串。
>
> 空节点则用一对空括号 "()" 表示。而且你需要省略所有不影响字符串与原始二叉树之间的一对一映射关系的空括号对。

## 递归

可以使用递归得到二叉树的前序遍历。递归时，根据题要求，需要加上额外的括号，有 4 种情况：

- 当前节点的左右子节点不为空，添加节点到结果，并需要为两个子节点的结果都加上括号。
- 当前节点没有子节点，添加节点到结果，不需要添加额外括号。
- 当前节点只有左子节点，添加节点到结果，并需要为左子节点的结果加上括号，右子节点不需要。
- 当前节点只有右子节点，添加节点到结果，并且添加括号表示左子节点为空，再为右子节点的结果添加括号。

**复杂度分析：**

- 时间复杂度：$O(n)$，递归遍历全部节点时间
- 空间复杂度：$O(h)$，递归堆栈空间，h 为二叉树高度，最差情况下退化成单链结构，时间 $O(n)$

```c++
class Solution {
public:
    string tree2str(TreeNode* root) {
        if (root == nullptr) {
            return "";
        } else if (root->left == nullptr && root->right == nullptr) {
            return to_string(root->val);
        } else if (root->right == nullptr) {
            return to_string(root->val) + "(" + tree2str(root->left) + ")";
        } else {
            return to_string(root->val) + "(" + tree2str(root->left) + ")(" + tree2str(root->right) + ")";
        }
    }
};
```

## 迭代

见[官网题解](https://leetcode-cn.com/problems/construct-string-from-binary-tree/solution/gen-ju-er-cha-shu-chuang-jian-zi-fu-chuan-by-leetc/)。

**复杂度分析：**

- 时间复杂度：$O(n)$，迭代遍历全部节点时间
- 空间复杂度：$O(n)$，堆栈存储节点空间 $O(n)$，集合存储访问过节点空间 $O(n)$，总空间 $O(2n) = O(n)$

```c++
class Solution {
public:
    string tree2str(TreeNode* root) {
        if (root == nullptr) {
            return "";
        }
        stack<TreeNode *> stk;
        unordered_set<TreeNode *> visited;
        string ans = "";
        stk.emplace(root);
        while (!stk.empty()) {
            TreeNode *cur = stk.top();
            if (visited.count(cur)) {
                stk.pop();
                ans += ")";
            } else {
                visited.insert(cur);
                ans += "(" + to_string(cur->val);
                if (cur->left == nullptr && cur->right != nullptr) {
                    ans += "()";
                }
                if (cur->right) {
                    stk.emplace(cur->right);
                }
                if (cur->left) {
                    stk.emplace(cur->left);
                }
            }
        }
        return ans.substr(1, ans.size() - 2);
    }
};
```



# 二叉树的层平均值

- [链接](https://leetcode-cn.com/problems/average-of-levels-in-binary-tree/)
- [code]((../cc/tree/binary_tree.h))

> 给定一个非空二叉树的根节点 root, 以数组的形式返回每一层节点的平均值。与实际答案相差 10-5 以内的答案可以被接受。

## 深度优先搜索

利用深度优先搜索计算每层的平均值，需要记录两个每层的节点数量和节点之和。

**复杂度分析：**

- 时间复杂度：$O(n)$，n 为节点数，需要遍历全部节点
- 空间复杂度：$O(h)$，h 为二叉树高度，存储每层节点数量和节点之和的空间 $O(h)$，递归调用堆栈空间 $O(h)$

```c++
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> ans, sums;
        vector<int> counts;
        dfs(root, 0, counts, sums);
        for (int i = 0; i < counts.size(); ++i) {
            ans.emplace_back(sums[i] / counts[i]);
        }
        return ans;
    }

    void dfs(TreeNode *root, int level, vector<int> &counts, vector<double> &sums) {
        if (root == nullptr) {
            return;
        }
        if (level < counts.size()) {
            ++counts[level];
        } else {
            counts.emplace_back(1);
        }
        if (level < sums.size()) {
            sums[level] += root->val;
        } else {
            sums.emplace_back(root->val);
        }
        dfs(root->left, level + 1, counts, sums);
        dfs(root->right, level + 1, counts, sums);
    }
};
```

## 广度优先搜索

使用广度优先搜索计算每层的平均值，利用队列访问每一层的全部节点，计算每层的节点的平均值。

**复杂度分析：**

- 时间复杂度：$O(n)$，需要遍历全部节点
- 空间复杂度：$O(n)$，队列存储节点空间

```c++
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> ans;
        if (root == nullptr) {
            ans;
        }
        queue<TreeNode *> q;
        q.emplace(root);
        while (!q.empty()) {
            int n = q.size();
            double sum = 0;
            for (int i = 0; i < n; ++i) {
                TreeNode *cur = q.front();
                q.pop();
                sum += cur->val;
                if (cur->left) {
                    q.emplace(cur->left);
                }
                if (cur->right) {
                    q.emplace(cur->right);
                }
            }
            ans.emplace_back(sum / n);
        }
        return ans;
    }
};
```



# 两数之和 IV - 输入 BST

- [链接](https://leetcode-cn.com/problems/two-sum-iv-input-is-a-bst/)
- [code]((../cc/tree/binary_tree.h))

> 给定一个二叉搜索树 root 和一个目标结果 k，如果 BST 中存在两个元素且它们的和等于给定的目标结果，则返回 true。

## 深度优先搜索+哈希集合

使用深度优先搜索遍历整棵树，找出所有可能的组合，利用哈希集合存储节点值，遍历到一个节点时，在集合中查找是否存在 `k - num` 的值，如果存在则返回 `true`，否则将 `num` 加入到集合中，如果遍历完整棵树，都没找到满足的组合，则返回 `false`。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历全部节点时间 $O(n)$，哈希集合查找操作时间 $O(1)$
- 空间复杂度：$O(n)$，递归调用空间 $O(h)$，哈希集合空间 $O(n)$

```c++
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        unordered_set<int> set;
        return find(root, k, set);
    }

    bool find(TreeNode *root, int k, unordered_set<int> &set) {
        if (root == nullptr) {
            return false;
        }
        if (set.count(k - root->val)) {
            return true;
        }
        set.insert(root->val);
        return find(root->left, k, set) || find(root->right, k, set);
    }
};
```

## 广度优先搜索+哈希集合

可以使用广度优先搜索遍历节点，其他与深度优先搜索一致，查找哈希集合中是否存在 `k - num` 的值。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历全部节点时间 $O(n)$，哈希集合查找操作时间 $O(1)$
- 空间复杂度：$O(n)$，队列存储节点空间 $O(n)$，哈希集合空间 $O(n)$

```c++
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        if (root == nullptr) {
            return false;
        }
        unordered_set<int> set;
        queue<TreeNode *> q;
        q.emplace(root);
        while (!q.empty()) {
            TreeNode *cur = q.front();
            q.pop();
            if (set.count(k - cur->val)) {
                return true;
            }
            set.emplace(cur->val);
            if (cur->left) {
                q.emplace(cur->left);
            }
            if (cur->right) {
                q.emplace(cur->right);
            }
        }
        return false;
    }
};
```

## 中序遍历+双指针

利用 BST 的中序遍历得到有序序列 `nums`，再通过双指针 `left` 和 `right` 分别从头部和尾部检索是否存在 `nums[left] + nums[right] == k` 的组合，如果存在则返回 `true`，否则返回 `false`。

**复杂度分析：**

- 时间复杂度：$O(n)$，中序遍历时间 $O(n)$，双指针检索时间 $O(n)$
- 空间复杂度：$O(n)$，存储遍历得到的有序序列空间

```c++
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> nums;
        inorder(root, nums);
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == k) {
                return true;
            } else if (sum < k) {
                ++left;
            } else {
                --right;
            }
        }
        return false;
    }

    void inorder(TreeNode *root, vector<int> &res) {
        if (root == nullptr) {
            return;
        }
        inorder(root->left, res);
        res.emplace_back(root->val);
        inorder(root->right, res);
    }
};
```



## 二叉树中第二小的节点

- [链接](https://leetcode-cn.com/problems/second-minimum-node-in-a-binary-tree/)
- [code]((../cc/tree/binary_tree.h))

> 给定一个非空特殊的二叉树，每个节点都是正数，并且每个节点的子节点数量只能为 2 或 0。
>
> 如果一个节点有两个子节点的话，那么该节点的值等于两个子节点中较小的一个。
>
> 更正式地说，即 root.val = min(root.left.val, root.right.val) 总成立。
>
> 给出这样的一个二叉树，你需要输出所有节点中的第二小的值。
>
> 如果第二小的值不存在的话，输出 -1。

## 深度优先搜索

根据题意可知，root 节点值是二叉树的节点中最小的值，遍历二叉树找到比 root 大的，在遍历左右子树时，遇到当前节点值比结果大的，则不继续遍历了，因为当前节点的左右子树都比它大。结果的初值设为 -1，如果当前节点值比最小值大，则更新结果；如果结果不为 -1，并且当前节点比结果大，则结束遍历。

**复杂度分析：**

- 时间复杂度：$O(n)$，最差可能需要遍历全部节点
- 空间复杂度：$O(h)$，h 为二叉树高度，递归调用空间 $O(h)$

```c++
class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        int ans = -1;
        if (root == nullptr) {
            return ans;
        }
        int minimum = root->val;
        function<void(TreeNode*)> dfs = [&](TreeNode *root) {
            if (root == nullptr) {
                return;
            }
            if (ans != -1 && root->val >= ans) {
                return;
            }
            if (root->val > minimum) {
                ans = root->val;
            }
            dfs(root->left);
            dfs(root->right);
        };
        dfs(root);
        return ans;
    }
};  
```

## 广度优先搜索

 可以使用广度优先搜索遍历节点。设结果初值为 -1，遍历到当前节点时，若结果为 -1，则判断是否大于最小值，如果是则更新结果，接着判断是否将左右子节点加入队列；若结果不为 -1，则当前节点比结果小才更新结果，判断是否添加左右子节点到队列中。

**复杂度分析：**

- 时间复杂度：$O(n)$，最差情况下遍历全部节点
- 空间复杂度：$O(n)$，队列存储节点所需空间

```c++
class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        int ans = -1;
        if (root == nullptr) {
            return ans;
        }
        int minimum = root->val;
        queue<TreeNode *> q;
        q.emplace(root);
        while (!q.empty()) {
            TreeNode *cur = q.front();
            q.pop();
            if (ans == -1 || (ans != -1 && cur->val < ans)) {
                if (cur->val > minimum) {
                    ans = cur->val;
                }
                if (cur->left) {
                    q.emplace(cur->left);
                }
                if (cur->right) {
                    q.emplace(cur->right);
                }
            }
        }
        return ans;
    }
};  
```

## 深度优先搜索+剪枝

可以对二叉树进行剪枝，遍历二叉树的左右子树，寻找次小的值。具体做法是，若当前左子节点的值等于当前节点的值，则继续遍历左子树；若不等，则将左子节点的值记录为 `left`；若当前右子节点的值等于当前节点的值，则继续遍历右子树；若不等，则将右子节点的值记录为 `right`；则 `left` 和 `right` 中较小的值就是二叉树中第二小的值。需要注意的是，若在子树中没找到次小值，返回 -1，此时不能以 `min(left,right)` 作为答案，需要返回有效值 `max(left,right)`，否则整棵树都是 -1。

**复杂度分析：**

- 时间复杂度：$O(n)$，最差情况下需要遍历全部节点
- 空间复杂度：$O(h)$，h 为二叉树高度，递归调用空间

```c++
class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        if (root == nullptr || root->left == nullptr || root->right == nullptr) {
            return -1;
        }
        int left = root->val == root->left->val ? findSecondMinimumValue(root->left) : root->left->val;
        int right = root->val == root->right->val ? findSecondMinimumValue(root->right) : root->right->val;
        int ans = min(left, right);
        return ans > 0 ? ans : max(left, right);
    }
};  
```



# 二叉搜索树中的搜索

- [链接]()
- [code]((../cc/tree/binary_tree.h))

> 给定二叉搜索树（BST）的根节点 root 和一个整数值 val。
>
> 你需要在 BST 中找到节点值等于 val 的节点。返回以该节点为根的子树。如果节点不存在，则返回 null。

## 递归

二叉搜索树的根节点大于左子树所有节点，小于右子树所有节点。因此可以递归遍历，若根节点值等于 val，则返回；若根节点值大于 val ，则遍历左子树；若根节点值小于 val，则遍历右子树。

**复杂度分析：**

- 时间复杂度：$O(n)$，最差情况下需要遍历全部节点
- 空间复杂度：$O(h)$，h 为 BST 高度，最差情况下递归空间 $O(n)$

```c++
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return nullptr;
        } else if (root->val == val) {
            return root;
        } else {
            return searchBST(val < root->val ? root->left : root->right, val);
        }
    }
};
```

## 迭代

可以通过迭代来遍历 BST，若当前节点值等于 val，则返回当前节点；若当前节点值小于 val，则将当前节点指向其右子节点；若当前节点值大于 val，则将当前节点指向其左子节点。

**复杂度分析：**

- 时间复杂度：$O(n)$，最差情况下需要遍历全部节点
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        TreeNode *cur = root;
        while (cur) {
            if (cur->val == val) {
                return cur;
            }
            cur = val < cur->val ? cur->left : cur->right;
        }
        return nullptr;
    }
};
```

