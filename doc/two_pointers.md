| :tiger:                    | :cat: | :dog: | :dragon: |
| -------------------------- | ----- | ----- | -------- |
| 838. [推多米诺](#推多米诺) |       |       |          |



# 推多米诺

- 链接
- code

> n 张多米诺骨牌排成一行，将每张多米诺骨牌垂直竖立。在开始时，同时把一些多米诺骨牌向左或向右推。
>
> 每过一秒，倒向左边的多米诺骨牌会推动其左侧相邻的多米诺骨牌。同样地，倒向右边的多米诺骨牌也会推动竖立在其右侧的相邻多米诺骨牌。
>
> 如果一张垂直竖立的多米诺骨牌的两侧同时有多米诺骨牌倒下时，由于受力平衡， 该骨牌仍然保持不变。
>
> 就这个问题而言，我们会认为一张正在倒下的多米诺骨牌不会对其它正在倒下或已经倒下的多米诺骨牌施加额外的力。
>
> 给你一个字符串 dominoes 表示这一行多米诺骨牌的初始状态，其中：
>
> - dominoes[i] = 'L'，表示第 i 张多米诺骨牌被推向左侧，
> - dominoes[i] = 'R'，表示第 i 张多米诺骨牌被推向右侧，
> - dominoes[i] = '.'，表示没有推动第 i 张多米诺骨牌。
>
> 返回表示最终状态的字符串。

## 双指针模拟

枚举所有连续的没有被推动的骨牌，根据这段骨牌的两边骨牌（如果有的话）的推倒方向决定这段骨牌的最终状态：

- 如果两边的骨牌同向，这段连续的骨牌会倒向同一方向
- 如果两边的骨牌相对，这段连续的骨牌会向中间倒
- 如果两边的骨牌相反，这段连续的骨牌会保持竖立

特别地，如果左侧没有被推到的骨牌，则假设存在一块向左到的骨牌；右侧没有被推到的骨牌，则假设存在一块向右倒的骨牌。这样的假设不会破坏骨牌的最终状态，并且边界也可以落入上述三种情况中。

使用两个指针 i，j 来枚举所有连续的没有被推动的骨牌，left 和 right 表示两边骨牌的推到方向。

**复杂度分析：**

- 时间复杂度：$O(n)$，n 是 dominoes 的长度，每个下标最多被访问一次和赋值一次
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    string pushDominoes(string dominoes) {
        int n = dominoes.size(), i = 0;
        char left = 'L';
        while (i < n) {
            int j = i;
            // 找到一段连续的没有被推动的骨牌
            while (j < n && dominoes[j] == '.') {
                ++j;
            }
            char right = j < n ? dominoes[j] : 'R';
            if (left == right) { // 方向相同，倒向同一边
                while (i < j) {
                    dominoes[i++] = right;
                }
            } else if(left == 'R' && right == 'L') { // 方向相对，倒向中间
                int k = j - 1;
                while (i < k) {
                    dominoes[i++] = 'R';
                    dominoes[k--] = 'L';
                }
            }
            left = right;
            i = j + 1;
        }
        return dominoes;
    }
};
```

## 广度优先搜索

当时间为 0 时，部分骨牌会受到一个初始的向左或向右的力而翻倒。过了 1 秒后，这些翻倒的骨牌会对其周围的骨牌施加一个力。具体表现为：

- 向左翻倒的骨牌，如果它有直立的左边紧邻的骨牌，则会对该直立的骨牌施加一个向左的力。
- 向右翻倒的骨牌，如果它有直立的右边紧邻的骨牌，则会对该直立的骨牌施加一个向右的力。

接下去需要分析这些 1 秒时受力的骨牌的状态。如果仅受到单侧的力，它们会倒向单侧；如果受到两个力，则会保持平衡。再过 1 秒后，这些新翻倒的骨牌又会对其他直立的骨牌施加力，而不会对正在翻倒或已经翻倒的骨牌施加力。

这样的思路类似于广度优先搜索。用一个队列 que 模拟搜索的顺序；数组 time 记录骨牌翻倒或者确定不翻倒的时间，翻倒的骨牌不会对正在翻倒或者已经翻倒的骨牌施加力；数组 force 记录骨牌受到的力，骨牌仅在受到单侧的力时会翻倒。

**复杂度分析：**

- 时间复杂度：$O(n)$，每个下标会最多被判断一次状态
- 空间复杂度：$O(n)$，队列和数组最多包含 n 个元素

```c++
class Solution {
public:
    string pushDominoes(string dominoes) {
        int n = dominoes.size();
        queue<int> que;
        vector<int> time(n, -1);
        vector<string> force(n);
        for (int i = 0; i < n; ++i) {
            if (dominoes[i] != '.') {
                que.emplace(i);
                time[i] = 0;
                force[i].push_back(dominoes[i]);
            }
        }

        string res(n, '.');
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            if (force[i].size() == 1) {
                char f = force[i][0];
                res[i] = f;
                int ni = (f == 'L') ? (i - 1) : (i + 1);
                if (ni >= 0 && ni < n) {
                    int t = time[i];
                    if (time[ni] == -1) {
                        que.emplace(ni);
                        time[ni] = t + 1;
                        force[ni].push_back(f);
                    } else if (time[ni] == t + 1) {
                        force[ni].push_back(f);
                    }
                }
            }
        }
        return res;
    }
};
```

