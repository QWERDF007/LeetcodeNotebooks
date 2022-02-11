| :tiger:                                             | :cat:                         | :dog:                                | :dragon:                    |
| --------------------------------------------------- | ----------------------------- | ------------------------------------ | --------------------------- |
| 13. [罗马数字转整数](#罗马数字转整数)               | 67. [二进制求和](#二进制求和) | 168. [Excel表列名称](#Excel表列名称) | 1446. [连续字符](#连续字符) |
| 1796. [字符串中第二大的数字](#字符串中第二大的数字) |                               |                                      |                             |



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

