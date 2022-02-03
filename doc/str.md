| :tiger:                               | :cat: | :dog: | :dragon: | :snake: |
| ------------------------------------- | ----- | ----- | -------- | ------- |
| 13. [罗马数字转整数](#罗马数字转整数) |       |       |          |         |



# 罗马数字转整数

- [链接](https://leetcode-cn.com/problems/roman-to-integer/)
- [code](../cc/str/str.cpp#L39-L218)

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

- 时间复杂度：O(n)，遍历字符串
- 空间复杂度：O(1)

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

- 时间复杂度：O(n)，构建动态数组时间 O(n)，遍历字符串 O(n)
- 空间复杂度：O(n)，构建动态数组空间

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

注：如果在方法内构建哈希表，构建哈希表的时间将严重影响转换时间。

**复杂度分析：**

- 时间复杂度：O(n)，构建哈希表时间 O(1)，遍历字符串时间 O(n)
- 空间复杂度：O(1)，哈希表所需空间，题目中罗马字符数固定为 7

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

