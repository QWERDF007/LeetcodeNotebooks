#include <iostream>
#include <unordered_map>
#include <random>
#include <benchmark/benchmark.h>
#include "graph.h"

namespace leetcode {
namespace graph {

void GraphSolution(int pid) {
    LeetcodeSolution *solution = nullptr;
    switch (pid) {
        case SolutionsId::FIND_CENTER: solution = new FindCenter(); break;
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

std::string FindCenter::Title() {
    return "1791. 找出星型图的中心节点\n";
}

std::string FindCenter::Problem() {
    return 
        "有一个无向的星型图，由 n 个编号从 1 到 n 的节点组成。\n"
        "星型图有一个中心节点，并且恰有 n - 1 条边将中心节点与其他每个节点连接起来。\n"
        "给你一个二维整数数组 edges，其中 edges[i] = [ui, vi] 表示在节点 ui 和 vi 之间存在一条边。\n"
        "请你找出并返回 edges 所表示星型图的中心节点。\n";
}

std::string FindCenter::Link() {
    return "https://leetcode-cn.com/problems/find-center-of-star-graph/";
}

std::string FindCenter::Solution() {
    return "找出出在两条边的节点，时间：O(1)，空间：O(1)。\n";
}

void FindCenter::Benchmark() {
    FindCenter solution;

    int n = 10000;
    std::vector<std::vector<int>> edges(n-1, std::vector<int>(2));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, n);
    int center = dis(gen);

    for (int i = 0; i < n-1; ++i) {
        edges[i][0] = i + 1;
        edges[i][1] = center;
    }

    benchmark::RegisterBenchmark("BM_FindCenter_NodeInTwoEdges", [](benchmark::State &state, FindCenter solution, std::vector<std::vector<int>> edges) {
        for (auto _ : state) {
            solution.Solution1(edges);
        }
    }, solution, edges);

    benchmark::RegisterBenchmark("BM_FindCenter_GraphDegrees", [](benchmark::State &state, FindCenter solution, std::vector<std::vector<int>> edges) {
        for (auto _ : state) {
            solution.Solution2(edges);
        }
    }, solution, edges);

    benchmark::RegisterBenchmark("BM_FindCenter_MaxCount", [](benchmark::State &state, FindCenter solution, std::vector<std::vector<int>> edges) {
        for (auto _ : state) {
            solution.Solution3(edges);
        }
    }, solution, edges);
}

int FindCenter::Solution1(std::vector<std::vector<int>> &edges) {
    return edges[0][0] == edges[1][0] || edges[0][0] == edges[1][1] ? edges[0][0] : edges[0][1];
}

int FindCenter::Solution2(std::vector<std::vector<int>> &edges) {
    int n = edges.size() + 1;
    std::vector<int> degrees(n + 1);
    for (auto &edge : edges) {
        ++degrees[edge[0]];
        ++degrees[edge[1]];
    }
    for (int i = 1; i <= n; ++i) {
        if (degrees[i] == n - 1) {
            return i;
        }
    }
    return 0;
}

int FindCenter::Solution3(std::vector<std::vector<int>> &edges) {
    int n = edges.size() + 1;
    std::vector<int> counts(n+1);
    for (auto &edge : edges) {
            ++counts[edge[0]];
            ++counts[edge[1]];
    }
    int max_count = 0, center = 0;
    for (int i = 1; i <= n; ++i) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            center = i;
        }
    }
    return center;
}

} // namespace graph
} // namespace leetcode
