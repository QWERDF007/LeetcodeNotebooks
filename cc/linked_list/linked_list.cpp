#include <iostream>

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
	return std::string();
}

void AddTwoNumbers::Benchmark() {
}

ListNode* AddTwoNumbers::Solution1(ListNode* l1, ListNode* l2) {
	return nullptr;
}

} // namespace linkedlist
} // namespace leetcode
