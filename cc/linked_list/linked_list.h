#pragma once

#include "leetcode_solution.h"


namespace leetcode {
namespace linkedlist {

void LinkedListSolution(int pid);

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *Vector2ListNode(std::vector<int> &nums);

void FreeListNode(ListNode *head);

bool CompareListNode(ListNode *l1, ListNode *l2);


class AddTwoNumbers : public LeetcodeSolution {
public:
    std::string Title() override;
    
    std::string Problem() override;

    std::string Link() override;

    std::string Solution() override;

    void Benchmark() override;

    /**
     * @brief 模拟
     * 时间复杂度：O(max(n,m))
     * 空间复杂度：O(1)
     * @param l1 
     * @param l2 
     * @return ListNode* 计算结果头节点
     */
    ListNode *Solution1(ListNode *l1, ListNode *l2);

    /**
     * @brief 递归
     * 时间复杂度：O(max(n,m))
     * 空间复杂度：O(max(n,m))
     * @param l1 
     * @param l2 
     * @return ListNode* 计算结果头节点
     */
    ListNode *Solution2(ListNode *l1, ListNode *l2);

private:
    /**
     * @brief 递归辅助函数，计算每个节点
     * 
     * @param l1 
     * @param l2 
     * @param carry 
     * @return ListNode* 
     */
    ListNode *Solution2Aux(ListNode *l1, ListNode *l2, int carry);
};
    
} // namespace linkedlist
} // namespace leetcode
