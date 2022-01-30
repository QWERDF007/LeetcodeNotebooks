#include <iostream>

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
        solution->Solution();
        solution->Benchmark();
        delete solution;
    }
}


std::string TwoSum::Title()
{
    return "1.两数之和";
}

std::string TwoSum::Problem() {
    return
        "给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值 target 的那两个整数，并返回它们的数组下标。\n"
        "你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。\n"
        "你可以按任意顺序返回答案。\n";
}

std::string TwoSum::Link()
{
    return "https://leetcode-cn.com/problems/two-sum";
}

void TwoSum::Solution() {
    // TODO
}

std::string TwoSum::Benchmark() {
    for (auto& test_input : { std::vector<int>{1,2,3}, std::vector<int>{1,2,3} }) {
        
    }
    benchmark::RegisterBenchmark("BM_TwoSum_Solution1", [](benchmark::State& state) {
        TwoSum solution;
        int target = 9;
        std::vector<int> inputs({ 2,7,11,15 }), res({ 0, 1 });
        for (auto _ : state)
            solution.Solution1(inputs, target);
    });

    return "TwoSum Benchmark.";
}

std::vector<int> TwoSum::Solution1(std::vector<int>& nums, int target)
{
    for (int i = 0; i < nums.size() - 1; i++)
    {
        for (int j = i + 1; j < nums.size(); j++)
        {
            if (nums[i] + nums[j] == target)
            {
                std::vector<int> result;
                result.push_back(i);
                result.push_back(j);
                return result;
            }

        }
    }
}


} // namespace array
} // namespace leetcode
