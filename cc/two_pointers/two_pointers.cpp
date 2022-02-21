#include <iostream>
#include <queue>
#include <random>
#include <benchmark/benchmark.h>
#include "two_pointers.h"

namespace leetcode {
namespace tp {

void TwoPointersSolution(int pid) {
    LeetcodeSolution *solution = nullptr;
    switch (pid) {
        case SolutionsId::PUSH_DOMINOES: solution = new PushDominoes(); break;
        default: std::cerr << "no such pid: " << pid << std::endl; exit(EXIT_FAILURE); break;
    }
    if (solution != nullptr) {
        //std::cout << typeid(*solution).name() << std::endl;
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

std::string PushDominoes::Title() {
    return "838. 推多米诺\n";
}

std::string PushDominoes::Problem() {
    return 
        "n 张多米诺骨牌排成一行，将每张多米诺骨牌垂直竖立。在开始时，同时把一些多米诺骨牌向左或向右推。\n"
        "每过一秒，倒向左边的多米诺骨牌会推动其左侧相邻的多米诺骨牌。同样地，倒向右边的多米诺骨牌也会推动竖立在其右侧的相邻多米诺骨牌。\n"
        "如果一张垂直竖立的多米诺骨牌的两侧同时有多米诺骨牌倒下时，由于受力平衡， 该骨牌仍然保持不变。\n"
        "就这个问题而言，我们会认为一张正在倒下的多米诺骨牌不会对其它正在倒下或已经倒下的多米诺骨牌施加额外的力。\n"
        "给你一个字符串 dominoes 表示这一行多米诺骨牌的初始状态，其中：\n"
        "- dominoes[i] = 'L'，表示第 i 张多米诺骨牌被推向左侧，\n"
        "- dominoes[i] = 'R'，表示第 i 张多米诺骨牌被推向右侧，\n"
        "- dominoes[i] = '.'，表示没有推动第 i 张多米诺骨牌。\n"
        "返回表示最终状态的字符串。\n";
}

std::string PushDominoes::Link() {
    return "https://leetcode-cn.com/problems/push-dominoes/";
}

std::string PushDominoes::Solution() {
    return "双指针模拟，时间：O(n)，空间：O(1)。\n";
}

void PushDominoes::Benchmark() {
    PushDominoes solution;
    int n = 10000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 9);
    std::string dominoes;
    for (int i = 0; i < n; ++i) {
        int v = dis(gen);
        if (v < 3) {
            dominoes.push_back('L');
        } else if (v < 5) {
            dominoes.push_back('R');
        } else {
            dominoes.push_back('.');
        }
    }

    benchmark::RegisterBenchmark("BM_PushDominoes_TwoPointers", [](benchmark::State &state, PushDominoes solution, std::string dominoes) {
        for (auto _ : state) {
            solution.Solution1(dominoes);
        }
    }, solution, dominoes);

    benchmark::RegisterBenchmark("BM_PushDominoes_BFS", [](benchmark::State &state, PushDominoes solution, std::string dominoes) {
        for (auto _ : state) {
            solution.Solution2(dominoes);
        }
    }, solution, dominoes);
}

std::string PushDominoes::Solution1(std::string dominoes) {
    int n = dominoes.size(), i = 0;
    char left = 'L';
    while (i < n) {
        int j = i;
        // 找到一段连续的没有被推动的骨牌
        while (j < n && dominoes[j] == '.') {
            ++j;
        }
        char right = j < n ? dominoes[j] : 'R';
        if (left == right) { // 方向相同，倒向同一边
            while (i < j) {
                dominoes[i++] = right;
            }
        } else if(left == 'R' && right == 'L') { // 方向相对，倒向中间
            int k = j - 1;
            while (i < k) {
                dominoes[i++] = 'R';
                dominoes[k--] = 'L';
            }
        }
        left = right;
        i = j + 1;
    }
    return dominoes;
}

std::string PushDominoes::Solution2(std::string dominoes) {
    int n = dominoes.size();
    std::queue<int> que;
    std::vector<int> time(n, -1);
    std::vector<std::string> force(n);
    for (int i = 0; i < n; ++i) {
        if (dominoes[i] != '.') {
            que.emplace(i);
            time[i] = 0;
            force[i].push_back(dominoes[i]);
        }
    }

    std::string res(n, '.');
    while (!que.empty()) {
        int i = que.front();
        que.pop();
        if (force[i].size() == 1) {
            char f = force[i][0];
            res[i] = f;
            int ni = (f == 'L') ? (i - 1) : (i + 1);
            if (ni >= 0 && ni < n) {
                int t = time[i];
                if (time[ni] == -1) {
                    que.emplace(ni);
                    time[ni] = t + 1;
                    force[ni].push_back(f);
                } else if (time[ni] == t + 1) {
                    force[ni].push_back(f);
                }
            }
        }
    }
    return res;
}

} // namespace tp    
} // namespace leetcode
