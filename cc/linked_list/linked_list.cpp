#include <vector>
#include <random>
#include <iostream>
#include <benchmark/benchmark.h>

#include "leetcode_solution.h"
#include "linked_list.h"

namespace leetcode {
namespace linkedlist {

void LinkedListSolution(int pid) {
	LeetcodeSolution* solution = nullptr;
	switch (pid) {
		case SolutionsId::ADD_TWO_NUMBERS: solution = new AddTwoNumbers(); break;
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

ListNode *Vector2ListNode(std::vector<int> &nums) {
	ListNode *head = nullptr;
	ListNode *tail = nullptr;
	for (int num : nums) {
		if (!head) {
			head = tail = new ListNode(num);
		}
		else {
			tail->next = new ListNode(num);
			tail = tail->next;
		}
	}
	return head;
}

void FreeListNode(ListNode *head) {
	while (head) {
		ListNode *p = head;
		head = head->next;
		delete p;
	}
}

bool CompareListNode(ListNode *l1, ListNode *l2) {
	ListNode *node1 = l1, *node2 = l2;
	while (node1 || node2) {
		if ((!node1 && node2) || (node1 && !node2)) {
			return false;
		}
		else if (node1->val != node2->val) {
			return false;
		}
		else {
			node1 = node1->next;
			node2 = node2->next;
		}
	}
	return true;
}

std::string AddTwoNumbers::Title() {
	return "2. 两数相加\n";
}

std::string AddTwoNumbers::Problem() {
	return 
		"给你两个非空的链表，表示两个非负的整数。\n"
		"它们每位数字都是按照逆序的方式存储的，并且每个节点只能存储一位数字。\n"
		"请你将两个数相加，并以相同形式返回一个表示和的链表。\n"
		"你可以假设除了数字 0 之外，这两个数都不会以 0 开头。\n";
}

std::string AddTwoNumbers::Link() {
	return "https://leetcode-cn.com/problems/add-two-numbers/";
}

std::string AddTwoNumbers::Solution() {
	return "模拟，时间：O(max(n,m))，空间：O(1)。\n";
}

void AddTwoNumbers::Benchmark() {
	AddTwoNumbers solution;

	int n = 100;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 9);
	std::vector<int> nums1(n), nums2(n);
	for (int i = 0; i < n; ++i) {
		nums1[i] = dis(gen);
		nums2[i] = dis(gen);
	}
	ListNode *l1 = Vector2ListNode(nums1);
	ListNode *l2 = Vector2ListNode(nums2);

	benchmark::RegisterBenchmark("BM_AddTwoNumbers_Simulate", [](benchmark::State &state, AddTwoNumbers solution, ListNode *l1, ListNode *l2) {
		for (auto _ : state) {
			ListNode *tmp_l1 = l1, *tmp_l2 = l2;
			ListNode *l3 = solution.Solution1(tmp_l1, tmp_l2);
			FreeListNode(l3);
		}
	}, solution, l1, l2);

	benchmark::RegisterBenchmark("BM_AddTwoNumbers_Recursion", [](benchmark::State &state, AddTwoNumbers solution, ListNode *l1, ListNode *l2) {
		for (auto _ : state) {
			ListNode *tmp_l1 = l1, *tmp_l2 = l2;
			ListNode *l3 = solution.Solution2(tmp_l1, tmp_l2);
			FreeListNode(l3);
		}
	}, solution, l1, l2);

	//FreeListNode(l1);
	//FreeListNode(l2);
}

ListNode* AddTwoNumbers::Solution1(ListNode* l1, ListNode* l2) {
	ListNode *head = nullptr, *tail = nullptr;
	int carry = 0;
	while (l1 || l2 || carry) {
		int v1 = l1 ? l1->val : 0;
		int v2 = l2 ? l2->val : 0;
		int sum = v1 + v2 + carry;
		if (!head) {
			head = tail = new ListNode(sum % 10);
		} else {
			tail->next = new ListNode(sum % 10);
			tail = tail->next;
		}
		carry = sum / 10;
		l1 = l1 ? l1->next : l1;
		l2 = l2 ? l2->next : l2;
	}
	return head;
}

ListNode *AddTwoNumbers::Solution2(ListNode *l1, ListNode *l2) {
	return Solution2Aux(l1, l2, 0);
}

ListNode *AddTwoNumbers::Solution2Aux(ListNode *l1, ListNode *l2, int carry) {
	if (l1 == nullptr && l2 == nullptr && carry == 0) {
		return nullptr;
	}
	int v1 = l1 ? l1->val : 0;
	int v2 = l2 ? l2->val : 0;
	int sum = v1 + v2 + carry;
	l1 = l1 ? l1->next : l1;
	l2 = l2 ? l2->next : l2;
	ListNode *node = new ListNode(sum % 10);
	node->next = Solution2Aux(l1, l2, sum / 10);
	return node;
}

} // namespace linkedlist
} // namespace leetcode
