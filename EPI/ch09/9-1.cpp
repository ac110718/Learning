#include <iostream>
#include <vector>
#include <stack>

using namespace std;
template <typename T>
struct BinaryTreeNode {
    T data;
    unique_ptr<BinaryTreeNode<T>> left, right;
};

vector<int> tree_data {314, 6, 271, 28, 0, 561, 3, 17, 6, 2, 1, 401, 641, 257, 271, 28};
auto A = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[0], nullptr, nullptr});
auto B = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[1], nullptr, nullptr});
auto C = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[2], nullptr, nullptr});
auto D = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[3], nullptr, nullptr});
auto E = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[4], nullptr, nullptr});
auto F = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[5], nullptr, nullptr});
auto G = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[6], nullptr, nullptr});
auto H = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[7], nullptr, nullptr});
auto I = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[8], nullptr, nullptr});
auto J = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[9], nullptr, nullptr});
auto K = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[10], nullptr, nullptr});
auto L = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[11], nullptr, nullptr});
auto M = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[12], nullptr, nullptr});
auto N = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[13], nullptr, nullptr});
auto O = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[14], nullptr, nullptr});
auto P = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[15], nullptr, nullptr});

void create_tree() {
    C->left = move(D);
    C->right = move(E);
    B->left = move(C);
    G->left = move(H);
    F->right = move(G);
    B->right = move(F);
    A->left = move(B);
    L->right = move(M);
    K->left = move(L);
    K->right = move(N);
    J->right = move(K);
    I->left = move(J);
    O->right = move(P);
    I->right = move(O);
    A->right = move(I);
}

//root first, then children.. specifically left branch first, then right
void PreOrder(const unique_ptr<BinaryTreeNode<int>>& root) {
    if (root) {
        cout << root->data << ", ";
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

//left first, then root, then right
void InOrder(const unique_ptr<BinaryTreeNode<int>>& root) {
    if (root) {
        InOrder(root->left);
        cout << root->data << ", ";
        InOrder(root->right);
    }
}

// left branch, right branch, finally root last
void PostOrder(const unique_ptr<BinaryTreeNode<int>>& root) {
    if (root) {
        PostOrder(root->left);
        PostOrder(root->right);
        cout << root->data << ", ";
    }
}

// check if tree is balanced

struct BalancedStatusWithHeight {
    bool balanced;
    int height;
};


BalancedStatusWithHeight CheckBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
    if (tree == nullptr) {
        return {true, -1};
    }
    auto left_result = CheckBalanced(tree->left);
    if (!left_result.balanced) {
        return {false, 0};
    }
    auto right_result = CheckBalanced(tree->right);
    if (!right_result.balanced) {
        return {false, 0};
    }
    bool is_balanced = abs(left_result.height - right_result.height) <= 1;
    int height = max(left_result.height, right_result.height) + 1;
    return {is_balanced, height};
}

bool isBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
    return CheckBalanced(tree).balanced;
}

vector<int> tree_data_bal {1, 2, 3, 4, 5, 6, 7};
auto S = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data_bal[0], nullptr, nullptr});
auto T = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data_bal[1], nullptr, nullptr});
auto U = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data_bal[2], nullptr, nullptr});
auto V = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data_bal[3], nullptr, nullptr});
auto W = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data_bal[4], nullptr, nullptr});
auto X = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data_bal[5], nullptr, nullptr});
auto Y = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data_bal[6], nullptr, nullptr});


void create_bal_tree() {
   W->right = move(Y);
   W->left = move(X);
   T->left = move(U);
   T->right = move(V);
   S->left = move(W);
   S->right = move(T);
}

vector<int> tree_data_sym {1, 2, 3};

auto b1 = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data_sym[0], nullptr, nullptr});
auto b2 = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data_sym[1], nullptr, nullptr});
auto b3 = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data_sym[1], nullptr, nullptr});
auto b4 = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data_sym[2], nullptr, nullptr});
auto b5 = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data_sym[2], nullptr, nullptr});

void create_sym_tree() {
    b2->left = move(b4);
    b3->right = move(b5);
    b1->left = move(b2);
    b1->right = move(b3);
}

// Test if symmetric

bool CheckSymmetric(const unique_ptr<BinaryTreeNode<int>>& subtree_0, const unique_ptr<BinaryTreeNode<int>>& subtree_1) {
    if (subtree_0 == nullptr && subtree_1 == nullptr) {
        return true;
    } else if (subtree_0 != nullptr && subtree_1 != nullptr) {
        return  subtree_0->data == subtree_1->data &&
                CheckSymmetric(subtree_0->left, subtree_1->right) &&
                CheckSymmetric(subtree_0->right, subtree_1->left);
    }
    return false; // one is empty, one is not
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
    return tree == nullptr || CheckSymmetric(tree->left, tree->right);
}

// Lowest Common Ancestor. Return first instance of where the two nodes you are looking for are present in the subtree (number exactly 2)

struct Status {
    int num_target_nodes;
    BinaryTreeNode<int>* ancestor;
};

Status LcaHelper(const unique_ptr<BinaryTreeNode<int>>& tree, const unique_ptr<BinaryTreeNode<int>>& node0, const unique_ptr<BinaryTreeNode<int>>& node1) {
    if (tree == nullptr) {
        return {0, nullptr};
    }
    // will return deepest instance of where target_nodes == 2
    auto left_result = LcaHelper(tree->left, node0, node1);
    if (left_result.num_target_nodes == 2) {
        return left_result;
    }
    auto right_result = LcaHelper(tree->right, node0, node1);
    if (right_result.num_target_nodes == 2) {
        return right_result;
    }
    int num_target_nodes = left_result.num_target_nodes + right_result.num_target_nodes + (tree == node0) + (tree == node1);
    // will return the first node where num_target_nodes == 2
    return {num_target_nodes, num_target_nodes == 2 ? tree.get() : nullptr};
}


BinaryTreeNode<int>* Lca (const unique_ptr<BinaryTreeNode<int>>& tree, const unique_ptr<BinaryTreeNode<int>>& node0, const unique_ptr<BinaryTreeNode<int>>& node1) {
    return LcaHelper(tree, node0, node1).ancestor;
}

// Sum up Binary tree representation where each node is 0 or 1

void make_binary_tree () {
    vector<int> bin_tree_data {1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0};
    A = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[0], nullptr, nullptr});
    B = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[1], nullptr, nullptr});
    C = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[2], nullptr, nullptr});
    D = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[3], nullptr, nullptr});
    E = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[4], nullptr, nullptr});
    F = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[5], nullptr, nullptr});
    G = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[6], nullptr, nullptr});
    H = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[7], nullptr, nullptr});
    I = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[8], nullptr, nullptr});
    J = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[9], nullptr, nullptr});
    K = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[10], nullptr, nullptr});
    L = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[11], nullptr, nullptr});
    M = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[12], nullptr, nullptr});
    N = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[13], nullptr, nullptr});
    O = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[14], nullptr, nullptr});
    P = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{bin_tree_data[15], nullptr, nullptr});
    create_tree();
}


int SumRootToLeafHelper(const unique_ptr<BinaryTreeNode<int>>& tree, int partial_path_sum) {
    if (tree == nullptr) {
        return 0;
    }
    // calc the accumulated sum up to this point
    partial_path_sum = partial_path_sum * 2 + tree -> data;

    if (tree->left == nullptr && tree->right == nullptr) {
        return partial_path_sum;
    } // end accumulation and return the sum back to parent caller only if leaf

    // request sum for each branch
    return  SumRootToLeafHelper(tree->left, partial_path_sum) +
            SumRootToLeafHelper(tree->right, partial_path_sum);
}

int SumRoomToLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
    return SumRootToLeafHelper(tree, 0);
}

bool HasPathSum(const unique_ptr<BinaryTreeNode<int>>& tree, int remaining_weight) {
    if (tree == nullptr) {
        return false;
    } else if (tree->left == nullptr && tree->right == nullptr) {
        // You're at a leaf, do final check
        return remaining_weight == tree->data;
    }
    return  HasPathSum(tree->left, remaining_weight - tree->data) ||
            HasPathSum(tree->right, remaining_weight - tree->data);
}

// InOrder Traversal using a stack

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
    vector<int> result;
    stack<pair<const BinaryTreeNode<int>*, bool>> in_process;
    in_process.emplace(tree.get(), false); // bool is left traversed and therefore node can be added?
    while (!empty(in_process)) {
        auto [node, left_subtree_traversed] = in_process.top();
        in_process.pop();
        if (node) {
            if (left_subtree_traversed) {
                result.emplace_back(node->data);
            } else {
                in_process.emplace(node->right.get(), false); // right will be processed last and buried in the stack
                in_process.emplace(node, true); // add to result next time around now that children are in_process
                in_process.emplace(node->left.get(), false); // left will be top of stack and processed first 
            }
        }
    }
    return result;
}



int main() {
    create_tree();
    cout << "PreOrder : ";
    PreOrder(A);
    cout << endl;

    cout << "InOrder : ";
    InOrder(A);
    cout << endl;

    auto stack_inorder = InorderTraversal(A);
    cout << "InOrder : ";
    for (auto n : stack_inorder) {
        cout << n << ", ";
    }
    cout << endl;

    cout << "PostOrder : ";
    PostOrder(A);
    cout << endl;
    
    cout << boolalpha << isBalanced(A) << endl;
    create_bal_tree();
    cout << boolalpha << isBalanced(S) << endl;
    create_sym_tree();
    cout << IsSymmetric(S) << endl;
    cout << IsSymmetric(b1) << endl;
    cout << Lca(A, A->right->left->right->left->right, A->right->left->right->right)->data << endl;
    cout << Lca(A, A->right->left->right->left->right, A->left->right->right->left)->data << endl;
    cout << "Pathsum 591: " << HasPathSum(A, 591) << endl;
    make_binary_tree();
    int output = 0b1000 + 0b1001 + 0b10110 + 0b110011 + 0b11000 + 0b1100;
    cout << SumRoomToLeaf(A) << " | " << output << endl;
    
    
}