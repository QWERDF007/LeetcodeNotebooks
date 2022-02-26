#include <ctime>
#include <random>
#include <stdlib.h>
#include <climits>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <benchmark/benchmark.h>

#include "array.h"




namespace leetcode {
namespace array{

void ArraySolution(int pid) {
    LeetcodeSolution* solution = nullptr;
    switch (pid) {
        case SolutionsId::TWO_SUM: solution = new TwoSum(); break;
        case SolutionsId::REMOVE_DUPLICATES: solution = new RemoveDuplicates(); break;
        case SolutionsId::FIND_MISSING_RANGES: solution = new FindMissingRanges(); break;
        case SolutionsId::MISSING_NUMBER: solution = new MissingNumber(); break;
        case SolutionsId::NUM_ARRAY: solution = new NumArray(); break;
        case SolutionsId::INTERSECTION: solution = new Intersection(); break;
        case SolutionsId::INTERSECT: solution = new Intersect(); break;
        case SolutionsId::THIRD_MAX: solution = new ThirdMax(); break;
        case SolutionsId::FIND_DISAPPEARED_NUMBERS: solution = new FindDisappearedNumbers(); break;
        case SolutionsId::MIN_MOVES: solution = new MinMoves(); break;
        case SolutionsId::SINGLE_NON_DUPLICATE: solution = new SingleNonDuplicate(); break;
        case SolutionsId::IS_ONE_BIT_CHARACTER: solution = new IsOneBitCharacter(); break;
        case SolutionsId::LUCKY_NUMBERS: solution = new LuckyNumbers(); break;
        case SolutionsId::FIND_BALL: solution = new FindBall(); break;
        case SolutionsId::MINIMUM_DIFFERENCE: solution = new MinimumDifference(); break;
        case SolutionsId::MAXIMUM_DIFFERENCE: solution = new MaximumDifference(); break;
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

    benchmark::RegisterBenchmark("BM_TwoSum_TwoPointers", [](benchmark::State& state, RemoveDuplicates solution, std::vector<int> nums) {
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


std::string FindMissingRanges::Title() {
    return "163. 缺失的区间\n";
}

std::string FindMissingRanges::Problem() {
    return "给定一个排序的整数数组 nums，其中元素的范围在闭区间 [lower, upper] 当中，返回不包含在数组中的缺失区间。\n";
}

std::string FindMissingRanges::Link() {
    return "https://leetcode-cn.com/problems/missing-ranges/";
}

std::string FindMissingRanges::Solution() {
    return "双指针，时间：O(n)，空间：O(1)。\n";
}

void FindMissingRanges::Benchmark() {
    FindMissingRanges solution;

    int n = 4000;
    int lower = -10000, upper = 10000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 5);
    std::vector<int> nums(n);
    int cur = lower;
    for (int i = 0; i < n; ++i) {
        cur += dis(gen);
        nums[i] = cur;
    }
    auto func = [](benchmark::State &state, FindMissingRanges solution, std::vector<int> nums, int lower, int upper) {
        for (auto _ : state) {
            solution.Solution1(nums, lower, upper);
        }
    };
    benchmark::RegisterBenchmark("BM_FindMissingRanges_Traversal", func, solution, nums, lower, upper);
}

std::vector<std::string> FindMissingRanges::Solution1(std::vector<int> &nums, int lower, int upper) {
    std::vector<std::string> ans;
    int n = nums.size();
    // lower - 1 将缺失 [lower] 的情况统一处理
    long long prev = (long long)lower - 1;
    for (int i = 0; i < n; ++i) {
        int d = nums[i] - prev;
        if (d == 2) {
            ans.emplace_back(std::to_string(prev + 1));
        } else if (d > 2) {
            ans.emplace_back(std::to_string(prev + 1) + "->" + std::to_string(nums[i] - 1));
        }
        prev = nums[i];
    }
    if (upper - prev == 1) {
        ans.emplace_back(std::to_string(prev + 1));
    } else if (upper - prev > 1) {
        ans.emplace_back(std::to_string(prev + 1) + "->" + std::to_string(upper));
    }
    return ans;
}

std::string MissingNumber::Title() {
    return "268. 丢失的数字\n";
}

std::string MissingNumber::Problem() {
    return  "给定一个包含 [0, n] 中 n 个数的数组 nums，找出 [0, n] 这个范围内没有出现在数组中的那个数。\n";
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

    benchmark::RegisterBenchmark("BM_Intersection_SortTwoPointers", [](benchmark::State& state, Intersection solution, std::vector<int> nums1, std::vector<int> nums2) {
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

    benchmark::RegisterBenchmark("BM_Intersection_SortTwoPointers", [](benchmark::State& state, Intersect solution, std::vector<int> nums1, std::vector<int> nums2) {
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




std::string FindDisappearedNumbers::Title() {
    return "448. 找到所有数组中消失的数字\n";
}

std::string FindDisappearedNumbers::Problem() {
    return 
        "给你一个含 n 个整数的数组 nums ，其中 nums[i] 在区间 [1, n] 内。\n"
        "请你找出所有在 [1, n] 范围内但没有出现在 nums 中的数字，并以数组的形式返回结果。\n";
}

std::string FindDisappearedNumbers::Link() {
    return "https://leetcode-cn.com/problems/find-all-numbers-disappeared-in-an-array/";
}

std::string FindDisappearedNumbers::Solution() {
    return "原地修改，数组模拟哈希表，时间：O(n)，空间：O(1)。\n";
}

void FindDisappearedNumbers::Benchmark() {
    FindDisappearedNumbers solution;

    int n = 10000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, n);
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = dis(gen);
    }
    auto fun_hashset = [](benchmark::State& state, FindDisappearedNumbers solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution1(nums);
        }
    };
    benchmark::RegisterBenchmark("BM_FindDisappearedNumbers_HashSet", fun_hashset, solution, nums);

    auto fun_inplace = [](benchmark::State& state, FindDisappearedNumbers solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution2(nums);
        }
    };
    benchmark::RegisterBenchmark("BM_FindDisappearedNumbers_Inplace", fun_inplace, solution, nums);

    auto fun_hashmap = [](benchmark::State& state, FindDisappearedNumbers solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution3(nums);
        }
    };

    benchmark::RegisterBenchmark("BM_FindDisappearedNumbers_HashMap", fun_hashmap, solution, nums);
}

std::vector<int> FindDisappearedNumbers::Solution1(std::vector<int>& nums) {
    std::unordered_set<int> set;
    int n = nums.size();
    for (int num : nums) {
        set.insert(num);
    }
    std::vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        if (!set.count(i)) {
            ans.emplace_back(i);
        }
    }
    return ans;
}

std::vector<int> FindDisappearedNumbers::Solution2(std::vector<int>& nums) {
    std::vector<int> ans;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        int j = (nums[i] - 1) % n;
        nums[j] += n;
    }
    for (int i = 0; i < n; ++i) {
        if (nums[i] <= n) {
            ans.emplace_back(i + 1);
        }
    }
    return ans;
}

std::vector<int> FindDisappearedNumbers::Solution3(std::vector<int>& nums) {
    std::unordered_map<int, int> map;
    int n = nums.size();
    for (int num : nums) {
        ++map[num];
    }
    std::vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        if (!map.count(i)) {
            ans.emplace_back(i);
        }
    }
    return ans;
}

std::string MinMoves::Title() {
    return "453. 最小操作次数使数组元素相等\n";
}

std::string MinMoves::Problem() {
    return 
        "给你一个长度为 n 的整数数组，每次操作将会使 n-1 个元素增加 1。返回让数组所有元素相等的最小操作次数。\n";
}

std::string MinMoves::Link() {
    return "https://leetcode-cn.com/problems/minimum-moves-to-equal-array-elements/";
}

std::string MinMoves::Solution() {
    return "数学，一次遍历，时间：O(n)，空间：O(1)。\n";
}

void MinMoves::Benchmark() {
    MinMoves solution;

    int n = 1000000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-n, n);
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = dis(gen);
    }

    benchmark::RegisterBenchmark("BM_MinMoves_Arithmetic", [](benchmark::State &state, MinMoves solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution1(nums);
        }
    }, solution, nums);
}

int MinMoves::Solution1(std::vector<int> &nums) {
    int n = nums.size();
    int m = INT_MAX;
    long long sum = 0;
    
    for (int num : nums) {
        sum += num;
        m = m > num ? num : m;
    }
    return sum - (long long)m * n;
}


std::string SingleNonDuplicate::Title() {
    return "540. 有序数组中的单一元素\n";
}

std::string SingleNonDuplicate::Problem() {
    return 
        "给你一个仅由整数组成的有序数组，其中每个元素都会出现两次，唯有一个数只会出现一次。\n"
        "请你找出并返回只出现一次的那个数。\n"
        "你设计的解决方案必须满足 O(log n) 时间复杂度和 O(1) 空间复杂度。\n";
}

std::string SingleNonDuplicate::Link() {
    return "https://leetcode-cn.com/problems/single-element-in-a-sorted-array/";
}

std::string SingleNonDuplicate::Solution() {
    return "偶数下标二分查找，时间：O(log n)，空间：O(1)。\n";
}

void SingleNonDuplicate::Benchmark() {
    SingleNonDuplicate solution;

    int n = 10000000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n/2 - 1);
    std::vector<int> nums(n-1);
    int num = dis(gen);
    for (int i = 0; i < n/2; ++i) {
        if (num == i) {
            nums[i] = 2 * i + 1;
        } else {
            nums[i] = 2 * i;
            nums[i + 1] = 2 * i;
        }
    }

    benchmark::RegisterBenchmark("BM_SingleNonDuplicate_Xor", [](benchmark::State &state, SingleNonDuplicate solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution1(nums);
        }
    }, solution, nums);

    benchmark::RegisterBenchmark("BM_SingleNonDuplicate_BinarySearchAll", [](benchmark::State &state, SingleNonDuplicate solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution2(nums);
        }
    }, solution, nums);

    benchmark::RegisterBenchmark("BM_SingleNonDuplicate_BinarySearchEven", [](benchmark::State &state, SingleNonDuplicate solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution3(nums);
        }
    }, solution, nums);

    benchmark::RegisterBenchmark("BM_SingleNonDuplicate_Traversal", [](benchmark::State &state, SingleNonDuplicate solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution4(nums);
        }
    }, solution, nums);
}

int SingleNonDuplicate::Solution1(std::vector<int> &nums) {
    int ans = 0;
    for (int num : nums) {
        ans ^= num;
    }
    return ans;
}

int SingleNonDuplicate::Solution2(std::vector<int> &nums) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        // 若 mid 是奇数，mid^1=mid-1 是偶数
        // 若 mid 是偶数，mid^1=mid+1 是奇数
        if (nums[mid] == nums[mid ^ 1]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return nums[right];
}

int SingleNonDuplicate::Solution3(std::vector<int> &nums) {
    int low = 0, high = nums.size() - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        // 确保 mid 是偶数
        // 若 mid 是奇数，mid&1=1，mid=mid-1 是偶数
        // 若 mid 是偶数，mid&1=0，mid=mid-0 是偶数
        mid -= mid & 1; 
        if (nums[mid] == nums[mid + 1]) {
            low = mid + 2;
        }
        else {
            high = mid;
        }
    }
    return nums[low];
}

int SingleNonDuplicate::Solution4(std::vector<int> &nums) {
    int n = nums.size();
    for (int i = 0; i < n; i+=2) {
        if (i < n - 1 && nums[i] != nums[i + 1]) {
            return nums[i];
        }
    }
    return nums[n - 1];
}


std::string IsOneBitCharacter::Title() {
    return "717. 1比特与2比特字符\n";
}

std::string IsOneBitCharacter::Problem() {
    return 
        "有两种特殊字符：\n"
        "- 第一种字符可以用一个比特 0 来表示\n"
        "- 第二种字符可以用两个比特(10 或 11)来表示\n"
        "给定一个以 0 结尾的二进制数组 bits，如果最后一个字符必须是一位字符，则返回 true。\n";
}

std::string IsOneBitCharacter::Link() {
    return "https://leetcode-cn.com/problems/1-bit-and-2-bit-characters/";
}

std::string IsOneBitCharacter::Solution() {
    return "倒序遍历，时间：O(n)，空间：O(1)。\n";
}

void IsOneBitCharacter::Benchmark() {
    IsOneBitCharacter solution;

    int n = 10000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    std::vector<int> bits(n + 1);
    for (int i = 0; i < n; ++i) {
        bits[i] = dis(gen);
    }

    auto func = [](benchmark::State &state, IsOneBitCharacter solution, std::vector<int> bits) {
        for (auto _ : state) {
            solution.Solution1(bits);
        }
    };
    benchmark::RegisterBenchmark("BM_IsOneBitCharacter_Traversal", func, solution, bits);

    auto rfunc = [](benchmark::State &state, IsOneBitCharacter solution, std::vector<int> bits) {
        for (auto _ : state) {
            solution.Solution2(bits);
        }
    };
    benchmark::RegisterBenchmark("BM_IsOneBitCharacter_Reversed", func, solution, bits);
}

bool IsOneBitCharacter::Solution1(std::vector<int> &bits) {
    int n = bits.size() - 1, i = 0;
    while (i < n) {
        i += bits[i] + 1;
    }
    return i == n;
}

bool IsOneBitCharacter::Solution2(std::vector<int> &bits) {
    int n = bits.size(), i = n - 2;
    while (i >= 0 && bits[i]) {
        --i;
    }
    return (n - i) % 2 == 0;
}


std::string LuckyNumbers::Title() {
    return "1380. 矩阵中的幸运数\n";
}

std::string LuckyNumbers::Problem() {
    return 
        "给你一个 m * n 的矩阵，矩阵中的数字各不相同。请你按任意顺序返回矩阵中的所有幸运数。\n"
        "幸运数是指矩阵中满足同时下列两个条件的元素：\n"
        "- 在同一行的所有元素中最小\n"
        "- 在同一列的所有元素中最大\n";
}

std::string LuckyNumbers::Link() {
    return "https://leetcode-cn.com/problems/lucky-numbers-in-a-matrix/";
}

std::string LuckyNumbers::Solution() {
    return "预处理，时间：O(nm)，空间：O(n+m)。\n";
}

void LuckyNumbers::Benchmark() {
    LuckyNumbers solution;
    int m = 1000;
    int n = 2000;
    std::vector<int> nums(m*n);
    for (int i = 0; i < m*n; ++i) {
        nums[i] = i;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(nums.begin(), nums.end(), gen);
    std::vector<std::vector<int>> matrix(m,std::vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = nums[i * m + j];
        }
    }

    auto preprocess_func = [](benchmark::State &state, LuckyNumbers solution, std::vector<std::vector<int>> matrix) {
        for (auto _ : state) {
            solution.Solution1(matrix);
        }
    };
    benchmark::RegisterBenchmark("BM_LuckyNumbers_Preprocess", preprocess_func, solution, matrix);

    auto simulate_func = [](benchmark::State & state, LuckyNumbers solution, std::vector<std::vector<int>> matrix) {
        for (auto _ : state) {
            solution.Solution2(matrix);
        }
    };
    benchmark::RegisterBenchmark("BM_LuckyNumbers_Simulate", simulate_func, solution, matrix);
}

std::vector<int> LuckyNumbers::Solution1(std::vector<std::vector<int>> &matrix) {
    int m = matrix.size(), n = matrix[0].size();
    std::vector<int> min_rows(m, INT_MAX), max_cols(n), ans;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            min_rows[i] = std::min(min_rows[i], matrix[i][j]);
            max_cols[j] = std::max(max_cols[j], matrix[i][j]);
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int v = matrix[i][j];
            if (v == min_rows[i] && v == max_cols[j]) {
                ans.emplace_back(v);
            }
        }
    }
    return ans;
}

std::vector<int> LuckyNumbers::Solution2(std::vector<std::vector<int>> &matrix) {
    int m = matrix.size(), n = matrix[0].size();
    std::vector<int> ans;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int v = matrix[i][j];
            bool is_max = true, is_min = true;
            for (int k = 0; k < n; ++k) {
                if (v > matrix[i][k]) {
                    is_min = false;
                    break;
                }
            }
            if (!is_min) {
                continue;
            }
            for (int k = 0; k < m; ++k) {
                if (v < matrix[k][j]) {
                    is_max = false;
                }
            }
            if (is_max) {
                ans.emplace_back(v);
            }
        }
    }
    return ans;
}


std::string FindBall::Title() {
    return "1706. 球会落何处\n";
}

std::string FindBall::Problem() {
    return 
        "用一个大小为 m x n 的二维网格 grid 表示一个箱子。你有 n 颗球。箱子的顶部和底部都是开着的。\n"
        "箱子中的每个单元格都有一个对角线挡板，跨过单元格的两个角，可以将球导向左侧或者右侧。\n"
        "- 将球导向右侧的挡板跨过左上角和右下角，在网格中用 1 表示。\n"
        "- 将球导向左侧的挡板跨过右上角和左下角，在网格中用 -1 表示。\n"
        "在箱子每一列的顶端各放一颗球。每颗球都可能卡在箱子里或从底部掉出来。\n"
        "如果球恰好卡在两块挡板之间的 \"V\" 形图案，或者被一块挡导向到箱子的任意一侧边上，就会卡住。\n"
        "返回一个大小为 n 的数组 answer ，其中 answer[i] 是球放在顶部的第 i 列后从底部掉出来的那一列对应的下标，如果球卡在盒子里，则返回 -1 。\n";
}

std::string FindBall::Link() {
    return "https://leetcode-cn.com/problems/where-will-the-ball-fall/";
}

std::string FindBall::Solution() {
    return "模拟，时间：O(mn)，空间：O(1)。\n";
}

void FindBall::Benchmark() {
    FindBall solution;

    int m = 500, n = 1000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    std::vector<std::vector<int>> grid(m, std::vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = dis(gen) == 0 ? -1 : 1;
        }
    }

    benchmark::RegisterBenchmark("BM_FindBall_Simulate", [](benchmark::State &state, FindBall solution, std::vector<std::vector<int>> grid) {
        for (auto _ : state) {
            solution.Solution1(grid);
        }
    }, solution, grid);
}

std::vector<int> FindBall::Solution1(std::vector<std::vector<int>> &grid) {
    int n = grid[0].size();
    int m = grid.size();
    std::vector<int> ans(n, -1);
    for (int j = 0; j < n; ++j) {
        int col = j;
        for (int i = 0; i < m; ++i) {
            int dir = grid[i][col];
            col += dir;
            if (col < 0 || col >= n || grid[i][col] != dir) {
                col = -1;
                break;
            }
        }
        if (col >= 0) {
            ans[j] = col;
        }
    }
    return ans;
}


std::string MinimumDifference::Title() {
    return "1984. 学生分数的最小差值\n";
}

std::string MinimumDifference::Problem() {
    return 
        "给你一个下标从 0 开始的整数数组 nums，其中 nums[i] 表示第 i 名学生的分数。另给你一个整数 k。\n"
        "从数组中选出任意 k 名学生的分数，使这 k 个分数间最高分和最低分的差值达到最小化。\n"
        "返回可能的最小差值。\n";
}

std::string MinimumDifference::Link() {
    return "https://leetcode-cn.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/";
}

std::string MinimumDifference::Solution() {
    return "排序+滑动窗口，时间：O(nlogn)，空间：O(logn)。\n";
}

void MinimumDifference::Benchmark() {
    MinimumDifference solution;

    int n = 100000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n);
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = dis(gen);
    }
    int k = dis(gen) % 999 + 1;

    auto func = [](benchmark::State &state, MinimumDifference solution, std::vector<int> nums, int k) {
        for (auto _ : state) {
            solution.Solution1(nums, k);
        }
    };

    benchmark::RegisterBenchmark("BM_MinimumDifference_SortSlidingWindow", func, solution, nums, k);
}

int MinimumDifference::Solution1(std::vector<int> &nums, int k) {
    if (k == 1) return 0;
    std::sort(nums.begin(), nums.end());
    int n = nums.size(), m = INT_MAX;
    int j = n - k + 1;
    for (int i = 0; i < j; ++i) {
        m = std::min(m, nums[i + k - 1] - nums[i]);
    }
    return m;
}


std::string MaximumDifference::Title() {
    return "2016. 增量元素之间的最大差值\n";
}

std::string MaximumDifference::Problem() {
    return 
        "给你一个下标从 0 开始的整数数组 nums ，该数组的大小为 n，\n"
        "请你计算 nums[j] - nums[i] 能求得的最大差值 ，其中 0 <= i < j < n 且 nums[i] < nums[j]。\n"
        "返回最大差值。如果不存在满足要求的 i 和 j，返回 -1。\n";
}

std::string MaximumDifference::Link() {
    return "https://leetcode-cn.com/problems/maximum-difference-between-increasing-elements/";
}

std::string MaximumDifference::Solution() {
    return "前缀最小值，时间：O(n)，空间：O(1)。\n";
}

void MaximumDifference::Benchmark() {
    MaximumDifference solution;
    int n = 10000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1e9);
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = dis(gen);
    }

    auto func = [](benchmark::State &state, MaximumDifference solution, std::vector<int> nums) {
        for (auto _ : state) {
            solution.Solution1(nums);
        }
    };
    benchmark::RegisterBenchmark("BM_MaximumDifference_PrefixMinimum", func, solution, nums);
}

int MaximumDifference::Solution1(std::vector<int> &nums) {
    int n = nums.size();
    int ans = -1, premin = n > 0 ? nums[0] : -1;
    for (int i = 1; i < n; ++i) {
        if (nums[i] > premin) {
            ans = std::max(ans, nums[i] - premin);
        } else {
            premin = nums[i];
        }
    }
    return ans;
}

} // namespace array
} // namespace leetcode
