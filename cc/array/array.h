#pragma once

#include <iostream>
#include <vector>

#include "leetcode_solution.h"

namespace leetcode {
namespace array{

class TwoSum : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;
    
    /**
     * @brief 两数之和：暴力枚举
     * 时间复杂度：O(n^2)
     * 空间复杂度：O(1)
     * @param nums 
     * @param target 
     * @return std::vector<int> 
     */
    std::vector<int> Solution1(std::vector<int>& nums, int target);

    /**
     * @brief 两数之和：哈希表
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param nums 
     * @param target 
     * @return std::vector<int> 
     */
    std::vector<int> Solution2(std::vector<int>& nums, int target);
};

class RemoveDuplicates : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 删除有序数组中的重复项：暴力解法
     * 时间复杂度：O(n^2)
     * 空间复杂度：O(1)
     * @return int 删除重复项后数组的长度
     */
    int Solution1(std::vector<int>& nums);

    /**
     * @brief 删除有序数组中的重复项：双指针
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @return int 删除重复项后数组的长度
     */
    int Solution2(std::vector<int>& nums);

};

class MissingNumber : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 丢失的数字：排序
     * 时间复杂度：O(nlogn)
     * 空间复杂度：O(logn)
     * @param nums 
     * @return int 丢失的数字
     */
    int Solution1(std::vector<int>& nums);

    /**
     * @brief 丢失的数字：哈希集合
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param nums 
     * @return int 丢失的数字
     */
    int Solution2(std::vector<int>& nums);

    /**
     * @brief 丢失的数字：位运算
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param nums 
     * @return int 丢失的数字
     */
    int Solution3(std::vector<int>& nums);

    /**
     * @brief 丢失的数字：数学等差数列求和
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param nums 
     * @return int 丢失的数字
     */
    int Solution4(std::vector<int>& nums);

};

class NumArray : public LeetcodeSolution {
public:
    NumArray() {};

    NumArray(std::vector<int>& nums);

    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 实时计算
     * 时间复杂度：O(n) + m * O(right-left+1)
     * 空间复杂度：O(n)
     * @param left 
     * @param right 
     * @return int 
     */
    int sumRange1(int left, int right);

    /**
     * @brief 前缀和
     * 时间复杂度：O(n) + m * O(1)
     * 空间复杂度：O(n)
     * @param left 
     * @param right 
     * @return int 
     */
    int sumRange2(int left, int right);

    std::vector<int> nums_, sums_;
};

class Intersection : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 哈希集合
     * 时间复杂度：O(n+m)
     * 空间复杂度：O(n+m)
     * @param nums1 
     * @param nums2 
     * @return std::vector<int> 数组交集
     */
    std::vector<int> Solution1(std::vector<int>& nums1, std::vector<int>& nums2);

    /**
     * @brief 排序+双指针
     * 时间复杂度：O(nlogn+mlogm)
     * 空间复杂度：O(logn+logm)
     * @param nums1 
     * @param nums2 
     * @return std::vector<int> 数组交集
     */
    std::vector<int> Solution2(std::vector<int>& nums1, std::vector<int>& nums2);
};

class Intersect : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 哈希表
     * 时间复杂度：O(n+m)
     * 空间复杂度：O(min(n,m))
     * @param nums1
     * @param nums2
     * @return std::vector<int> 数组交集
     */
    std::vector<int> Solution1(std::vector<int>& nums1, std::vector<int>& nums2);

    /**
     * @brief 排序+双指针
     * 时间复杂度：O(nlogn+mlogm)
     * 空间复杂度：O(logn+logm)
     * @param nums1
     * @param nums2
     * @return std::vector<int> 数组交集
     */
    std::vector<int> Solution2(std::vector<int>& nums1, std::vector<int>& nums2);
};

/**
 * @brief 数组题目入口
 * 
 * @param pid 数组题目id
 */
void ArraySolution(int pid);

} // namespace array
} // namespace leetcode
