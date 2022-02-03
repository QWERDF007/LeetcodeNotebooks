#include <iostream>
#include <unordered_map>

#include <benchmark/benchmark.h>

#include "str.h"
#include "leetcode_solution.h"


namespace leetcode {
namespace str {

void StrSolution(int pid) {
    LeetcodeSolution* solution = nullptr;
    switch (pid) {
    case ROMAN_TO_INT: {
        solution = new RomanToInt();
        break;
    }
    default:
        std::cerr << "no such pid: " << pid << std::endl;
        exit(EXIT_FAILURE);
        break;
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

std::string RomanToInt::Title() {
    return "13. 罗马数字转整数\n";
}

std::string RomanToInt::Problem() {
    return
        "罗马数字包含以下其中字符：I, V, X, L, C, D 和 M。\n"
        "字符          数值\n"
        "I             1\n"
        "V             5\n"
        "X             10\n"
        "L             50\n"
        "C             100\n"
        "D             500\n"
        "M             1000\n"
        "给定一个罗马数字，将其转换成整数。\n";
}

std::string RomanToInt::Link() {
    return "https://leetcode-cn.com/problems/roman-to-integer/";
}

std::string RomanToInt::Solution() {
    return "动态数组，时间：O(n)，空间：O(n)。\n";
}

void RomanToInt::Benchmark() {
    RomanToInt solution;

    std::string s = "MMMDCCCLXXXVIII";
    
    benchmark::RegisterBenchmark("BM_RomanToInt_BruteForceSearch", [](benchmark::State& state, RomanToInt solution, std::string s) {
        for (auto _ : state) {
            solution.Solution1(s);
        }
    }, solution, s);

    benchmark::RegisterBenchmark("BM_RomanToInt_DynamicArray", [](benchmark::State& state, RomanToInt solution, std::string s) {
        for (auto _ : state) {
            solution.Solution2(s);
        }
    }, solution, s);

    benchmark::RegisterBenchmark("BM_RomanToInt_HashMap", [](benchmark::State& state, RomanToInt solution, std::string s) {
        for (auto _ : state) {
            solution.Solution3(s);
        }
    }, solution, s);
}

int RomanToInt::Solution1(std::string s) {
    int n = s.size();
    int m = n - 1, ret = 0;
    for (int i = 0; i < n; ++i) {
        if (i < m) {
            if (s[i] == 'I') {
                if (s[i + 1] == 'V') {
                    ret += 4;
                    ++i;
                } else if (s[i + 1] == 'X') {
                    ret += 9;
                    ++i;
                } else {
                    ret += 1;
                }
            } else if (s[i] == 'V') {
                ret += 5;
            } else if (s[i] == 'X') {
                if (s[i + 1] == 'L') {
                    ret += 40;
                    ++i;
                }
                else if (s[i + 1] == 'C') {
                    ret += 90;
                    ++i;
                }
                else {
                    ret += 10;
                }
            } else if (s[i] == 'L') {
                ret += 50;
            } else if (s[i] == 'C') {
                if (s[i + 1] == 'D') {
                    ret += 400;
                    ++i;
                }
                else if (s[i + 1] == 'M') {
                    ret += 900;
                    ++i;
                }
                else {
                    ret += 100;
                }
            } else if (s[i] == 'D') {
                ret += 500;
            } else {
                ret += 1000;
            }
        } else if (s[i] == 'I') {
            ret += 1;
        } else if (s[i] == 'V') {
            ret += 5;
        } else if (s[i] == 'X') {
            ret += 10;
        } else if (s[i] == 'L') {
            ret += 50;
        } else if (s[i] == 'C') {
            ret += 100;
        } else if (s[i] == 'D') {
            ret += 500;
        } else {
            ret += 1000;
        }
    }
    return ret;
}

int RomanToInt::Solution2(std::string s) {
    int n = s.size();
    int *ss = new int[n];
    for (int i = 0; i < n; ++i) {
        switch (s[i]) {
        case 'I': {
            ss[i] = 1; 
            break;
        }
        case 'V': {
            ss[i] = 5;
            break;
        }
        case 'X': {
            ss[i] = 10;
            break;
        }
        case 'L': {
            ss[i] = 50;
            break;
        }
        case 'C': {
            ss[i] = 100;
            break;
        }
        case 'D': {
            ss[i] = 500;
            break;
        }
        case 'M': {
            ss[i] = 1000;
            break;
        }
        default:
            break;
        }
    }

    int ret = ss[0];
    for (int i = 1; i < n; ++i) {
        if (ss[i - 1] < ss[i]) {
            ret -= 2 * ss[i - 1];
        } 
        ret += ss[i];
    }

    delete[] ss;
    return ret;
}

int RomanToInt::Solution3(std::string s) {
    int n = s.size();
    int m = n - 1, ret = 0;
    for (int i = 0; i < n; ++i) {
        int v = symbols_value_[s[i]];
        if (i < m && v < symbols_value_[s[i + 1]]) {
            ret -= v;
        } else {
            ret += v;
        }
    }
    return ret;
}

} // namespace str
} // namespace leetcode 

