#include <iostream>
#include <string>
#include <random>
#include <climits>
#include <cmath>
#include <regex>

#include <benchmark/benchmark.h>

#include "leetcode_math.h"

namespace leetcode {
namespace math {

void MathSolution(int pid) {
    LeetcodeSolution *solution = nullptr;
	switch (pid) {
        case SolutionsId::IS_PALINDROME: solution = new IsPalindrome(); break;
        case SolutionsId::MY_SQRT: solution = new MySqrt(); break;
        case SolutionsId::IS_HAPPY: solution = new IsHappy(); break;
        case SolutionsId::ADD_DIGITS: solution = new AddDigits(); break;
        case SolutionsId::COMPLEX_NUMBER_MULTIPLY: solution = new ComplexNumberMultiply(); break;
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

    benchmark::RegisterBenchmark("BM_IsPalindrome_ToStringTwoPointers", [](benchmark::State &state, IsPalindrome solution, int x) {
        for (auto _ : state) {
            solution.Solution1(x);
        }
    }, solution, x);

    benchmark::RegisterBenchmark("BM_IsPalindrome_RevertHalf", [](benchmark::State &state, IsPalindrome solution, int x) {
        for (auto _ : state) {
            solution.Solution2(x);
        }
    }, solution, x);

    benchmark::RegisterBenchmark("BM_IsPalindrome_TwoPointers", [](benchmark::State &state, IsPalindrome solution, int x) {
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

std::string IsHappy::Title() {
    return "202. 快乐数\n";
}

std::string IsHappy::Problem() {
    return 
        "编写一个算法来判断一个数 n 是不是快乐数。\n"
        "「快乐数」定义为：\n"
        "- 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。\n"
        "- 然后重复这个过程直到这个数变为 1，也可能是无限循环但始终变不到 1。\n"
        "- 如果这个过程结果为 1，那么这个数就是快乐数。\n"
        "如果 n 是快乐数就返回 true；不是，则返回 false。\n";
}

std::string IsHappy::Link() {
    return "https://leetcode-cn.com/problems/happy-number/";
}

std::string IsHappy::Solution() {
    return "快慢指针，时间：O(log n)，空间：O(1)。\n";
}

void IsHappy::Benchmark() {
    IsHappy solution;

    int n = INT_MAX;

    benchmark::RegisterBenchmark("BM_IsHappy_HashSet", [](benchmark::State &state, IsHappy solution, int n) {
        for (auto _ : state) {
            solution.Solution1(n);
        }
    }, solution, n);

    benchmark::RegisterBenchmark("BM_IsHappy_FloydCycleDetection", [](benchmark::State &state, IsHappy solution, int n) {
        for (auto _ : state) {
            solution.Solution2(n);
        }
    }, solution, n);

    benchmark::RegisterBenchmark("BM_IsHappy_Arithmetic", [](benchmark::State &state, IsHappy solution, int n) {
        for (auto _ : state) {
            solution.Solution3(n);
        }
    }, solution, n);
}

bool IsHappy::Solution1(int n) {
    std::unordered_set<int> seen;
    while (n != 1 && !seen.count(n)) {
        seen.insert(n);
        n = GetNext(n);
    }
    return n == 1;
}

bool IsHappy::Solution2(int n) {
    int slow = n, fast = GetNext(n);
    while (fast != 1 && slow != fast) {
        slow = GetNext(slow);
        fast = GetNext(GetNext(fast));
    }
    return fast == 1;
}

bool IsHappy::Solution3(int n) {
    while (n != 1 && !cycle_nums_.count(n)) {
        n = GetNext(n);
    }
    return n == 1;
}

int IsHappy::GetNext(int n) {
    int sum = 0;
    while (n > 0) {
        int d = n % 10;
        sum += d * d;
        n /= 10;
    }
    return sum;
}


std::string AddDigits::Title() {
    return "258. 各位相加\n";
}

std::string AddDigits::Problem() {
    return "给定一个非负整数 num，反复将各个位上的数字相加，直到结果为一位数。返回这个结果。\n";
}

std::string AddDigits::Link() {
    return "https://leetcode-cn.com/problems/add-digits/";
}

std::string AddDigits::Solution() {
    return "数学，时间：O(1)，空间：O(1)。\n";
}

void AddDigits::Benchmark() {
    AddDigits solution;

    int num = INT_MAX;

    benchmark::RegisterBenchmark("BM_AddDigits_Recursion", [](benchmark::State &state, AddDigits solution, int num) {
        for (auto _ : state) {
            solution.Solution1(num);
        }
    }, solution, num);;

    benchmark::RegisterBenchmark("BM_AddDigits_Loop", [](benchmark::State &state, AddDigits solution, int num) {
        for (auto _ : state) {
            solution.Solution2(num);
        }
    }, solution, num);;

    benchmark::RegisterBenchmark("BM_AddDigits_Math", [](benchmark::State &state, AddDigits solution, int num) {
        for (auto _ : state) {
            solution.Solution3(num);
        }
    }, solution, num);;
}

int AddDigits::Solution1(int num) {
    if (num / 10 == 0) {
        return num;
    }
    return Solution1(Solution1(num / 10) + num % 10);
}

int AddDigits::Solution2(int num) {
    while (num >= 10) {
        int sum = 0;
        while (num) {
            sum += num % 10;
            num /= 10;
        }
        num = sum;
    }
    return num;
}

int AddDigits::Solution3(int num) {
    return (num - 1) % 9 + 1;
}


std::string ComplexNumberMultiply::Title() {
    return "537. 复数乘法\n";
}

std::string ComplexNumberMultiply::Problem() {
    return 
        "复数可以用字符串表示，遵循 \"实部 + 虚部i\" 的形式，并满足下述条件：\n"
        "- 实部是一个整数，取值范围是 [-100, 100]\n"
        "- 虚部也是一个整数，取值范围是 [-100, 100]\n"
        "- i^2 == -1\n"
        "给你两个字符串表示的复数 num1 和 num2，请你遵循复数表示形式，返回表示它们乘积的字符串。\n";
}

std::string ComplexNumberMultiply::Link() {
    return "https://leetcode-cn.com/problems/complex-number-multiplication/";
}

std::string ComplexNumberMultiply::Solution() {
    return "遍历，时间：O(n+m)，空间：O(1)。\n";
}

void ComplexNumberMultiply::Benchmark() {
    ComplexNumberMultiply solution;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1000, 1000);
    int real1 = dis(gen), imag1 = dis(gen);
    int real2 = dis(gen), imag2 = dis(gen);
    std::string num1 = std::to_string(real1) + "+" + std::to_string(imag1);
    std::string num2 = std::to_string(real2) + "+" + std::to_string(imag2);

    auto func1 = [](benchmark::State &state, ComplexNumberMultiply solution, std::string num1, std::string num2) {
        for (auto _ : state) {
            solution.Solution1(num1, num2);
        }
    };
    benchmark::RegisterBenchmark("BM_ComplexNumberMultiply_Traversal", func1, solution, num1, num2);

    auto func2 = [](benchmark::State &state, ComplexNumberMultiply solution, std::string num1, std::string num2) {
        for (auto _ : state) {
            solution.Solution2(num1, num2);
        }
    };
    benchmark::RegisterBenchmark("BM_ComplexNumberMultiply_Regex", func2, solution, num1, num2);
}

std::string ComplexNumberMultiply::Solution1(std::string num1, std::string num2) {
    int a, b, c, d;
    int n = num1.size(), m = num2.size();
    for (int i = 0; i < n; ++i) {
        if (num1[i] == '+') {
            a = std::atoi(num1.substr(0, i).c_str());
            b = std::atoi(num1.substr(i + 1, n - i - 2).c_str());
            break;
        }
    }
    for (int j = 0; j < m; ++j) {
        if (num2[j] == '+') {
            c = std::atoi(num2.substr(0, j).c_str());;
            d = std::atoi(num2.substr(j + 1, m - j - 2).c_str());
            break;
        }
    }
    return std::to_string((a * c - b * d)) + "+" + std::to_string(a * d + b * c) + "i";
}

std::string ComplexNumberMultiply::Solution2(std::string num1, std::string num2) {
    std::regex re("\\+|i");
    std::vector<std::string> complex1(
        std::sregex_token_iterator(num1.begin(), num1.end(), re, -1), std::sregex_token_iterator());
    std::vector<std::string> complex2(
        std::sregex_token_iterator(num2.begin(), num2.end(), re, -1), std::sregex_token_iterator());
    int real1 = std::stoi(complex1[0]);
    int imag1 = std::stoi(complex1[1]);
    int real2 = std::stoi(complex2[0]);
    int imag2 = std::stoi(complex2[1]);
    return std::to_string(real1 * real2 - imag1 * imag2) + "+" + std::to_string(real1 * imag2 + real2 * imag1) + "i";
}


} // namespace math
} // namespace leetcode