#include <iostream>
#include <vector>
#include <queue>

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

//return list of list of nodes by order of depth
vector<vector<int>> BinaryTreeDepthOrder(const unique_ptr<BinaryTreeNode<int>>& tree) {
    vector<vector<int>> result;
    if (!tree.get()) {
        return result;
    }
    queue<BinaryTreeNode<int>*> curr_depth_nodes({tree.get()});
    while (!empty(curr_depth_nodes)) {
        queue<BinaryTreeNode<int>*> next_depth_nodes;
        vector<int> this_level;
        while (!empty(curr_depth_nodes)) {
            auto curr = curr_depth_nodes.front();
            curr_depth_nodes.pop();
            this_level.emplace_back(curr->data); // populate this_level_data
            if (curr->left) {
                next_depth_nodes.emplace(curr->left.get()); // load up next iteration
            }
            if (curr->right) {
                next_depth_nodes.emplace(curr->right.get());
            }
        }
        result.emplace_back(this_level); // record fully-built list
        curr_depth_nodes = next_depth_nodes;
    }
    return result;
}

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

void print_vec_vec(vector<vector<int>>& input) {
    cout << "<";
    for (int i = 0; i < input.size(); i++) {
        cout << "<";
        for (int j = 0; j < input[i].size(); j++) {
            cout << input[i][j];
            if (j != input[i].size() - 1) {
                cout << ", ";
            }
        }
        cout << ">";
        if (i != input.size() - 1) {
            cout << ", ";
        }
    }
    cout << ">" << endl;
}

int main() {
    create_tree();
    auto result = BinaryTreeDepthOrder(A);
    print_vec_vec(result);
}