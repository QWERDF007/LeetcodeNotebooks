#include <stack>
#include <queue>
#include <deque>
#include <random>
#include <climits>
#include <iostream>
#include <functional>
#include <benchmark/benchmark.h>

#include "tree.h"

namespace leetcode {
namespace tree {

void TreeSolution(SolutionsId pid) {
    LeetcodeSolution *solution = nullptr;
	switch (pid) {
        case SolutionsId::PREORDER_TRAVERSAL: solution = new PreorderTraversal(); break;
        case SolutionsId::INORDER_TRAVERSAL: solution = new InorderTraversal(); break;
        case SolutionsId::POSTORDER_TRAVERSAL: solution = new PostorderTraversal(); break;
        case SolutionsId::GENERATE_TREES: solution = new GenerateTrees(); break;
        case SolutionsId::RECOVER_TREE: solution = new RecoverTree(); break;
        case SolutionsId::IS_SAME_TREE: solution = new IsSameTree(); break;
        case SolutionsId::ZIGZAG_LEVEL_ORDER: solution = new ZigzagLevelOrder(); break;
        case SolutionsId::IS_BALANCED: solution = new IsBalanced(); break;
        case SolutionsId::MIN_DEPTH: solution = new MinDepth(); break;
        case SolutionsId::HAS_PATH_SUM: solution = new HasPathSum(); break;
        case SolutionsId::UPSIDE_DOWN_BINARY_TREE: solution = new UpsideDownBinaryTree(); break;
        case SolutionsId::INVERT_TREE: solution = new InvertTree(); break;
        case SolutionsId::LOWEST_COMMON_ANCESTOR: solution = new LowestCommonAncestor(); break;
        case SolutionsId::BINARY_TREE_PATHS: solution = new BinaryTreePaths(); break;
        case SolutionsId::SUM_OF_LEFT_LEAVES: solution = new SumOfLeftLeaves(); break;
        case SolutionsId::FIND_MODE: solution = new FindMode(); break;
        case SolutionsId::FIND_TILT: solution = new FindTilt(); break;
        case SolutionsId::IS_SUBTREE: solution = new IsSubtree(); break;
        case SolutionsId::PREORDER: solution = new Preorder(); break;
        case SolutionsId::POSTORDER: solution = new Postorder(); break;
        case SolutionsId::TREE_2_STR: solution = new Tree2Str(); break;
        case SolutionsId::AVERAGE_OF_LEVELS: solution = new AverageOfLevels(); break;
        case SolutionsId::FIND_TARGET: solution = new FindTarget(); break;
        case SolutionsId::FIND_SECOND_MINIMUM_VALUE: solution = new FindSecondMinimumValue(); break;
        case SolutionsId::SEARCH_BST: solution = new SearchBST(); break;
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

TreeNode *NewBinaryTree(std::vector<std::string> &tree) {
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

void CopyBinaryTree(TreeNode *root, TreeNode *&copy) {
    if (root == nullptr) {
        return;
    }
    copy = new TreeNode(root->val);
    CopyBinaryTree(root->left, copy->left);
    CopyBinaryTree(root->right, copy->right);
}


TreeNode *NewRandomBinaryTree(int n, int a, int b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(a, b);
    std::vector<std::string> s_tree(n);
    int null = dis(gen);
    for (int i = 0; i < n; ++i) {
        int v = dis(gen);
        if (v != null) {
            s_tree[i] = std::to_string(v);
        }
        else {
            s_tree[i] = "null";
        }
    }
    TreeNode *root = NewBinaryTree(s_tree);
    return root;
}


void DeleteBinaryTree(TreeNode *root) {
    if (root == nullptr) {
        return;
    }
    DeleteBinaryTree(root->left);
    DeleteBinaryTree(root->right);
    delete root;
}

Node *NewNAryTree(std::vector<std::string> &tree) {
    int n = tree.size();
    if (n == 0) {
        return nullptr;
    }
    Node *root = new Node(std::stoi(tree[0])), *cur = root;
    std::queue<Node *> q;
    int i = 1;
    while (i < n) {
        if (!q.empty() && tree[i] == "null") { // 处理下一组子节点
            cur = q.front();
            q.pop();
        } else if (tree[i] != "null") { // 当前节点添加新子节点
            Node *child = new Node(std::stoi(tree[i]));
            cur->children.emplace_back(child);
            q.emplace(child);
        }
        ++i;
    }
    return root;
}

void DeleteNAryTree(Node *root) {
    if (root == nullptr) {
        return;
    }
    for (Node *child : root->children) {
        DeleteNAryTree(child);
    }
    delete root;
}

Node *NewRandomNAryTree(int n, int a, int b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(a, b);
    std::vector<std::string> s_tree(n);
    int null = dis(gen);
    for (int i = 0; i < n; ++i) {
        int v = dis(gen);
        if (v != null) {
            s_tree[i] = std::to_string(v);
        }
        else {
            s_tree[i] = "null";
        }
    }
    Node *root = NewNAryTree(s_tree);
    return root;
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
    TreeNode *root = NewBinaryTree(str_tree);

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
    //DeleteBinaryTree(root);
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
    TreeNode *root = NewBinaryTree(str_tree);

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
    //DeleteBinaryTree(root);
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
    TreeNode *root = NewBinaryTree(str_tree);

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
    //DeleteBinaryTree(root);
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



std::string GenerateTrees::Title() {
    return "95. 不同的二叉搜索树 II\n";
}

std::string GenerateTrees::Problem() {
    return "给你一个整数 n，请你生成并返回所有由 n 个节点组成且节点值从 1 到 n 互不相同的不同二叉搜索树。可以按任意顺序返回答案。\n";
}

std::string GenerateTrees::Link() {
    return "https://leetcode-cn.com/problems/unique-binary-search-trees-ii/";
}

std::string GenerateTrees::Solution() {
    return "回溯，时间：O(nGn)，空间：O(nGn)，Gn 是生成 n 个卡特兰数所需时间空间，O(4^n/n^{3/2})";
}

void GenerateTrees::Benchmark() {
    GenerateTrees solution;
    int n = 10;
    benchmark::RegisterBenchmark("BM_GenerateTrees_TraceBack", [](benchmark::State &state, GenerateTrees solution, int n) {
        for (auto _ : state) {
            solution.Solution1(n);
        }
    }, solution, n);
}

std::vector<TreeNode *> GenerateTrees::Solution1(int n) {
    if (n <= 0) {
        return {};
    }
    return GenTrees(1, n);
}

std::vector<TreeNode *> GenerateTrees::GenTrees(int start, int end) {
    if (start > end) {
        return { nullptr };
    }
    std::vector<TreeNode *> all_trees;
    for (int i = start; i <= end; ++i) {
        // 生成左子树和右子树
        std::vector<TreeNode *> left_trees = GenTrees(start, i - 1);
        std::vector<TreeNode *> right_trees = GenTrees(i + 1, end);
        // 从左和右子树中分别选一棵，拼接到根节点上形成二叉搜索树
        for (TreeNode *left : left_trees) {
            for (TreeNode *right : right_trees) {
                TreeNode *cur = new TreeNode(i);
                cur->left = left;
                cur->right = right;
                all_trees.emplace_back(cur);
            }
        }
    }
    return all_trees;
}


std::string RecoverTree::Title() {
    return "99. 恢复二叉搜索树\n";
}

std::string RecoverTree::Problem() {
    return "给你二叉搜索树的根节点 root，该树中的恰好两个节点的值被错误地交换。请在不改变其结构的情况下，恢复这棵树。\n";
}

std::string RecoverTree::Link() {
    return "https://leetcode-cn.com/problems/recover-binary-search-tree/";
}

std::string RecoverTree::Solution() {
    return "隐式递归遍历，时间：O(n)，空间：O(h)。\n";
}

void RecoverTree::Benchmark() {
    RecoverTree solution;
    std::vector<std::string> s_tree{
        "390","255","2266","-273","337","1105","3440","-425","4113","null","null","600","1355","3241","4731",
        "-488","-367","16","null","565","780","1311","1755","3075","3392","4725","4817","null","null","null",
        "null","-187","152","395","null","728","977","1270","null","1611","1786","2991","3175","3286","null",
        "164","null","null","4864","-252","-95","82","null","391","469","638","769","862","1045","1138","null",
        "1460","1663","null","1838","2891","null","null","null","null","3296","3670","4381","null","4905","null",
        "null","null","-58","null","null","null","null","null","null","null","null","734","null","843","958",
        "null","null","null","1163","1445","1533","null","null","null","2111","2792","null","null","null",
        "3493","3933","4302","4488","null","null","null","null","null","null","819","null","null","null",
        "null","1216","null","null","1522","null","1889","2238","2558","2832","null","3519","3848","4090",
        "4165","null","4404","4630","null","null","null","null","null","null","1885","2018","2199","null",
        "2364","2678","null","null","null","3618","3751","null","4006","null","null","4246","null","null",
        "4554","null","null","null","1936","null","null","null","null","2444","2642","2732","null","null",
        "null","null","null","null","null","4253","null","null","null","null","2393","2461","null","null",
        "null","null","4250","null","null","null","null","2537" 
    };
    TreeNode *root = NewBinaryTree(s_tree);

    benchmark::RegisterBenchmark("BM_RecoverTree_ExplicitTraversal", [](benchmark::State &state, RecoverTree solution, TreeNode *root) {
        for (auto _ : state) {
            TreeNode *cur = nullptr;
            CopyBinaryTree(root, cur);
            solution.Solution1(cur);
            DeleteBinaryTree(cur);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_RecoverTree_ImplicitIteration", [](benchmark::State &state, RecoverTree solution, TreeNode *root) {
        for (auto _ : state) {
            TreeNode *cur = nullptr;
            CopyBinaryTree(root, cur);
            solution.Solution2(cur);
            DeleteBinaryTree(cur);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_RecoverTree_ImplicitRecursion", [](benchmark::State &state, RecoverTree solution, TreeNode *root) {
        for (auto _ : state) {
            TreeNode *cur = nullptr;
            CopyBinaryTree(root, cur);
            solution.Solution3(cur);
            DeleteBinaryTree(cur);
        }
    }, solution, root);

    //DeleteBinaryTree(root);
}

void RecoverTree::Solution1(TreeNode *root) {
    std::vector<int> nums;
    InOrderTraversal(root, nums);
    int num1, num2;
    FindTwoSwapped(nums, num1, num2);
    Recover(root, 2, num1, num2);
}

void RecoverTree::Solution2(TreeNode *root) {
    std::stack<TreeNode *> stk;
    TreeNode *cur = root, *pred = nullptr;
    TreeNode *x = nullptr, *y = nullptr;
    while (!stk.empty() || cur) {
        while (cur) {
            stk.emplace(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();
        if (pred && cur->val < pred->val) {
            y = cur;
            if (x == nullptr) {
                x = pred;
            } else {
                break;
            }
        }
        pred = cur;
        cur = cur->right;
    }
    if (x && y) {
        std::swap(x->val, y->val);
    }
}

void RecoverTree::Solution3(TreeNode *root) {
    TreeNode *pred = nullptr, *x = nullptr, *y = nullptr;
    Inorder(root, pred, x, y);
    if (x && y) {
        std::swap(x->val, y->val);
    }
}

void RecoverTree::FindTwoSwapped(std::vector<int> &nums, int &num1, int &num2) {
    int n = nums.size();
    int index1 = -1, index2 = -1;
    for (int i = 1; i < n; ++i) {
        if (nums[i] < nums[i - 1]) {
            index2 = i;
            if (index1 == -1) {
                index1 = i - 1;
            } else {
                break;
            }
        }
    }
    num1 = nums[index1];
    num2 = nums[index2];
}

void RecoverTree::Recover(TreeNode *root, int count, int num1, int num2) {
    if (root == nullptr) {
        return;
    }
    if (root->val == num1 || root->val == num2) {
        root->val = root->val == num1 ? num2 : num1;
        if (--count == 0) {
            return;
        }
    }
    Recover(root->left, count, num1, num2);
    Recover(root->right, count, num1, num2);
}

void RecoverTree::Inorder(TreeNode *root, TreeNode *&pred, TreeNode *&x, TreeNode *&y) {
    if (root == nullptr) {
        return;
    }
    Inorder(root->left, pred, x, y);
    if (pred && root->val < pred->val) {
        y = root;
        if (x == nullptr) {
            x = pred;
        } else {
            return;
        }
    }
    pred = root;
    Inorder(root->right, pred, x, y);
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

    TreeNode *p = NewBinaryTree(sp);
    TreeNode *q = NewBinaryTree(sq);
    
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


    //DeleteBinaryTree(p);
    //DeleteBinaryTree(q);
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


std::string ZigzagLevelOrder::Title() {
    return "103. 二叉树的锯齿形层序遍历\n";
}

std::string ZigzagLevelOrder::Problem() {
    return "给你二叉树的根节点 root，返回其节点值的锯齿形层序遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。\n";
}

std::string ZigzagLevelOrder::Link() {
    return "https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/";
}

std::string ZigzagLevelOrder::Solution() {
    return "双端队列，时间：O(n)，空间：O(n)。\n";
}

void ZigzagLevelOrder::Benchmark() {
    ZigzagLevelOrder solution;
    TreeNode *root = NewRandomBinaryTree(2000, -100, 100);

    benchmark::RegisterBenchmark("BM_ZigzagLevelOrder_Deque", [](benchmark::State &state, ZigzagLevelOrder solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    //DeleteBinaryTree(root);
}

std::vector<std::vector<int>> ZigzagLevelOrder::Solution1(TreeNode *root) {
    std::vector<std::vector<int>> ans;
    if (root == nullptr) {
        return ans;
    }
    std::queue<TreeNode *> q;
    q.emplace(root);
    bool isReversed = false;
    while (!q.empty()) {
        int n = q.size();
        std::deque<int> layer;
        for (int i = 0; i < n; ++i) {
            TreeNode *cur = q.front();
            q.pop();
            if (isReversed) {
                layer.emplace_front(cur->val);
            } else {
                layer.emplace_back(cur->val);
            }
            if (cur->left) {
                q.emplace(cur->left);
            }
            if (cur->right) {
                q.emplace(cur->right);
            }
        }
        isReversed = !isReversed;
        ans.emplace_back(std::vector<int>{ layer.begin(), layer.end() });
    }
    return ans;
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
    TreeNode *root = NewBinaryTree(str_tree);

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

    //DeleteBinaryTree(root);
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

    TreeNode *root = NewBinaryTree(str_tree);

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

    //DeleteBinaryTree(root);
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

    TreeNode *root = NewBinaryTree(s_tree);

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
    //DeleteBinaryTree(root);
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
    return "层序遍历，时间：O(h)，空间：O(1)，h 为二叉树高度。\n";
}

void UpsideDownBinaryTree::Benchmark() {
    UpsideDownBinaryTree solution;
    std::vector<std::string> s_tree{
         "1","2","3","4","5","null","null","6","7","null","null","8","9"
    };
    
    benchmark::RegisterBenchmark("BM_UpsideDownBinaryTree_Simulate", [](benchmark::State &state, UpsideDownBinaryTree solution, std::vector<std::string> s_tree) {
        for (auto _ : state) {
            TreeNode *root = NewBinaryTree(s_tree);
            root = solution.Solution1(root);
            DeleteBinaryTree(root);
        }
    }, solution, s_tree);
}

TreeNode *UpsideDownBinaryTree::Solution1(TreeNode *root) {
    TreeNode *right = nullptr, *father = nullptr;
    while (root) {
        // 记录当前节点的左子节点，待下一次遍历
        TreeNode *left = root->left;
        // 更新当前节点左节点为父节点的右节点
        root->left = right;
        // 记录当前节点的右子节点
        right = root->right;
        // 更新当前节点的右子节点为原父节点
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

    TreeNode *root = NewBinaryTree(s_tree);

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

    //DeleteBinaryTree(root);
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


std::string LowestCommonAncestor::Title() {
    return "235. 二叉搜索树的最近公共祖先\n";
}

std::string LowestCommonAncestor::Problem() {
    return 
        "给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。\n"
        "百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，\n"
        "最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”\n";
}

std::string LowestCommonAncestor::Link() {
    return "https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree/";
}

std::string LowestCommonAncestor::Solution() {
    return "递归，时间：O(n)，空间：O(h)，h 为二叉树高度。\n";
}

void LowestCommonAncestor::Benchmark() {
    LowestCommonAncestor solution;
    std::vector<std::string> s_tree{
        "28","12","45","4","24","35","47","2","9","14","25","31","42","46","48","0","3","8","11","13","20",
        "null","26","30","33","41","43","null","null","null","49","null","1","null","null","7","null","10",
        "null","null","null","17","22","null","27","29","null","32","34","36","null","null","44","null","null",
        "null","null","6","null","null","null","16","18","21","23","null","null","null","null","null","null",
        "null","null","null","37","null","null","5","null","15","null","null","19","null","null","null","null",
        "null","40","null","null","null","null","null","null","39","null","38",
    };
    TreeNode *root = NewBinaryTree(s_tree);
    TreeNode *p = new TreeNode(1);
    TreeNode *q = new TreeNode(23);

    auto func1 = [](benchmark::State &state, LowestCommonAncestor solution, TreeNode *root, TreeNode *p, TreeNode *q) {
        for (auto _ : state) {
            solution.Solution1(root, p, q);
        }
    };
    benchmark::RegisterBenchmark("BM_LowestCommonAncestor_Recursion", func1, solution, root, p, q);

    auto func2 = [](benchmark::State &state, LowestCommonAncestor solution, TreeNode *root, TreeNode *p, TreeNode *q) {
        for (auto _ : state) {
            solution.Solution2(root, p, q);
        }
    };
    benchmark::RegisterBenchmark("BM_LowestCommonAncestor_Traversal", func2, solution, root, p, q);

    //DeleteBinaryTree(root);
    //delete p;
    //delete q;
}

TreeNode *LowestCommonAncestor::Solution1(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (p->val < root->val && q->val < root->val) {
        return Solution1(root->left, p, q);
    } else if (p->val > root->val && q->val > root->val) {
        return Solution1(root->right, p, q);
    } else {
        return root;
    }
}

TreeNode *LowestCommonAncestor::Solution2(TreeNode *root, TreeNode *p, TreeNode *q) {
    std::vector<TreeNode *> p_path = GetPath(root, p);
    std::vector<TreeNode *> q_path = GetPath(root, q);
    int n = p_path.size(), m = q_path.size();
    TreeNode *ancestor = nullptr;
    for (int i = 0; i < n && i < m; ++i) {
        if (p_path[i] == q_path[i]) {
            ancestor = p_path[i];
        } else {
            break;
        }
    }
    return ancestor;
}

std::vector<TreeNode *> LowestCommonAncestor::GetPath(TreeNode *root, TreeNode *target) {
    std::vector<TreeNode *> path;
    TreeNode *cur = root;
    while (cur && cur->val != target->val) {
        path.emplace_back(cur);
        if (target->val < cur->val) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    path.emplace_back(cur); // 加入 target 节点
    return path;
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

    TreeNode *root = NewBinaryTree(s_tree);

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

    //DeleteBinaryTree(root);
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


std::string SumOfLeftLeaves::Title() {
    return "404. 左叶子之和\n";
}

std::string SumOfLeftLeaves::Problem() {
    return "给定二叉树的根节点 root，返回所有左叶子之和。\n";
}

std::string SumOfLeftLeaves::Link() {
    return "https://leetcode-cn.com/problems/sum-of-left-leaves/";
}

std::string SumOfLeftLeaves::Solution() {
    return "DFS，时间：O(n)，空间：O(h)，h 为二叉树高度。\n";
}

void SumOfLeftLeaves::Benchmark() {
    SumOfLeftLeaves solution;
    int n = 1000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1000, 1000);
    std::vector<std::string> s_tree(n);
    int null = dis(gen);
    for (int i = 0; i < n; ++i) {
        int v = dis(gen);
        if (v != null) {
            s_tree[i] = std::to_string(v);
        }
        else {
            s_tree[i] = "null";
        }
    }
    TreeNode *root = NewBinaryTree(s_tree);

    benchmark::RegisterBenchmark("BM_SumOfLeftLeaves_DFS", [](benchmark::State &state, SumOfLeftLeaves solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_SumOfLeftLeaves_BFS", [](benchmark::State &state, SumOfLeftLeaves solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution2(root);
        }
    }, solution, root);

    // DeleteBinaryTree(root);
}

int SumOfLeftLeaves::Solution1(TreeNode *root) {
    int ans = 0;
    if (root->left) {
        ans = IsLeafNode(root->left) ? root->left->val : Solution1(root->left);
    }
    if (root->right && !IsLeafNode(root->right)) {
        ans += Solution1(root->right);
    }
    return ans;
}

int SumOfLeftLeaves::Solution2(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    
    std::queue<TreeNode *> q;
    q.emplace(root);
    int ans = 0;
    while (!q.empty()) {
        TreeNode *cur = q.front();
        q.pop();
        if (cur->left) {
            if (IsLeafNode(cur->left)) {
                ans += cur->left->val;
            } else {
                q.emplace(cur->left);
            }
        }
        if (cur->right && !IsLeafNode(cur->right)) {
            q.emplace(cur->right);
        }
    }
    return ans;
}

bool SumOfLeftLeaves::IsLeafNode(TreeNode *node) {
    return !node->left && !node->right;
}


std::string FindMode::Title() {
    return "501. 二叉搜索树中的众数\n";
}

std::string FindMode::Problem() {
    return
        "给你一个含重复值的二叉搜索树（BST）的根节点 root，找出并返回 BST 中的所有众数（即，出现频率最高的元素）。\n"
        "如果树中有不止一个众数，可以按任意顺序返回。\n"
        "假定 BST 满足如下定义：\n"
        "- 结点左子树中所含节点的值小于等于当前节点的值\n"
        "- 结点右子树中所含节点的值大于等于当前节点的值\n"
        "- 左子树和右子树都是二叉搜索树\n";
}

std::string FindMode::Link() {
    return "https://leetcode-cn.com/problems/find-mode-in-binary-search-tree/";
}

std::string FindMode::Solution() {
    return "递归，时间：O(n)，空间：O(1)。\n";
}

void FindMode::Benchmark() {
    FindMode solution;

    std::vector<std::string> s_tree{
        "41","37","44","24","39","42","48","1","35","38","40","null","43","46","49","0",
        "2","30","36","null","null","null","null","null","null","45","47","null","null",
        "null","null","null","4","29","32","null","null","null","null","null","null","3",
        "9","26","null","31","34","null","null","7","11","25","27","null","null","33",
        "null","6","8","10","16","null","null","null","28","null","null","5","null","null",
        "null","null","null","15","19","null","null","null","null","12","null","18","20",
        "null","13","17","null","null","22","null","14","null","null","21","24"
    };

    TreeNode *root = NewBinaryTree(s_tree);

    benchmark::RegisterBenchmark("BM_FindMode_HashMap", [](benchmark::State &state, FindMode solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_FindMode_Recursion", [](benchmark::State &state, FindMode solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution2(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_FindMode_Iteration", [](benchmark::State &state, FindMode solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution3(root);
        }
    }, solution, root);

    //DeleteBinaryTree(root);
}

std::vector<int> FindMode::Solution1(TreeNode *root) {
    std::vector<int> nums, ans;
    std::unordered_map<int, int> counts;
    InOrderTraversal(root, nums);
    int max_count = 0;
    for (int num : nums) {
        ++counts[num];
        if (counts[num] > max_count) {
            max_count = counts[num];
        }
    }
    for (std::unordered_map<int, int>::iterator ite = counts.begin(); ite != counts.end(); ++ite) {
        if (ite->second == max_count) {
            ans.emplace_back(ite->first);
        }
    }
    std::min_element(nums.begin(), nums.end());
    return ans;
}

std::vector<int> FindMode::Solution2(TreeNode *root) {
    int base = 1e-5 - 1, count = 0, max_count = 0;
    std::vector<int> ans;
    Inorder(root, count, max_count, base, ans);
    return ans;
}

std::vector<int> FindMode::Solution3(TreeNode *root) {
    int base = 1e-5 - 1, count = 0, max_count = 0;
    std::vector<int> ans;
    if (!root) {
        return ans;
    }
    std::stack<TreeNode *> stk;
    TreeNode *cur = root;
    while (cur || !stk.empty()) {
        while (cur) {
            stk.emplace(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();
        Update(cur->val, count, max_count, base, ans);
        cur = cur->right;
    }
    return ans;
}

void FindMode::Inorder(TreeNode *root, int &count, int &max_count, int &base, std::vector<int> &ans) {
    if (!root) {
        return;
    }
    Inorder(root->left, count, max_count, base, ans);
    Update(root->val, count, max_count, base, ans);
    Inorder(root->right, count, max_count, base, ans);
}

void FindMode::Update(int num, int &count, int &max_count, int &base, std::vector<int> &ans) {
    if (num == base) {
        ++count;
    } else {
        count = 1;
        base = num;
    }

    if (count == max_count) {
        ans.emplace_back(num);
    } else if (count > max_count) {
        max_count = count;
        ans = std::vector<int>({ base });
    }
}

std::string FindTilt::Title() {
    return "563. 二叉树的坡度\n";
}

std::string FindTilt::Problem() {
    return 
        "给你一个二叉树的根节点 root，计算并返回整个树的坡度。\n"
        "一个树的节点的坡度定义即为，该节点左子树的节点之和和右子树节点之和的差的绝对值。\n"
        "如果没有左子树的话，左子树的节点之和为 0；没有右子树的话也是一样。空结点的坡度是 0。\n"
        "整个树的坡度就是其所有节点的坡度之和。\n";
}

std::string FindTilt::Link() {
    return "https://leetcode-cn.com/problems/binary-tree-tilt/";
}

std::string FindTilt::Solution() {
    return "DFS，时间：O(n)，空间：O(h)，h 为二叉树高度。";
}

void FindTilt::Benchmark() {
    FindTilt solution;

    int n = 10000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1000, 1000);
    std::vector<std::string> s_tree(n);
    int null = dis(gen);
    for (int i = 0; i < n; ++i) {
        int v = dis(gen);
        if (v != null) {
            s_tree[i] = std::to_string(v);
        }
        else {
            s_tree[i] = "null";
        }
    }
    TreeNode *root = NewBinaryTree(s_tree);

    benchmark::RegisterBenchmark("BM_FindTilt_DFS", [](benchmark::State &state, FindTilt solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    //DeleteBinaryTree(root);
}

int FindTilt::Solution1(TreeNode *root) {
    int ans = 0;
    Dfs(root, ans);
    return ans;
}

int FindTilt::Dfs(TreeNode *root, int &res) {
    if (root == nullptr) {
        return 0;
    }
    int sum_left = Dfs(root->left, res);
    int sum_right = Dfs(root->right, res);
    res += std::abs(sum_left - sum_right);
    return root->val + sum_left + sum_right;
}

std::string IsSubtree::Title() {
    return "572. 另一棵树的子树\n";
}

std::string IsSubtree::Problem() {
    return 
        "给你两棵二叉树 root 和 subRoot。检验 root 中是否包含和 subRoot 具有相同结构和节点值的子树。如果存在，返回 true；否则，返回 false。\n"
        "二叉树 tree 的一棵子树包括 tree 的某个节点和这个节点的所有后代节点。tree 也可以看做它自身的一棵子树。\n";
}

std::string IsSubtree::Link() {
    return "https://leetcode-cn.com/problems/subtree-of-another-tree/";
}

std::string IsSubtree::Solution() {
    return "树哈希，时间：O(arg pi(max(n,m))，空间：O(arg pi(max(n,m))。arg pi(x) 表示有多少以内包含 x 个素数。\n";
}

void IsSubtree::Benchmark() {
    IsSubtree solution;

    TreeNode *root = NewRandomBinaryTree(2000, -1e4, 1e4);
    TreeNode *subroot = NewRandomBinaryTree(1000, -1e4, 1e4);

    benchmark::RegisterBenchmark("BM_IsSubtree_DfsCompare", [](benchmark::State &state, IsSubtree solution, TreeNode *root, TreeNode *subroot) {
        for (auto _ : state) {
            solution.Solution1(root, subroot);
        }
    }, solution, root, subroot);

    benchmark::RegisterBenchmark("BM_IsSubtree_CompareSequence", [](benchmark::State &state, IsSubtree solution, TreeNode *root, TreeNode *subroot) {
        for (auto _ : state) {
            solution.Solution2(root, subroot);
        }
    }, solution, root, subroot);

    benchmark::RegisterBenchmark("BM_IsSubtree_TreeHash", [](benchmark::State &state, IsSubtree solution, TreeNode *root, TreeNode *subroot) {
        for (auto _ : state) {
            solution.Solution3(root, subroot);
        }
    }, solution, root, subroot);
}

bool IsSubtree::Solution1(TreeNode *root, TreeNode *subRoot) {
    if (root == nullptr) {
        return false;
    } else {
        return _IsSameTree(root, subRoot) || Solution1(root->left, subRoot) || Solution1(root->right, subRoot);
    }
}

bool IsSubtree::Solution2(TreeNode *root, TreeNode *subRoot) {
    std::vector<int> root_inorder, subroot_inorder;
    int lnull = INT_MIN, rnull = INT_MAX;
    Inorder(root, lnull, rnull, root_inorder);
    Inorder(subRoot, lnull, rnull, subroot_inorder);
    return IsSubVector(root_inorder, subroot_inorder);
}

bool IsSubtree::Solution3(TreeNode *root, TreeNode *subRoot) {
    if (root == nullptr) {
        return false;
    }
    GetPrime();
    std::unordered_map<TreeNode *, Status> root_hash, subroot_hash;
    TreeHash(root, root_hash);
    TreeHash(subRoot, subroot_hash);
    int target = subroot_hash[subRoot].f;
    for (const auto &[k, v] : root_hash) {
        if (v.f == target) {
            return true;
        }
    }
    return false;
}

bool IsSubtree::_IsSameTree(TreeNode *root, TreeNode *subRoot) {
    if (root == nullptr && subRoot == nullptr) {
        return true;
    } else if (root == nullptr || subRoot == nullptr || root->val != subRoot->val) {
        return false;
    } else {
        return _IsSameTree(root->left, subRoot->left) && _IsSameTree(root->right, subRoot->right);
    }
}

void IsSubtree::Inorder(TreeNode *root, int lnull, int rnull, std::vector<int> &res) {
    if (root == nullptr) {
        return;
    }

    res.emplace_back(root->val);
    if (root->left) {
        Inorder(root->left, lnull, rnull, res);
    } else {
        res.emplace_back(lnull);
    }
    if (root->right) {
        Inorder(root->right, lnull, rnull, res);
    } else {
        res.emplace_back(rnull);
    }
}

bool IsSubtree::IsSubVector(std::vector<int> &nums, std::vector<int> &sub) {
    int n = nums.size(), m = sub.size();
    std::vector<int> fail(m, -1);
    for (int i = 1, j = -1; i < m; ++i) {
        while (j != -1 && sub[i] != sub[j + 1]) {
            j = fail[j];
        }
        if (sub[i] == sub[j + 1]) {
            ++j;
        }
        fail[i] = j;
    }
    for (int i = 0, j = -1; i < n; ++i) {
        while (j != -1 && nums[i] != sub[j + 1]) {
            j = fail[j];
        }
        if (nums[i] == sub[j + 1]) {
            ++j;
        }
        if (j == m - 1) {
            return true;
        }
    }
    return false;
}

void IsSubtree::GetPrime() {
    vis[0] = vis[1] = 1;
    tot = 0;
    for (int i = 2; i < MAX_N; ++i) {
        if (!vis[i])
            p[++tot] = i;
        for (int j = 1; j <= tot && i * p[j] < MAX_N; ++j) {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0)
                break;
        }
    }
}

void IsSubtree::TreeHash(TreeNode *root, std::unordered_map<TreeNode *, Status> &hash) {
    if (root == nullptr) {
        return;
    }
    // 对子树进行哈希，h(root) = root.val + 31 * h(root.left) + 179 * h(root.right)
    hash[root] = Status(root->val, 1);
    if (root->left) {
        TreeHash(root->left, hash);
        hash[root].s += hash[root->left].s;
        hash[root].f = (hash[root].f + (31LL * hash[root->left].f + p[hash[root->left].s]) % MOD) % MOD;
    }
    if (root->right) {
        TreeHash(root->right, hash);
        hash[root].s += hash[root->right].s;
        hash[root].f = (hash[root].f + (179LL * hash[root->right].f + p[hash[root->right].s]) % MOD) % MOD;
    }
}


std::string Preorder::Title() {
    return "589. N叉树的前序遍历\n";
}

std::string Preorder::Problem() {
    return 
        "给定一个 n 叉树的根节点 root，返回其节点值的前序遍历。\n"
        "n 叉树在输入中按层序遍历进行序列化表示，每组子节点由空值 null 分隔（请参见示例）。\n";
}

std::string Preorder::Link() {
    return "https://leetcode-cn.com/problems/n-ary-tree-preorder-traversal/";
}

std::string Preorder::Solution() {
    return "递归，时间：O(n)，空间：O(h)，h 为 n 叉树高度。\n";
}

void Preorder::Benchmark() {
    Preorder solution;

    Node *root = NewRandomNAryTree(1e4, 0, 1e4);

    benchmark::RegisterBenchmark("BM_Preorder_Recursion", [](benchmark::State &state, Preorder solution, Node *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_Preorder_Iteration", [](benchmark::State &state, Preorder solution, Node *root) {
        for (auto _ : state) {
            solution.Solution2(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_Preorder_RIteration", [](benchmark::State &state, Preorder solution, Node *root) {
        for (auto _ : state) {
            solution.Solution3(root);
        }
    }, solution, root);

    //DeleteNAryTree(root);
}

std::vector<int> Preorder::Solution1(Node *root) {
    std::vector<int> ans;
    PreorderTraversal(root, ans);
    return ans;
}

std::vector<int> Preorder::Solution2(Node *root) {
    std::vector<int> ans;
    if (root == nullptr) {
        return ans;
    }
    std::unordered_map<Node *, int> cnt;
    std::stack<Node *> stk;
    Node *cur = root;
    while (!stk.empty() || cur) {
        while (cur) {
            ans.emplace_back(cur->val);
            stk.emplace(cur);
            if (cur->children.size() > 0) {
                cnt[cur] = 0;
                cur = cur->children[0]; // 访问第一个孩子
            } else {
                cur = nullptr;
            }
        }
        cur = stk.top();
        int index = (cnt.count(cur) ? cnt[cur] : -1) + 1; // 访问下一个孩子
        if (index < cur->children.size()) {
            cnt[cur] = index;
            cur = cur->children[index];
        } else {
            stk.pop();
            cnt.erase(cur);
            cur = nullptr;
        }
    }
    return ans;
}

std::vector<int> Preorder::Solution3(Node *root) {
    std::vector<int> ans;
    if (root == nullptr) {
        return ans;
    }

    std::stack<Node *> stk;
    stk.emplace(root); 
    while (!stk.empty()){
        Node *cur = stk.top();
        stk.pop();
        ans.emplace_back(cur->val);
        // 从右往左将子节点入栈，每组子节点的最左的子节点会在堆栈顶部
        for (auto it = cur->children.rbegin(); it != cur->children.rend(); ++it) {
            stk.emplace(*it);
        }
    }
    return ans;
}

void Preorder::PreorderTraversal(Node *root, std::vector<int> &res) {
    if (root == nullptr) {
        return;
    }
    res.emplace_back(root->val);
    for (Node *child : root->children) {
        PreorderTraversal(child, res);
    }
}



std::string Postorder::Title() {
    return "590. N叉树的后序遍历\n";
}

std::string Postorder::Problem() {
    return 
        "给定一个 n 叉树的根节点 root ，返回其节点值的后序遍历。\n"
        "n 叉树在输入中按层序遍历进行序列化表示，每组子节点由空值 null 分隔（请参见示例）。\n";
}

std::string Postorder::Link() {
    return "https://leetcode-cn.com/problems/n-ary-tree-postorder-traversal/";
}

std::string Postorder::Solution() {
    return "递归，时间：O(n)，空间：O(h)，h 为 n 叉树高度。\n";
}

void Postorder::Benchmark() {
    Postorder solution;

    Node *root = NewRandomNAryTree(1e4, 0, 1e4);

    benchmark::RegisterBenchmark("BM_Postorder_Recursion", [](benchmark::State &state, Postorder solution, Node *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_Postorder_Iteration", [](benchmark::State &state, Postorder solution, Node *root) {
        for (auto _ : state) {
            solution.Solution2(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_Postorder_RIteration", [](benchmark::State &state, Postorder solution, Node *root) {
        for (auto _ : state) {
            solution.Solution3(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_Postorder_PreorderReverse", [](benchmark::State &state, Postorder solution, Node *root) {
        for (auto _ : state) {
            solution.Solution4(root);
        }
    }, solution, root);

    //DeleteNAryTree(root);
}

std::vector<int> Postorder::Solution1(Node *root) {
    std::vector<int> ans;
    PostorderTraversal(root, ans);
    return ans;
}

std::vector<int> Postorder::Solution2(Node *root) {
    std::vector<int> ans;
    if (root == nullptr) {
        return ans;
    }
    std::stack<Node *> stk;
    std::unordered_map<Node *, int> cnt;
    Node *cur = root;
    while (cur || !stk.empty()) {
        while (cur) {
            stk.emplace(cur);
            if (cur->children.size() > 0) { // 访问第一个子节点
                cnt[cur] = 0;
                cur = cur->children[0];
            } else {
                cur = nullptr;
            }
        }
        cur = stk.top();
        int index = (cnt.count(cur) ? cnt[cur] : -1) + 1;
        if (index < cur->children.size()) { // 访问下一个子节点
            cnt[cur] = index;
            cur = cur->children[index];
        } else {
            ans.emplace_back(cur->val);
            stk.pop();
            cnt.erase(cur);
            cur = nullptr;
        }
    }
    return ans;
}

std::vector<int> Postorder::Solution3(Node *root) {
    std::vector<int> ans;
    if (root == nullptr) {
        return ans;
    }
    std::stack<Node *> stk;
    std::unordered_set<Node *> visited;
    stk.emplace(root);
    while (!stk.empty()) {
        Node *cur = stk.top();
        // 当前节点是叶子节点或已经访问过其子节点
        if (cur->children.size() == 0 || visited.count(cur)) {
            ans.emplace_back(cur->val);
            stk.pop();
        } else {
            // 反向，从右向左将子节点入栈，出栈时栈顶为最左的子节点
            for (auto it = cur->children.rbegin(); it != cur->children.rend(); ++it) {
                stk.emplace(*it);
            }
            visited.emplace(cur);
        }
    }
    return ans;
}

std::vector<int> Postorder::Solution4(Node *root) {
    std::vector<int> ans;
    if (root == nullptr) {
        return ans;
    }
    std::stack<Node *> stk;
    stk.emplace(root);
    while (!stk.empty()) {
        Node *cur = stk.top();
        stk.pop();
        ans.emplace_back(cur->val);
        for (Node *child : cur->children) {
            stk.emplace(child);
        }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

void Postorder::PostorderTraversal(Node *root, std::vector<int> &res) {
    if (root == nullptr) {
        return;
    }
    for (Node *child : root->children) {
        PostorderTraversal(child, res);
    }
    res.emplace_back(root->val);
}


std::string Tree2Str::Title() {
    return "606. 根据二叉树创建字符串\n";
}

std::string Tree2Str::Problem() {
    return 
        "你需要采用前序遍历的方式，将一个二叉树转换成一个由括号和整数组成的字符串。\n"
        "空节点则用一对空括号 \"()\" 表示。而且你需要省略所有不影响字符串与原始二叉树之间的一对一映射关系的空括号对。\n";
}

std::string Tree2Str::Link() {
    return "https://leetcode-cn.com/problems/construct-string-from-binary-tree/";
}

std::string Tree2Str::Solution() {
    return "递归，时间：O(n)，空间：O(h)，h 为二叉树高度。\n";
}

void Tree2Str::Benchmark() {
    Tree2Str solution;

    int n = 1000;
    int a = -1000, b = 1000;
    TreeNode *root = NewRandomBinaryTree(n, a, b);

    benchmark::RegisterBenchmark("BM_Tree2Str_Recursion", [](benchmark::State &state, Tree2Str solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_Tree2Str_Iteration", [](benchmark::State &state, Tree2Str solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution2(root);
        }
    }, solution, root);

    //DeleteBinaryTree(root);
}

std::string Tree2Str::Solution1(TreeNode *root) {
    if (root == nullptr) {
        return "";
    } else if (root->left == nullptr && root->right == nullptr) {
        return std::to_string(root->val);
    } else if (root->right == nullptr) {
        return std::to_string(root->val) + "(" + Solution1(root->left) + ")";
    } else {
        return std::to_string(root->val) + "(" + Solution1(root->left) + ")(" + Solution1(root->right) + ")";
    }
}

std::string Tree2Str::Solution2(TreeNode *root) {
    if (root == nullptr) {
        return "";
    }
    std::stack<TreeNode *> stk;
    std::unordered_set<TreeNode *> visited;
    std::string ans = "";
    stk.emplace(root);
    while (!stk.empty()) {
        TreeNode *cur = stk.top();
        if (visited.count(cur)) {
            stk.pop();
            ans += ")";
        } else {
            visited.insert(cur);
            ans += "(" + std::to_string(cur->val);
            if (cur->left == nullptr && cur->right != nullptr) {
                ans += "()";
            }
            if (cur->right) {
                stk.emplace(cur->right);
            }
            if (cur->left) {
                stk.emplace(cur->left);
            }
        }
    }
    return ans.substr(1, ans.size() - 2);
}


std::string AverageOfLevels::Title() {
    return "637. 二叉树的层平均值\n";
}

std::string AverageOfLevels::Problem() {
    return "给定一个非空二叉树的根节点 root, 以数组的形式返回每一层节点的平均值。与实际答案相差 10-5 以内的答案可以被接受。\n";
}

std::string AverageOfLevels::Link() {
    return "https://leetcode-cn.com/problems/average-of-levels-in-binary-tree/";
}

std::string AverageOfLevels::Solution() {
    return "DFS，时间：O(n)，空间：O(h)，h 为二叉树高度。\n";
}

void AverageOfLevels::Benchmark() {
    AverageOfLevels solution;
    TreeNode *root = NewRandomBinaryTree(1e4, INT_MIN, INT_MAX);

    benchmark::RegisterBenchmark("BM_AverageOfLevels_DFS", [](benchmark::State &state, AverageOfLevels solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_AverageOfLevels_BFS", [](benchmark::State &state, AverageOfLevels solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution2(root);
        }
    }, solution, root);

    //DeleteBinaryTree(root);
}

std::vector<double> AverageOfLevels::Solution1(TreeNode *root) {
    std::vector<double> ans, sums;
    std::vector<int> counts;
    Dfs(root, 0, counts, sums);
    int n = counts.size();
    for (int i = 0; i < n; ++i) {
        ans.emplace_back(sums[i] / counts[i]);
    }
    return ans;
}

std::vector<double> AverageOfLevels::Solution2(TreeNode *root) {
    std::vector<double> ans;
    if (root == nullptr) {
        return ans;
    }
    std::queue<TreeNode *> q;
    q.emplace(root);
    while (!q.empty()) {
        int n = q.size();
        double sum = 0;
        for (int i = 0; i < n; ++i) {
            TreeNode *cur = q.front();
            q.pop();
            sum += cur->val;
            if (cur->left) {
                q.emplace(cur->left);
            }
            if (cur->right) {
                q.emplace(cur->right);
            }
        }
        ans.emplace_back(sum / n);
    }
    return ans;
}

void AverageOfLevels::Dfs(TreeNode *root, int level, std::vector<int> &counts, std::vector<double> &sums) {
    if (root == nullptr) {
        return;
    }

    if (level < counts.size()) {
        ++counts[level];
    }
    else {
        counts.emplace_back(1);
    }
    if (level < sums.size()) {
        sums[level] += root->val;
    }
    else {
        sums.emplace_back(root->val);
    }
    Dfs(root->left, level + 1, counts, sums);
    Dfs(root->right, level + 1, counts, sums);
}



std::string FindTarget::Title() {
    return "653. 两数之和 IV - 输入 BST\n";
}

std::string FindTarget::Problem() {
    return "给定一个二叉搜索树 root 和一个目标结果 k，如果 BST 中存在两个元素且它们的和等于给定的目标结果，则返回 true。\n";
}

std::string FindTarget::Link() {
    return "https://leetcode-cn.com/problems/two-sum-iv-input-is-a-bst/";
}

std::string FindTarget::Solution() {
    return "中序遍历+双指针，时间：O(n)，空间：O(n)。\n";
}

void FindTarget::Benchmark() {
    FindTarget solution;

    int k = 6903;
    std::vector<std::string> s_tree{
        "5223","1005","5333","888","5160","5272","null","246","948","2264","5197","null","5295","27","856",
        "null","null","1930","3238","5171","null","null","null","2","216","503","null","1265","2253","2358",
        "3644","null","null","null","null","147","null","441","579","1073","1382","2038","null","2297","2506",
        "3598","4013","null","null","419","null","null","717","null","1204","null","1476","1946","2166","null",
        "null","2409","2845","3504","null","3794","4119","328","null","651","731","1096","null","null","1881",
        "null","null","2062","null","null","null","2615","2971","3357","null","3723","3846","4057","4995","null",
        "null","null","null","null","764","null","1139","1627","null","null","null","2519","2787","2908","3089",
        "3307","3456","3666","null","null","3902","4027","null","4215","5108","null","null","null","null","1530",
        "1726","null","null","2633","null","null","null","3024","3180","null","3336","null","null","null","null",
        "null","3939","null","null","4160","4846","5031","null","null","1575","null","1798","null","2686","null",
        "3035","3137","null","null","null","null","null","null","4203","4376","4963","null","5065","null","null",
        "null","null","null","null","null","null","null","null","null","null","4318","4662","4864","null","null",
        "null","null","null","4631","4803","null","4899","4458","null","4761","null","null","null","null","4568",
        "null","null","4532"
    };
    TreeNode *root = NewBinaryTree(s_tree);

    benchmark::RegisterBenchmark("BM_FindTarget_DfsHashSet", [](benchmark::State &state, FindTarget solution, TreeNode *root, int k) {
        for (auto _ : state) {
            solution.Solution1(root, k);
        }
    }, solution, root, k);

    benchmark::RegisterBenchmark("BM_FindTarget_BfsHashSet", [](benchmark::State &state, FindTarget solution, TreeNode *root, int k) {
        for (auto _ : state) {
            solution.Solution2(root, k);
        }
    }, solution, root, k);

    benchmark::RegisterBenchmark("BM_FindTarget_InorderTwoPointers", [](benchmark::State &state, FindTarget solution, TreeNode *root, int k) {
        for (auto _ : state) {
            solution.Solution3(root, k);
        }
    }, solution, root, k);

    //DeleteBinaryTree(root);
}

bool FindTarget::Solution1(TreeNode *root, int k) {
    std::unordered_set<int> set;
    return Find(root, k, set);
}

bool FindTarget::Solution2(TreeNode *root, int k) {
    if (root == nullptr) {
        return false;
    }
    std::unordered_set<int> set;
    std::queue<TreeNode *> q;
    q.emplace(root);
    while (!q.empty()) {
        TreeNode *cur = q.front();
        q.pop();
        if (set.count(k - cur->val)) {
            return true;
        }
        set.emplace(cur->val);
        if (cur->left) {
            q.emplace(cur->left);
        }
        if (cur->right) {
            q.emplace(cur->right);
        }
    }
    return false;
}

bool FindTarget::Solution3(TreeNode *root, int k) {
    std::vector<int> nums;
    InOrderTraversal(root, nums);
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == k) {
            return true;
        } else if (sum < k) {
            ++left;
        } else {
            --right;
        }
    }
    return false;
}

bool FindTarget::Find(TreeNode *root, int k, std::unordered_set<int> &set) {
    if (root == nullptr) {
        return false;
    }
    if (set.count(k - root->val)) {
        return true;
    }
    set.emplace(root->val);
    return Find(root->left, k, set) || Find(root->right, k, set);
}

std::string FindSecondMinimumValue::Title() {
    return "671. 二叉树中第二小的节点\n";
}

std::string FindSecondMinimumValue::Problem() {
    return 
        "给定一个非空特殊的二叉树，每个节点都是正数，并且每个节点的子节点数量只能为 2 或 0。\n"
        "如果一个节点有两个子节点的话，那么该节点的值等于两个子节点中较小的一个。\n"
        "更正式地说，即 root.val = min(root.left.val, root.right.val) 总成立。\n"
        "给出这样的一个二叉树，你需要输出所有节点中的第二小的值。\n"
        "如果第二小的值不存在的话，输出 -1。\n";
}

std::string FindSecondMinimumValue::Link() {
    return "https://leetcode-cn.com/problems/second-minimum-node-in-a-binary-tree/";
}

std::string FindSecondMinimumValue::Solution() {
    return "DFS+剪枝，时间：O(n)，空间：O(h)。\n";
}

void FindSecondMinimumValue::Benchmark() {
    FindSecondMinimumValue solution;

    std::vector<std::string> s_tree{
        "1","1","3","1","1","3","4","3","1","1","1","3","8","4","8","3","3","1","6","2","1"
    };

    TreeNode *root = NewBinaryTree(s_tree);

    benchmark::RegisterBenchmark("BM_FindSecondMinimumValue_DFS", [](benchmark::State &state, FindSecondMinimumValue solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution1(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_FindSecondMinimumValue_BFS", [](benchmark::State &state, FindSecondMinimumValue solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution2(root);
        }
    }, solution, root);

    benchmark::RegisterBenchmark("BM_FindSecondMinimumValue_DfsPrune", [](benchmark::State &state, FindSecondMinimumValue solution, TreeNode *root) {
        for (auto _ : state) {
            solution.Solution3(root);
        }
    }, solution, root);

    //DeleteBinaryTree(root);
}

int FindSecondMinimumValue::Solution1(TreeNode *root) {
    int ans = -1;
    if (root == nullptr) {
        return ans;
    }
    int minimum = root->val;
    std::function<void(TreeNode*)> dfs = [&](TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        if (ans != -1 && root->val >= ans) {
            return;
        }
        if (root->val > minimum) {
            ans = root->val;
        }
        dfs(root->left);
        dfs(root->right);
    };
    dfs(root);
    return ans;
}

int FindSecondMinimumValue::Solution2(TreeNode *root) {
    int ans = -1;
    if (root == nullptr) {
        return ans;
    }
    int minimum = root->val;
    std::queue<TreeNode *> q;
    q.emplace(root);
    while (!q.empty()) {
        TreeNode *cur = q.front();
        q.pop();
        if (ans == -1 || (ans != -1 && cur->val < ans)) {
            if (cur->val > minimum) {
                ans = cur->val;
            }
            if (cur->left) {
                q.emplace(cur->left);
            }
            if (cur->right) {
                q.emplace(cur->right);
            }
        }
    }
    return ans;
}

int FindSecondMinimumValue::Solution3(TreeNode *root) {
    if (root == nullptr || root->left == nullptr || root->right == nullptr) {
        return -1;
    }
    int left = root->val == root->left->val ? Solution3(root->left) : root->left->val;
    int right = root->val == root->right->val ? Solution3(root->right) : root->right->val;
    int ans = std::min(left, right);
    return ans > 0 ? ans : std::max(left, right);
}


std::string SearchBST::Title() {
    return "700. 二叉搜索树中的搜索\n";
}

std::string SearchBST::Problem() {
    return 
        "给定二叉搜索树（BST）的根节点 root 和一个整数值 val。\n"
        "你需要在 BST 中找到节点值等于 val 的节点。返回以该节点为根的子树。如果节点不存在，则返回 null。\n";
}

std::string SearchBST::Link() {
    return "https://leetcode-cn.com/problems/search-in-a-binary-search-tree/";
}

std::string SearchBST::Solution() {
    return "迭代，时间：O(n)，空间：O(1)。\n";
}

void SearchBST::Benchmark() {
    SearchBST solution;
    std::vector<std::string> s_tree{
        "9980","9740","null","9680","null","9355","null","9309","null","8473","null","8397",
        "null","8391","null","8326","null","8188","null","7999","null","7950","null","7846",
        "null","7574","null","7569","null","7386","null","7188","null","7039","null","6723",
        "null","6706","null","6623","null","6612","null","6480","null","6469","null","6454",
        "null","6328","null","6286","null","6276","null","5989","null","5928","null","5924",
        "null","5903","null","5837","null","5635","null","5596","null","5550","null","5495",
        "null","5465","null","5109","null","4962","null","4687","null","4598","null","4570",
        "null","4529","null","4426","null","4294","null","4261","null","4180","null","4113",
        "null","4106","null","4042","null","4023","null","4020","null","3998","null","3864",
        "null","3863","null","3841","null","3822","null","3700","null","3613","null","3599",
        "null","3598","null","3561","null","3434","null","3365","null","3318","null","3209",
        "null","3075","null","2999","null","2876","null","2857","null","2672","null","2538",
        "null","2518","null","2338","null","2293","null","2265","null","2175","null","2165",
        "null","1915","null","1579","null","1512","null","1499","null","1404","null","1337",
        "null","1323","null","975","null","800","null","766","null","671","null","566","null",
        "555","null","501","null","343","null","279","null","236","null","175","null","117",
        "null","60","null","19","null","null","null",
    };
    int val = 1404;
    TreeNode *root = NewBinaryTree(s_tree);

    benchmark::RegisterBenchmark("BM_SearchBST_Recursion", [](benchmark::State &state, SearchBST solution, TreeNode *root, int val) {
        for (auto _ : state) {
            solution.Solution1(root, val);
        }
    }, solution, root, val);

    benchmark::RegisterBenchmark("BM_SearchBST_Iteration", [](benchmark::State &state, SearchBST solution, TreeNode *root, int val) {
        for (auto _ : state) {
            solution.Solution2(root, val);
        }
    }, solution, root, val);
    //DeleteBinaryTree(root);
}

TreeNode *SearchBST::Solution1(TreeNode *root, int val) {
    if (root == nullptr) {
        return nullptr;
    } else if (root->val == val) {
        return root;
    } else {
        return Solution1(val < root->val ? root->left : root->right, val);
    }
}

TreeNode *SearchBST::Solution2(TreeNode *root, int val) {
    TreeNode *cur = root;
    while (cur) {
        if (cur->val == val) {
            return cur;
        }
        cur = val < cur->val ? cur->left : cur->right;
    }
    return nullptr;
}

} // namespace tree
} // namespace leetcode
