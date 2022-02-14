#include <iostream>
#include <benchmark/benchmark.h>
#include "bitwise_operation.h"

namespace leetcode {
namespace bit {

void BitwiseOperationSolution(int pid) {
    LeetcodeSolution *solution = nullptr;
    switch (pid) {
        case SolutionsId::HAMMING_WEIGHT: solution = new HammingWeight(); break;
        default: std::cerr << "no such pid: " << pid << std::endl; exit(EXIT_FAILURE); break;
    }
    if (solution != nullptr) {
        std::cout << solution->Title() << std::endl;
        std::cout << "Link:\n";
        std::cout << solution->Link() << std::endl << std::endl;
        std::cout << "Problem:\n";
        std::cout << solution->Problem() << std::endl;
        std::cout << "Solution:\n";
        std::cout << solution->Solution() << std::endl;
        solution->Benchmark();
        delete solution;
    }
}

std::string HammingWeight::Title() {
    return "191. 位1的个数\n";
}

std::string HammingWeight::Problem() {
    return 
        "编写一个函数，输入是一个无符号整数（以二进制串的形式），\n"
        "返回其二进制表达式中数字位数为 '1' 的个数（也被称为汉明重量）。\n";
}

std::string HammingWeight::Link() {
    return "https://leetcode-cn.com/problems/number-of-1-bits/";
}

std::string HammingWeight::Solution() {
    return "n-1，时间：O(k)，空间：O(1)。k 为 1 的个数\n";
}

void HammingWeight::Benchmark() {
    HammingWeight solution;

    uint32_t n = 0b11111101111011110111110111011101;

    benchmark::RegisterBenchmark("BM_HammingWeight_RightShift", [](benchmark::State &state, HammingWeight solution, uint32_t n) {
        for (auto _ : state) {
            solution.Solution1(n);
        }
    }, solution, n);

    benchmark::RegisterBenchmark("BM_HammingWeight_LeftShift", [](benchmark::State &state, HammingWeight solution, uint32_t n) {
        for (auto _ : state) {
            solution.Solution2(n);
        }
    }, solution, n);

    benchmark::RegisterBenchmark("BM_HammingWeight_NSubtractOne", [](benchmark::State &state, HammingWeight solution, uint32_t n) {
        for (auto _ : state) {
            solution.Solution3(n);
        }
    }, solution, n);
}

int HammingWeight::Solution1(uint32_t n) {
    int cnt = 0;
    while (n > 0) {
        if (n & 1) {
            ++cnt;
        }
        n = n >> 1;
    }
    return cnt;
}

int HammingWeight::Solution2(uint32_t n) {
    int cnt = 0;
    uint64_t i = 1;
    while (i <= n) {
        if (n & i) {
            ++cnt;
        }
        i = i << 1;
    }
    return cnt;
}

int HammingWeight::Solution3(uint32_t n) {
    int cnt = 0;
    while (n) {
        ++cnt;
        n &= n - 1;
    }
    return cnt;
}

} // namespace bit
} // namespace leetcode


