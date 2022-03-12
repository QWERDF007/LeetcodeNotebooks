#include <iostream>
#include <algorithm>
#include <random>
#include <climits>
#include <benchmark/benchmark.h>
#include "greedy_algorithm.h"

namespace leetcode {
namespace greedy {

void GreedyAlgorithmSolution(SolutionsId pid) {
    LeetcodeSolution *solution = nullptr;
    switch (pid) {
        case SolutionsId::FIND_CONTENT_CHILDREN: solution = new FindContentChildren(); break;
        case SolutionsId::PANCAKE_SORT: solution = new PancakeSort(); break;
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

std::string PancakeSort::Title() {
    return "969. 煎饼排序\n";
}

std::string PancakeSort::Problem() {
    return 
        "给你一个整数数组 arr，请使用煎饼翻转完成对数组的排序。\n"
        "一次煎饼翻转的执行过程如下：\n"
        "- 选择一个整数 k，1 <= k <= arr.length\n"
        "- 反转子数组 arr[0...k-1]（下标从 0 开始）\n"
        "例如，arr = [3,2,1,4]，选择 k = 3 进行一次煎饼翻转，反转子数组 [3,2,1]，得到 arr = [1,2,3,4]。\n"
        "以数组形式返回能使 arr 有序的煎饼翻转操作所对应的 k 值序列。\n"
        "任何将数组排序且翻转次数在 10 * arr.length 范围内的有效答案都将被判断为正确。\n";
}

std::string PancakeSort::Link() {
    return "https://leetcode-cn.com/problems/pancake-sorting/";
}

std::string PancakeSort::Solution() {
    return "贪心，时间：O(n^2)，空间：O(1)。\n";
}

void PancakeSort::Benchmark() {
    PancakeSort solution;

    int n = 100;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(arr.begin(), arr.end(), gen);
    
    benchmark::RegisterBenchmark("BM_PancakeSort_GreedyAlgorithm", [](benchmark::State &state, PancakeSort solution, std::vector<int> arr) {
        for (auto _ : state) {
            std::vector<int> tmp = arr;
            solution.Solution1(tmp);
        }
    }, solution, arr);
}

std::vector<int> PancakeSort::Solution1(std::vector<int> &arr) {
    std::vector<int> ans;
    for (int n = arr.size(); n > 1; --n) {
        // 在 arr[0...n] 中找出最大值的位置
        int index = std::max_element(arr.begin(), arr.begin() + n) - arr.begin();
        // arr[0...k-1] 中最大值已经处于最右了就不反转
        if (index == n - 1) {
            continue;
        }

        // 反转 arr[0...k-1]，将最大值放到最前面，将 k 放到结果
        // 再反转整个 arr[0...n]，将最大值放到最后面，将 n 放到结果
        // 完成一次循环，n 减 1
        std::reverse(arr.begin(), arr.begin() + index + 1);
        std::reverse(arr.begin(), arr.begin() + n);
        ans.emplace_back(index + 1);
        ans.emplace_back(n);
    }
    return ans;
}

void PancakeSort::Pancake(std::vector<int> &arr, std::vector<int> &indices) {
    for (int k : indices) {
        std::reverse(arr.begin(), arr.begin() + k);
    }
}

} // namespace greedy
} // namespace leetcode