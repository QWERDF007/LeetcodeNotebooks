| :tiger:                  | :cat:                                                 | :dog:                          | :dragon: | :snake: |
| ------------------------ | ----------------------------------------------------- | ------------------------------ | -------- | ------- |
| 1. [两数之和](#两数之和) | 26. [删除有序数组中的重复项](#删除有序数组中的重复项) | 268. [丢失的数字](#丢失的数字) |          |         |



# 两数之和

- [链接](https://leetcode-cn.com/problems/two-sum/)
- [code](../cc/array/array.cpp#L23-L90)


> 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
>
> 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
>
> 你可以按任意顺序返回答案。

## 暴力求解

遍历数组中的每个数 `x`，寻找数组中是否存在 `y = target - x`，使 `x + y = target`。需要注意遍历过程中 `x` 之前的元素都和 `x` 匹配过，且每个元素不能出现两次，所以只需要在 `x` 之后的元素寻找 `y`。

**复杂度分析**：

- 时间复杂度：$O(n^2)$。最坏情况下数组中任意两个数都要被匹配一次
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};
    }
};
```

## 哈希表

构建哈希表，对每个 `x`，将寻找 `y = target - x` 的时间从 $O(N)$ 降到 $O(1)$。以数组的 `value` 和 `index` 作为键值对构建哈希表，对于每个 `x`，首先查询哈希表中是否存在 `y = target - x`，如果存在则直接返回 `x` 和 `y` 的索引，否则将 `x` 插入到哈希表。

**复杂度分析：**

- 时间复杂度：$O(n)$。最坏情况下遍历整个数组，建立哈希表。对每个 `x`， $O(1)$ 时间查询 `y = target - x` 
- 空间复杂度：$O(n)$

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};
```

# 删除有序数组中的重复项

- [链接](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/)
- [code](../cc/array/array.cpp#L93-L170)

>给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。
>
>不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

## 暴力求解

遍历数组，每次遇到重复项时，将数组从重复的地方整体向前移动，且数组长度减去 1。**(leetcode测试超时)**

**复杂度分析：**

- 时间复杂度：$O(n^2)$。除第一和最后一个数外，都要移动数组当前位置之后元素
- 空间复杂度：$O(1)$。

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        int i = 1;
        while (i < n) {
            if (nums[i] == nums[i - 1]) {
                int j = i + 1;
                while (j < n) {
                    nums[j - 1] = nums[j];
                    ++j;
                }
                --n;
            }
            else {
                ++i;
            }
        }
        return n;
    }
};
```

## 双指针 (快慢指针)

用快慢指针来完成，指针初始位置为 1。将快指针 `fast` 依次遍历 1 到 n -1 的每个位置，遇到 `nums[fast] != nums[fast-1]`，说明 `nums[fast]` 和之前的元素都不同，使  `nums[slow] = nums[fast]`， `slow` 加 1。需要单独处理数组长度为 0 的情况。

**复杂度分析：**

- 时间复杂度：$O(n)$。只需遍历一次数组
- 空间复杂度：$O(1)$。两个指针所需空间与数组大小无关

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n==0) {
            return 0;
        }
        int slow = 1, fast = 1;
        while (fast < n) {
            if (nums[fast] !=  nums[fast - 1]) {
                nums[slow] = nums[fast];
                ++slow;
            }
            ++fast;
        }
        return slow;
    }
};
```

# 丢失的数字

- [链接]()
- [code](../cc/array/array.cpp#L172-L276)

> 给定一个包含 [0, n] 中 n 个数的数组 nums ，找出 [0, n] 这个范围内没有出现在数组中的那个数。

## 排序

将数组排序后，遍历数组，即可根据数组元素是否和下标相等，得出丢失的数字。

**复杂度分析：**

- 时间复杂度：$O(nlogn)$，排序时间复杂度 $O(nlogn)$，遍历数组 $O(n)$
- 空间复杂度：$O(logn)$，排序递归调用栈空间

```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] != i) {
                return i;
            }
        }
        return n;
    }
};
```

## 哈希集合

遍历数组，将数组中每个元素加入到哈希集合，然后依次检查从 0 到 n 的每个数是否在哈希集合中。

**复杂度分析：**

- 时间复杂度：$O(n)$，添加数组元素到哈希集合时间 $O(n)$，检查每个数是否存在时间 $O(n)$。**实际测试下来时间远超过排序方法所需 $O(nlogn)$**
- 空间复杂度：$O(n)$，哈希集合需要存储 n 个数组元素

```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        unordered_set<int> set;
        int n = nums.size();
        for (int& num : nums) {
            set.insert(num);
        }
        for (int i = 0; i < n; ++i) {
            if (!set.count(i)) {
                return i;
            }
        }
        return n;
    }
};
```

## 位运算

按位异或运算。对于任意整数 x，都有 x 异或 x 等于 0，x 异或 0 等于 x 本身，且按位异或运算满足交换律和结合律。设结果初值为 0，将 n 个数组元素与结果异或，再将 0 到 n 个数与结果异或，共有 2n + 1 个数，根据数组元素出现的奇偶，即可得到丢失的数字。

**复杂度分析：**

- 时间复杂度：$O(n)$，需要遍历 2n + 1 个数
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int ret = 0;
        for (int i = 0; i <= n; ++i) {
            ret ^= i;
        }
        for (int i = 0; i < n; ++i) {
            ret ^= nums[i];
        }
        return ret;
    }
};
```

## 数学

等差数列求和。按公式得到 n+1 个数的总和，再减去 n 个数组元素的总和，即可得到丢失的数。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历 n 个数组元素
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int total = (n + 1) * n / 2, sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
        }
        return total - sum;
    }
};
```

