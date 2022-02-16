#include <stack>
#include <queue>
#include <random>
#include <iostream>
#include <benchmark/benchmark.h>

#include "binary_tree.h"

namespace leetcode {
namespace tree {

void BinaryTreeSolution(int pid) {
    LeetcodeSolution *solution = nullptr;
	switch (pid) {
        case SolutionsId::INORDER_TRAVERSAL: solution = new InorderTraversal(); break;
        case SolutionsId::IS_SAME_TREE: solution = new IsSameTree(); break;
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

template <typename T>
void PreOrderTraversal(TreeNode *root, std::vector<T> &res) {
    if (!root) {
        return;
    }
    res.emplace_back(root->val);
    PreOrderTraversal(root->left, res);
    PreOrderTraversal(root->right, res);
}

template <typename T>
void InOrderTraversal(TreeNode *root, std::vector<T> &res) {
    if (!root) {
        return;
    }
    InOrderTraversal(root->left, res);
    res.emplace_back(root->val);
    InOrderTraversal(root->right, res);
}

template <typename T>
void PostOrderTraversal(TreeNode *root, std::vector<T> &res) {
    if (!root) {
        return;
    }
    PostOrderTraversal(root->left, res);
    PostOrderTraversal(root->right, res);
    res.emplace_back(root->val);
}

TreeNode *NewTree(std::vector<std::string> &tree) {
    int n = tree.size();
    if (n == 0) {
        return nullptr;
    }
    TreeNode *root = new TreeNode(std::atoi(tree[0].c_str())), *cur = nullptr;
    std::queue<TreeNode *> q;
    q.push(root);
    int i = 1;
    while (i < n) {
        cur = q.front();
        q.pop();
        if (tree[i] != "null") {
            cur->left = new TreeNode(std::atoi(tree[i].c_str()));
            q.push(cur->left);
        }
        ++i;
        if (i < n && tree[i] != "null") {
            cur->right = new TreeNode(std::atoi(tree[i].c_str()));
            q.push(cur->right);
        }
        ++i;
    }
    return root;
}

void DeleteTree(TreeNode *root) {
    if (root == nullptr) {
        return;
    }
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
}

std::string InorderTraversal::Title() {
    return "94. 二叉树的中序遍历\n";
}

std::string InorderTraversal::Problem() {
    return "给定一个二叉树的根节点 root，返回它的中序遍历。\n";
}

std::string InorderTraversal::Link() {
    return "https://leetcode-cn.com/problems/binary-tree-inorder-traversal/";
}

std::string InorderTraversal::Solution() {
    return "递归，时间：O(n)，空间：O(n)，n 为结点数量。\n";
}

void InorderTraversal::Benchmark() {
    InorderTraversal solution;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-100, 100);
    int null = dis(gen);
    int n = 1000;
    std::vector<std::string> str_tree(n);
    for (int i = 0; i < n; ++i) {
        int v = dis(gen);
        if (v != null) {
            str_tree.emplace_back(std::to_string(v));
        } else {
            str_tree.emplace_back("null");
        }
    }
    TreeNode *root = NewTree(str_tree);

    benchmark::RegisterBenchmark("BM_InorderTraversal_Recursion", [](benchmark::State &state, InorderTraversal solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_InorderTraversal_Iteration", [](benchmark::State &state, InorderTraversal solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution2(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_InorderTraversal_Morris", [](benchmark::State &state, InorderTraversal solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution3(root);
        }
    }, solution, root);
    //DeleteTree(root);
}

std::vector<int> InorderTraversal::Solution1(TreeNode *root) {
    std::vector<int> res;
    InOrderTraversal(root, res);
    return res;
}

std::vector<int> InorderTraversal::Solution2(TreeNode *root) {
    std::vector<int> res;
    std::stack<TreeNode *> stk;
    TreeNode *cur = root;
    while (cur != nullptr || !stk.empty()) {
        while (cur != nullptr) {
            stk.push(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();
        res.emplace_back(cur->val);
        cur = cur->right;
    }
    return res;
}

std::vector<int> InorderTraversal::Solution3(TreeNode *root) {
    std::vector<int> res;
    TreeNode *predecessor = nullptr;
    TreeNode *cur = root;
    while (cur != nullptr) {
        if (cur->left != nullptr) {
            // predecessor 节点就是当前 cur 节点向左走一步，然后一直向右走至无法走为止
            predecessor = cur->left;
            while (predecessor->right != nullptr && predecessor->right != cur) {
                predecessor = predecessor->right;
            }

            // 让 predecessor 的右指针指向 cur，继续遍历左子树
            if (predecessor->right == nullptr) {
                predecessor->right = cur;
                cur = cur->left;
            }
            // 说明左子树已经访问完了，我们需要断开链接
            else {
                res.push_back(cur->val);
                predecessor->right = nullptr;
                cur = cur->right;
            }
        }
        // 如果没有左孩子，则直接访问右孩子
        else {
            res.push_back(cur->val);
            cur = cur->right;
        }
    }
    return res;
}


std::string IsSameTree::Title() {
    return "100. 相同的树\n";
}

std::string IsSameTree::Problem() {
    return 
        "给你两棵二叉树的根节点 p 和 q，编写一个函数来检验这两棵树是否相同。\n"
        "如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。\n";
}

std::string IsSameTree::Link() {
    return "https://leetcode-cn.com/problems/same-tree/";
}

std::string IsSameTree::Solution() {
    return "DFS，时间：O(min(n,m))，空间：O(min(n,m))，n，m 分别为两棵树的节点数。\n";
}

void IsSameTree::Benchmark() {
    IsSameTree solution;
    std::vector<std::string> sp{
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
    };
    std::vector<std::string> sq{
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","7","8","9",
        "0","1","2","3","4","5","6","null","8","9",
        "0","1","2","3","4","5","6","7","8","9",
    };

    TreeNode *p = NewTree(sp);
    TreeNode *q = NewTree(sq);
    
    benchmark::RegisterBenchmark("BM_IsSameTree_DFS", [](benchmark::State &state, IsSameTree solution, TreeNode *p, TreeNode *q) {
        for (auto _ : state) {
            solution.Solution1(p, q);
        }
    }, solution, p, q);

    benchmark::RegisterBenchmark("BM_IsSameTree_BFS", [](benchmark::State &state, IsSameTree solution, TreeNode *p, TreeNode *q) {
        for (auto _ : state) {
            solution.Solution2(p, q);
        }
    }, solution, p, q);


    //DeleteTree(p);
    //DeleteTree(q);
}

bool IsSameTree::Solution1(TreeNode *p, TreeNode *q) {
    if (p == nullptr && q == nullptr) {
        return true;
    } else if (p == nullptr || q == nullptr || p->val != q->val) {
        return false;
    } else {
        return Solution1(p->left, q->left) && Solution1(p->right, q->right);
    }
}

bool IsSameTree::Solution2(TreeNode *p, TreeNode *q) {
    std::queue<TreeNode *> cmp_queue;
    cmp_queue.emplace(p);
    cmp_queue.emplace(q);
    while (!cmp_queue.empty()) {
        TreeNode *cur_p = cmp_queue.front();
        cmp_queue.pop();
        TreeNode *cur_q = cmp_queue.front();
        cmp_queue.pop();
        if (cur_p == nullptr && cur_q == nullptr) {
            continue;
        } else if (cur_p == nullptr || cur_q == nullptr || cur_p->val != cur_q->val) {
            return false;
        } else {
            cmp_queue.emplace(cur_p->left);
            cmp_queue.emplace(cur_q->left);

            cmp_queue.emplace(cur_p->right);
            cmp_queue.emplace(cur_q->right);
        }
    }
    return true;
}



} // namespace tree
} // namespace leetcode
