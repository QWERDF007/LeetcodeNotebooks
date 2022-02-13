| :tiger:                      | :cat: | :dog: | :dragon: |
| ---------------------------- | ----- | ----- | -------- |
| 191. [位1的个数](#位1的个数) |       |       |          |



# 位1的个数

- [链接](https://leetcode-cn.com/problems/number-of-1-bits/)
- [code](../cc/bitwise_operation/bitwise_operation.h)

> 编写一个函数，输入是一个无符号整数（以二进制串的形式），返回其二进制表达式中数字位数为 '1' 的个数（也被称为汉明重量）。

## 右移

将 n 与 2^i 进行与运算，当第 i 位为 1 时，运算结果不为 0。通过右移来实现第 i 位的比较。

**复杂度分析：**

- 时间复杂度：$O(n)$，n 为最高位 1 的位置
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        while (n > 0) {
            if (n & 1) {
                ++cnt;
            }
            n = n >> 1;
        }
        return cnt;
    }
};
```

## 左移

将 n 与 2^i 进行与运算，当第 i 位为 1 时，运算结果不为 0。通过左移来实现第 i 位的比较。

**注意：** 用 32 位数左移可能会溢出

**复杂度分析：**

- 时间复杂度：$O(n)$，n 为最高位 1 的位置
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        uint64_t i = 1;
        while (i <= n) {
            if (n & i) {
                ++cnt;
            }
            i = i << 1;
        }
        return cnt;
    }
};
```

## N-1

观察运算：`n & (n - 1)`，其运算结果恰为把 n 的二进制中的最低位 1变为 0 之后的结果。例如，`6 & (6 - 1) = 4`，`6 = 0b110`，`4 = 0b100`。利用这个性质可以加速检查过程，不断让 n 与 n - 1 做与运算，直到 n 变为 0，运算次数就等于 n 的二进制中 1 的个数。

**复杂度分析：**

- 时间复杂度：$O(n)$，n 为二进制中 1 的个数
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        while (n) {
            ++cnt;
            n &= n - 1;
        }
        return cnt;
    }
};
```

