#include <iostream>
#include <vector>

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


int main() {
    create_tree();
    cout << "PreOrder : ";
    PreOrder(A);
    cout << endl;

    cout << "InOrder : ";
    InOrder(A);
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
}