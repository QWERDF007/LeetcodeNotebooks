#include <iostream>
#include <string>
#include <random>
#include <climits>
#include <cmath>

#include <benchmark/benchmark.h>

#include "leetcode_math.h"

namespace leetcode {
namespace math {

void MathSolution(int pid) {
    LeetcodeSolution *solution = nullptr;
	switch (pid) {
		case IS_PALINDROME: solution = new IsPalindrome(); break;
        case MY_SQRT: solution = new MySqrt(); break;
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

std::string IsPalindrome::Title() {
	return "9. 回文数\n";
}

std::string IsPalindrome::Problem() {
	return 
        "给你一个整数 x，如果 x 是一个回文整数，返回 true；否则，返回 false。\n"
        "回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。例如，121 是回文，而 123 不是。\n";
}

std::string IsPalindrome::Link() {
	return "https://leetcode-cn.com/problems/palindrome-number/";
}

std::string IsPalindrome::Solution() {
	return "反转一半数字，时间：O(n)，空间：O(1)。\n";
}

void IsPalindrome::Benchmark() {
    IsPalindrome solution;
    
    int x = INT_MAX;

    benchmark::RegisterBenchmark("BM_IsPalindrome_ToStringDualPointer", [](benchmark::State &state, IsPalindrome solution, int x) {
        for (auto _ : state) {
            solution.Solution1(x);
        }
    }, solution, x);

    benchmark::RegisterBenchmark("BM_IsPalindrome_RevertHalf", [](benchmark::State &state, IsPalindrome solution, int x) {
        for (auto _ : state) {
            solution.Solution2(x);
        }
    }, solution, x);

    benchmark::RegisterBenchmark("BM_IsPalindrome_DualPointer", [](benchmark::State &state, IsPalindrome solution, int x) {
        for (auto _ : state) {
            solution.Solution3(x);
        }
    }, solution, x);

    benchmark::RegisterBenchmark("BM_IsPalindrome_ToStringAndReverseString", [](benchmark::State &state, IsPalindrome solution, int x) {
        for (auto _ : state) {
            solution.Solution4(x);
        }
    }, solution, x);
}

bool IsPalindrome::Solution1(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }
    std::string s = std::to_string(x);
    int left = 0, right = s.size() - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        ++left;
        --right;
    }
    return true;
}

bool IsPalindrome::Solution2(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }
    int reverted_number = 0;
    while (x > reverted_number) {
        reverted_number = reverted_number * 10 + x % 10;
        x /= 10;
    }
    return x == reverted_number || x == reverted_number / 10;
}

bool IsPalindrome::Solution3(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }
    int div = 1;
    // 找出最大位数
    while (x / div >= 10) {
        div *= 10;
    }
    while (x > 0) {
        // 找出两头比较
        int left = x / div;
        int right = x % 10;
        if (left != right) {
            return false;
        }
        // 抹掉两头，准备下一次
        x = (x % div) / 10;
        // 抹掉了两位，除数除以100
        div /= 100;
    }
    return true;
}

bool IsPalindrome::Solution4(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }
    std::string s = std::to_string(x);
    std::string reversed_s = std::to_string(x);
    std::reverse(reversed_s.begin(), reversed_s.end());
    return s == reversed_s;
}

std::string MySqrt::Title() {
    return "69. x 的平方根\n";
}

std::string MySqrt::Problem() {
    return 
        "给你一个非负整数 x，计算并返回 x 的算术平方根。\n"
        "由于返回类型是整数，结果只保留整数部分，小数部分将被舍去 。\n"
        "注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。\n";
}

std::string MySqrt::Link() {
    return "https://leetcode-cn.com/problems/sqrtx/";
}

std::string MySqrt::Solution() {
    return "牛顿迭代法，时间：O(log x)，空间：O(1)。\n";
}

void MySqrt::Benchmark() {
    MySqrt solution;

    int x = INT_MAX;

    benchmark::RegisterBenchmark("BM_MySqrt_BruteForceSearch", [](benchmark::State &state, MySqrt solution, int x) {
        for (auto _ : state) {
            solution.Solution1(1);
        }
    }, solution, x);

    benchmark::RegisterBenchmark("BM_MySqrt_BinarySearch", [](benchmark::State &state, MySqrt solution, int x) {
        for (auto _ : state) {
            solution.Solution2(1);
        }
    }, solution, x);

    benchmark::RegisterBenchmark("BM_MySqrt_Newton'sMethod", [](benchmark::State &state, MySqrt solution, int x) {
        for (auto _ : state) {
            solution.Solution3(1);
        }
    }, solution, x);

    benchmark::RegisterBenchmark("BM_MySqrt_ExponentLogarithm", [](benchmark::State &state, MySqrt solution, int x) {
        for (auto _ : state) {
            solution.Solution4(1);
        }
    }, solution, x);
}

int MySqrt::Solution1(int x) {
    long long k = 1;
    while (k * k <= x) {
        ++k;
    }
    return k - 1;
}

int MySqrt::Solution2(int x) {
    int left = 0, right = x, k = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if ((long long)mid * mid <= x) {
            k = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return k;
}

int MySqrt::Solution3(int x) {
    if (x == 0) {
        return 0;
    }
    double C = x, x0 = x;
    while (true) {
        double xi = 0.5 * (x0 + C / x0);
        if (fabs(xi - x0) < 1e-6) {
            break;
        }
        x0 = xi;
    }
    return int(x0);
}

int MySqrt::Solution4(int x) {
    if (x == 0) {
        return 0;
    }
    int k = exp(0.5 * log(x));
    return (long long)(k + 1) * (k + 1) <= x ? k + 1 : k;
}

} // namespace math
} // namespace leetcode