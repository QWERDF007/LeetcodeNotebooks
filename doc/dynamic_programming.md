| :tiger: | :cat: | :dog: | :dragon:                                       |
| ------- | ----- | ----- | ---------------------------------------------- |
|         |       |       |                                                |
|         |       |       |                                                |
|         |       |       |                                                |
|         |       |       | 688. [骑士在棋盘上的概率](#骑士在棋盘上的概率) |



# 骑士在棋盘上的概率

- 链接
- code

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



