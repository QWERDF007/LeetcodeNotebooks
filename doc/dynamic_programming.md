| :tiger:                                   | :cat: | :dog: | :dragon:                                       |
| ----------------------------------------- | ----- | ----- | ---------------------------------------------- |
| 96. [不同的二叉搜索树](#不同的二叉搜索树) |       |       |                                                |
|                                           |       |       |                                                |
|                                           |       |       |                                                |
|                                           |       |       | 688. [骑士在棋盘上的概率](#骑士在棋盘上的概率) |



# 不同的二叉搜索树

- [链接](https://leetcode-cn.com/problems/unique-binary-search-trees/)
- [code](../cc/dynamic_programming/dynamic_programming.h)

> 给你一个整数 n，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的二叉搜索树有多少种？返回满足题意的二叉搜索树的种数。

## 动态规划

详见[题解](https://leetcode-cn.com/problems/unique-binary-search-trees/solution/bu-tong-de-er-cha-sou-suo-shu-by-leetcode-solution/)

给定序列 [1 ... n]，为构建二叉搜索树，枚举每个数字 i，以 i 作为树根，将 [1 ... i -1] 作为左子树，将 [i+1 ... n] 作为右子树，按照相同的方式递归构建左子树和右子树，原问题可以分解为规模较小的两个子问题，且子问题的解可以复用，可以使用动态规划求解。

题目要求计算不同二叉树的个数，可以定义两个函数：

1. $G(n)$：长度为 n 的序列能构成的不同二叉搜索树的个数
2. $F(i,n)$：以 i 为根，序列长度为 n 的不同二叉搜索树个数 $(1 \le i \le n)$

首先，$G(n)$ 是枚举所有 i 的 $F(i,n)$ 之和：
$$
G(n) = \sum \limits_{i=1}^n F(i, n) \tag{1}
$$
对于边界情况，序列长度为 1 (只有根) 或为 0 (空树) 时，只有一种情况，即：
$$
G(0) = 1 , G(1) = 1
$$
给定序列 [1 ... n]，选 i 为根，则以 i 为根的所有二叉搜索树的集合是左子树集合和右子树集合的[笛卡儿积](https://baike.baidu.com/item/%E7%AC%9B%E5%8D%A1%E5%B0%94%E4%B9%98%E7%A7%AF/6323173)，即 $A \times B = \{(x,y) | x \in A \wedge y \in B \}$ 再加上根节点形成完整的二叉搜索树。
$$
F(i, n) = G(i - 1) \cdot G(n - i) \tag{2}
$$
将公式 (1)，(2) 结合，得到 $G(n)$ 的转移方程：
$$
G(n) = \sum \limits_{i = 1}^{n} G(i - 1) \cdot  G(n - i) \tag{3}
$$
从小到大计算 G(n) 即可。



**复杂度分析：**

- 时间复杂度：$O(n^2)$，$G(n)$ 需要计算 n 个值，每次求解需要 $O(n)$ 时间
- 空间复杂度：$O(n)$

```c++
class Solution {
public:
    int numTrees(int n) {
        vector<int> g(n+1, 0);
        g[0] = 1;
        g[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                g[i] += g[j - 1] * g[i - j];
            }
        }
        return g[n];
    }
};
```

## 数学

$G(n)$ 函数的值在数学上被称为卡特兰数，其求解公式如下：
$$
C_0 = 1, C_{n+1} = \frac{2(2n + 1)}{n + 2} C_n
$$
**复杂度分析：**

- 时间复杂度：$O(n)$，遍历计算每个 $C_n$ 时间
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int numTrees(int n) {
        long long C = 1;
        for (int i = 0; i < n; ++i) {
            C = C * 2 * (2 * i + 1) / (i + 2);
        }
        return (int)C;
    }
};
```





# 骑士在棋盘上的概率

- [链接](https://leetcode-cn.com/problems/knight-probability-in-chessboard/)
- [code](../cc/dynamic_programming/dynamic_programming.h)

>在一个 n x n 的国际象棋棋盘上，一个骑士从单元格 (row, column)?开始，并尝试进行 k 次移动。
>行和列是 从 0 开始的，所以左上单元格是 (0,0) ，右下单元格是 (n - 1, n - 1) 。
>象棋骑士有8种可能的走法，如下图所示。每次移动在基本方向上是两个单元格，然后在正交方向上是一个单元格。
>每次骑士要移动时，它都会随机从8种可能的移动中选择一种（即使棋子会离开棋盘），然后移动到那里。
>骑士继续移动，直到它走了 k 步或离开了棋盘。
>返回骑士在棋盘停止移动后仍留在棋盘上的概率。

## 动态规划

骑士每一步有 8 种可能走法，骑士以等概率的可能从中选取一种。

定义 $prob[step][i][j]$ 表示骑士从棋盘上 $(i,j)$ 位置出发，走了 $step$ 步后仍停留在棋盘上的概率。

- 当 $(i,j)$ 不在棋盘上，$prob[step][i][j] = 0$；

- 当 $(i,j)$ 在棋盘上，且 $step = 0$ 时，$prob[step][i][j] = 1$；

- 其他情况：
  $$
  prob[step][i][j] = \frac{1}{8} \sum\limits_{di,dj} prob[step-1][i+di][j+dj]
  $$
  其中 $(di,dj)$ 表示 8 种走法的偏移量，分别是 $(-2,-1), (-2,1), (2,-1), (2,1), (-1,-2), (-1,2), (1,-2), (1,-2)$。

**复杂度分析：**

- 时间复杂度：$O(k \times n^2)$。状态数一共用 $O(k \times n^2)$ 种，每次转移需要考虑 8 种走法，时间 $O(1)$
- 空间复杂度：$O(k \times n^2)$。存储每种状态所需空间，可以优化至 $O(n^2)$

```c++
class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        // 定义 prob[step][i][j] 为从 (i,j) 出发，走 step 步仍在棋盘的概率
        // (i,j) 不在棋盘时，prob[step][i][j] = 0
        // (i,j) 在棋盘且 step = 0 时，prob[step][i][j] = 1
        // 其他情况，prob[step][i][j] 等于从 step - 1 步走到 (i,j) 的概率之和除以 8
        // 若要定义为 prob[i][j][step] 则需要先处理全部 step = 0 情况才能计算后续
        vector<vector<vector<double>>> prob(k+1, vector<vector<double>>(n, vector<double>(n)));
        for (int step = 0; step <= k; ++step) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (step == 0) {
                        prob[step][i][j] = 1;
                    } else {
                        for (auto &dir : dirs) {
                            int ni = i + dir[0], nj = j + dir[1];
                            if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
                                prob[step][i][j] += prob[step - 1][ni][nj];
                            }
                        }
                        prob[step][i][j] /= 8;
                    }
                }
            }
        }
        return prob[k][row][column];
    }
    
    std::vector<std::vector<int>> dirs = {
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}
    };
};
```



