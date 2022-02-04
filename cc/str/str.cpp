#include <iostream>
#include <benchmark/benchmark.h>

#include "str.h"












namespace leetcode {
namespace str {

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
                } else if (s[i + 1] == 'C') {
                    ret += 90;
                    ++i;
                } else {
                    ret += 10;
                }
            } else if (s[i] == 'L') {
                ret += 50;
            } else if (s[i] == 'C') {
                if (s[i + 1] == 'D') {
                    ret += 400;
                    ++i;
                } else if (s[i + 1] == 'M') {
                    ret += 900;
                    ++i;
                } else {
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


std::string AddBinary::Title() {
    return "67. 二进制求和\n";
}

std::string AddBinary::Problem() {
    return 
        "给你两个二进制字符串，返回它们的和（用二进制表示）。\n"
        "输入为非空字符串且只包含数字 1 和 0。\n";
}

std::string AddBinary::Link() {
    return "https://leetcode-cn.com/problems/add-binary/";
}

std::string AddBinary::Solution() {
    return "模拟列竖式，时间：O(n)，空间：O(1)。\n";
}

void AddBinary::Benchmark() {
    AddBinary solution;

    std::string a = "10100000100100110110010000010101111011011001101110111111111101000000101111001110001111100001101";
    std::string b = "110101001011101110001111100110001010100001101011101010000011011011001011101111001100000011011110011";

    benchmark::RegisterBenchmark("BM_AddBinary_Simulate", [](benchmark::State &state, AddBinary solution, std::string a, std::string b) {
        for (auto _ : state) {
            solution.Solution1(a, b);
        }
    }, solution, a, b);

    benchmark::RegisterBenchmark("BM_AddBinary_BitwiseOperation", [](benchmark::State& state, AddBinary solution, std::string a, std::string b) {
        for (auto _ : state) {
            solution.Solution2(a, b);
        }
    }, solution, a, b);
}

std::string AddBinary::Solution1(std::string a, std::string b) {
    std::string ans;
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    int m = a.size();
    int n = b.size();
    int i = 0, carry = 0;
    int p = std::max(m, n);
    while (i < p) {
        carry += i < m ? a[i] == '1' : 0;
        carry += i < n ? b[i] == '1' : 0;
        ans.push_back(carry % 2 ? '1' : '0');
        carry /= 2;
        ++i;
    }
    if (carry) {
        ans.push_back('1');
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

std::string AddBinary::Solution2(std::string a, std::string b) {
    std::string ans;
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    int m = a.size();
    int n = b.size();
    int i = 0, carry = 0, x = 0, y = 0;
    int p = std::max(m, n);
    while (i < p) {
        x = i < m ? a[i] == '1' : 0;
        y = i < n ? b[i] == '1' : 0;
        ans.push_back((x ^ y) ^ carry ? '1' : '0');
        carry = carry ? (carry & x | carry & y) : (x & y);
        ++i;
    }
    if (carry) {
        ans.push_back('1');
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}


void StrSolution(int pid) {
    LeetcodeSolution* solution = nullptr;
    switch (pid) {
    case ROMAN_TO_INT: {
        solution = new RomanToInt();
        break;
    }
    case ADD_BINARY: {
        solution = new AddBinary();
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

} // namespace str
} // namespace leetcode 

