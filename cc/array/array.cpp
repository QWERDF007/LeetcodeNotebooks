#include <ctime>
#include <random>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <benchmark/benchmark.h>

#include "array.h"









namespace leetcode {
namespace array{

std::string TwoSum::Title() {
    return "1.两数之和\n";
}

std::string TwoSum::Problem() {
    return
        "给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值 target 的那两个整数，并返回它们的数组下标。\n"
        "你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。\n"
        "你可以按任意顺序返回答案。\n";
}

std::string TwoSum::Link() {
    return "https://leetcode-cn.com/problems/two-sum/";
}

std::string TwoSum::Solution() {
    return "哈希表，时间：O(n)，空间：O(n)。\n";
}

void TwoSum::Benchmark() {
    TwoSum solution;

    int n = 10001;
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = i+1;
    }
    int target = 19999;

    benchmark::RegisterBenchmark("BM_TwoSum_BruteForceSearch", [](benchmark::State& state, TwoSum solution, std::vector<int> nums, int target) {
        for (auto _ : state) {
            solution.Solution1(nums, target);
        }
    }, solution, nums, target);

    benchmark::RegisterBenchmark("BM_TwoSum_HashMap", [](benchmark::State& state, TwoSum solution, std::vector<int> nums, int target) {
        for (auto _ : state) {
            solution.Solution2(nums, target);
        }
    }, solution, nums, target);
}

std::vector<int> TwoSum::Solution1(std::vector<int>& nums, int target) {
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                return { i,j };
            }

        }
    }
    return {};
}

std::vector<int> TwoSum::Solution2(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> hashtable;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        int d = target - nums[i];
        auto finded = hashtable.find(d);
        if (finded != hashtable.end()) {
            return { hashtable[d], i };
        }
        hashtable[nums[i]] = i;
    }
    return std::vector<int>();
}


std::string RemoveDuplicates::Title() {
    return "26. 删除有序数组中的重复项\n";
}

std::string RemoveDuplicates::Problem() {
    return 
        "给你一个有序数组 nums ，请你原地删除重复出现的元素，使每个元素只出现一次，返回删除后数组的新长度。\n"
        "不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。\n";
}

std::string RemoveDuplicates::Link() {
    return "https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/";
}

std::string RemoveDuplicates::Solution() {
    return "双指针，时间：O(n)，空间：O(1)。\n";
}

void RemoveDuplicates::Benchmark() {
    RemoveDuplicates solution;

    int n = 10001;
    std::vector<int> nums;
    std::srand(std::time(nullptr));
    for (int i = 0; i < n; ++i) {
        int m = std::rand() % 5; // [0,5) 随机数
        for (int j = 0; j < m; ++j) {
            nums.emplace_back(i);
        }
    }

    benchmark::RegisterBenchmark("BM_TwoSum_BruteForceSearch", [](benchmark::State& state, RemoveDuplicates solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution1(nums);
        }
    }, solution, nums);

    benchmark::RegisterBenchmark("BM_TwoSum_DoublePointers", [](benchmark::State& state, RemoveDuplicates solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution2(nums);
        }
    }, solution, nums);
}

int RemoveDuplicates::Solution1(std::vector<int>& nums) {
    int n = nums.size();
    int i = 1;
    while (i < n) {
        if (nums[i] == nums[i - 1]) {
            int j = i + 1;
            while (j < n) {
                nums[j - 1] = nums[j];
                ++j;
            }
            --n;
        }
        else {
            ++i;
        }
    }
    return n;
}

int RemoveDuplicates::Solution2(std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) {
        return 0;
    }
    int slow = 1, fast = 1;
    while (fast < n) {
        if (nums[fast] != nums[fast - 1]) {
            nums[slow] = nums[fast];
            ++slow;
        }
        ++fast;
    }
    return slow;
}

std::string MissingNumber::Title() {
    return "268. 丢失的数字\n";
}

std::string MissingNumber::Problem() {
    return 
        "给定一个包含 [0, n] 中 n 个数的数组 nums，找出 [0, n] 这个范围内没有出现在数组中的那个数。\n";
}

std::string MissingNumber::Link() {
    return "https://leetcode-cn.com/problems/missing-number/";
}

std::string MissingNumber::Solution() {
    return "数学，等差数列求和，减去数组中元素。时间：O(n)，空间：O(1)。\n";
}

void MissingNumber::Benchmark() {
    MissingNumber solution;

    int n = 1000000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n);
    int missing_num = dis(gen);
    std::vector<int> nums;
    for (int i = 0; i <= n; ++i) {
        if (i == missing_num) {
            continue;
        } else {
            nums.emplace_back(i);
        }
    }
    std::shuffle(nums.begin(), nums.end(), gen);

    benchmark::RegisterBenchmark("BM_MissingNumber_Sort", [](benchmark::State& state, MissingNumber solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution1(nums);
        }
    }, solution, nums);

    benchmark::RegisterBenchmark("BM_MissingNumber_HashSet", [](benchmark::State& state, MissingNumber solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution2(nums);
        }
    }, solution, nums);

    benchmark::RegisterBenchmark("BM_MissingNumber_Xor", [](benchmark::State& state, MissingNumber solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution3(nums);
        }
    }, solution, nums);

    benchmark::RegisterBenchmark("BM_MissingNumber_Arithmetic", [](benchmark::State& state, MissingNumber solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution4(nums);
        }
    }, solution, nums);
}

int MissingNumber::Solution1(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        if (i != nums[i]) {
            return i;
        }
    }
    return n;
}

int MissingNumber::Solution2(std::vector<int>& nums) {
    std::unordered_set<int> set;
    int n = nums.size();
    for (int& num : nums) {
        set.insert(num);
    }
    for (int i = 0; i < n; ++i) {
        if (!set.count(i)) {
            return i;
        }
    }
    return n;
}

int MissingNumber::Solution3(std::vector<int>& nums) {
    int n = nums.size();
    int ret = 0;
    for (int i = 0; i <= n; ++i) {
        ret ^= i;
    }
    for (int i = 0; i < n; ++i) {
        ret ^= nums[i];
    }
    return ret;
}

int MissingNumber::Solution4(std::vector<int>& nums) {
    int n = nums.size();
    int total = (n + 1) * n / 2, sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += nums[i];
    }
    return total - sum;
}


NumArray::NumArray(std::vector<int>& nums) : nums_(nums) {
    int n = nums.size();
    sums_.resize(n + 1);
    for (int i = 0; i < n; ++i) {
        sums_[i + 1] = sums_[i] + nums[i];
    }
}

std::string NumArray::Title() {
    return "303. 区域和检索 - 数组不可变\n";
}

std::string NumArray::Problem() {
    return
        "给定一个整数数组 nums，处理以下类型的多个查询：\n"
        "实现 NumArray 类：\n"
        "- NumArray(vector<int>& nums) 使用数组 nums 初始化对象\n"
        "- int sumRange(int i, int j)  返回数组 nums 中索引 left 和 right 之间的元素的总和 ，包含 left 和 right 两点\n";
}

std::string NumArray::Link() {
    return "https://leetcode-cn.com/problems/range-sum-query-immutable/";
}

std::string NumArray::Solution() {
    return "前缀和，时间：O(n) + m * O(right-left+1)，空间：O(n)。\n";
}

void NumArray::Benchmark() {
    int n = 10000;
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = i + 1;
    }
    int left = 3888, right = 9998;

    NumArray solution(nums);

    benchmark::RegisterBenchmark("BM_NumArray_RunTimeCalc", [](benchmark::State& state, NumArray solution, int left, int right) {
        for (auto _ : state) {
            solution.sumRange1(left, right);
        }
    }, solution, left, right);

    benchmark::RegisterBenchmark("BM_NumArray_PrefixSum", [](benchmark::State& state, NumArray solution, int left, int right) {
        for (auto _ : state) {
            solution.sumRange2(left, right);
        }
    }, solution, left, right);
}

int NumArray::sumRange1(int left, int right) {
    int sum = 0;
    for (int k = left; k <= right; ++k) {
        sum += nums_[k];
    }
    return sum;
}

int NumArray::sumRange2(int left, int right) {
    return sums_[right + 1] - sums_[left];
}


std::string Intersection::Title() {
    return "349. 两个数组的交集\n";
}

std::string Intersection::Problem() {
    return 
        "给定两个数组 nums1 和 nums2 ，返回它们的交集。输出结果中的每个元素一定是唯一的。我们可以不考虑输出结果的顺序。\n";
}

std::string Intersection::Link() {
    return "https://leetcode-cn.com/problems/intersection-of-two-arrays/";
}

std::string Intersection::Solution() {
    return "哈希集合，时间：O(n+m)，空间：O(n+m)。\n";
}

void Intersection::Benchmark() {
    Intersection solution;

    int n = 10000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n/20);
    std::vector<int> nums1(n/3), nums2(n);
    for (int i = 0; i < n/3; ++i) {
        nums1[i] = dis(gen);
    }
    for (int i = 0; i < n; ++i) {
        nums2[i] = dis(gen);
    }

    benchmark::RegisterBenchmark("BM_Intersection_HashSet", [](benchmark::State &state, Intersection solution, std::vector<int> nums1, std::vector<int> nums2) {
        for (auto _ : state) {
            solution.Solution1(nums1, nums2);
        }
    }, solution, nums1, nums2);

    benchmark::RegisterBenchmark("BM_Intersection_SortDualPointer", [](benchmark::State& state, Intersection solution, std::vector<int> nums1, std::vector<int> nums2) {
        for (auto _ : state) {
            solution.Solution2(nums1, nums2);
        }
    }, solution, nums1, nums2);
}

std::vector<int> Intersection::Solution1(std::vector<int>& nums1, std::vector<int>& nums2) {
    if (nums1.size() > nums2.size()) {
        return Solution1(nums2, nums1);
    }
    std::unordered_set<int> set1(nums1.begin(), nums1.end());
    std::unordered_set<int> set2;
    for (auto num : nums2) {
        if (set1.find(num) != set1.end()) {
            set2.insert(num);
        }
    }
    return std::vector<int>(set2.begin(), set2.end());
}

std::vector<int> Intersection::Solution2(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());
    std::vector<int> ans;
    int i = 0, j = 0;
    int n = nums1.size(), m = nums2.size();
    while (i < n && j < m) {
        int num1 = nums1[i], num2 = nums2[j];
        if (num1 == num2) {
            // 保证唯一性
            if (!ans.size() || num1 != ans.back()) {
                ans.emplace_back(num1);
            }
            ++i;
            ++j;
        } else if (num1 < num2) {
            ++i;
        } else {
            ++j;
        }
    }
    return ans;
}


std::string Intersect::Title() {
    return "350. 两个数组的交集 II\n";
}

std::string Intersect::Problem() {
    return 
        "给你两个整数数组 nums1 和 nums2 ，请你以数组形式返回两数组的交集。\n"
        "返回结果中每个元素出现的次数，应与元素在两个数组中都出现的次数一致（如果出现次数不一致，则考虑取较小值）。\n"
        "可以不考虑输出结果的顺序。\n";
}

std::string Intersect::Link() {
    return "https://leetcode-cn.com/problems/intersection-of-two-arrays-ii/";
}

std::string Intersect::Solution() {
    return "哈希表，时间：O(n+m)，空间：O(min(n,m))。\n";
}

void Intersect::Benchmark() {
    Intersect solution;

    int n = 10000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n/100);
    std::vector<int> nums1(n), nums2(n/3);
    for (int i = 0; i < n; ++i) {
        nums1[i] = dis(gen);
    }
    for (int i = 0; i < n/3; ++i) {
        nums2[i] = dis(gen);
    }

    benchmark::RegisterBenchmark("BM_Intersection_HashTable", [](benchmark::State& state, Intersect solution, std::vector<int> nums1, std::vector<int> nums2) {
        for (auto _ : state) {
            solution.Solution1(nums1, nums2);
        }
    }, solution, nums1, nums2);

    benchmark::RegisterBenchmark("BM_Intersection_SortDualPointer", [](benchmark::State& state, Intersect solution, std::vector<int> nums1, std::vector<int> nums2) {
        for (auto _ : state) {
            solution.Solution2(nums1, nums2);
        }
    }, solution, nums1, nums2);
}

std::vector<int> Intersect::Solution1(std::vector<int>& nums1, std::vector<int>& nums2) {
    if (nums1.size() > nums2.size()) {
        return Solution1(nums2, nums1);
    }
    std::unordered_map<int, int> map;
    for (int num : nums1) {
        ++map[num];
    }
    std::vector<int> ans;
    for (int num : nums2) {
        if (map.count(num) && map[num] > 0) {
            ans.emplace_back(num);
            --map[num];
        }
    }
    return ans;
}

std::vector<int> Intersect::Solution2(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());
    int i = 0, j = 0;
    int n = nums1.size(), m = nums2.size();
    std::vector<int> ans;
    while (i < n && j < m) {
        int num1 = nums1[i], num2 = nums2[j];
        if (num1 == num2) {
            ans.emplace_back(num1);
            ++i;
            ++j;
        } else if (num1 < num2) {
            ++i;
        } else {
            ++j;
        }
    }
    return ans;
}


std::string ThirdMax::Title() {
    return "414. 第三大的数\n";
}

std::string ThirdMax::Problem() {
    return 
        "给你一个非空数组，返回此数组中第三大的数。如果不存在，则返回数组中最大的数。\n";
}

std::string ThirdMax::Link() {
    return "https://leetcode-cn.com/problems/third-maximum-number/";
}

std::string ThirdMax::Solution() {
    return "有限变量遍历，时间：O(n)，空间：O(1)。\n";
}

void ThirdMax::Benchmark() {
    ThirdMax solution;

    int n = 10000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n / 20);
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = dis(gen);
    }

    benchmark::RegisterBenchmark("BM_ThirdMax_Sort", [](benchmark::State & state, ThirdMax solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution1(nums);
        }
    }, solution, nums);

    benchmark::RegisterBenchmark("BM_ThirdMax_SortedSet", [](benchmark::State& state, ThirdMax solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution2(nums);
        }
    }, solution, nums);

    benchmark::RegisterBenchmark("BM_ThirdMax_LimitedVars", [](benchmark::State& state, ThirdMax solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution3(nums);
        }
    }, solution, nums);
}

int ThirdMax::Solution1(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end(), std::greater<>());
    int n = nums.size();
    for (int i = 1, diff = 1; i < n; ++i) {
        if (nums[i] != nums[i - 1] && ++diff == 3) {
            return nums[i];
        }
    }
    return nums[0];
}

int ThirdMax::Solution2(std::vector<int>& nums) {
    std::set<int> set;
    for (int num : nums) {
        set.insert(num);
        if (set.size() > 3) {
            set.erase(set.begin());
        }
    }
    return set.size() == 3 ? *set.begin() : *set.rbegin();
}

int ThirdMax::Solution3(std::vector<int>& nums) {
    long long a = LLONG_MIN, b = LLONG_MIN, c = LLONG_MIN;
    for (int num : nums) {
        if (num > a) {
            c = b;
            b = a;
            a = num;
        } else if (a > num && num > b) {
            c = b;
            b = num;
        } else if (b > num && num > c) {
            c = num;
        }
    }
    return c == LLONG_MIN ? a : c;
}


void ArraySolution(int pid) {
    LeetcodeSolution* solution = nullptr;
    switch (pid) {
    case SolutionsId::TWO_SUM: solution = new TwoSum(); break;
    case SolutionsId::REMOVE_DUPLICATES: solution = new RemoveDuplicates(); break;
    case SolutionsId::MISSING_NUMBER: solution = new MissingNumber(); break;
    case SolutionsId::NUM_ARRAY: solution = new NumArray(); break;
    case SolutionsId::INTERSECTION: solution = new Intersection(); break;
    case SolutionsId::INTERSECT: solution = new Intersect(); break;
    case SolutionsId::THIRD_MAX: solution = new ThirdMax(); break;
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



} // namespace array
} // namespace leetcode
