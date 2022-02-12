#include <iostream>
#include <gtest/gtest.h>
#include "linked_list.h"

namespace leetcode {
namespace test {

using namespace linkedlist;

TEST(LinkedListTest, AddTwoNumbersTest) {
    AddTwoNumbers solution;
    std::vector<std::vector<int>> nums1{
        { 2,4,3 },
        { 0 },
        { 9,9,9,9,9,9,9 },
    };
    std::vector<std::vector<int>> nums2{
        { 5,6,4 },
        { 0 },
        { 9,9,9,9 },
    };
    std::vector<std::vector<int>> nums3{
        { 7,0,8 },
        { 0 },
        { 8,9,9,9,0,0,0,1 },
    };
    std::vector<ListNode*> l1{
        Vector2ListNode(nums1[0]),
        Vector2ListNode(nums1[1]),
        Vector2ListNode(nums1[2]),
    };
    std::vector<ListNode*> l2{
        Vector2ListNode(nums2[0]),
        Vector2ListNode(nums2[1]),
        Vector2ListNode(nums2[2]),
    };
    std::vector<ListNode*> l3{
        Vector2ListNode(nums3[0]),
        Vector2ListNode(nums3[1]),
        Vector2ListNode(nums3[2]),
    };

    ListNode *tmp_l1 = l1[0], *tmp_l2 = l2[0], *tmp_l3 = l3[0];
    ListNode *l_solution = solution.Solution1(tmp_l1, tmp_l2);
    EXPECT_TRUE(CompareListNode(l_solution, tmp_l3));
    FreeListNode(l_solution);
    
    tmp_l1 = l1[1]; tmp_l2 = l2[1];  tmp_l3 = l3[1];
    l_solution = solution.Solution1(tmp_l1, tmp_l2);
    EXPECT_TRUE(CompareListNode(l_solution, tmp_l3));
    FreeListNode(l_solution);

    tmp_l1 = l1[2]; tmp_l2 = l2[2];  tmp_l3 = l3[2];
    l_solution = solution.Solution1(tmp_l1, tmp_l2);
    EXPECT_TRUE(CompareListNode(l_solution, tmp_l3));
    FreeListNode(l_solution);

    tmp_l1 = l1[0], tmp_l2 = l2[0], tmp_l3 = l3[0];
    l_solution = solution.Solution2(tmp_l1, tmp_l2);
    EXPECT_TRUE(CompareListNode(l_solution, tmp_l3));
    FreeListNode(l_solution);

    tmp_l1 = l1[1]; tmp_l2 = l2[1];  tmp_l3 = l3[1];
    l_solution = solution.Solution2(tmp_l1, tmp_l2);
    EXPECT_TRUE(CompareListNode(l_solution, tmp_l3));
    FreeListNode(l_solution);

    tmp_l1 = l1[2]; tmp_l2 = l2[2];  tmp_l3 = l3[2];
    l_solution = solution.Solution2(tmp_l1, tmp_l2);
    EXPECT_TRUE(CompareListNode(l_solution, tmp_l3));
    FreeListNode(l_solution);

    for (ListNode *p : l1) {
        FreeListNode(p);
    }
    for (ListNode *p : l2) {
        FreeListNode(p);
    }
    for (ListNode *p : l3) {
        FreeListNode(p);
    }
}

} // namespace test
} // namespace leetcode