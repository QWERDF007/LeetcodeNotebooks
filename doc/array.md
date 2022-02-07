| :tiger:                  | :cat:                                                 | :dog:                          | :dragon:                                             | :snake:                                |
| ------------------------ | ----------------------------------------------------- | ------------------------------ | ---------------------------------------------------- | -------------------------------------- |
| 1. [两数之和](#两数之和) | 26. [删除有序数组中的重复项](#删除有序数组中的重复项) | 268. [丢失的数字](#丢失的数字) | 303. [区域和检索-数组不可变](#区域和检索-数组不可变) | 349. [两个数组的交集](#两个数组的交集) |



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

# 区域和检索-数组不可变

- [链接](https://leetcode-cn.com/problems/range-sum-query-immutable/)
- [code](../cc/array/array.cpp#L279-L340)

> 给定一个整数数组 nums，处理以下类型的多个查询：
>
> 实现 NumArray 类：
>
> - NumArray(vector<int>& nums) 使用数组 nums 初始化对象
> - int sumRange(int i, int j)  返回数组 nums 中索引 left 和 right 之间的元素的总和 ，包含 left 和 right 两点

## 实时计算

把数组保存下来，每次调用 `sumRange` 时计算索引从 `i` 到 `j` 的元素的总和。**(超出题目时间限制)**

**复杂度分析：**

- 时间复杂度：保存数组时间 $O(n)$，每次求和时间 $O(j-i+1)$
- 空间复杂度：$O(n)$，保存数组所需空间

```c++
class NumArray {
public:
    NumArray(vector<int>& nums) : nums_(nums) {
    }
    
    int sumRange(int left, int right) {
        int sum = 0;
        for (int i = left; i <= right; ++i) {
            sum += nums_[i];
        }
        return sum;
    }
    vector<int> nums_;
};
```

## 前缀和

前缀和，利用积分的可加性来实现求和。对于任意 0 <= i <= j，`sumRange(i, j) = sumRange(0, j) - sumRange(0,i-1)`。具体实现时，将前缀和的数组 sums 的长度设为 n + 1，则可以不对 i = 0 的情况进行特殊处理，即用位置 k 的元素存储 sumRange(0, k - 1)。

**复杂度分析：**

- 时间复杂度：$O(n)$，初始化计算前缀和数组时间 $O(n)$，每次求和时间 $O(1)$
- 空间复杂度：$O(n)$

```c++
class NumArray {
public:
    NumArray(vector<int>& nums)  {
        int n = nums.size();
        sums_.resize(n+1);
        for (int i = 0; i < n; ++i) {
            sums_[i+1] = sums_[i] + nums[i];
        }
    }
    
    int sumRange(int left, int right) {
        return sums_[right+1] - sums_[left];
    }
    vector<int> sums_;
};
```

# 两个数组的交集

- [链接](https://leetcode-cn.com/problems/intersection-of-two-arrays/)
- [code](../cc/array/array.cpp#L343-L419)

> 给定两个数组 nums1 和 nums2 ，返回它们的交集。输出结果中的每个元素一定是唯一的。我们可以不考虑输出结果的顺序。

## 哈希集合

将其中一个数组添加至哈希集合中，再遍历另一个数组，查询数组元素是否在集合中。

优化：将第二个数组添加至哈希集合时，可以直接判断是否在第一个集合中，只将交集部分加入第二个集合，将第二个集合作为结果。

**注：**虽然哈希集合理论时间复杂度低于排序方法，但实际时间超过排序，随着两个数组中元素的重复数量增加，两者性能接近。

**复杂度分析：**

- 时间复杂度：$O(n+m)$，添加到集合所需时间 $O(n)$ 和 $O(m)$，遍历查询另一数组是否在集合中所需时间 $O(m)$ 或 $O(n)$，
- 空间复杂度：$O(n)$，哈希集合所需空间 

```c++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set1(nums1.begin(), nums1.end());
        unordered_set<int> set2;
        for (int num : nums2) {
            if (set1.find(num) != set1.end()) {
                set2.insert(num);
            }
        }
        return vector<int>(set2.begin(), set2.end());
    }
};
```

## 排序

将两个数组排序，然后再分别用两个指针遍历两个数组，再额外记录上次添加的元素，以确保结果的唯一性。

**复杂度分析：**

- 时间复杂度：$O(n \log n + m \log m)$，排序两个数组所需时间分别为 $O(n \log n)$ 和 $O(m \log m)$，遍历两个数组所需时间为 $O(n+m)$
- 空间复杂度：$O(\log n + \log m)$，两个数组排序所用的空间

```c++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int> ans;
        int i = 0, j = 0;
        int n = nums1.size(), m = nums2.size();
        while (i < n && j < m) {
            int num1 = nums1[i], num2 = nums2[j];
            if (num1 == num2) {
                // 保证唯一性
                if (!ans.size() || num1 != ans.back()) {
                    ans.emplace_back(num1);
                }
                ++i;
                ++j;
            } else if (num1 < num2) {
                ++i;
            } else {
                ++j;
            }
        }
        return ans;
    }
};
```

