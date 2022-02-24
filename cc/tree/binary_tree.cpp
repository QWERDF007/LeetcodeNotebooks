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
        case SolutionsId::PREORDER_TRAVERSAL: solution = new PreorderTraversal(); break;
        case SolutionsId::INORDER_TRAVERSAL: solution = new InorderTraversal(); break;
        case SolutionsId::POSTORDER_TRAVERSAL: solution = new PostorderTraversal(); break;
        case SolutionsId::IS_SAME_TREE: solution = new IsSameTree(); break;
        case SolutionsId::IS_BALANCED: solution = new IsBalanced(); break;
        case SolutionsId::MIN_DEPTH: solution = new MinDepth(); break;
        case SolutionsId::HAS_PATH_SUM: solution = new HasPathSum(); break;
        case SolutionsId::UPSIDE_DOWN_BINARY_TREE: solution = new UpsideDownBinaryTree(); break;
        case SolutionsId::INVERT_TREE: solution = new InvertTree(); break;
        case SolutionsId::BINARY_TREE_PATHS: solution = new BinaryTreePaths(); break;
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


void LevelOrderTraversal(TreeNode *root, std::vector<int> &res) {
    if (!root) {
        return;
    }
    std::queue<TreeNode *> que;
    que.emplace(root);
    while (!que.empty()) {
        TreeNode *cur = que.front();
        que.pop();
        res.emplace_back(cur->val);
        if (cur->left) {
            que.emplace(cur->left);
        }
        if (cur->right) {
            que.emplace(cur->right);
        }
    }
}

int TreeHeight(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    } else {
        return std::max(TreeHeight(root->left), TreeHeight(root->right)) + 1;
    }
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


std::string PreorderTraversal::Title() {
    return "144. 二叉树的前序遍历\n";
}

std::string PreorderTraversal::Problem() {
    return "给你二叉树的根节点 root，返回它节点值的前序遍历。\n";
}

std::string PreorderTraversal::Link() {
    return "https://leetcode-cn.com/problems/binary-tree-preorder-traversal/";
}

std::string PreorderTraversal::Solution() {
    return "递归，时间：O(n)，空间：O(h)，h 为二叉树高度。\n";
}

void PreorderTraversal::Benchmark() {
    PreorderTraversal solution;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-100, 100);
    int null = dis(gen);
    int n = 1000;
    std::vector<std::string> str_tree(n);
    for (int i = 0; i < n; ++i) {
        int v = dis(gen);
        if (v != null) {
            str_tree[i] = std::to_string(v);
        }
        else {
            str_tree[i] = "null";
        }
    }
    TreeNode *root = NewTree(str_tree);

    benchmark::RegisterBenchmark("BM_PreorderTraversal_Recursion", [](benchmark::State &state, PreorderTraversal solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_PreorderTraversal_Iteration", [](benchmark::State &state, PreorderTraversal solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution2(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_PreorderTraversal_Morris", [](benchmark::State &state, PreorderTraversal solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution3(root);
        }
    }, solution, root);
    //DeleteTree(root);
}

std::vector<int> PreorderTraversal::Solution1(TreeNode *root) {
    std::vector<int> res;
    PreOrderTraversal(root, res);
    return res;
}

std::vector<int> PreorderTraversal::Solution2(TreeNode *root) {
    std::vector<int> res;
    std::stack<TreeNode *> stk;
    TreeNode *cur = root;
    while (cur != nullptr || !stk.empty()) {
        while (cur != nullptr) {
            res.emplace_back(cur->val);
            stk.emplace(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();
        cur = cur->right;
    }
    return res;
}

std::vector<int> PreorderTraversal::Solution3(TreeNode *root) {
    std::vector<int> res;
    TreeNode *cur = root, *predecessor = nullptr;
    while (cur) {
        if (cur->left) {
            predecessor = cur->left;
            // 找到 cur 中序遍历的前驱节点，即准备输出 cur 的前一个节点
            while (predecessor->right && predecessor->right != cur) {
                predecessor = predecessor->right;
            }
            // 第一次遍历到前驱，前驱节点的右节点指向 cur
            if (predecessor->right == nullptr) {
                res.emplace_back(cur->val);
                predecessor->right = cur;
                cur = cur->left;
            } 
            // 第二次遍历到前驱，说明左子树遍历完了
            else {
                predecessor->right = nullptr;
                cur = cur->right; // 进入右子树
            }
        } else {
            res.emplace_back(cur->val);
            cur = cur->right; // 回退根节点或进入右子树
        }
    }
    return res;
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
    return "递归，时间：O(n)，空间：O(h)，h 为二叉树高度。\n";
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
            str_tree[i] = std::to_string(v);
        } else {
            str_tree[i] = "null";
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


std::string PostorderTraversal::Title() {
    return "145. 二叉树的后序遍历\n";
}

std::string PostorderTraversal::Problem() {
    return "给你一棵二叉树的根节点 root，返回其节点值的后序遍历。\n";
}

std::string PostorderTraversal::Link() {
    return "https://leetcode-cn.com/problems/binary-tree-postorder-traversal/";
}

std::string PostorderTraversal::Solution() {
    return "递归，时间：O(n)，空间：O(h)，h 为二叉树高度。\n";
}

void PostorderTraversal::Benchmark() {
    PostorderTraversal solution;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-100, 100);
    int null = dis(gen);
    int n = 1000;
    std::vector<std::string> str_tree(n);
    for (int i = 0; i < n; ++i) {
        int v = dis(gen);
        if (v != null) {
            str_tree[i] = std::to_string(v);
        }
        else {
            str_tree[i] = "null";
        }
    }
    TreeNode *root = NewTree(str_tree);

    benchmark::RegisterBenchmark("BM_PostorderTraversal_Recursion", [](benchmark::State &state, PostorderTraversal solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_PostorderTraversal_Iteration", [](benchmark::State &state, PostorderTraversal solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution2(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_PostorderTraversal_Morris", [](benchmark::State &state, PostorderTraversal solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution3(root);
        }
    }, solution, root);
    //DeleteTree(root);
}

std::vector<int> PostorderTraversal::Solution1(TreeNode *root) {
    std::vector<int> res;
    PostOrderTraversal(root, res);
    return res;
}

std::vector<int> PostorderTraversal::Solution2(TreeNode *root) {
    std::vector<int> res;
    std::stack<TreeNode *> stk;
    TreeNode *cur = root, *prev = nullptr;
    while (cur != nullptr || !stk.empty()) {
        while (cur != nullptr) {
            stk.emplace(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();
        // 右子树为空或已经处理完则加入根节点，避免死循环
        if (cur->right == nullptr || cur->right == prev) {
            res.emplace_back(cur->val);
            prev = cur;
            cur = nullptr;
        } else {
            stk.emplace(cur);
            cur = cur->right;
        }
    }
    return res;
}

std::vector<int> PostorderTraversal::Solution3(TreeNode *root) {
    std::vector<int> res;
    TreeNode *cur = root, *predecessor = nullptr;
    while (cur) {
        predecessor = cur->left;
        if (predecessor) {
            while (predecessor->right && predecessor->right != cur) {
                predecessor = predecessor->right;
            }

            // 第一次访问到 cur 的中序遍历的前驱
            if (predecessor->right == nullptr) {
                predecessor->right = cur;
                cur = cur->left;
                continue;
            } 
            // 左子树访问完
            else {
                predecessor->right = nullptr;
                AddPath(cur->left, res);
                //cur = cur->right;
            }
        } 
        cur = cur->right;
    }
    AddPath(root, res);
    return res;
}

void PostorderTraversal::AddPath(TreeNode *root, std::vector<int> &res) {
    int count = 0;
    while (root) {
        ++count;
        res.emplace_back(root->val);
        root = root->right;
    }
    std::reverse(res.end() - count, res.end());
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



std::string IsBalanced::Title() {
    return "110. 平衡二叉树\n";
}

std::string IsBalanced::Problem() {
    return 
        "给定一个二叉树，判断它是否是高度平衡的二叉树。\n"
        "本题中，一棵高度平衡二叉树定义为：\n"
        "- 一个二叉树每个节点的左右两个子树的高度差的绝对值不超过 1。\n";
}

std::string IsBalanced::Link() {
    return "https://leetcode-cn.com/problems/balanced-binary-tree/";
}

std::string IsBalanced::Solution() {
    return "自底向上递归，时间：O(n)，空间：O(n)。\n";
}

void IsBalanced::Benchmark() {
    IsBalanced solution;

    int n = 50000;
    int range = 10000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-range, range);
    int null = dis(gen);
    
    std::vector<std::string> str_tree(n);
    for (int i = 0; i < n; ++i) {
        int v = dis(gen);
        if (v != null) {
            str_tree[i] = std::to_string(v);
        }
        else {
            str_tree[i] = "null";
        }
    }
    TreeNode *root = NewTree(str_tree);

    benchmark::RegisterBenchmark("BM_IsBalanced_TopToDown", [](benchmark::State &state, IsBalanced solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_IsBalanced_DownToTop", [](benchmark::State &state, IsBalanced solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution2(root);
        }
    }, solution, root);

    //DeleteTree(root);
}

bool IsBalanced::Solution1(TreeNode *root) {
    if (root == nullptr) {
        return true;
    } else {
        return std::abs(TreeHeight(root->left) - TreeHeight(root->right)) <= 1 && Solution1(root->left) && Solution1(root->right);
    }
}

bool IsBalanced::Solution2(TreeNode *root) {
    return Height(root) >= 0;
}

int IsBalanced::Height(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    int left_height = Height(root->left);
    int right_height = Height(root->right);
    if (left_height == -1 || right_height == -1 || std::abs(left_height - right_height) > 1) {
        return -1;
    } else {
        return std::max(left_height, right_height) + 1;
    }
}


std::string MinDepth::Title() {
    return "111. 二叉树的最小深度\n";
}

std::string MinDepth::Problem() {
    return 
        "给定一个二叉树，找出其最小深度。\n"
        "最小深度是从根节点到最近叶子节点的最短路径上的节点数量。\n"
        "说明：叶子节点是指没有子节点的节点。\n";
}

std::string MinDepth::Link() {
    return "https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/";
}

std::string MinDepth::Solution() {
    return "DFS，时间：O(n)，空间：O(h)，h 为二叉树高度。\n";
}

void MinDepth::Benchmark() {
    MinDepth solution;

    int n = 1000;
    int range = 1000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-range, range);
    int null = dis(gen);

    std::vector<std::string> str_tree(n);
    for (int i = 0; i < n; ++i) {
        int v = dis(gen);
        if (v != null) {
            str_tree[i] = std::to_string(v);
        } else {
            str_tree[i] = "null";
        }
    }

    TreeNode *root = NewTree(str_tree);

    benchmark::RegisterBenchmark("BM_MinDepth_DFS", [](benchmark::State &state, MinDepth solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_MinDepth_BFS", [](benchmark::State &state, MinDepth solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution2(root);
        }
    }, solution, root);

    //DeleteTree(root);
}

int MinDepth::Solution1(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    } else if (root->left == nullptr && root->right == nullptr) {
        return 1;
    } else if (root->left == nullptr){
        return Solution1(root->right) + 1;
    } else if (root->right == nullptr) {
        return Solution1(root->left) + 1;
    } else {
        return std::min(Solution1(root->left), Solution1(root->right)) + 1;
    }
}

int MinDepth::Solution2(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    int depth = 1;
    std::queue<TreeNode *> que;
    que.emplace(root);
    while (!que.empty()) {
        int n = que.size();
        for (int i = 0; i < n; ++i) {
            TreeNode *cur = que.front();
            que.pop();
            if (cur->left == nullptr && cur->right == nullptr) {
                return depth;
            }
            if (cur->left) {
                que.emplace(cur->left);
            }
            if (cur->right) {
                que.emplace(cur->right);
            }
        }
        ++depth;
    }
    return depth;
}

std::string HasPathSum::Title() {
    return "112. 路径总和\n";
}

std::string HasPathSum::Problem() {
    return 
        "给你二叉树的根节点 root 和一个表示目标和的整数 targetSum。\n"
        "判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和 targetSum。\n"
        "如果存在，返回 true；否则，返回 false。\n"
        "叶子节点是指没有子节点的节点。\n";
}

std::string HasPathSum::Link() {
    return "https://leetcode-cn.com/problems/path-sum/";
}

std::string HasPathSum::Solution() {
    return "DFS，时间：O(n)，空间：O(h)，h 为二叉树高度。\n";
}

void HasPathSum::Benchmark() {
    HasPathSum solution;

    int n = 1000;
    std::vector<std::string> s_tree(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1000, 1000);
    int null = dis(gen);
    int target = dis(gen);
    for (int i = 0; i < n; ++i) {
        int v = dis(gen);
        if (v != null) {
            s_tree[i] = std::to_string(v);
        } else {
            s_tree[i] = "null";
        }
    }

    TreeNode *root = NewTree(s_tree);

    benchmark::RegisterBenchmark("BM_HasPathSum_DFS", [](benchmark::State &state, HasPathSum solution, TreeNode *root, int target) {
        for (auto _ : state) {
            solution.Solution1(root, target);
        }
    }, solution, root, target);

    benchmark::RegisterBenchmark("BM_HasPathSum_BFS_PAIR", [](benchmark::State &state, HasPathSum solution, TreeNode *root, int target) {
        for (auto _ : state) {
            solution.Solution2(root, target);
        }
    }, solution, root, target);

    benchmark::RegisterBenchmark("BM_HasPathSum_BFS_DualQueue", [](benchmark::State &state, HasPathSum solution, TreeNode *root, int target) {
        for (auto _ : state) {
            solution.Solution3(root, target);
        }
    }, solution, root, target);
    //DeleteTree(root);
}

bool HasPathSum::Solution1(TreeNode *root, int targetSum) {
    if (root == nullptr) {
        return false;
    } else if (root->left == nullptr && root->right == nullptr) {
        return root->val == targetSum;
    } else {
        return Solution1(root->left, targetSum - root->val) || Solution1(root->right, targetSum - root->val);
    }
}

bool HasPathSum::Solution2(TreeNode *root, int targetSum) {
    if (!root) {
        return false;
    }
    std::queue<std::pair<TreeNode *, int>> que;
    que.emplace(root, 0);
    while (!que.empty()) {
        TreeNode *cur = que.front().first;
        int sum = que.front().second + cur->val;
        que.pop();
        if (!cur->left && !cur->right && sum == targetSum) {
            return true;
        }
        if (cur->left) {
            que.emplace(cur->left, sum);
        }
        if (cur->right) {
            que.emplace(cur->right, sum);
        }
    }
    return false;
}

bool HasPathSum::Solution3(TreeNode *root, int targetSum) {
    if (!root) {
        return false;
    }
    std::queue<TreeNode *> que_tree;
    std::queue<int> que_sum;
    que_tree.emplace(root);
    que_sum.emplace(0);
    while (!que_tree.empty()) {
        TreeNode *cur = que_tree.front();
        int sum = que_sum.front() + cur->val;
        que_tree.pop();
        que_sum.pop();
        if (!cur->left && !cur->right && sum == targetSum) {
            return true;
        }
        if (cur->left) {
            que_tree.emplace(cur->left);
            que_sum.emplace(sum);
        }
        if (cur->right) {
            que_tree.emplace(cur->right);
            que_sum.emplace(sum);
        }
    }
    return false;
}

std::string UpsideDownBinaryTree::Title() {
    return "156. 上下翻转二叉树\n";
}

std::string UpsideDownBinaryTree::Problem() {
    return 
        "给你一个二叉树的根节点 root，请你将此二叉树上下翻转，并返回新的根节点。\n"
        "你可以按下面的步骤翻转一棵二叉树：\n"
        "1. 原来的左子节点变成新的根节点\n"
        "2. 原来的根节点变成新的右子节点\n"
        "3. 原来的右子节点变成新的左子节点\n"
        "上面的步骤逐层进行。题目数据保证每个右节点都有一个同级节点（即共享同一父节点的左节点）且不存在子节点。\n";
}

std::string UpsideDownBinaryTree::Link() {
    return "https://leetcode-cn.com/problems/binary-tree-upside-down/";
}

std::string UpsideDownBinaryTree::Solution() {
    return "TODO\n";
}

void UpsideDownBinaryTree::Benchmark() {
}

TreeNode *UpsideDownBinaryTree::Solution1(TreeNode *root) {
    TreeNode *right = nullptr, *father = nullptr;
    while (root) {
        // 记录当前节点的左子节点
        TreeNode *left = root->left;
        // 更新当前节点左节点为父节点的右节点
        root->left = right;
        // 记录当前节点的右子节点
        right = root->right;
        // 跟新当前节点的右子节点为原父节点
        root->right = father;
        // 记录当前节点作为下一个待遍历节点的父节点
        father = root;
        root = left;
        // 最终 root=nullptr ，father 指向翻转后的二叉树的根节点
    }
    return father;
}

std::string InvertTree::Title() {
    return "226. 翻转二叉树\n";
}

std::string InvertTree::Problem() {
    return "给你一棵二叉树的根节点 root，翻转这棵二叉树，并返回其根节点。\n";
}

std::string InvertTree::Link() {
    return "https://leetcode-cn.com/problems/invert-binary-tree/";
}

std::string InvertTree::Solution() {
    return "DFS，时间：O(n)，空间：O(h)，h 为二叉树高度。\n";
}

void InvertTree::Benchmark() {
    InvertTree solution;

    int n = 1000;
    std::vector<std::string> s_tree(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1000, 1000);
    int null = dis(gen);
    int target = dis(gen);
    for (int i = 0; i < n; ++i) {
        int v = dis(gen);
        if (v != null) {
            s_tree[i] = std::to_string(v);
        }
        else {
            s_tree[i] = "null";
        }
    }

    TreeNode *root = NewTree(s_tree);

    benchmark::RegisterBenchmark("BM_InvertTree_DFS", [](benchmark::State &state, InvertTree solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_InvertTree_BFS", [](benchmark::State &state, InvertTree solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution2(root);
        }
    }, solution, root);

    //DeleteTree(root);
}

TreeNode *InvertTree::Solution1(TreeNode *root) {
    if (root == nullptr) {
        return nullptr;
    }
    TreeNode *left = Solution1(root->left);
    TreeNode *right = Solution1(root->right);
    root->left = right;
    root->right = left;
    return root;
}

TreeNode *InvertTree::Solution2(TreeNode *root) {
    if (root == nullptr) {
        return nullptr;
    }
    std::queue<TreeNode *> que;
    que.emplace(root);
    while (!que.empty()) {
        TreeNode *cur = que.front();
        que.pop();
        TreeNode *tmp = cur->left;
        cur->left = cur->right;
        cur->right = tmp;
        if (cur->left) {
            que.emplace(cur->left);
        }
        if (cur->right) {
            que.emplace(cur->right);
        }
    }
    return root;
}

std::string BinaryTreePaths::Title() {
    return "257. 二叉树的所有路径\n";
}

std::string BinaryTreePaths::Problem() {
    return 
        "给你一个二叉树的根节点 root，按任意顺序，返回所有从根节点到叶子节点的路径。\n"
        "叶子节点是指没有子节点的节点。\n";
}

std::string BinaryTreePaths::Link() {
    return "https://leetcode-cn.com/problems/binary-tree-paths/";
}

std::string BinaryTreePaths::Solution() {
    return "DFS，时间：O(n^2)，空间：O(h^2)。\n";
}

void BinaryTreePaths::Benchmark() {
    BinaryTreePaths solution;

    int n = 1000;
    std::vector<std::string> s_tree(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-100, 100);
    int null = dis(gen);
    int target = dis(gen);
    for (int i = 0; i < n; ++i) {
        int v = dis(gen);
        if (v != null) {
            s_tree[i] = std::to_string(v);
        }
        else {
            s_tree[i] = "null";
        }
    }

    TreeNode *root = NewTree(s_tree);

    benchmark::RegisterBenchmark("BM_BinaryTreePaths_DFS", [](benchmark::State &state, BinaryTreePaths solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_BinaryTreePaths_BFS", [](benchmark::State &state, BinaryTreePaths solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution2(root);
        }
    }, solution, root);

    //DeleteTree(root);
}

std::vector<std::string> BinaryTreePaths::Solution1(TreeNode *root) {
    std::vector<std::string> paths;
    TreePaths(root, paths, "");
    return paths;
}

std::vector<std::string> BinaryTreePaths::Solution2(TreeNode *root) {
    std::vector<std::string> paths;
    if (root == nullptr) {
        return paths;
    }
    std::queue<TreeNode *> que_node;
    std::queue<std::string> que_path;
    que_node.emplace(root);
    que_path.emplace("");
    while (!que_node.empty()) {
        TreeNode *cur = que_node.front();
        std::string path = que_path.front();
        que_node.pop();
        que_path.pop();
        path += std::to_string(cur->val);
        if (cur->left == nullptr && cur->right == nullptr) {
            paths.emplace_back(path);
        } else {
            path += "->";
            if (cur->left) {
                que_node.emplace(cur->left);
                que_path.emplace(path);
            }
            if (cur->right) {
                que_node.emplace(cur->right);
                que_path.emplace(path);
            }
        }
    }
    return paths;
}

void BinaryTreePaths::TreePaths(TreeNode *root, std::vector<std::string> &paths, std::string path) {
    if (root) {
        path += std::to_string(root->val);
        if (root->left == nullptr && root->right == nullptr) {
            paths.emplace_back(path);
        } else {
            path += "->";
            TreePaths(root->left, paths, path);
            TreePaths(root->right, paths, path);
        }
    }
}


} // namespace tree
} // namespace leetcode
