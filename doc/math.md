| :tiger:                  | :cat:                | :dog: | :dragon: |
| ------------------------ | -------------------- | ----- | -------- |
| 7. [整数反转](#整数反转) | 9. [回文数](#回文数) |       |          |



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

