| :tiger:                                                 | :cat:                                                        | :dog:                                              | :dragon:                                                   |
| ------------------------------------------------------- | ------------------------------------------------------------ | -------------------------------------------------- | ---------------------------------------------------------- |
| 1. [两数之和](#两数之和)                                | 26. [删除有序数组中的重复项](#删除有序数组中的重复项)        |                                                    |                                                            |
| 163. [缺失的区间](#缺失的区间)                          |                                                              |                                                    |                                                            |
| 268. [丢失的数字](#丢失的数字)                          | 303. [区域和检索-数组不可变](#区域和检索-数组不可变)         |                                                    |                                                            |
| 349. [两个数组的交集](#两个数组的交集)                  | 350. [两个数组的交集II](#两个数组的交集II)                   | 414. [第三大的数](#第三大的数)                     | 448. [找到所有数组中消失的数字](#找到所有数组中消失的数字) |
|                                                         | 453. [最小操作次数使数组元素相等](#最小操作次数使数组元素相等) | 540. [有序数组中的单一元素](#有序数组中的单一元素) | 717. [1比特与2比特字符](#1比特与2比特字符)                 |
|                                                         | 1380. [矩阵中的幸运数](#矩阵中的幸运数)                      | 1706. [球会落何处](#球会落何处)                    | 1984. [学生分数的最小差值](#学生分数的最小差值)            |
| 2016. [增量元素之间的最大差值](#增量元素之间的最大差值) |                                                              |                                                    |                                                            |



# 两数之和

- [链接](https://leetcode-cn.com/problems/two-sum/)
- [code](../cc/array/array.h)


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
- [code](../cc/array/array.h)

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

# 缺失的区间

- [链接](https://leetcode-cn.com/problems/missing-ranges/)
- [code](../cc/array/array.h)

> 给定一个排序的整数数组 nums，其中元素的范围在闭区间 [lower, upper] 当中，返回不包含在数组中的缺失区间。

## 双指针

- 使用双指针 `low`、`num`，遍历 `nums` 添加对应范围即可
- 需要先向 `nums` 尾部添加 `upper + 1`

```c++
class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> ans;
        int n = nums.size();
        // lower - 1 将缺失 [lower] 的情况统一处理
        long long prev = (long long)lower - 1;
        for (int i = 0; i < n; ++i) {
            int d = nums[i] - prev;
            if (d == 2) {
                ans.emplace_back(to_string(prev + 1));
            } else if (d > 2) {
                ans.emplace_back(to_string(prev + 1) + "->" + to_string(nums[i] - 1));
            }
            prev = nums[i];
        }
        if (upper - prev == 1) {
            ans.emplace_back(to_string(prev + 1));
        } else if (upper - prev > 1) {
            ans.emplace_back(to_string(prev + 1) + "->" + to_string(upper));
        }
        return ans;
    }
};
```



# 丢失的数字

- [链接]()
- [code](../cc/array/array.h)

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
- [code](../cc/array/array.h)

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
- [code](../cc/array/array.h)

> 给定两个数组 nums1 和 nums2 ，返回它们的交集。输出结果中的每个元素一定是唯一的。我们可以不考虑输出结果的顺序。

## 哈希集合

将其中一个数组添加至哈希集合中，再遍历另一个数组，查询数组元素是否在集合中。

优化：判断两个数组大小，以小的数组构建哈希表能够降低空间复杂度。

**注意：** 虽然哈希集合理论时间复杂度低于排序方法，但实际时间超过排序，随着两个数组中元素的重复数量增加，两者性能接近。

**复杂度分析：**

- 时间复杂度：$O(n+m)$，添加到哈希集合所需时间 $O(\min(n,m))$，遍历查询另一数组是否在集合中所需时间 $O(\max(n,m))$
- 空间复杂度：$O(\min(n,m))$，哈希集合所需空间 

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

## 排序+双指针

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



# 两个数组的交集II

- [链接](https://leetcode-cn.com/problems/intersection-of-two-arrays-ii/)
- [code](../cc/array/array.h)

> 给你两个整数数组 nums1 和 nums2 ，请你以数组形式返回两数组的交集。
>
> 返回结果中每个元素出现的次数，应与元素在两个数组中都出现的次数一致（如果出现次数不一致，则考虑取较小值）。
>
> 可以不考虑输出结果的顺序。

## 哈希表

遍历其中一个数组，以数组元素作为 key，元素出现次数作为 value 构建哈希表。遍历另一个数组，判断元素是否存在哈希表中，若元素存在哈希表中，则将元素加入结果数组，并减少哈希表中该元素的出现次数。

优化：判断两个数组大小，以小的数组构建哈希表能够降低空间复杂度

**复杂度分析：**

- 时间复杂度：$O(n+m)$，构建哈希表时间 $O(\min(n,m))$，遍历大数组时间 $O(\max(n,m))$
- 空间复杂度：$O(\min(n,m))$，构建哈希表所需空间

```c++
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return intersect(nums2, nums1);
        }
        unordered_map<int, int> map;
        for (int num : nums1) {
            ++map[num];
        }
        vector<int> ans;
        for (int num : nums2) {
            if (map.count(num) && map[num] > 0) {
                ans.emplace_back(num);
                --map[num];
            }
        }
        return ans;
    }
};
```

## 排序+双指针

将两个数组排序，然后再分别用两个指针遍历两个数组，遇到两个数组元素相等时，添加至结果数组中。

**复杂度分析：**

- 时间复杂度：$O(n\log n + m\log m)$，排序两个数组所需时间分别为 $O(n \log n)$ 和 $O(m \log m)$，遍历两个数组所需时间为 $O(n+m)$
- 空间复杂度：$O(\log n + \log m)$，两个数组排序所用的空间

```c++
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int i = 0, j = 0;
        int n = nums1.size(), m = nums2.size();
        vector<int> ans;
        while (i < n && j < m) {
            int num1 = nums1[i], num2 = nums2[j];
            if (num1 == num2) {
                ans.emplace_back(num1);
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



# 第三大的数

- [链接](https://leetcode-cn.com/problems/third-maximum-number/)
- [code](../cc/array/array.h)

> 给你一个非空数组，返回此数组中第三大的数。如果不存在，则返回数组中最大的数。

## 排序

将数组按从大到小排序，然后遍历获取第三大的数。遍历过程中返回第三大元素，遍历结束时返回最大的元素。

**注意：** 数组中可能存在重复元素，需要去重，可以在遍历的时候用一个记数指针来处理

**复杂度分析：**

- 时间复杂度：$O(n \log n)$，排序所需时间
- 空间复杂度：$O(\log n)$，排序所需空间

```c++
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<>());
        int n = nums.size();
        for (int i = 1, diff = 1; i < n; ++i) {
            if (nums[i] != nums[i-1] && ++diff == 3) {
                return nums[i];
            }
        }
        return nums[0];
    }
};
```

## 有序集合

维护一个大小为 3 的有序集合，遍历数组，将元素加入到集合，集合大小超过 3 时删除最小元素。

**注意：** 虽然插入、删除操作理论时间 O(1)，但实际时间远超

**复杂度分析：**

- 时间复杂度：$O(n)$，有序集合的大小至多为 3，插入、删除操作时间可视为 $O(1)$，遍历数组时间 $O(n)$
- 空间复杂度：$O(1)$，

```c++
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        std::set<int> set;
        for (int num : nums) {
            set.insert(num);
            if (set.size() > 3) {
                set.erase(set.begin());
            }
        }
        return set.size() == 3 ? *set.begin() : *set.rbegin();
    }
};
```

## 有限变量遍历

利用有限变量模拟有序集。使用变量 `a`，`b`，`c` 来维护数组中最大、次大和第三大的元素，遍历数组，更新变量。并使用超过 int 范围的最小值来指示没找到第三大的数。

优化：可以使用指针，空指针作为没找到的条件，可以不依赖元素范围

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历数组所需时间
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long long a = LLONG_MIN, b = LLONG_MIN, c = LLONG_MIN;
        for (int num : nums) {
            if (num > a) {
                c = b;
                b = a;
                a = num;
            } else if (a > num && num > b) {
                c = b;
                b = num;
            } else if (b > num && num > c) {
                c = num;
            }
        }
        return c == LLONG_MIN ? a : c;
    }
};
```



# 找到所有数组中消失的数字

- [链接](https://leetcode-cn.com/problems/find-all-numbers-disappeared-in-an-array/)
- [code](../cc/array/array.h)

> 给你一个含 n 个整数的数组 nums ，其中 nums[i] 在区间 [1, n] 内。
>
> 请你找出所有在 [1, n] 范围内但没有出现在 nums 中的数字，并以数组的形式返回结果。

## 哈希集合/哈希表

构建哈希集合，遍历数组，将元素插入集合中，去除重复元素。再遍历 1 到 n，判断是否存在集合中，不存在则加入结果数组。

**复杂度分析：**

- 时间复杂度：$O(n)$，构建哈希集合/表时间 $O(n)$，遍历查询时间 $O(n)$
- 空间复杂度：$O(k)$，构建哈希表所需空间，k 为数组中不重复的大小，最差可能 k = n

```c++
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        unordered_set<int> set;
        int n = nums.size();
        for (int num : nums) {
            set.insert(num);
        }
        vector<int> ans;
        for (int i = 1; i <= n; ++i) {
            if (!set.count(i)) {
                ans.emplace_back(i);
            }
        }
        return ans;
    }
};
```

## 原地修改

利用数组 nums 充当哈希表。nums 范围 [1,n]，可以利用范围之外的数表示 “数字存在”。遍历数组，遇到每个数 x，就让 `nums[x-1]` 加上数组长度 n，再次遍历 nums，若第 `i` 个元素不大于 n，则数 `i+1` 不存在 nums 中。需要注意的是，第一轮遍历时，`nums[i]` 可能已经被修改，需要对 `n` 求余，获取正确位置 `x-1`。

**注意：** 让位置 x -1 的元素增加而不是 x 的原因是，数组下标从 0 开始。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历修改数组时间 $O(n)$，遍历查询数组时间 $O(n)$
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int j = (nums[i] - 1) % n;
            nums[j] += n;
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] <= n) {
                ans.emplace_back(i + 1);
            }
        }
        return ans;
    }
};
```



# 最小操作次数使数组元素相等

- [链接](https://leetcode-cn.com/problems/minimum-moves-to-equal-array-elements/)
- [code](../cc/array/array.h)

> 给你一个长度为 n 的整数数组，每次操作将会使 n-1 个元素增加 1。返回让数组所有元素相等的最小操作次数。

## 数学

因为只需找出让数组所有元素相等的操作次数，所以不用考虑元素的绝对大小，则可以将操作 n-1 个元素增加 1 等效为 操作 1 个元素减少 1。使 m 为数组中最小元素，每个元素的操作次数为
$$
s_i = a_i - m
$$
则总次数为
$$
S = \sum\limits_{i=1}^{n} s_i = \sum\limits_{i=1}^{n}a_i - m = \sum\limits_{i}^{n}a_i - n*m
$$
优化：动态更新最小值，一次遍历

**注意：** 可能最后 n*m 会溢出 int 的范围

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历数组所需时间
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n = nums.size();
        int m = INT_MAX;
        long long sum = 0;
        for (int num : nums) {
            sum += num;
            m = m > num ? num : m;
        }
        return sum - (long long)m * n;
    }
};
```



# 有序数组中的单一元素

- [链接](https://leetcode-cn.com/problems/single-element-in-a-sorted-array/)
- [code](../cc/array/array.h)

> 给你一个仅由整数组成的有序数组，其中每个元素都会出现两次，唯有一个数只会出现一次。
>
> 请你找出并返回只出现一次的那个数。
>
> 你设计的解决方案必须满足 O(log n) 时间复杂度和 O(1) 空间复杂度。

## 异或

由于除了答案的数字，其余数字都会出现两次，因此可以用异或操作来找出答案。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历数组时间
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int ans = 0;
        for (int num : nums) {
            ans ^= num;
        }
        return ans;
    }
};
```

## 下标二分查找

假设一次出现的数的下标为 x，由于其他数字都出现两次，因此 x 左右两边各有偶数个元素，数组长度为奇数。

由于数组是有序的，因此数组中相同元素一定是相邻的。对于 x 的左边的下标 y，如果 `nums[y] = nums[y+1]`，则 y 一定是偶数；对于 x 的右边的下标 z，如果 `nums[z] = nums[z+1]`，则 z 一定是奇数。由于下标 x 是相同元素的开始下标的奇偶性的分界，可以用二分查找的方法寻找下标 x。

二分查找的左边界是 0，右边界是数组的最大下标。每次取左右边界的平均值 mid 作为待判断的下标，根据 mid 的奇偶性决定和左边或右边的相邻元素比较：

- 如果 mid 是奇数，则比较 `nums[mid - 1]` 和 `nums[mid]`，若相等则说明 `mid < x`，更新左边界为 `mid + 1`，否则 `mid >= x`，更新右边界为 `mid`
- 如果 mid 是偶数，则比较 `nums[mid]` 和 `nums[mid + 1]`，若相等则说明 `mid < x`，更新左边界为 `mid + 1`，否则 `mid >= x`，更新右边界为 `mid`

查找结束后，左边界等于右边界，即为 x，返回 x 所在位置的元素即为只出现一次的数。

**优化：** 利用异或可以减少奇偶数判定条件，可得 mid 和相邻的数之间的如下关系：

- 当 mid 为奇数，`mid ^ 1 = mid - 1`
- 当 mid 为偶数，`mid ^ 1 = mid + 1 `

**复杂度分析：**

- 时间复杂度：$O(\log n)$，二分查找时间
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            // 若 mid 是奇数，mid^1=mid-1 是偶数
            // 若 mid 是偶数，mid^1=mid+1 是奇数
            if (nums[mid] == nums[mid ^ 1]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return nums[left];
    }
};
```

## 偶数下标二分查找

由于只出现一次的元素所在下标 x 的左边有偶数个元素，因此下标 x 一定是偶数。在偶数下标范围内二分查找，找到满足 `nums[x] != nums[x+1]` 的最小偶数下标 x。

二分查找的左边界是 0，右边界是数组的最大下标，每次取左右边界的平均值 mid 作为待判断的下标，根据 mid 的奇偶性决定和左边或右边的相邻元素比较：

- 如果 mid 是奇数，则将 mid 减 1，比较 `nums[mid]` 和 `nums[mid +1 ]`，若相等则说明 `mid < x`，更新左边界为 `mid + 2`，否则 `mid >= x`，更新右边界为 `mid`
- 如果 mid 是偶数，则比较 `nums[mid]` 和 `nums[mid +1 ]`，若相等则说明 `mid < x`，更新左边界为 `mid + 2`，否则否则 `mid >= x`，更新右边界为 `mid`

查找结束后，左边界等于右边界，即为 x，返回 x 所在位置的元素即为只出现一次的数。

**优化：** 考虑 mid 与 1 按位与运输的结果可以减少奇偶数判定条件：

- 当 mid 为奇数，`mid & 1 = 1`，`mid - mid & 1 = mid - 1`
- 当 mid 为偶数，`mid & 1 = 0`，`mid - mid & 1 = mid`

**复杂度分析：**

- 时间复杂度：$O(\log n)$，二分查找时间，由于只查找偶数下标，会比全部下标的二分查找快
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;
        while (low < high) {
            int mid = low + (high - low) / 2;
            // 确保 mid 是偶数
            // 若 mid 是奇数，mid&1=1，mid=mid-1 是偶数
            // 若 mid 是偶数，mid&1=0，mid=mid-0 是偶数
            mid -= mid & 1; 
            if (nums[mid] == nums[mid + 1]) {
                low = mid + 2;
            }
            else {
                high = mid;
            }
        }
        return nums[low];
    }
};
```

## 遍历

因为只出现一次的元素的下标 x 左边有偶数个元素，所以从头开始，两两遍历数组元素，找出第一个 `nums[x] != nums[x+1]` 的下标 x，返回下标所在元素即为答案。需要注意如果 x 在最后一个时，数组越界问题。

复杂度分析：

- 时间复杂度：$O(n)$，两两遍历数组元素时间
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i+=2) {
            if (i < n - 1 && nums[i] != nums[i + 1]) {
                return nums[i];
            }
        }
        return nums[n - 1];
    }
};
```



# 1比特与2比特字符

- [链接](https://leetcode-cn.com/problems/1-bit-and-2-bit-characters/)
- [code](../cc/array/array.h)

> 有两种特殊字符：
>
> - 第一种字符可以用一个比特 0 来表示
> - 第二种字符可以用两个比特(10 或 11)来表示
>
> 给定一个以 0 结尾的二进制数组 bits，如果最后一个字符必须是一位字符，则返回 true。

## 正序遍历

根据题意，第一种字符一定以 0 开头，第二种字符一定以 1 开头。对 bits 数组正序遍历，遍历到 `bits[i]` 时，如果 `bits[0] == 0`，说明遇到了第一种字符，将 i 加 1；如果 `bits[i] == 1`，说明遇到了第二种字符，则可以跳过 `bits[i+1]`，将 i 加 2。

上述流程也说明 bits 的编码方式是唯一确定的，因此若遍历到 n - 1，那么说明最后一个字符一定是第一种字符。

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历数组所需时间
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int n = bits.size() - 1, i = 0;
        while (i < n) {
            i += bits[i] + 1;
        }
        return i == n;
    }
};
```

## 倒序遍历

根据题意，0 一定是一个字符的结尾。找到倒数第二个 0 的位置 i，则 `bits[i + 1]` 到 `bits[n - 2]` 中这 `n - 2 - i` 个比特均为 1。根据 `n - 2 - i` 的奇偶性来确定最后一个字符是否一位字符：

- n - 2 - i 是偶数，则这些比特 1 组成了 $\frac{n - 2 - i}{2}$ 个第二种字符，所以最后一个字符是一位字符
- n - 2 - i 是奇数，则这些比特 1 的前 n - 3 - i 个比特组成了 $\frac{n - 3 - i}{2}$ 个第二种字符，多出一个比特 1 和最后一位比特 0 组成第二种字符

根据 n - 2 - i 的奇偶性，可以判断最后一个字符是否一位字符，且由于 n - i - 2 的奇偶性与 n - 2 的奇偶性相同，可用 n - i 代替判断。

**复杂度分析**：

- 时间复杂度：$O(n)$，倒序遍历最差情况下需要遍历完整个 bits 数组
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int n = bits.size(), i = n - 2;
        while (i >= 0 && bits[i]) {
            --i;
        }
        return (n - i) % 2 == 0;
    }
};
```



# 矩阵中的幸运数

- [链接](https://leetcode-cn.com/problems/lucky-numbers-in-a-matrix/)
- [code](../cc/array/array.h)

> 给你一个 m * n 的矩阵，矩阵中的数字各不相同。请你按任意顺序返回矩阵中的所有幸运数。
>
> 幸运数是指矩阵中满足同时下列两个条件的元素：
>
> - 在同一行的所有元素中最小
> - 在同一列的所有元素中最大

## 预处理

先遍历矩阵，找出并存储每行最小和每列最大。然后再遍历矩阵，判断是否幸运数。

**复杂度分析：**

- 时间复杂度：$O(nm)$，找出并存储每行最小和每列最大时间 $O(nm)$，遍历数组找出幸运数时间 $O(nm)$
- 空间复杂度：$O(n+m)$，存储每行最小和每列最大所需空间

```c++
class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> min_rows(m, INT_MAX), max_cols(n), ans;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                min_rows[i] = std::min(min_rows[i], matrix[i][j]);
                max_cols[j] = std::max(max_cols[j], matrix[i][j]);
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int v = matrix[i][j];
                if (v == min_rows[i] && v == max_cols[j]) {
                    ans.push_back(v);
                }
            }
        }
        return ans;
    }
};
```

## 模拟

遍历矩阵，判断每个元素是否幸运数。

**复杂度分析：**

- 时间复杂度：$O(nm(n+m))$，判断每个元素是否幸运数时间 $O(n+m)$，遍历判断全部元素时间 $O(nm(n+m))$
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> ans;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int v = matrix[i][j];
                bool is_max = true, is_min = true;
                for (int k = 0; k < n; ++k) {
                    if (v > matrix[i][k]) {
                        is_min = false;
                        break;
                    }
                }
                if (!is_min) {
                    continue;
                }
                for (int k = 0; k < m; ++k) {
                    if (v < matrix[k][j]) {
                        is_max = false;
                    }
                }
                if (is_max) {
                    ans.emplace_back(v);
                }
            }
        }
        return ans;
    }
};
```



# 球会落何处

- [链接](https://leetcode-cn.com/problems/where-will-the-ball-fall/)
- [code](../cc/array/array.h)

>用一个大小为 m x n 的二维网格 grid 表示一个箱子。你有 n 颗球。箱子的顶部和底部都是开着的。
>
>箱子中的每个单元格都有一个对角线挡板，跨过单元格的两个角，可以将球导向左侧或者右侧。
>
>- 将球导向右侧的挡板跨过左上角和右下角，在网格中用 1 表示。
>- 将球导向左侧的挡板跨过右上角和左下角，在网格中用 -1 表示。
>
>在箱子每一列的顶端各放一颗球。每颗球都可能卡在箱子里或从底部掉出来。
>
>如果球恰好卡在两块挡板之间的 \"V\" 形图案，或者被一块挡导向到箱子的任意一侧边上，就会卡住。
>
>返回一个大小为 n 的数组 answer，其中 answer[i] 是球放在顶部的第 i 列后从底部掉出来的那一列对应的下标，如果球卡在盒子里，则返回 -1。

## 模拟

依次判断每个球的最终位置。对于每个球，从上至下判断球的移动方向。在对应位置，如果挡板导向右侧，则球往右移动；如果挡板导向左侧，则球向左移动。若过程中碰到侧边或者 V 型，则球会停止移动，卡在箱子里。如果可以完成本层的移动，则继续判断下一层的移动方向，直到落出箱子或者卡住。

**复杂度分析：**

- 时间复杂度：$O(mn)$，m 和 n 是网格的行数和列数
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    vector<int> findBall(vector<vector<int>>& grid) {
        int n = grid[0].size();
        int m = grid.size();
        vector<int> ans(n, -1);
        for (int j = 0; j < n; ++j) {
            int col = j;
            for (int i = 0; i < m; ++i) {
                int dir = grid[i][col];
                col += dir;
                if (col < 0 || col >= n || grid[i][col] != dir) {
                    col = -1;
                    break;
                }
            }
            if (col >= 0) {
                ans[j] = col;
            }
        }
        return ans;
    }
};
```



# 学生分数的最小差值

- [链接](https://leetcode-cn.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/)
- [code](../cc/array/array.h)

> 给你一个下标从 0 开始的整数数组 nums，其中 nums[i] 表示第 i 名学生的分数。另给你一个整数 k。
>
> 从数组中选出任意 k 名学生的分数，使这 k 个分数间最高分和最低分的差值达到最小化。
>
> 返回可能的最小差值。

## 排序+滑动窗口

要使 k 个分数极差最小化，一定是在排序后的数组中连续选择。对数组升序排序后，用一个大小固定为 k 的窗口滑过数组，窗口左边界为 `i`，右边界为 `i+k-1`，那么窗口中的分数的极差一定是 `nums[i+k-1] - nums[i]`。

**复杂度分析：**

- 时间复杂度：$O(n \log n)$，排序时间 $O(n \log n)$，遍历数组时间 $O(n)$
- 空间复杂度：$O(\log n)$

```c++
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        if (k==1) return 0;
        int n = nums.size(), m = INT_MAX;
        sort(nums.begin(), nums.end());
        for (int i = 0; i+k-1 < n; ++i) {
            m = min(m, nums[i+k-1] - nums[i]);
        }
        return m;
    }
};
```



# 增量元素之间的最大差值

- [链接](https://leetcode-cn.com/problems/maximum-difference-between-increasing-elements/)
- [code](../cc/array/array.h)

> 给你一个下标从 0 开始的整数数组 nums ，该数组的大小为 n，请你计算 nums[j] - nums[i] 能求得的最大差值 ，其中 0 <= i < j < n 且 nums[i] < nums[j]。
>
> 返回最大差值。如果不存在满足要求的 i 和 j，返回 -1。

## 前缀最小值

固定 j 时，选择的下标 i 一定是满足 $0 \le i < j$ 并且 nums[i] 最小的那个 i。遍历数组，维护 nums[0...j-1] 的前缀最小值，记为 premin：

- 如果 nums[i] > premin，那么用 nums[i] - premin 更新最大差值 ans
- 否则，用 nums[i] 更新 premin

**复杂度分析：**

- 时间复杂度：$O(n)$，遍历数组时间
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        int n = nums.size();
        int ans = -1, premin = n > 0 ? nums[0] : -1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] > premin) {
                ans = std::max(ans, nums[i] - premin);
            } else {
                premin = nums[i];
            }
        }
        return ans;
    }
};
```

