#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <unordered_map>

#include <benchmark/benchmark.h>

#include "leetcode_solution.h"
#include "array.h"

namespace leetcode {
namespace array{


void ArraySolution(int pid) {
    LeetcodeSolution *solution = nullptr;
    switch (pid) {
    case SolutionsId::TWO_SUM: {
        solution = new TwoSum();
        break;
    }
    case SolutionsId::REMOVE_DUPLICATES: {
        solution = new RemoveDuplicates();
        break;
    }
    default:
        std::cerr << "no such pid: " << pid << std::endl;
        exit(EXIT_FAILURE);
        break;
    }
    if (solution != nullptr) {
        std::cout << typeid(*solution).name() << std::endl;
        std::cout << solution->Title() << std::endl;
        std::cout << solution->Problem() << std::endl;
        std::cout << solution->Solution() << std::endl;
        solution->Benchmark();
        delete solution;
    }
}


std::string TwoSum::Title() {
    return "1.两数之和\n";
}

std::string TwoSum::Problem() {
    return
        "给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值 target 的那两个整数，并返回它们的数组下标。\n"
        "你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。\n"
        "你可以按任意顺序返回答案。\n";
}

std::string TwoSum::Link() {
    return "https://leetcode-cn.com/problems/two-sum/";
}

std::string TwoSum::Solution() {
    return "哈希表，时间：O(n)，空间：O(n)。\n";
}

void TwoSum::Benchmark() {
    TwoSum solution;

    int n = 10001;
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = i+1;
    }
    int target = 19999;

    benchmark::RegisterBenchmark("BM_TwoSum_BruteForceSearch", [](benchmark::State& state, TwoSum solution, std::vector<int> nums, int target) {
        for (auto _ : state) {
            solution.Solution1(nums, target);
        }
    }, solution, nums, target);

    benchmark::RegisterBenchmark("BM_TwoSum_HashTable", [](benchmark::State& state, TwoSum solution, std::vector<int> nums, int target) {
        for (auto _ : state) {
            solution.Solution2(nums, target);
        }
    }, solution, nums, target);
}

std::vector<int> TwoSum::Solution1(std::vector<int>& nums, int target) {
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                return { i,j };
            }

        }
    }
    return {};
}

std::vector<int> TwoSum::Solution2(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> hashtable;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        int d = target - nums[i];
        auto finded = hashtable.find(d);
        if (finded != hashtable.end()) {
            return { hashtable[d], i };
        }
        hashtable[nums[i]] = i;
    }
    return std::vector<int>();
}


std::string RemoveDuplicates::Title() {
    return "26. 删除有序数组中的重复项\n";
}

std::string RemoveDuplicates::Problem() {
    return 
        "给你一个有序数组 nums ，请你原地删除重复出现的元素，使每个元素只出现一次，返回删除后数组的新长度。\n"
        "不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。\n";
}

std::string RemoveDuplicates::Link() {
    return "https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/";
}

std::string RemoveDuplicates::Solution() {
    return "双指针，时间：O(n)，空间：O(1)。\n";
}

void RemoveDuplicates::Benchmark() {
    RemoveDuplicates solution;

    int n = 10001;
    std::vector<int> nums;
    std::srand(std::time(nullptr));
    for (int i = 0; i < n; ++i) {
        int m = std::rand() % 5; // [0,5) 随机数
        for (int j = 0; j < m; ++j) {
            nums.emplace_back(i);
        }
    }

    benchmark::RegisterBenchmark("BM_TwoSum_BruteForceSearch", [](benchmark::State& state, RemoveDuplicates solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution1(nums);
        }
    }, solution, nums);

    benchmark::RegisterBenchmark("BM_TwoSum_DoublePointers", [](benchmark::State& state, RemoveDuplicates solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution2(nums);
        }
    }, solution, nums);
}

int RemoveDuplicates::Solution1(std::vector<int>& nums) {
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

int RemoveDuplicates::Solution2(std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) {
        return 0;
    }
    int slow = 1, fast = 1;
    while (fast < n) {
        if (nums[fast] != nums[fast - 1]) {
            nums[slow] = nums[fast];
            ++slow;
        }
        ++fast;
    }
    return slow;
}

} // namespace array
} // namespace leetcode
