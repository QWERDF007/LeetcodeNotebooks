#include <iostream>
#include <algorithm>
#include <random>
#include <climits>
#include <benchmark/benchmark.h>
#include "greedy_algorithm.h"

namespace leetcode {
namespace greedy {

void GreedyAlgorithmSolution(int pid) {
    LeetcodeSolution *solution = nullptr;
    switch (pid) {
        case SolutionsId::FIND_CONTENT_CHILDREN: solution = new FindContentChildren(); break;
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

std::string FindContentChildren::Title() {
    return "455. 分发饼干\n";
}

std::string FindContentChildren::Problem() {
    return 
        "假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。\n"
        "对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；\n"
        "并且每块饼干 j，都有一个尺寸 s[j]。如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i，这个孩子会得到满足。\n"
        "你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。\n";
}

std::string FindContentChildren::Link() {
    return "https://leetcode-cn.com/problems/assign-cookies/";
}

std::string FindContentChildren::Solution() {
    return "排序+贪心，时间：O(nlogn+mlogm)，空间：O(logn+logm)。\n";
}

void FindContentChildren::Benchmark() {
    FindContentChildren solution;

    int n = 10000, m = 10000;
    std::vector<int> g(n), s(m);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, INT_MAX);
    for (int i = 0; i < n; ++i) {
        g[i] = dis(gen);
    }
    for (int i = 0; i < m; ++i) {
        s[i] = dis(gen);
    }

    auto func = [](benchmark::State &state, FindContentChildren solution, std::vector<int> g, std::vector<int> s) {
        for (auto _ : state) {
            solution.Solution1(g, s);
        }
    };
    benchmark::RegisterBenchmark("BM_FindContentChildren_SortAndGreedy", func, solution, g, s);
}

int FindContentChildren::Solution1(std::vector<int> &g, std::vector<int> &s) {
    std::sort(g.begin(), g.end());
    std::sort(s.begin(), s.end());
    int n = g.size(), m = s.size();
    int i = 0, j = 0, cnt = 0;
    while (i < n && j < m) {
        if (g[i] > s[j]) {
            ++j;
        } else {
            ++cnt;
            ++i;
            ++j;
        }
    }
    return cnt;
}

} // namespace greedy
} // namespace leetcode