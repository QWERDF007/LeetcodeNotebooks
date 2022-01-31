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
    default:
        std::cerr << "no such pid: " << pid << std::endl;
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
    return "1.两数之和";
}

std::string TwoSum::Problem() {
    return
        "给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值 target 的那两个整数，并返回它们的数组下标。\n"
        "你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。\n"
        "你可以按任意顺序返回答案。\n";
}

std::string TwoSum::Link() {
    return "https://leetcode-cn.com/problems/two-sum";
}

std::string TwoSum::Solution() {
    return "使用哈希表，时间：O(n)，空间：O(n)。\n";
}

std::string TwoSum::Benchmark() {
    TwoSum solution;
    int n = 10001;
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = i+1;
    }
    int target = 19999;
    benchmark::RegisterBenchmark("BM_TwoSum_BruteForceSearch", [](benchmark::State& state, TwoSum solution, std::vector<int> nums, int target) {
        for (auto _ : state)
            solution.Solution1(nums, target);
    }, solution, nums, target);

    benchmark::RegisterBenchmark("BM_TwoSum_HashTable", [](benchmark::State& state, TwoSum solution, std::vector<int> nums, int target) {
        for (auto _ : state)
            solution.Solution2(nums, target);
    }, solution, nums, target);

    return "TwoSum Benchmark.";
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


} // namespace array
} // namespace leetcode
