| :tiger:                  | :cat: | :dog: | :dragon: | :snake: |
| ------------------------ | ----- | ----- | -------- | ------- |
| 2. [两数相加](#两数相加) |       |       |          |         |



# 两数相加

- [链接](https://leetcode-cn.com/problems/add-two-numbers/)
- [code](../cc/linked_list/linked_list.h)

> 给你两个非空的链表，表示两个非负的整数。它们每位数字都是按照逆序的方式存储的，并且每个节点只能存储一位数字。
>
> 请你将两个数相加，并以相同形式返回一个表示和的链表。
>
> 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

## 模拟

由于两个链表是逆序存储的，因此两个链表同一位置的数字可以直接相加。同时遍历两个链表，逐位计算它们的和，并与当前位置的进位相加。若当前两个链表处相应的数字为 n1，n2，则答案链表相应处的数字为 `(n1+n2+carry)%10`，新的进位为 `(n1+n2+carry)/10`。若两个链表长度不同，较短的末尾补 0。

优化：可以判断其中一个链表是否遍历完，可以将答案链表的当前位置的 next 指向另一链表当前位置，并结束遍历，时间可以缩短至 $O(\min(n,m))$

**复杂度分析：**

- 时间复杂度：$O(\max(n,m))$，遍历两个链表所需时间，优化后时间 $O(\min(n,m))$
- 空间复杂度：$O(1)$

```c++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
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
};
```

## 递归

递归计算结果。递归终止条件为两个链表为空，且进位为 0。递推条件 `node->next = fun(l1,l2,carry)`。初始状态进位为 0。

优化：感觉可以在递归函数中判断其中一个链表是否遍历完，将另一链表返回，结束递归，将时间和空间优化至 $O(\min(n,m))$

**复杂度分析：**

- 时间复杂度：$O(\max(n,m))$，递归所需时间
- 空间复杂度：$O(\max(n,m))$，递归所需堆栈空间

```c++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return add(l1, l2, 0);
    }

    ListNode* add(ListNode *l1, ListNode *l2, int carry) {
        if (l1 == nullptr && l2 == nullptr && carry == 0) {
            return nullptr;
        }
        int v1 = l1 ? l1->val : 0;
        int v2 = l2 ? l2->val : 0;
        int sum = v1 + v2 + carry;
        l1 = l1 ? l1->next : l1;
        l2 = l2 ? l2->next : l2;
        ListNode *node = new ListNode(sum % 10);
        node->next = add(l1, l2, sum / 10);
        return node;
    }
};
```

