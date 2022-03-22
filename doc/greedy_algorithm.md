| :tiger:                    | :cat:                      | :dog:                                                        | :dragon: |
| -------------------------- | -------------------------- | ------------------------------------------------------------ | -------- |
| 455. [分发饼干](#分发饼干) | 969. [煎饼排序](#煎饼排序) | 2038. [如果相邻两个颜色均相同则删除当前颜色](#如果相邻两个颜色均相同则删除当前颜色) |          |



# 分发饼干

- [链接](https://leetcode-cn.com/problems/assign-cookies/)
- [code](../cc/greedy_algorithm/greedy_algorithm.h)

> 假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。
>
> 对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；
>
> 并且每块饼干 j，都有一个尺寸 s[j]。如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i，这个孩子会得到满足。
>
> 你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

## 排序+贪心算法

为了尽可能满足最多数量的孩子，从贪心的角度考虑，应该按照孩子的胃口从小到大的顺序依次满足每个孩子，且对每个孩子，应该选择可以满足这个孩子的胃口且尺寸最小的饼干。

假设有 m 个孩子，胃口分别是 $g_1$ 到 $g_m$，有 n 块饼干，尺寸分别是 $s_1$ 到 $s_n$，满足 $g_i \le g_{i+1}$和 $s_j \le s_{j+1}$，其中 $1 \le i \le m$，$1 \le j \le n$。

假设在对前 i - 1 个孩子分配饼干之后，可以满足第 i 个孩子的胃口的最小饼干是第 j 块饼干，即 $s_j$ 是剩下饼干中满足 $g_i \le s_j$ 的最小值，最优解是将第 j 块饼干分配给第 i 个孩子。如果不这样分配，考虑如下两种情况：

- 如果 $i < m$ 且 $g_{i+1} \le s_j$ 也成立，则如果将第 j 块饼干分配给第 i + 1 个孩子，且还有剩余的饼干，则可将第 j + 1 快饼干分配给第 i 个孩子，分配结果不会让更多孩子被满足；
- 如果 $j < n$，则如果将第 j + 1 块饼干分配给第 i 个孩子，当 $g_{i+1} \le s_j$ 时，可将第 j 块饼干分配给第 i + 1 个孩子，分配结果不会让更多孩子被满足；当 $g_{i+1} > s_j$ 时，第 j 块饼干无法分配给任何孩子，因此剩下可用的饼干少了一块，分配结果不会让更多孩子被满足，甚至可能会因为少了一块可用的饼干而导致更少的孩子被满足

基于上述分析，可以使用贪心算法尽可能满足最多数量的孩子。具体实现是，将两个数组进行排序，对于 g 中每个元素 `g[i]`，找到 s 中未被使用的最小值 $s[j]$，使得 $g[i] \le s[j]$。

复杂度分析：

- 时间复杂度：$O(n \log n + m \log m)$，排序时间 $O(n \log n + m \log m)$，遍历数组时间 $O(n+m)$
- 空间复杂度：$O(\log n + \log m)$，排序所需空间

```c++
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int n = g.size(), m = s.size();
        int i = 0, j = 0, cnt = 0;
        while (i < n && j < m) {
            if (g[i] > s[j]) {
                ++j;
            } else {
                ++cnt;
                ++i;
                ++j;
            }
        }
        return cnt;
    }
};
```

# 煎饼排序

- [链接](https://leetcode-cn.com/problems/pancake-sorting/)
- [code](../cc/greedy_algorithm/greedy_algorithm.h)

> 给你一个整数数组 arr，请使用煎饼翻转完成对数组的排序。
> 一次煎饼翻转的执行过程如下：
>
> - 选择一个整数 k，1 <= k <= arr.length
> - 反转子数组 arr[0...k-1]（下标从 0 开始）
> 
> 例如，arr = [3,2,1,4]，选择 k = 3 进行一次煎饼翻转，反转子数组 [3,2,1]，得到 arr = [1,2,3,4]。
> 以数组形式返回能使 arr 有序的煎饼翻转操作所对应的 k 值序列。任何将数组排序且翻转次数在 10 * arr.length 范围内的有效答案都将被判断为正确。

## 贪心算法

选取子数组，寻找当前子数组中最大值，反转子数组中最大值和其前面部分，将最大值放到首部，再反转整个子数组，将最大值放到最后，因为已经将最大值放到最后了，去掉尾部元素作为新的处理数组，重复上述过程，直到处理长度为 1，即对整个数组完成排序。

**复杂度分析：**

- 时间复杂度：$O(n)$，最多需要 n - 1 次寻找最大值，反转数组 2 * (n - 1) 次。查找最大值所需时间 $O(n)$，反转数组时间 $O(n)$，因此总时间是 $O(n^2)$
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    vector<int> pancakeSort(vector<int>& arr) {
        vector<int> ans;
        for (int n = arr.size(); n > 1; --n) {
            // 在 arr[0...n] 中找出最大值的位置
            int index = max_element(arr.begin(), arr.begin() + n) - arr.begin();
            // arr[0...k-1] 中最大值已经处于最右了就不反转
            if (index == n - 1) {
                continue;
            }

	        // 反转 arr[0...k-1]，将最大值放到最前面，将 k 放到结果
	        // 再反转整个 arr[0...n]，将最大值放到最后面，将 n 放到结果
	        // 完成一次循环，n 减 1
            reverse(arr.begin(), arr.begin() + index + 1);
            reverse(arr.begin(), arr.begin() + n);
            ans.emplace_back(index + 1);
            ans.emplace_back(n);
        }
        return ans;
    }
};
```



# 如果相邻两个颜色均相同则删除当前颜色

- [链接](https://leetcode-cn.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/)
- [code](../cc/greedy_algorithm/greedy_algorithm.h)

> 总共有 n 个颜色片段排成一列，每个颜色片段要么是 'A' 要么是 'B'。给你一个长度为 n 的字符串 colors，其中 colors[i] 表示第 i 个颜色片段的颜色。Alice 和 Bob 在玩一个游戏，他们轮流从这个字符串中删除颜色。Alice 先手。
>
> - 如果一个颜色片段为 'A' 且相邻两个颜色都是颜色 'A'，那么 Alice 可以删除该颜色片段。Alice 不可以删除任何颜色 'B' 片段。
> - 如果一个颜色片段为 'B' 且相邻两个颜色都是颜色 'B'，那么 Bob 可以删除该颜色片段。Bob 不可以删除任何颜色 'A' 片段。
> - Alice 和 Bob 不能从字符串两端删除颜色片段。
> - 如果其中一人无法继续操作，则该玩家输掉游戏且另一玩家获胜。
>
> 假设 Alice 和 Bob 都采用最优策略，如果 Alice 获胜，请返回 true，否则 Bob 获胜，返回 false。

## 贪心算法

根据题意，当 colors 中有一串长度为 LA 的 A 时，Alice 可以删除 LA - 2 个 A，而不能删除两边的 A。且 Bob 删除 B 的操作不会影响 Alice 删除 A 的操作。可以分别计算 Alice 和 Bob 的操作数，当 Alice 的操作数大于 Bob 时，返回 `true`，否则返回 `false`。

**复杂度分析：**

- 时间复杂度：$O(n)$，n 是 colors 的长度，需要遍历 colors 来分别统计操作数
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    bool winnerOfGame(string colors) {
        int freq[2] = {0, 0};
        char cur = 'C';
        int cnt = 0;
        for (char c : colors) {
            if (c != cur) {
                cur = c;
                cnt = 1;
            } else if (++cnt >= 3) {
                ++freq[cur - 'A'];
            }
        }            
        return freq[0] > freq[1];
    }
};
```

