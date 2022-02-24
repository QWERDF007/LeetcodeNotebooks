#pragma once

#include <iostream>
#include <vector>

#include "leetcode_solution.h"

namespace leetcode {
namespace array{

/**
 * @brief 数组题目入口
 *
 * @param pid 数组题目id
 */
void ArraySolution(int pid);


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
     * @return std::vector<int> 数组中找出和为目标值 target 的那两个整数
     */
    std::vector<int> Solution1(std::vector<int> &nums, int target);

    /**
     * @brief 两数之和：哈希表
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param nums 
     * @param target 
     * @return std::vector<int> 数组中找出和为目标值 target 的那两个整数
     */
    std::vector<int> Solution2(std::vector<int> &nums, int target);
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
     * @param nums
     * @return int 删除重复项后数组的长度
     */
    int Solution1(std::vector<int> &nums);

    /**
     * @brief 删除有序数组中的重复项：双指针
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param nums
     * @return int 删除重复项后数组的长度
     */
    int Solution2(std::vector<int> &nums);

};

class FindMissingRanges : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    std::vector<std::string> Solution1(std::vector<int> &nums, int lower, int upper);
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
    int Solution1(std::vector<int> &nums);

    /**
     * @brief 丢失的数字：哈希集合
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param nums 
     * @return int 丢失的数字
     */
    int Solution2(std::vector<int> &nums);

    /**
     * @brief 丢失的数字：位运算
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param nums 
     * @return int 丢失的数字
     */
    int Solution3(std::vector<int> &nums);

    /**
     * @brief 丢失的数字：数学等差数列求和
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param nums 
     * @return int 丢失的数字
     */
    int Solution4(std::vector<int> &nums);

};

class NumArray : public LeetcodeSolution {
public:
    NumArray() {};

    NumArray(std::vector<int> &nums);

    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 实时计算
     * 时间复杂度：O(n) + m * O(right-left+1)
     * 空间复杂度：O(n)
     * @param left 索引
     * @param right 索引
     * @return int 索引 left 和 right 之间的元素的总和
     */
    int sumRange1(int left, int right);

    /**
     * @brief 前缀和
     * 时间复杂度：O(n) + m * O(1)
     * 空间复杂度：O(n)
     * @param left 索引
     * @param right 索引
     * @return int 索引 left 和 right 之间的元素的总和
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
    std::vector<int> Solution1(std::vector<int> &nums1, std::vector<int> &nums2);

    /**
     * @brief 排序+双指针
     * 时间复杂度：O(nlogn+mlogm)
     * 空间复杂度：O(logn+logm)
     * @param nums1 
     * @param nums2 
     * @return std::vector<int> 数组交集
     */
    std::vector<int> Solution2(std::vector<int> &nums1, std::vector<int> &nums2);
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
    std::vector<int> Solution1(std::vector<int> &nums1, std::vector<int> &nums2);

    /**
     * @brief 排序+双指针
     * 时间复杂度：O(nlogn+mlogm)
     * 空间复杂度：O(logn+logm)
     * @param nums1
     * @param nums2
     * @return std::vector<int> 数组交集
     */
    std::vector<int> Solution2(std::vector<int> &nums1, std::vector<int> &nums2);
};

class ThirdMax : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;
    
    /**
     * @brief 排序
     * 时间复杂度：O(nlogn)
     * 空间复杂度：O(logn)
     * @param nums 
     * @return int 第三大的数
     */
    int Solution1(std::vector<int> &nums);

    /**
     * @brief 有序集合
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param nums 
     * @return int 第三大的数
     */
    int Solution2(std::vector<int> &nums);

    /**
     * @brief 有限变量遍历
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param nums 
     * @return int 第三大的数
     */
    int Solution3(std::vector<int> &nums);
};

class FindDisappearedNumbers : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 哈希集合
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param nums 
     * @return std::vector<int> 消失的数字
     */
    std::vector<int> Solution1(std::vector<int> &nums);

    /**
     * @brief 原地修改
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param nums 
     * @return std::vector<int> 消失的数字
     */
    std::vector<int> Solution2(std::vector<int> &nums);

    /**
     * @brief 哈希表
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param nums
     * @return std::vector<int> 消失的数字
     */
    std::vector<int> Solution3(std::vector<int> &nums);
};

class MinMoves : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 数学，一次遍历
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param nums 
     * @return int 最小次数
     */
    int Solution1(std::vector<int> &nums);
};

class SingleNonDuplicate : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 异或
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param nums 有序数组
     * @return int 有序数组中的单一元素
     */
    int Solution1(std::vector<int> &nums);

    /**
     * @brief 二分查找
     * 时间复杂度：O(logn)
     * 空间复杂度：O(1)
     * @param nums 有序数组
     * @return int 有序数组中的单一元素
     */
    int Solution2(std::vector<int> &nums);

    /**
     * @brief 偶数二分查找
     * 时间复杂度：O(logn)
     * 空间复杂度：O(1)
     * @param nums 有序数组
     * @return int 有序数组中的单一元素
     */
    int Solution3(std::vector<int> &nums);

    /**
     * @brief 遍历
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param nums 有序数组
     * @return int 有序数组中的单一元素
     */
    int Solution4(std::vector<int> &nums);
};

class IsOneBitCharacter : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 正序遍历
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param bits 以 0 结尾的比特数组
     * @return true 
     * @return false 
     */
    bool Solution1(std::vector<int> &bits);

    /**
     * @brief 倒序遍历
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param bits 以 0 结尾的比特数组
     * @return true 
     * @return false 
     */
    bool Solution2(std::vector<int> &bits);
};

class LuckyNumbers : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 预处理
     * 时间复杂度：O(nm)
     * 空间复杂度：O(n+m)
     * @param matrix 待处理矩阵
     * @return std::vector<int> 幸运数
     */
    std::vector<int> Solution1(std::vector<std::vector<int>> &matrix);

    /**
     * @brief 模拟
     * 时间复杂度：O(nm(n+m))
     * 空间复杂度：O(1)
     * @param matrix 待处理矩阵
     * @return std::vector<int> 幸运数
     */
    std::vector<int> Solution2(std::vector<std::vector<int>> &matrix);
};

class FindBall : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;
    
    /**
     * @brief 模拟
     * 时间复杂度：O(mn)
     * 空间复杂度：O(1)
     * @param grid 二维网格数组
     * @return std::vector<int> 每个小球最终掉落位置
     */
    std::vector<int> Solution1(std::vector<std::vector<int>> &grid);
};

class MinimumDifference : public LeetcodeSolution {
public:
    std::string Title() override;
    
    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 排序+滑动窗口
     * 时间复杂度：O(nlogn)
     * 空间复杂度：O(logn)
     * @param nums 学生分数
     * @param k 选择学生数量
     * @return int 学生分数的最小差值
     */
    int Solution1(std::vector<int> &nums, int k);
};

} // namespace array
} // namespace leetcode
