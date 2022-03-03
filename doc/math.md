| :tiger:                    | :cat:                | :dog:                       | :dragon:               |
| -------------------------- | -------------------- | --------------------------- | ---------------------- |
| 7. [整数反转](#整数反转)   | 9. [回文数](#回文数) | 69. [x的平方根](#x的平方根) | 202. [快乐数](#快乐数) |
| 258. [各位相加](#各位相加) |                      | 537. [复数乘法](#复数乘法)  |                        |



# 回文数

- [链接](https://leetcode-cn.com/problems/palindrome-number/)
- [code](../cc/math/leetcode_math.h)

> 给你一个整数 x，如果 x 是一个回文整数，返回 true；否则，返回 false。
>
> 回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。例如，121 是回文，而 123 不是。

## 转字符串+双指针

将数字转换为字符串，然后用双指针逐位比较两头。若数字是负数，或者个位是 0 都不可能是回文数。

**注意：** 时间复杂度不知道怎么算，若按数字的位数则为 n，则转字符串时间为 $O(n)$，空间为 $O(n)$，遍历比较两头时间为 $O(n)$，若以数字大小为 n，则转换字符串时间 $O(\log n)$，遍历比较两头时间 $O(\log n)$，因为每次遍历都相当于数字除以 10，所以复杂度跟 $\log n$ 有关，以 100 为底？

**复杂度分析：**

- 时间复杂度：$O(n)$，数字转字符 $O(n)$，遍历比较字符串两头 $O(n)$
- 空间复杂度：$O(n)$

```c++
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        string s = to_string(x);
        int left = 0, right = s.size() - 1;
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            ++left;
            --right;
        }
        return true;
    }
};
```

## 反转一半数字

反转数字的一半，将前半部分与后半部分比较。例如，对于数字 1221，可以将数字对 10 求余，得到最后一位数 1，然后将数字除以 10，移除最后一位数，得到 122，再将数字对 10 求余，得到倒数第二位数 2。把得到的最后一位数 1 乘 10，再加上得到倒数第二位数，得到反转后的数字 12。以此类推，可以得到更多的位数。由于整个过程不断将原始数字除以 10，将反转后的数字乘 10，所以当原始数字小于等于反转数字时，意味着处理了一半位数的数字，结束循环。奇数位数需要对反转数字除以 10，以去除处于中位的数字。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历数字时间，每次遍历数字除以 10，只需遍历一半，假设数字位数为 n
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        int reverted_number = 0;
        while (x > reverted_number) {
            reverted_number = reverted_number * 10 + x % 10;
            x /= 10;
        }
        return x == reverted_number || x == reverted_number / 10;
    }
};
```

## 双指针

用双指针获取两头数字，进行比较。先求出数字最大位数，然后分别获取两头的数字，进行对比。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历数字时间，每次数字除以 100
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        int div = 1;
        // 找出最大位数
        while (x / div >= 10) {
            div *= 10;
        }
        while (x > 0) {
            // 找出两头比较
            int left = x / div;
            int right = x % 10;
            if (left != right) {
                return false;
            }
            // 抹掉两头，准备下一次
            x = (x % div) / 10;
            // 抹掉了两位，除数除以100
            div /= 100;
        }
        return true;
    }
};
```

## 转字符串+反转字符串

将数字转换为字符串，然后将字符串反转后，比较两个字符串是否相等。

**复杂度分析**：

- 时间复杂度：$O(n)$，转换字符串时间 $O(n)$，反转字符串时间 $O(n)$，比较字符串时间 $O(n)$
- 空间复杂度：$O(n)$，数字转字符空间 $O(n)$，反转字符空间 $O(n)$

```c++
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        string s = to_string(x);
        string reversed_s = to_string(x);
        reverse(reversed_s.begin(), reversed_s.end());
        return s == reversed_s;
    }
};
```

# x的平方根

- [链接](https://leetcode-cn.com/problems/sqrtx/)
- [code](../cc/math/leetcode_math.h)

> 给你一个非负整数 x，计算并返回 x 的算术平方根。
>
> 由于返回类型是整数，结果只保留整数部分，小数部分将被舍去 。
>
> 注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。

## 暴力解法

由于只保留平方根的整数部分，所以可以遍历 `i * i` 直到大于 x。

**复杂度分析：**

- 时间复杂度：$O(x^{1/2})$，遍历到 x 的平方根时结束遍历
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int mySqrt(int x) {
        long long i = 1;
        while (i * i <= x) {
            ++i;
        }
        return i - 1;
    }
};
```

## 二分查找

x 的平方根的整数部分是满足 `k * k <= x` 的最大 k 值，可以对 k 进行二分查找，得到答案。

复杂度分析：

- 时间复杂度：$O(\log x)$，二分查找所需时间
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int mySqrt(int x) {
        int left = 0, right = x, k = -1;
        while (left <= right) {
            long mid = left + (right - left) / 2;
            if (mid * mid <= x) {
                k = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return k;
    }
};
```

## 牛顿迭代

牛顿迭代法是一种快速求解函数零点的方法。用 $C$ 表示待求平方根的数，显然 $C$ 的平方根就是函数
$$
y = f(x) = x^2 - C
$$
的零点。

牛顿迭代法的本质是借助泰勒级数，从初始值开始快速向零点逼近。任取一个 $x_0$ 作为初始值，在每一步的迭代中，找到函数图像上的点 $(x_i, f(x_i))$，过该点做一条斜率为该点导数 $f'(x_i)$ 的直线，与横轴的交点记为 $x_{i+1}$。$x_{i+1}$ 相较于 $x_i$ 而言距离零点更近。在经过多次迭代后，就可以得到一个距离零点非常接近的交点。

选择 $x_0 = C$ 作为初始值。

每一步迭代中，通过当前的交点 $x_i$，找到函数图像上的点 $(x_i, x^2 - C)$，作一条斜率为 $f'(x_i) = 2x_i$ 的直线，直线方程为：
$$
\begin{align}
y &= 2x_i (x - x_i) + x_i^2 - C \\
  &= 2x_ix - (x_i^2 + C)
\end{align}
$$
与横轴交点为方程 $2x_ix - (x_i^2 + C) = 0$ 的解，即为新的迭代结果 $x_{i+1}$：
$$
x_{i+1} = \frac{1}{2} (x_i + \frac{C}{x_i})
$$
在进行 k 次迭代后，$x_k$ 的值与真实零点 $\sqrt{C}$ 足够接近，即可作为答案。

**注意：**

- 为什么选 $x_0 = C$ 作为初始值？若选取初始值较小，可能会迭代到 $-\sqrt{C}$ 这个零点，而希望找到的是 $\sqrt{C}$，因此选择 $x_0 = C$ 作为初始值，每次迭代均有 $x_{i+1} < x_i$，零点 $\sqrt{C}$ 在其左侧，所以一定会迭代到这个零点。
- 迭代何时结束？每次迭代后，都距离零点更进一步，所以当相邻两次迭代得到的交点**非常接近**时，可以断定结果足够得到答案了。一般来说，判断两次迭代结果的差值是否小于一个极小的非负数 $\epsilon$，一般取 $10^{-6}$ 或者 $10^{-7}$。

```c++
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }
        double C = x, x0 = x;
        while (true) {
            double xi = 0.5 * (x0 + C / x0);
            if (fabs(xi - x0) < 1e-6) {
                break;
            }
            x0 = xi;
        }
        return int(x0);
    }
};
```



## 数学替换

可以用指数和对数来代替平方根函数。将 $\sqrt{x}$ 写成形式 $x^{1/2}$，可以利用指数和对数的性质，得：
$$
\sqrt{x} = x^{1/2} = e^{\ln x^{1/2}} = e^{1/2 \ln x}
$$
即可得到平方根。

**注意：** 因为计算机无法存储浮点数的精确值，而指数和对数函数的参数和返回值均为浮点数，因此运算过程中会存在误差。例如 $x = 2147395600$ 时，$e^{1/2 \ln x}$ 的计算结果与正确值 46340 相差 $10^{-11}$，这样结果取整后，会得到46339 这个错误结果。因此在得到结果的整数部分 k 后，要找出 k 与 k+1 中哪个是真正的答案，即先判断 k+1 的平方是否大于 x。

```c++
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }
        int k = exp(0.5 * log(x));
        return (long long)(k + 1) * (k + 1) <= x ? k + 1 : k;
    }
};
```

# 快乐数

- [链接](https://leetcode-cn.com/problems/happy-number/)
- [code](../cc/math/leetcode_math.h)

> 编写一个算法来判断一个数 n 是不是快乐数。
>
> 「快乐数」定义为：
>
> - 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
> - 然后重复这个过程直到这个数变为 1，也可能是无限循环但始终变不到 1。
> - 如果这个过程结果为 1，那么这个数就是快乐数。
>
> 如果 n 是快乐数就返回 true；不是，则返回 false。

猜测会有以下三种可能：

1. 最终会得到 11。
2. 最终会进入循环。
3. 值会越来越大，最后接近无穷大。

| Digits | Largest       | Next |
| ------ | ------------- | ---- |
| 1      | 9             | 81   |
| 2      | 99            | 162  |
| 3      | 999           | 243  |
| 4      | 9999          | 324  |
| 13     | 9999999999999 | 1053 |

对于 3 位数的数字，它替换后的数字不大于 243，要么跌到 1，要么在 243 内循环。对于 4 或 4 位以上的数字在每一步都会丢失位数，直到降到 3 位数为止。所以可以排除第三种情况，不可能接近无穷大。

算法分为两部分：

1. 计算数字 n 的下一个数字
2. 判断是否进入了循环

## 哈希集合

使用哈希集合来检查当前数字是否存在，若当前数字为 1 或者存在于哈希集合中则返回结果，否则将数字加入集合中，并计算下一个数字，循环直到数字跌倒 1 或数字存在于集合中。

**复杂度分析：**

- 时间复杂度：$O(\log n)$
  - 查找给定数字的下一个值时间 $\log n$
  - 低于 243 的数字不可能回到 243 以上，因此用 243 一下最长的循环长度来代替 243，常数时间
  - 高于 243 的数字，最坏情况下时间 $O(\log n) + O(\log \log n) + O(\log \log \log n) \dots$，$O(\log n)$ 占主导地位
- 空间复杂度：$O(\log n)$，放入哈希集合的数字所需空间，可以优化至 $O(243 \cdot 3) = O(1)$

```c++
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> seen;
        while (n != 1 && !seen.count(n)) {
            seen.insert(n);
            n = getNext(n);
        }
        return n == 1;
    }

    int getNext(int n) {
        int sum = 0;
        while (n > 0) {
            int d = n % 10;
            sum += d * d;
            n /= 10;
        }
        return sum;
    }
};
```

## 快慢指针

可以将通过反复调用 `getNext(n)` 得到的链是一个隐式的链表。头节点是起始数字 n，next 是通过调用 `getNext(n)` 获得的数字，可以使用**Floyd判圈算法**来判断是否存在环，即两个奔跑选手，一个跑的慢的“乌龟”，一个跑的快的“兔子”，不管乌龟合兔子在循环哪里开始，它们最终会相遇，算法时间复杂度 $O(n+m)$。

具体实现时，维护两个数值，即乌龟和兔子，乌龟通过调用一次 `getNext(n)` 获得，兔子通过嵌套调用 `getNext(n)` 得到。

**复杂度分析：**

- 时间复杂度：$O(\log n)$
  - 没有循环，乌龟达到链表中的一半，兔子达到 1。最坏情况下时间 $O(2 \cdot \log n) = O(\log n)$
  - 在循环中，假设循环有 k 个数字，它们起点相隔 k-1 个位置（可以开始的最远距离），兔子 k-1 步后可以追上乌龟，主操作仍是计算数字的下一个值，时间  $O(\log n)$。
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    bool isHappy(int n) {
        int slow = n, fast = getNext(n);
        while (fast != 1 && slow != fast) {
            slow = getNext(slow);
            fast = getNext(getNext(fast));
        }
        return fast == 1;
    }

    int getNext(int n) {
        int sum = 0;
        while (n > 0) {
            int d = n % 10;
            sum += d * d;
            n /= 10;
        }
        return sum;
    }
};
```

## 数学

通过前面的分析，可以知道任意数字经过一系列的替换后，数字都低于 243，因此任何循环都必须包含小于 243 的数字，可以编写一个找到 243 以下所有周期的强力程序。最后发现只有一个循环：$4 \rightarrow 16 \rightarrow 37 \rightarrow 58 \rightarrow 89 \rightarrow 145 \rightarrow 20 \rightarrow 4$。其他数字要么在进入这个循环的链上，要么在进入 1 的链上。因此可以通过硬编码包含这些数字的哈希集合，如果达到其中任意一个数字，就可以判断是在循环中。

**复杂度分析：**

- 时间复杂度：$O(\log n)$，计算下一个数字的时间
- 空间复杂度：$O(1)$，固定大小哈希集空间

```c++
class Solution {
public:
    bool isHappy(int n) {
        while (n != 1 && !cycle_nums_.count(n)) {
            n = getNext(n);
        }
        return n == 1;
    }

    int getNext(int n) {
        int sum = 0;
        while (n > 0) {
            int d = n % 10;
            sum += d * d;
            n /= 10;
        }
        return sum;
    }
    std::unordered_set<int> cycle_nums_{ 4, 16, 37, 58, 89, 145, 42, 20 };
};
```



# 各位相加

- [链接](https://leetcode-cn.com/problems/add-digits/)
- [code](../cc/math/leetcode_math.h)

> 给定一个非负整数 num，反复将各个位上的数字相加，直到结果为一位数。返回这个结果。

## 递归

根据题意，可以递归的计算各位之和，然后再递归计算结果的各位之和。

**复杂度分析：**

- 时间复杂度：$O(\log n)$，每次计算各位之和时间 $O(\log n)$，由于 num < 2^31 - 1，因此一次计算最大可能结果为 82，对于任意两位数最多只需计算两次各位相加的结果即可得到一位数
- 空间复杂度：$O(\log n)$，递归空间

```c++
class Solution {
public:
    int addDigits(int num) {
        if (num / 10 == 0) {
            return num;
        }
        return addDigits(addDigits(num / 10) + num % 10);
    }
};
```

## 循环

循环计算每次各位相加，再计算结果的各位相加，两个循环即可。

**复杂度分析：**

- 时间复杂度：$O(\log n)$，分析同递归
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int addDigits(int num) {
        while (num / 10) {
            int sum = 0;
            while (num) {
                sum += num % 10;
                num /= 10;
            }
            num = sum;
        }
        return num;
    }
};
```

## 数学

根据定义，本题是在求数根，一个数的数根是它对9的余数。[数学证明](https://www.zhihu.com/question/30972581/answer/379865832)。

**复杂度分析：**

- 时间复杂度：$O(1)$
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int addDigits(int num) {
        return (num - 1) % 9  + 1;
    }
};
```



# 复数乘法

- [链接](https://leetcode-cn.com/problems/complex-number-multiplication/)
- [code](../cc/math/leetcode_math.h)

> 复数可以用字符串表示，遵循 "实部 + 虚部i" 的形式，并满足下述条件：
>
> - 实部是一个整数，取值范围是 [-100, 100]
> - 虚部也是一个整数，取值范围是 [-100, 100]
> - i^2 == -1
>
> 给你两个字符串表示的复数 num1 和 num2，请你遵循复数表示形式，返回表示它们乘积的字符串。

## 遍历

观察可得，题目复数的实部和虚部由字符 `+` 隔开，因此可以遍历字符串，获取复数的实部和虚部，再分别按数学计算即可得到结果。
$$
(a + bi) \times (c + di) = (ac - bd) + (ad + bc)i
$$
**复杂度分析：**

- 时间复杂度：$O(n+m)$，n 和 m 分别为两个字符串数字的长度
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    string complexNumberMultiply(string num1, string num2) {
        int a, b, c, d;
        int n = num1.size(), m = num2.size();
        for (int i = 0; i < n; ++i) {
            if (num1[i] == '+') {
                a = atoi(num1.substr(0, i).c_str());
                b = atoi(num1.substr(i+1, n-i-2).c_str());
                break;
            }
        }
        for (int i = 0; i < m; ++i) {
            if (num2[i] == '+') {
                c = atoi(num2.substr(0, i).c_str());
                d = atoi(num2.substr(i+1, m-i-2).c_str());
                break;
            }
        }
        return to_string((a*c - b*d)) + "+" + to_string(a*d + b*c) + "i";
    }
};
```

## 正则匹配

正则匹配字符串的 `+` 和 `i` 获取实部和虚部。

**复杂度分析：**

- 时间复杂度：$O(n+m)$，正则匹配时间
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    string complexNumberMultiply(string num1, string num2) {
        std::regex re("\\+|i");
        std::vector<std::string> complex1(
            std::sregex_token_iterator(num1.begin(), num1.end(), re, -1), std::sregex_token_iterator());
        std::vector<std::string> complex2(
            std::sregex_token_iterator(num2.begin(), num2.end(), re, -1), std::sregex_token_iterator());
        int real1 = std::stoi(complex1[0]);
        int imag1 = std::stoi(complex1[1]);
        int real2 = std::stoi(complex2[0]);
        int imag2 = std::stoi(complex2[1]);
        return std::to_string(real1 * real2 - imag1 * imag2) + "+" + std::to_string(real1 * imag2 + real2 * imag1) + "i";
    }
};
```

