#include <set>
#include <climits>
#include <iostream>
#include <functional>
#include <random>
#include <unordered_set>
#include <benchmark/benchmark.h>

#include "str.h"


namespace leetcode {
namespace str {


void StrSolution(SolutionsId pid) {
    LeetcodeSolution *solution = nullptr;
    switch (pid) {
        case SolutionsId::ROMAN_TO_INT: solution = new RomanToInt(); break;
        case SolutionsId::ADD_BINARY: solution = new AddBinary(); break;
        case SolutionsId::CONVERT_TO_TITLE: solution = new ConvertToTitle(); break;
        case SolutionsId::LONGEST_PALINDROME: solution = new LongestPalindrome(); break;
        case SolutionsId::FIND_RESTAURANT: solution = new FindRestaurant(); break;
        case SolutionsId::LONGEST_WORD: solution = new LongestWord(); break;
        case SolutionsId::COMMON_CHARS: solution = new CommonChars(); break;
        case SolutionsId::MAX_NUMBER_OF_BALLONS: solution = new MaxNumberOfBallons(); break;
        case SolutionsId::MAX_POWER: solution = new MaxPower(); break;
        case SolutionsId::SECOND_HIGHEST: solution = new SecondHighest(); break;
        case SolutionsId::PLATES_BETWEEN_CANDLES: solution = new PlatesBetweenCandles(); break;
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


std::string ConvertToTitle::Title() {
    return "168. Excel表列名称\n";
}

std::string ConvertToTitle::Problem() {
    return
        "给你一个整数 columnNumber ，返回它在 Excel 表中相对应的列名称。\n"
        "A -> 1\n"
        "B -> 2\n"
        "...\n"
        "AB -> 28\n";
}

std::string ConvertToTitle::Link() {
    return "https://leetcode-cn.com/problems/excel-sheet-column-title/";
}

std::string ConvertToTitle::Solution() {
    return "数学，时间：O(log26C)，空间：O(1)。\n";
}

void ConvertToTitle::Benchmark() {
    ConvertToTitle solution;

    int column_number = 123456789;

    benchmark::RegisterBenchmark("BM_ConvertToTitle_Arithmetic", [](benchmark::State& state, ConvertToTitle solution, int column_number) {
        for (auto _ : state) {
            solution.Solution1(column_number);
        }
    }, solution, column_number);

    benchmark::RegisterBenchmark("BM_ConvertToTitle_Borrow", [](benchmark::State& state, ConvertToTitle solution, int column_number) {
        for (auto _ : state) {
            solution.Solution2(column_number);
        }
    }, solution, column_number);
}

std::string ConvertToTitle::Solution1(int columnNumber) {
    std::string ans;
    while (columnNumber > 0) {
        --columnNumber;
        ans += columnNumber % 26 + 'A';
        columnNumber /= 26;
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

std::string ConvertToTitle::Solution2(int columnNumber) {
    std::string ans;
    while (columnNumber > 0) {
        int remainder = columnNumber % 26;
        if (remainder == 0) {
            remainder = 26;
            columnNumber -= 26;
        }
        ans.push_back(remainder + 64); // 'A' 的前一位，因为 remainder 的值域为 [1,26]
        columnNumber /= 26;
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}


std::string LongestPalindrome::Title() {
    return "409. 最长回文串\n";
}

std::string LongestPalindrome::Problem() {
    return 
        "给定一个包含大写字母和小写字母的字符串 s，返回 通过这些字母构造成的最长的回文串。\n"
        "在构造过程中，请注意区分大小写。比如 \"Aa\" 不能当做一个回文字符串。\n";
}

std::string LongestPalindrome::Link() {
    return "https://leetcode-cn.com/problems/longest-palindrome/";
}

std::string LongestPalindrome::Solution() {
    return "数组统计，时间：O(n)，空间：O(k)，k=52。\n";
}

void LongestPalindrome::Benchmark() {
    LongestPalindrome solution;

    std::string table = "ABCDEABCDEFGHIJKLMNOPQRSTUVWXYZabcdeabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, table.size() - 1);
    constexpr int n = 20000;
    std::string s;
    for (int i = 0; i < n; ++i) {
        s += table[dis(gen)];
    }

    benchmark::RegisterBenchmark("BM_LongestPalindrome_StatsArray", [](benchmark::State &state, LongestPalindrome solution, std::string s) {
        for (auto _ : state) {
            solution.Solution1(s);
        }
    }, solution, s);

    benchmark::RegisterBenchmark("BM_LongestPalindrome_StatsHashMap", [](benchmark::State &state, LongestPalindrome solution, std::string s) {
        for (auto _ : state) {
            solution.Solution2(s);
        }
    }, solution, s);
}

int LongestPalindrome::Solution1(std::string s) {
    int counts[52] = { 0 };
    for (char c : s) {
        if (c >= 'a' && c <= 'z') {
            ++counts[c - 'a' + 26];
        }
        else {
            ++counts[c - 'A'];
        }
    }
    int cnt = 0;
    for (int count : counts) {
        cnt += count / 2 * 2;
    }
    return cnt < s.size() ? cnt + 1 : cnt;
}

int LongestPalindrome::Solution2(std::string s) {
    std::unordered_map<char, int> counts;
    for (char c : s) {
        ++counts[c];
    }
    int cnt = 0;
    for (auto p : counts) {
        cnt += p.second / 2 * 2;
    }
    return cnt < s.size() ? cnt + 1 : cnt;
}


std::string FindRestaurant::Title() {
    return "599. 两个列表的最小索引总和\n";
}

std::string FindRestaurant::Problem() {
    return 
        "假设 Andy 和 Doris 想在晚餐时选择一家餐厅，并且他们都有一个表示最喜爱餐厅的列表，每个餐厅的名字用字符串表示。\n"
        "你需要帮助他们用最少的索引和找出他们共同喜爱的餐厅。如果答案不止一个，则输出所有答案并且不考虑顺序。你可以假设答案总是存在。\n";
}

std::string FindRestaurant::Link() {
    return "https://leetcode-cn.com/problems/minimum-index-sum-of-two-lists/";
}

std::string FindRestaurant::Solution() {
    return "哈希表，时间：O(n+m)，空间：O(min(n,m))。\n";
}

void FindRestaurant::Benchmark() {
    FindRestaurant solution;

    std::vector<std::string> list1{
        "eecba","dcddd","cceac","adbde","bbbdd","baaed","abdcc","cedbe","aedcd","ddeec","aceda","cddcc","dbbdb","babca","abcbc",
        "bcddd","acbbb","edcee","abcdc","dbeeb","bebdb","eeedc","bdede","aeeea","cecec","bdcbb","caeda","cbdcd","ddcbe","bbdbd",
        "acccb","eecdd","abbee","ebbde","beead","ebaae","dadbc","cabdc","cbcda","aeedb","ceead","dbbee","ebdac","beadb","ceabe",
        "ddbad","adcbc","eaadb","dcbdd","badcd","edebd","KFC"
    };

    std::vector<std::string> list2{
        "dcddd","cceac","aaecb","bcbea","deecd","adbde","bbbdd","aedcd","aedda","eacbd","dbbdb","babca","abcbc","bcddd","cbedb",
        "edcee","abcdc","beacc","cdceb","bebdb","deadb","cecec","bdcbb","bbedc","bbdbd","acccb","edbee","eecdd","accad","cceea",
        "ebaae","cbbbd","cabdc","cbcda","ceedb","ceead","beadb","baccd","aaaab","caeca","eddab","edebd","bccec","KFC"
    };

    auto brute_func = [](benchmark::State &state, FindRestaurant solution, std::vector<std::string> list1, std::vector<std::string> list2) {
        for (auto _ : state) {
            solution.Solution1(list1, list2);
        }
    };
    benchmark::RegisterBenchmark("BM_FindRestaurant_BruteForceSearch", brute_func, solution, list1, list2);

    auto hashmap_func = [](benchmark::State &state, FindRestaurant solution, std::vector<std::string> list1, std::vector<std::string> list2) {
        for (auto _ : state) {
            solution.Solution2(list1, list2);
        }
    };
    benchmark::RegisterBenchmark("BM_FindRestaurant_HashMap", hashmap_func, solution, list1, list2);
}

std::vector<std::string> FindRestaurant::Solution1(std::vector<std::string> &list1, std::vector<std::string> &list2) {
    std::vector<std::string> ans;
    int n = list1.size(), m = list2.size();
    int min_sum = INT_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (list1[i] == list2[j]) {
                int sum = i + j;
                if (sum == min_sum) {
                    ans.emplace_back(list1[i]);
                } else if (sum < min_sum) {
                    min_sum = sum;
                    if (!ans.empty()) {
                        ans.clear();
                    }
                    ans.emplace_back(list1[i]);
                }
            }
        }
    }
    return ans;
}

std::vector<std::string> FindRestaurant::Solution2(std::vector<std::string> &list1, std::vector<std::string> &list2) {
    if (list1.size() > list2.size()) {
        return Solution2(list2, list1);
    }

    int n = list1.size(), m = list2.size();
    int min_sum = INT_MAX;
    std::unordered_map<std::string, int> map;
    for (int i = 0; i < n; ++i) {
        map.emplace(list1[i], i);
    }

    std::vector<std::string> ans;
    for (int j = 0; j < m; ++j) {
        if (map.count(list2[j])) {
            int sum = map[list2[j]] + j;
            if (sum < min_sum) {
                min_sum = sum;
                if (!ans.empty()) {
                    ans.clear();
                }
                ans.emplace_back(list2[j]);
            } else if (sum == min_sum) {
                ans.emplace_back(list2[j]);
            }
        }
    }

    return ans;
}


std::string LongestWord::Title() {
    return "720. 词典中最长的单词\n";
}

std::string LongestWord::Problem() {
    return 
        "给出一个字符串数组 words 组成的一本英语词典。返回 words 中最长的一个单词，该单词是由 words 词典中其他单词逐步添加一个字母组成。\n"
        "若其中有多个可行的答案，则返回答案中字典序最小的单词。若无答案，则返回空字符串。\n";
}

std::string LongestWord::Link() {
    return "https://leetcode-cn.com/problems/longest-word-in-dictionary/";
}

std::string LongestWord::Solution() {
    return "字典树，时间：O(nm)，空间：O(nm)，n 为数组长度，m 为字符串平均长度。\n";
}

void LongestWord::Benchmark() {
    LongestWord solution;

    int n = 1000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(97, 122);
    std::vector<std::string> words;
    for (int i = 0; i < 1000; ++i) {
        int v = dis(gen);
        int len = v % 30;
        std::string word = "";
        for (int j = 0; j < len; ++j) {
            word += static_cast<char>(dis(gen));
        }
        words.emplace_back(word);
    }

    benchmark::RegisterBenchmark("BM_LongestWord_SortHashSet", [](benchmark::State &state, LongestWord solution, std::vector<std::string> words) {
        for (auto _ : state) {
            solution.Solution1(words);
        }
    }, solution, words);

    benchmark::RegisterBenchmark("BM_LongestWord_Trie", [](benchmark::State &state, LongestWord solution, std::vector<std::string> words) {
        for (auto _ : state) {
            solution.Solution2(words);
        }
    }, solution, words);
}


std::string LongestWord::Solution1(std::vector<std::string> &words) {
    // 对数字按长度升序、字典序降序排序
    std::sort(words.begin(), words.end(), [](const std::string &a, const std::string &b) {
        if (a.size() != b.size()) {
            return a.size() < b.size();
        } else {
            return a > b;
        }
    });
    std::string longest = "";
    std::unordered_set<std::string> set;
    set.emplace("");
    for (auto &word : words) {
        // 对排序后的数组，检查前缀是否在 set 中
        if (set.count(word.substr(0, word.size() - 1))) {
            longest = word;
            set.emplace(word);
        }
    }
    return longest;
}

std::string LongestWord::Solution2(std::vector<std::string> &words) {
    return "字典树，TODO。\n";
}



std::string CommonChars::Title() {
    return "1002. 查找共用字符\n";
}

std::string CommonChars::Problem() {
    return 
        "给你一个字符串数组 words，请你找出所有在 words 的每个字符串中都出现的共用字符（ 包括重复字符），并以数组形式返回。你可以按任意顺序返回答案。\n";
}

std::string CommonChars::Link() {
    return "https://leetcode-cn.com/problems/find-common-characters/";
}

std::string CommonChars::Solution() {
    return "统计，时间：O(n(m+k))，空间：O(k)。m 为平均字符串长度，k=26 为小写字母数。\n";
}

void CommonChars::Benchmark() {
    CommonChars solution;
    int n = 100;
    std::vector<std::string> words(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    for (int i = 0; i < n; ++i) {
        int len = dis(gen);
        for (int j = 0; j < len; ++j) {
            int num = dis(gen);
            words[i] += 'a' + num % 26;
        }
    }

    benchmark::RegisterBenchmark("BM_CommonChars_Stats", [](benchmark::State &state, CommonChars solution, std::vector<std::string> words) {
        for (auto _ : state) {
            solution.Solution1(words);
        }
    }, solution, words);
}

std::vector<std::string> CommonChars::Solution1(std::vector<std::string> &words) {
    int n = words.size();
    std::vector<int> min_freq(26, INT_MAX);
    std::vector<int> freq(26);
    for (const std::string &word : words) {
        std::fill(freq.begin(), freq.end(), 0);
        for (char c : word) {
            ++freq[c - 'a'];
        }
        for (int i = 0; i < 26; ++i) {
            min_freq[i] = std::min(min_freq[i], freq[i]);
        }
    }
    std::vector<std::string> ans;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < min_freq[i]; ++j) {
            ans.emplace_back(std::string(1, 'a' + i));
        }
    }
    return ans;
}

std::string MaxNumberOfBallons::Title() {
    return "1189. “气球” 的最大数量\n";
}

std::string MaxNumberOfBallons::Problem() {
    return 
        "给你一个字符串 text，你需要使用 text 中的字母来拼凑尽可能多的单词 balloon（气球）。\n"
        "字符串 text 中的每个字母最多只能被使用一次。请你返回最多可以拼凑出多少个单词 balloon。\n";
}

std::string MaxNumberOfBallons::Link() {
    return "https://leetcode-cn.com/problems/maximum-number-of-balloons/";
}

std::string MaxNumberOfBallons::Solution() {
    return "统计，时间：O(n)，空间：O(1)。\n";
}

void MaxNumberOfBallons::Benchmark() {
    MaxNumberOfBallons solution;
    int n = 10000;
    std::string table = "0123456789abcdeabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, table.size() - 1);
    std::string text;
    for (int i = 0; i < n; ++i) {
        text += table[dis(gen)];
    }

    benchmark::RegisterBenchmark("BM_MaxNumberOfBallons_Stats", [](benchmark::State &state, MaxNumberOfBallons solution, std::string text) {
        for (auto _ : state) {
            solution.Solution1(text);
        }
    }, solution, text);
}

int MaxNumberOfBallons::Solution1(std::string text) {
    int counts[5] = { 0 };
    for (char c : text) {
        switch (c) {
            case 'b': counts[0] += 2; break;
            case 'a': counts[1] += 2; break;
            case 'l': counts[2] += 1; break;
            case 'o': counts[3] += 1; break;
            case 'n': counts[4] += 2; break;
            default: break;
        }
    }
    int m = INT_MAX;
    for (int count : counts) {
        if (count < m) {
            m = count;
        }
    }
    return m / 2;
}

std::string MaxPower::Title() {
    return "1446. 连续字符\n";
}

std::string MaxPower::Problem() {
    return
        "给你一个字符串 s，字符串的「能量」定义为：只包含一种字符的最长非空子字符串的长度。\n"
        "请你返回字符串的能量。\n";
}

std::string MaxPower::Link() {
    return "https://leetcode-cn.com/problems/consecutive-characters/";
}

std::string MaxPower::Solution() {
    return "双指针，时间：O(n)，空间：O(1)。\n";
}

void MaxPower::Benchmark() {
    MaxPower solution;

    int n = 1000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis('a', 'z');
    std::string s;
    for (int i = 0; i < n; ++i) {
        s += static_cast<char>(dis(gen));
    }

    benchmark::RegisterBenchmark("BM_MaxPower_TwoPointers", [](benchmark::State &state, MaxPower solution, std::string s) {
        for (auto _ : state) {
            solution.Solution1(s);
        }
    }, solution, s);
}

int MaxPower::Solution1(std::string s) {
    int n = s.size();
    int m = 1, c = 1;
    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i - 1]) {
            ++c;
            if (c > m) {
                m = c;
            }
        }
        else {
            c = 1;
        }
    }
    return m;
}


std::string SecondHighest::Title() {
    return "1796. 字符串中第二大的数字\n";
}

std::string SecondHighest::Problem() {
    return 
        "给你一个混合字符串 s，请你返回 s 中第二大的数字，如果不存在第二大的数字，请你返回 -1。\n"
        "混合字符串由小写英文字母和数字组成。\n";
}

std::string SecondHighest::Link() {
    return "https://leetcode-cn.com/problems/second-largest-digit-in-a-string/";
}

std::string SecondHighest::Solution() {
    return "有限变量遍历，时间：O(n)，空间：O(1)。\n";
}

void SecondHighest::Benchmark() {
    SecondHighest solution;

    std::string table = "0123456789abcdeabcdefghijklmnopqrstuvwxyz";
    int n = 10000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, table.size() - 1);
    
    std::string s;
    for (int i = 0; i < n; ++i) {
        s += table[dis(gen)];
    }

    benchmark::RegisterBenchmark("BM_SecondHighest_LimitedVars", [](benchmark::State &state, SecondHighest solution, std::string s) {
        for (auto _ : state) {
            solution.Solution1(s);
        }
    }, solution, s);

    benchmark::RegisterBenchmark("BM_SecondHighest_SortedSet", [](benchmark::State& state, SecondHighest solution, std::string s) {
        for (auto _ : state) {
            solution.Solution2(s);
        }
    }, solution, s);

    benchmark::RegisterBenchmark("BM_SecondHighest_Sort", [](benchmark::State& state, SecondHighest solution, std::string s) {
        for (auto _ : state) {
            solution.Solution3(s);
        }
    }, solution, s);
}

int SecondHighest::Solution1(std::string s) {
    int a = -1, b = -1;
    for (char c : s) {
        if (c <= '9') {
            int num = c - '0';
            if (num > a) {
                b = a;
                a = num;
            } else if (a > num && num > b) {
                b = num;
            }
        }
    }
    return b;
}

int SecondHighest::Solution2(std::string s) {
    std::set<int> set;
    for (char c : s) {
        if (c <= '9') {
            set.insert(c - '0');
            if (set.size() > 2) {
                set.erase(set.begin());
            }
        }
    }
    return set.size() == 2 ? *set.begin() : -1;
}

int SecondHighest::Solution3(std::string s) {
    std::string s_num;
    for (char c : s) {
        if (c <= '9') {
            s_num += c;
        }
    }
    std::sort(s_num.begin(), s_num.end(), std::greater<>());
    int n = s_num.size();
    for (int i = 1; i < n; ++i) {
        if (s_num[i] != s_num[i - 1]) {
            return s_num[i] - '0';
        }
    }
    return -1;
}


std::string PlatesBetweenCandles::Title() {
    return "2055. 蜡烛之间的盘子\n";
}

std::string PlatesBetweenCandles::Problem() {
    return 
        "给你一个长桌子，桌子上盘子和蜡烛排成一列。给你一个下标从 0 开始的字符串 s，它只包含字符 '*' 和 '|'，其中 '*' 表示一个盘子，'|' 表示一支蜡烛。\n"
        "同时给你一个下标从 0 开始的二维整数数组 queries，其中 queries[i] = [lefti, righti] 表示子字符串 s[lefti...righti]（包含左右端点的字符）。\n"
        "你需要找到子字符串中在两支蜡烛之间的盘子的数目 。如果一个盘子在子字符串中左边和右边都至少有一支蜡烛，那么这个盘子满足在两支蜡烛之间。\n"
        "- 比方说，s = \"||**||**|*\"，查询 [3, 8]，表示的是子字符串 \"*||**|\" 。\n"
        "  子字符串中在两支蜡烛之间的盘子数目为 2，子字符串中右边两个盘子在它们左边和右边都至少有一支蜡烛。\n"
        "请你返回一个整数数组 answer，其中 answer[i] 是第 i 个查询的答案。\n";
}

std::string PlatesBetweenCandles::Link() {
    return "https://leetcode-cn.com/problems/plates-between-candles/";
}

std::string PlatesBetweenCandles::Solution() {
    return "前缀和，时间：O(n+q)，空间：O(n)，n 为字符串长度，q 为 queries 的长度。\n";
}

void PlatesBetweenCandles::Benchmark() {
    PlatesBetweenCandles solution;

    int n = 1e5;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, n);

    std::string s;
    for (int i = 0; i < n; ++i) {
        int v = dis(gen);
        if (v % 3 == 0) {
            s.push_back('*');
        } else {
            s.push_back('|');
        }
    }

    int m = 1e4;
    std::vector<std::vector<int>> queries(m+1, std::vector<int>(2));
    for (int i = 0; i <= m; ++i) {
        int left = dis(gen);
        int right = dis(gen);
        while (right < left) {
            right = dis(gen);
        }
        queries[i][0] = left;
        queries[i][1] = right;
    }

    auto func_presum = [](benchmark::State &state, PlatesBetweenCandles solution, std::string s, std::vector<std::vector<int>> queries) {
        for (auto _ : state) {
            solution.Solution1(s, queries);
        }
    };
    benchmark::RegisterBenchmark("BM_PlatesBetweenCandles_PreSum", func_presum, solution, s, queries);

    auto func_runtime = [](benchmark::State &state, PlatesBetweenCandles solution, std::string s, std::vector<std::vector<int>> queries) {
        for (auto _ : state) {
            solution.Solution2(s, queries);
        }
    };
    benchmark::RegisterBenchmark("BM_PlatesBetweenCandles_Runtime", func_runtime, solution, s, queries);
}

std::vector<int> PlatesBetweenCandles::Solution1(std::string s, std::vector<std::vector<int>> &queries) {
    int n = s.length();
    std::vector<int> presum(n);
    for (int i = 0, sum = 0; i < n; ++i) {
        if (s[i] == '*') {
            ++sum;
        }
        presum[i] = sum;
    }
    std::vector<int> left(n), right(n);
    for (int i = 0, l = -1, r = -1; i < n; ++i) {
        if (s[i] == '|') {
            l = i;
        }
        left[i] = l;
        int j = n - 1 - i;
        if (s[j] == '|') {
            r = j;
        }
        right[j] = r;
    }
    std::vector<int> ans;
    for (auto &query : queries) {
        int x = right[query[0]]; // 区间内最左侧的蜡烛
        int y = left[query[1]];  // 区间内最右侧的蜡烛
        ans.emplace_back(x == -1 || y == -1 || x >= y ? 0 : presum[y] - presum[x]);
    }
    return ans;
}

std::vector<int> PlatesBetweenCandles::Solution2(std::string s, std::vector<std::vector<int>> &queries) {
    std::vector<int> ans;
    for (auto &query : queries) {
        int start = query[0];
        int end = query[1];
        int count = 0;
        while (start <= end && s[start] != '|') {
            ++start;
        }
        while (start <= end && s[end] != '|') {
            --end;
        }
        for (int i = start; i <= end; ++i) {
            if (s[i] == '*') {
                ++count;
            }
        }
        ans.emplace_back(count);
    }
    return ans;
}



} // namespace str
} // namespace leetcode 

