#include <iostream>
#include <benchmark/benchmark.h>

#include "dynamic_programming.h"

namespace leetcode {
namespace dp {

void DynamicProgrammingSolution(int pid) {
    LeetcodeSolution *solution = nullptr;
    switch (pid) {
        case SolutionsId::KNIGHT_PROBABILITY: solution = new KnightProbability(); break;
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

std::string KnightProbability::Title() {
    return "688. 骑士在棋盘上的概率\n";
}

std::string KnightProbability::Problem() {
    return 
        "在一个 n x n 的国际象棋棋盘上，一个骑士从单元格 (row, column) 开始，并尝试进行 k 次移动。\n"
        "行和列是 从 0 开始的，所以左上单元格是 (0,0) ，右下单元格是 (n - 1, n - 1) 。\n"
        "象棋骑士有8种可能的走法，如下图所示。每次移动在基本方向上是两个单元格，然后在正交方向上是一个单元格。\n"
        "每次骑士要移动时，它都会随机从8种可能的移动中选择一种（即使棋子会离开棋盘），然后移动到那里。\n"
        "骑士继续移动，直到它走了 k 步或离开了棋盘。\n"
        "返回骑士在棋盘停止移动后仍留在棋盘上的概率。\n";
}

std::string KnightProbability::Link() {
    return "https://leetcode-cn.com/problems/knight-probability-in-chessboard/";
}

std::string KnightProbability::Solution() {
    return "动态规划，时间：O(kn^2)，空间：O(kn^2)。\n";
}

void KnightProbability::Benchmark() {
    KnightProbability solution;

    int n = 25, k = 100, row = 15, column = 20;

    auto func = [](benchmark::State &state, KnightProbability solution, int n, int k, int row, int column) {
        for (auto _ : state) {
            solution.Solution1(n, k, row, column);
        }
    };
    benchmark::RegisterBenchmark("BM_KnightProbability_DynamicProgramming", func, solution, n, k, row, column);
}

double KnightProbability::Solution1(int n, int k, int row, int column) {

    // 定义 prob[step][i][j] 为从 (i,j) 出发，走 step 步仍在棋盘的概率
    // (i,j) 不在棋盘时，prob[step][i][j] = 0
    // (i,j) 在棋盘且 step = 0 时，prob[step][i][j] = 1
    // 其他情况，prob[step][i][j] 等于从 step - 1 步走到 (i,j) 的概率之和除以 8
    // 若要定义为 prob[i][j][step] 则需要先处理全部 step = 0 情况才能计算后续
    std::vector<std::vector<std::vector<double>>> prob(k+1, std::vector<std::vector<double>>(n, std::vector<double>(n)));
    for (int step = 0; step <= k; ++step) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (step == 0) {
                    prob[step][i][j] = 1;
                } else {
                    for (auto &dir : dirs_) {
                        int ni = i + dir[0], nj = j + dir[1];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
                            prob[step][i][j] += prob[step - 1][ni][nj];
                        }
                    }
                    prob[step][i][j] /= 8;
                }
            }
        }
    }
    return prob[k][row][column];
}



} // namespace dp
} // namespace leetcode
