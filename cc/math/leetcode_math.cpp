#include <iostream>
#include <string>
#include <random>

#include <benchmark/benchmark.h>

#include "leetcode_math.h"

namespace leetcode {
namespace math {

void MathSolution(int pid) {
    LeetcodeSolution *solution = nullptr;
	switch (pid) {
		case IS_PALINDROME: solution = new IsPalindrome(); break;
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
	return "9. ������\n";
}

std::string IsPalindrome::Problem() {
	return 
        "����һ������ x����� x ��һ���������������� true�����򣬷��� false��\n"
        "��������ָ���򣨴������ң��͵��򣨴������󣩶�����һ�������������磬121 �ǻ��ģ��� 123 ���ǡ�\n";
}

std::string IsPalindrome::Link() {
	return "https://leetcode-cn.com/problems/palindrome-number/";
}

std::string IsPalindrome::Solution() {
	return "��תһ�����֣�ʱ�䣺O(n)���ռ䣺O(1)��\n";
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
    // �ҳ����λ��
    while (x / div >= 10) {
        div *= 10;
    }
    while (x > 0) {
        // �ҳ���ͷ�Ƚ�
        int left = x / div;
        int right = x % 10;
        if (left != right) {
            return false;
        }
        // Ĩ����ͷ��׼����һ��
        x = (x % div) / 10;
        // Ĩ������λ����������100
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

} // namespace math
} // namespace leetcode