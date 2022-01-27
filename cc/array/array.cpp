#pragma once

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
        std::cout << typeid(*solution).name() << "\n" << solution->problem() << std::endl;
        solution->solution();
        solution->benchmark();
        delete solution;
    }
}


std::string TwoSum::problem() {
    return
        "给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。\n"
        "你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。\n"
        "你可以按任意顺序返回答案。\n"
        "来源：力扣（LeetCode）\n"
        "链接：https://leetcode-cn.com/problems/two-sum\n"
        "著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。\n";
}

void TwoSum::solution() {
    // TODO
}

std::string TwoSum::benchmark() {
    std::cout << "TwoSum benchmark" << std::endl;
    benchmark::RegisterBenchmark("BM_TwoSum", [](benchmark::State& state) {
        TwoSum solution;
        for (auto _ : state)
            solution.solution();
    });

    return "twoSum no benchmark, TODO.";
}

void TwoSum::_benchmark()
{
}

} // namespace array
} // namespace leetcode
