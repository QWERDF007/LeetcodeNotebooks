# 1. 两数之和

- [链接](https://leetcode-cn.com/problems/two-sum/)


> 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
>
> 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
>
> 你可以按任意顺序返回答案。

- [solutions](../cc/array/array.cpp#L35-L101)：

## 暴力求解

遍历数组中的每个数 `x`，寻找数组中是否存在 `y = target - x`，使 `x + y = target`。需要注意遍历过程中 `x` 之前的元素都和 `x` 匹配过，且每个元素不能出现两次，所以只需要在 `x` 之后的元素寻找 `y`。

**复杂度分析**：

- 时间复杂度：$O(N^2)$，最坏情况下数组中任意两个数都要被匹配一次
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

- 时间复杂度：$O(N)$，最坏情况下遍历整个数组，建立哈希表。对每个 `x`， $O(1)$ 时间查询 `y = target - x` 
- 空间复杂度：$O(N)$

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

