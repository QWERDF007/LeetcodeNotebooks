| :tiger:                                 | :cat:                                   | :dog:                                                  | :dragon:                                            |
| --------------------------------------- | --------------------------------------- | ------------------------------------------------------ | --------------------------------------------------- |
| 13. [罗马数字转整数](#罗马数字转整数)   | 67. [二进制求和](#二进制求和)           | 168. [Excel表列名称](#Excel表列名称)                   | 208. [实现 Trie (前缀树)](#实现 Trie (前缀树))      |
|                                         |                                         |                                                        |                                                     |
|                                         |                                         |                                                        |                                                     |
| 409. [最长回文串](#最长回文串)          |                                         | 599. [两个列表的最小索引总和](#两个列表的最小索引总和) | 720. [词典中最长的单词](#词典中最长的单词)          |
| 1002. [查找共用字符](#查找共用字符)     | 1189. [气球的最大数量](#气球的最大数量) | 1446. [连续字符](#连续字符)                            | 1796. [字符串中第二大的数字](#字符串中第二大的数字) |
| 2055. [蜡烛之间的盘子](#蜡烛之间的盘子) |                                         |                                                        |                                                     |
|                                         |                                         |                                                        |                                                     |



# 罗马数字转整数

- [链接](https://leetcode-cn.com/problems/roman-to-integer/)
- [code](../cc/str/str.h)

> 罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。
>
> 字符          数值
> I             1
> V             5
> X             10
> L             50
> C             100
> D             500
> M             1000
>
> 给定一个罗马数字，将其转换成整数。

## 暴力解法

用 if else 列出所有情况。遍历字符串，计算所有情况下罗马数字所代表的数值。当前位置小于字符串长度减 1 时，`I`、`X` 和 `C` 需考虑是否特殊情况，其他则直接加对应值即可。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历字符串
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int romanToInt(string s) {
        int n = s.size();
        int m = n - 1, ret = 0;
        for (int i = 0; i < n; ++i) {
            if (i < m) {
                if (s[i] == 'I') {
                    if (s[i + 1] == 'V') {
                        ret += 4;
                        ++i;
                    } else if (s[i + 1] == 'X') {
                        ret += 9;
                        ++i;
                    } else {
                        ret += 1;
                    }
                } else if (s[i] == 'V') {
                    ret += 5;
                } else if (s[i] == 'X') {
                    if (s[i + 1] == 'L') {
                        ret += 40;
                        ++i;
                    } else if (s[i + 1] == 'C') {
                        ret += 90;
                        ++i;
                    } else {
                        ret += 10;
                    }
                } else if (s[i] == 'L') {
                    ret += 50;
                } else if (s[i] == 'C') {
                    if (s[i + 1] == 'D') {
                        ret += 400;
                        ++i;
                    } else if (s[i + 1] == 'M') {
                        ret += 900;
                        ++i;
                    } else {
                        ret += 100;
                    }
                } else if (s[i] == 'D') {
                    ret += 500;
                } else {
                    ret += 1000;
                }
            } else if (s[i] == 'I') {
                ret += 1;
            } else if (s[i] == 'V') {
                ret += 5;
            } else if (s[i] == 'X') {
                ret += 10;
            } else if (s[i] == 'L') {
                ret += 50;
            } else if (s[i] == 'C') {
                ret += 100;
            } else if (s[i] == 'D') {
                ret += 500;
            } else {
                ret += 1000;
            }
        }
        return ret;
    }
};
```

## 动态数组

动态构建字符串中每个罗马字符的数字数组。**从 1 开始遍历数组**，遇到小的数字在大的数字的左边时，减去小的数字，加上特例值。

**题目提示字符串长度大于等于 1。**也可从 0 开始遍历数组，则需多加判断是否越界。

**复杂度分析：**

- 时间复杂度：$O(n)$，构建动态数组时间 O(n)，遍历字符串 O(n)
- 空间复杂度：$O(n)$，构建动态数组空间

```c++
class Solution {
public:
    int romanToInt(string s) {
        int n = s.size();
        // int *ss = new int[n];
        int ss[n]; // gcc/g++ 编译通过，vs 编译不通过
        for (int i = 0; i < n; ++i) {
            switch (s[i]) {
            case 'I': {
                ss[i] = 1; 
                break;
            }
            case 'V': {
                ss[i] = 5;
                break;
            }
            case 'X': {
                ss[i] = 10;
                break;
            }
            case 'L': {
                ss[i] = 50;
                break;
            }
            case 'C': {
                ss[i] = 100;
                break;
            }
            case 'D': {
                ss[i] = 500;
                break;
            }
            case 'M': {
                ss[i] = 1000;
                break;
            }
            default:
                break;
            }
        }

        int ret = ss[0];
        for (int i = 1; i < n; ++i) {
            if (ss[i - 1] < ss[i]) {
                ret -= 2 * ss[i - 1];
            } 
            ret += ss[i];
        }

        // delete[] ss;
        return ret;
    }
};
```

## 哈希表

构建罗马字符和数值直接的哈希表。**从 0 遍历数组**，遇到小的数字在大的数字的左边时，减去小数。

**注：** 如果在方法内构建哈希表，构建哈希表的时间将严重影响转换时间。

**复杂度分析：**

- 时间复杂度：$O(n)$，构建哈希表时间 O(1)，遍历字符串时间 O(n)
- 空间复杂度：$O(1)$，哈希表所需空间，题目中罗马字符数固定为 7

```c++
class Solution {
public:
    int romanToInt(string s) {
        int n = s.size();
        int m = n - 1, ret = 0;
        for (int i = 0; i < n; ++i) {
            int v = symbols_value_[s[i]];
            if (i < m && v < symbols_value_[s[i + 1]]) {
                ret -= v;
            } else {
                ret += v;
            }
        }
        return ret;
    }

    std::unordered_map<char, int> symbols_value_{
        {'I',1}, {'V', 5}, {'X', 10}, {'L', 50}, 
        {'C', 100}, {'D', 500}, {'M', 1000}
    };
};
```

# 二进制求和

- [链接](https://leetcode-cn.com/problems/add-binary/)
- [code](../cc/str/str.h)

>给你两个二进制字符串，返回它们的和（用二进制表示）。
>
>输入为非空字符串且只包含数字 1 和 0。

## 列竖式(模拟)

借鉴列竖式，将两个字符串对齐，逐位相加。反转字符串后，从低位开始遍历，高位补 0，即可对齐字符串。用 `carry` 表示上一位的进位，每一位的答案为 `(carry + ai + bi) % 2`，下一位的进位为 `(carry + ai + b) / 2`。遍历完后若 `carry` 不为 0，则向结果添加一位 1。

- 时间复杂度：$O(n)$，n = max{|a|, |b|}
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    string addBinary(string a, string b) {
        string ans;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int m = a.size();
        int n = b.size();
        int i = 0, carry = 0;
        int p = max(m, n);
        while (i < p) {
            carry += i < m ? a[i] == '1' : 0;
            carry += i < n ? b[i] == '1' : 0;
            ans.push_back(carry % 2 ? '1' : '0');
            carry /= 2;
            ++i;
        }
        if (carry) {
            ans.push_back('1');
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```

## 列竖式(位运算)

同样使用列竖式，用位运算代替加减乘除。每一位的答案为 `(ai ^ bi) ^ carry`，下一位的进位 `carry` 需要考虑上一位的进位，若上一位进位为 0 ，则进位为 `x & y`；若不为 0， 则进位为 `carry & x | carry & y`。遍历完后若 `carry` 不为 0，则向结果添加一位 1。

**复杂度分析：**

- 时间复杂度：$O(n)$，n = max{|a|, |b|}
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    string addBinary(string a, string b) {
        string ans;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int m = a.size();
        int n = b.size();
        int i = 0, carry = 0, x = 0, y = 0;
        int p = max(m, n);
        while (i < p) {
            x = i < m ? a[i] == '1' : 0;
            y = i < n ? b[i] == '1' : 0;
            ans.push_back((x ^ y) ^ carry ? '1' : '0');
            carry = carry ? (carry & x | carry & y) : (x & y);
            ++i;
        }
        if (carry) {
            ans.push_back('1');
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```

# Excel表列名称

- [链接](https://leetcode-cn.com/problems/excel-sheet-column-title/)
- [code](../cc/str/str.h)

> 给你一个整数 columnNumber ，返回它在 Excel 表中相对应的列名称。
>
> 例如：
>
> A -> 1
> B -> 2
> C -> 3
> ...
> Z -> 26
> AA -> 27
> AB -> 28 
> ...

## 数学

如果列名称的长度为 n，每一位对应的序号为 $a_{n-1}$, $a_{n-2}$, ... , $a_0$，其中对于任意 $0 \leq i < n$，都有 $1 \leq a_i \leq 26$，则列名称对应的序号为：
$$
number = \sum\limits_{i=0}^{n-1} a_i \times 26^i
$$
分离出 $a_0$ 项，提出其余项公因式 26， 上式可改写为：
$$
number = a_0 + 26 \times \sum\limits_{i=1}^{n-1} ai \times 26^{i-1}
$$
等式两边减 1，得：
$$
number - 1 = a_0 - 1 + 26 \times \sum\limits_{i=1}^{n-1} ai \times 26^{i-1}
$$
由于 $0 \leq a_0 - 1 \leq 25$，由上是可知 $a_0 - 1$ 是 $number - 1$ 除以 26 的余数，可得 $a_0$。令
$$
number^{\prime} = \frac{number - a_0}{26}
$$
使用同样的方法可得 $a_1$。迭代直到 $number^{\prime} = 0$，可得到 $a_0$ 到 $a_{n-1}$ 的值。

又因为整数除法的特性：
$$
number^{\prime} = \frac{number - a_0}{26} = \frac{(number - a_0) + (a_0 - 1)}{26} = \frac{number - 1}{26}
$$
因此可以在每轮迭代过程中，先将 number 值减 1，再计算 $a_i$ 和 $number^{\prime}$。

**复杂度分析：**

- 时间复杂度：$O(\log_{26}columnNuber)$，即将 columnNuber 转换为 26 进制的位数
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    string convertToTitle(int columnNumber) {
        std::string ans;
        while (columnNumber > 0) {
            --columnNumber;
            ans += columnNumber % 26 + 'A';
            columnNumber /= 26;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```

## 借位

10 进制转换 26 进制，当除数是 26 的倍数时，余数为 0，不在范围 [1, 26] 中，因此应该向高位借位，并使得余数强行为 26。

因为 ai 的范围是 [1,26]，所以叠加的 64，即 'A' 的前一位。

**复杂度分析：**

- 时间复杂度：$O(\log_{26}columnNumber)$
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    string convertToTitle(int columnNumber) {
        std::string ans;
        while (columnNumber > 0) {
            int remainder = columnNumber % 26;
            if(remainder==0)//如果余数是0，就像上一位借个1（26）出来，让余数强行等于26
            {
                remainder = 26;
                columnNumber -= 26;
            }
            ans.push_back(remainder+ 64);
            columnNumber /= 26;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```



# 实现 Trie (前缀树)

- [链接](https://leetcode-cn.com/problems/implement-trie-prefix-tree/)
- [code](../cc/str/str.h)

> Trie（发音类似 "try"）或者说前缀树是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补完和拼写检查。
>
> 请你实现 Trie 类：
>
> - Trie() 初始化前缀树对象。
> - void insert(String word) 向前缀树中插入字符串 word。
> - boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false。
> - boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true；否则，返回 false。

## 前缀树

详见[题解](https://leetcode-cn.com/problems/implement-trie-prefix-tree/solution/shi-xian-trie-qian-zhui-shu-by-leetcode-ti500/)

**复杂度分析：**

- 时间复杂度：初始化时间 $O(1)$，其余操作为 $O(|S|)$，|S| 是要操作的字符串的长度。
- 空间复杂度：$O(|T| \cdot k)$，k 为字符集大小，此处为 26。

```c++
class Trie {
public:
    Trie() : children(26, nullptr), isEnd(false) {

    }
    
    void insert(string word) {
        Trie *cur = this;
        for (char ch : word) {
            ch -= 'a';
            if (cur->children[ch] == nullptr) {
                cur->children[ch] = new Trie();
            }
            cur = cur->children[ch];
        }
        cur->isEnd = true;
    }
    
    bool search(string word) {
        Trie *cur = searchPrefix(word);
        return cur != nullptr && cur->isEnd;
    }
    
    bool startsWith(string prefix) {
        return searchPrefix(prefix) != nullptr;
    }

private:
    vector<Trie *> children;
    bool isEnd;

    Trie* searchPrefix(string prefix) {
        Trie *cur = this;
        for (char ch : prefix) {
            ch -= 'a';
            if (cur->children[ch] == nullptr) {
                return nullptr;
            }
            cur = cur->children[ch];
        }
        return cur;
    }
};
```



# 最长回文串

- [链接](https://leetcode-cn.com/problems/longest-palindrome/)
- [code](../cc/str/str.h)

> 给定一个包含大写字母和小写字母的字符串 s，返回 通过这些字母构造成的最长的回文串。
>
> 在构造过程中，请注意区分大小写。比如 "Aa" 不能当做一个回文字符串。

## 数组统计

因为回文串是以中轴对称的，所以字符必然成对出现，可以统计字符的出现次数，并将次数除 2 之后加起来，所得的和即为最长的回文串长度。因为只包含大小写字母，所以可以构建一个大小为 52 的数组来统计每个字母的出现次数。最后考虑回文串长度是否小于字符串长度，若小于字符串长度，则可加入一个单一字符，即回文串长度加 1，否则保持长度不变。

**注意**： 利用整数除法性质，可以将数先除以 2 再乘以 2，得到成对的字符数量。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历字符串时间 $O(n)$，遍历统计数组时间 $O(k)$ ，其中 $k = 52$，即常数时间
- 空间复杂度：$O(k)$，统计数组所需空间，$k = 52$，常数大小空间

```c++
class Solution {
public:
    int longestPalindrome(string s) {
        int n = s.size();
        // std::vector<int> counts(52);
        int counts[52] = { 0 };
        for (char c : s) {
            if (c >= 'a' && c <= 'z') {
                ++counts[c - 'a' + 26];
            } else {
                ++counts[c - 'A'];
            }
        }
        int cnt = 0;
        for (int count : counts) {
            cnt += count / 2 * 2;
        }
        return cnt < n ? cnt + 1 : cnt;
    }
};
```

## 哈希表统计

利用哈希表统计字符出现次数，可以将空间降低到字符串中不重复的字符的数量大小。

**注意：** 当哈希表过大时，即字符串中不重复字符过多时，构建哈希表时间将成为瓶颈，本题不存在该情况。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历字符串时间 $O(n)$，遍历哈希表时间 $O(k)$，k 为字符串中不重复字符数量
- 空间复杂度：$O(k)$，哈希表所需空间，k 为字符串中不重复字符数量

```c++
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> counts;
        for (char c : s) {
            ++counts[c];
        }
        int cnt = 0;
        for (auto p : counts) {
            cnt += p.second / 2 * 2;
        }
        return cnt < s.size() ? cnt + 1 : cnt;
    }
};
```



# 两个列表的最小索引总和

- [链接](https://leetcode-cn.com/problems/minimum-index-sum-of-two-lists/)
- [code](../cc/str/str.h)

> 假设 Andy 和 Doris 想在晚餐时选择一家餐厅，并且他们都有一个表示最喜爱餐厅的列表，每个餐厅的名字用字符串表示。
>
> 你需要帮助他们用最少的索引和找出他们共同喜爱的餐厅。如果答案不止一个，则输出所有答案并且不考虑顺序。你可以假设答案总是存在。

## 暴力搜索

对于 list1 中每个元素寻找 list2 中是否存在相同元素，判断两者的索引和是否最小，有三种情况：

- 如果索引和比当前最小的索引和小，则更新索引和，将结果清空，添加当前元素到结果中
- 如果索引和等于当前最小的索引和，则添加元素到结果中
- 如果索引和大于当前最小的索引和，则不满足条件

**复杂度分析：**

- 时间复杂度：$O(nm)$，n 和 m 分别为 list1 和 list2 的长度，对于 list1 中每个元素都要遍历一遍 list2
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        vector<string> ans;
        int n = list1.size(), m = list2.size();
        int min_sum = INT_MAX;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (list1[i] == list2[j]) {
                    int sum = i + j;
                    if (sum == min_sum) {
                        ans.emplace_back(list1[i]);
                    } else if (sum < min_sum) {
                        min_sum = sum;
                        if (!ans.empty()) {
                            ans.clear();
                        }
                        ans.emplace_back(list1[i]);
                    }
                }
            }
        }
        return ans;
    }
};
```

## 哈希表

先遍历 list1，将其元素和索引作为键值对添加到哈希表中，再遍历 list2，查找元素是否存在哈希表中。可以对较小的 list 建立哈希表，以优化空间。

**复杂度分析：**

- 时间复杂度：$O(n+m)$，构建哈希表时间 $O(\min(n,m))$，遍历另一列表时间 $O(\max(n,m))$，哈希表查找操作时间 $O(1)$
- 空间复杂度：$O(\min(n,m))$，对较小的列表构建哈希表所需空间

```c++
class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        if (list1.size() > list2.size()) {
            return findRestaurant(list2, list1);
        }
        int n = list1.size(), m = list2.size();
        unordered_map<string, int> map;
        int min_sum = INT_MAX;
        for (int i = 0; i < n; ++i) {
            map[list1[i]] = i;
        }
        vector<string> ans;
        for (int j = 0; j < m; ++j) {
            if (map.count(list2[j])) {
                int sum = map[list2[j]] + j;
                if (sum < min_sum) {
                    min_sum = sum;
                    if (!ans.empty()) {
                        ans.clear();
                    }
                    ans.emplace_back(list2[j]);
                } else if (sum == min_sum) {
                    ans.emplace_back(list2[j]);
                }
            }
        }
        return ans;
    }
};
```



# 词典中最长的单词

- [链接](https://leetcode-cn.com/problems/longest-word-in-dictionary/)
- [code](../cc/str/str.h)

> 给出一个字符串数组 words 组成的一本英语词典。返回 words 中最长的一个单词，该单词是由 words 词典中其他单词逐步添加一个字母组成。
>
> 若其中有多个可行的答案，则返回答案中字典序最小的单词。若无答案，则返回空字符串。

## 排序+哈希集

题目要求返回数组 words 中最长符合要求的单词，若有多个则返回字典序最小的。可以按长度升序排序，对相同长度的按字典序降序排序。然后遍历排序后的数组，用哈希集合存储符号要求的单词，即对每个单词判断去掉最后一个单词的前缀是否存在哈希集合中，如果存在则说明符号要求，将单词添加至集合中，并更新当前单词为答案。遍历结束后即可得到符号要求的答案。

**复杂度分析：**

- 时间复杂度：$O(\sum_{0 \le i < n} l_i \times \log n)$，n 是数组长度，$l_i$ 是 words[i] 的长度，对数组排序时间 $O(\sum_{0 \le i < n} l_i \times \log n)$，遍历排序后的数组将单词加入到哈希集合时间 $O(\sum_{0 \le i < n} l_i)$
- 空间复杂度：$O(\sum_{0 \le i < n} l_i)$，排序空间 $O(\log n)$，哈希集合空间 $O(\sum_{0 \le i < n} l_i)$

```c++
class Solution {
public:
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end(), [](const string &a, const string &b) {
            if (a.size() != b.size()) {
                return a.size() < b.size();
            } else {
                return a > b;
            }
        });
        string longest = "";
        unordered_set<string> set;
        set.emplace("");
        for (auto &word : words) {
            if (set.count(word.substr(0, word.size() - 1))) {
                set.emplace(word);
                longest = word;
            }
        }
        return longest;
    }
};
```

## 字典树

详见[题解](https://leetcode-cn.com/problems/longest-word-in-dictionary/solution/ci-dian-zhong-zui-chang-de-dan-ci-by-lee-k5gj/)

```c++

class Trie {
public:
    Trie() {
        this->children = vector<Trie *>(26, nullptr);
        this->isEnd = false;
    }
    
    bool insert(const string & word) {
        Trie * node = this;
        for (const auto & ch : word) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new Trie();
            }
            node = node->children[index];
        }
        node->isEnd = true;
        return true;
    }

    bool search(const string & word) {
        Trie * node = this;
        for (const auto & ch : word) {
            int index = ch - 'a';
            if (node->children[index] == nullptr || !node->children[index]->isEnd) {
                return false;
            }
            node = node->children[index];
        }
        return node != nullptr && node->isEnd;
    }
private:
    vector<Trie *> children;
    bool isEnd;
};


class Solution {
public:
    string longestWord(vector<string>& words) {
        Trie trie;
        for (const string &word : words) {
            trie.insert(word);
        }
        string longest = "";
        for (const string &word : words) {
            if (trie.search(word)) {
                if (word.size() > longest.size() || (word.size() == longest.size() && word < longest)) {
                    longest = word;
                }
            }
        }
        return longest;
    }
};
```





# 查找共用字符

- [链接](https://leetcode-cn.com/problems/find-common-characters/)
- [code](../cc/str/str.h)

>给你一个字符串数组 words，请你找出所有在 words 的每个字符串中都出现的共用字符（ 包括重复字符），并以数组形式返回。你可以按任意顺序返回答案。

## 统计

根据题意，只需要统计 26 个字母在每个字符串的出现次数，并找出每个字母的最小出现次数，加入到结果中即可。

**复杂度分析：**

- 时间复杂度：$O(n(m+k))$，n 是字符串数组的长度，m 是字符串的平均长度，k 是字符集大小，本题中 k 是小写字母数量，即 26，遍历字符串数组时间 $O(n)$，遍历字符串平均时间 $O(m)$，寻找字母最小出现次数时间 $O(k)$，遍历全部字符串并统计字母最小出现次数时间 $O(n(m+k))$，
- 空间复杂度：$O(k)$，存储每个字母出现次数空间 $O(k)$，存储字母最小出现次数空间 $O(k)$

```c++
class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        int n = words.size();
        vector<int> min_freq(26, INT_MAX);
        vector<int> freq(26);
        for (const string &word : words) {
            fill(freq.begin(), freq.end(), 0);
            for (char c : word) {
                ++freq[c - 'a'];
            }
            for (int i = 0; i < 26; ++i) {
                min_freq[i] = min(min_freq[i], freq[i]);
            }
        }
        vector<string> ans;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < min_freq[i]; ++j) {
                ans.emplace_back(string(1, 'a' + i));
            }
        }
        return ans;
    }
};
```



# 气球的最大数量

- [链接](https://leetcode-cn.com/problems/maximum-number-of-balloons/)
- [code](../cc/str/str.h)

> 给你一个字符串 text，你需要使用 text 中的字母来拼凑尽可能多的单词 balloon（气球）。
>
> 字符串 text 中的每个字母最多只能被使用一次。请你返回最多可以拼凑出多少个单词 balloon。

## 统计

"balloon" 由一个 'b'，'a', 'n' 和两个 'l'，'o' 组成，统计text中构成 "balloon" 单词的字母，然后再找出统计中最小的数。注意的是 'l' 和 'n' 的统计数量需要除以 2。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历字符串时间 $O(n)$，遍历统计时间 $O(C)$，C 为单词中字符种类数量，本题 $C=5$。总体时间：$O(n+C) = O(n)$
- 空间复杂度：$O(1)$，统计单词字符的种类空间

```c++
class Solution {
public:
    int maxNumberOfBalloons(string text) {
        int counts[5] = { 0 };
        for (char c : text) {
            switch (c) {
                case 'b': counts[0] += 2; break;
                case 'a': counts[1] += 2; break;
                case 'l': counts[2] += 1; break;
                case 'o': counts[3] += 1; break;
                case 'n': counts[4] += 2; break;
                default: break;
            }
        }
        int m = INT_MAX;
        for (int count : counts) {
            if (count < m) {
                m = count;
            }
        }
        return m / 2;
    }
};
```



# 连续字符

- [链接](https://leetcode-cn.com/problems/consecutive-characters/)
- [code](../cc/str/str.h)

> 给你一个字符串 s，字符串的「能量」定义为：只包含一种字符的最长非空子字符串的长度。
>
> 请你返回字符串的能量。

## 双指针

遍历字符串，用双指针指示字符串中相邻的字符，所两个指针所指的字符相等则计数加 1，否则计数重置为 1，指针右移。同时记录最大的计数，即能量。

优化：更新最大值只发生在相邻字符相等的情况

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历字符串所需时间
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int maxPower(string s) {
        int n = s.size();
        int m = 1, c = 1;
        for (int i = 1; i < n; ++i) {
            if (s[i] == s[i - 1]) {
                ++c;
                if (c > m) {
                    m = c;
                }
            } else {
                c = 1;
            }
        }
        return m;
    }
};
```

# 字符串中第二大的数字

- [链接](https://leetcode-cn.com/problems/second-largest-digit-in-a-string/)
- [code](../cc/str/str.h)

> 给你一个混合字符串 s，请你返回 s 中第二大的数字，如果不存在第二大的数字，请你返回 -1。
>
> 混合字符串由小写英文字母和数字组成。

**注：** 与数组题 [414. 第三大的数](array.md) 类似

## 有限变量遍历

使用变量 `a`，`b` 记录字符串中最大和次大的数字，遍历数组，更新变量，需要跳过不是数字的字符。

优化：可以使用 -1 作为初值，无需特殊考虑不存在的情况

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历字符串所需时间
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int secondHighest(string s) {
        int a = -1, b = -1;
        for (char c : s) {
            if (c <= '9') {
                int num = c - '0';
                if (num > a) {
                    b = a;
                    a = num;
                } else if (a > num && num > b) {
                    b = num;
                }
            }
        }
        return b;
    }
};
```

## 有序集合

维护一个大小为 2 的有序集合，遍历字符串，将数字字符插入集合，集合大小超过 2 时，删除集合中最小的数字。

**注：** 虽然插入、删除操作理论时间 O(1)，但实际时间远超，足以影响整体时间

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历字符串时间 $O(n)$，常数大小集合插入、删除操作时间 $O(1)$
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int secondHighest(string s) {
        set<int> set;
        for (char c : s) {
            if (c <= '9') {
                set.insert(c - '0');
                if (set.size() > 2) {
                    set.erase(set.begin());
                }
            }
        }
        return set.size() == 2 ? *set.begin() : -1;
    }
};
```

## 排序

先遍历数组，删除非数字的字符。再对字符串按从大到小排序，获取第二大的数字。

**复杂度分析：**

- 时间复杂度：$O(n\log n)$，最差情况全数字字符串，遍历一遍 $O(n)$，排序 $O(n \log n)$，找出第二大数字 $O(1)$
- 空间复杂度：$O(n)$，最差情况下，存储数字字符串所需空间

```c++
class Solution {
public:
    int secondHighest(string s) {
        string s_num;
        for (char c : s) {
            if (c <= '9') {
                s_num += c;
            }
        }
        sort(s_num.begin(), s_num.end(), greater<>());
        int n = s_num.size();
        for (int i = 1; i < n; ++i) {
            if (s_num[i] != s_num[i - 1]) {
                return s_num[i] - '0';
            }
        }
        return -1;
    }
};
```



# 蜡烛之间的盘子

- [链接](https://leetcode-cn.com/problems/plates-between-candles/)
- [code](../cc/str/str.h)

> 给你一个长桌子，桌子上盘子和蜡烛排成一列。给你一个下标从 0 开始的字符串 s，它只包含字符 '*' 和 '|'，其中 '*' 表示一个盘子，'|' 表示一支蜡烛。
>
> 同时给你一个下标从 0 开始的二维整数数组 queries，其中 queries[i] = [lefti, righti] 表示子字符串 s[lefti...righti]（包含左右端点的字符）。
>
> 你需要找到子字符串中在两支蜡烛之间的盘子的数目 。如果一个盘子在子字符串中左边和右边都至少有一支蜡烛，那么这个盘子满足在两支蜡烛之间。
>
> - 比方说，s = "||\*\*||\*\*|\*"，查询 [3, 8]，表示的是子字符串 "\*||\*\*|" 。子字符串中在两支蜡烛之间的盘子数目为 2，子字符串中右边两个盘子在它们左边和右边都至少有一支蜡烛。
>
> 请你返回一个整数数组 answer，其中 answer[i] 是第 i 个查询的答案。

## 前缀和

对于每个查询，需要找到最给定区间内最左侧和最右侧的两个蜡烛，这样两个蜡烛之间的所有盘子都是符合条件的。

对于寻找蜡烛，可以预处理区间内每个位置左侧的第一个蜡烛和右侧的第一个蜡烛。这样区间左端点 $left_i$ 右侧的第一个蜡烛即为区间内最左侧的蜡烛，区间右端点 $right_i$ 左侧的第一个蜡烛即为区间内最右侧的蜡烛。

对于计算盘子数量，可以计算盘子数量的前缀和 presum。假设找到的两蜡烛位置分别为 x 和 y，那么两位置之间的盘子数量即为 $presum_y - presum_{x-1}$。

实际处理中，某个位置的左侧或者右侧可能没有蜡烛，此时将其记为 -1，当 `x == -1` 或 `y == -1` 或 `x >= y` 时，不存在满足的盘子，同时注意到，x 的位置是蜡烛，所以 `presum[x] == presum[x-1]`，可以用 `presum[x]` 代替 `presum[x-1]` 来避免 x 为 0 时的数组越界。

**复杂度分析：**

- 时间复杂度：$O(n+q)$，n 为字符串长度，需要遍历字符串进行预处理，计算前缀和时间 $O(n)$，寻找蜡烛的位置时间 $O(n)$，q 为查询数组长度，对于每对查询，计算盘子数量时间 $O(1)$，总时间 $O(2n+q)$
- 空间复杂度：$O(n)$，记录前缀和空间 $O(n)$，记录蜡烛位置空间 $O(n)$，总空间 $O(n)$

```c++
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = s.length();
        vector<int> presum(n);
        for (int i = 0, sum = 0; i < n; ++i) {
            if (s[i] == '*') {
                ++sum;
            }
            presum[i] = sum;
        }
        vector<int> left(n), right(n);
        for (int i = 0, l = -1, r = -1; i < n; ++i) {
            if (s[i] == '|') {
                l = i;
            }
            left[i] = l;
            int j = n - 1 - i;
            if (s[j] == '|') {
                r = j;
            }
            right[j] = r;
        }
		vector<int> ans;
        for (auto &query : queries) {
            int x = right[query[0]]; // 区间内最左侧的蜡烛
            int y = left[query[1]];  // 区间内最右侧的蜡烛
            ans.emplace_back(x == -1 || y == -1 || x >= y ? 0 : presum[y] - presum[x]);
        }
        return ans;
    }
};
```

## 实时计算

对于每个 query，找出左右端点所表示的子字符串的左侧蜡烛和右侧蜡烛的位置，并统计蜡烛之间盘子数量。

**注意：** 该解答超出**力扣**时间限制，经过测试，在超长字符串与大量查询情况下，与前缀和方法时间至少相差大概上百倍。

**复杂度分析：**

- 时间复杂度：$O(qm)$，遍历 q 对 query 时间 $O(q)$，每对 query 的端点平均差为 m，统计子字符串的蜡烛数量时间 $O(m)$，总时间 $O(qm)$
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        vector<int> ans;
        for (vector<int>& query : queries)    {
            int start = query[0];
            int end = query[1];
            int count = 0;
            while (start <= end && s[start] != '|') {
                ++start;
            }
            while (start <= end && s[end] != '|') {
                --end;
            }
            for (int i = start; i <= end; ++i) {
                if (s[i] == '*') {
                    ++count;
                }
            }
            ans.emplace_back(count);
        }
        return ans;
    }
};
```
