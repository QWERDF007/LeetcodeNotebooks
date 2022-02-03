#pragma once

#include <string>
#include <unordered_map>

#include "leetcode_solution.h"

namespace leetcode {
namespace str {

void StrSolution(int pid);

class RomanToInt : public LeetcodeSolution {
public:
    std::string Title() override;

    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 暴力求解，列出所有情况
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * @param s 
     * @return int 
     */
    int Solution1(std::string s);

    /**
     * @brief 动态数组
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param s 
     * @return int 
     */
    int Solution2(std::string s);

    /**
     * @brief 哈希表
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     * @param s 
     * @return int 
     */
    int Solution3(std::string s);

    std::unordered_map<char, int> symbols_value_{
        {'I',1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000}
    };
};
    
} // namespace str
} // namespace leetcode 