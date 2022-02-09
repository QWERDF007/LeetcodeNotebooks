#pragma once

#include "leetcode_solution.h"

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};


namespace leetcode {
namespace linkedlist {

void LinkedListSolution(int pid);

class AddTwoNumbers : public LeetcodeSolution {
public:
    std::string Title() override;
    
    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    ListNode* Solution1(ListNode* l1, ListNode* l2);
};
    
} // namespace linkedlist
} // namespace leetcode
