#include <iostream>
#include <vector>
#include <queue>
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

// Queue implementation with stack
class Queue {
  public:
    void Enqueue(int x) {
        enqueue_.emplace(x);
    }
    int Dequeue() {
        if(empty(dequeue_)) {
            while (!empty(enqueue_)) {
                dequeue_.emplace(enqueue_.top()); // newest enqueue element will be buried at the bottom of dequeue stack
                enqueue_.pop();
            }
        }
        int result = dequeue_.top();
        dequeue_.pop();
        return result;
    }
  private:
    stack<int> enqueue_, dequeue_;
};

//Queue With Max. 
// Keep two queues.. one that holds the max up to a certain point. 
// Always compare the heads.. pop out the max queue only when it is the same as normal queue
// When enqueuing, empty out the back of the max queue to update for any bigger max that has been loaded into the normal queue

template <typename T>
class QueueWithMax {
  public:
    void Enqueue(const T& x) {
        entries_.emplace(x);
        while (!empty(candidates_for_max_) && candidates_for_max_.back() < x) {
            candidates_for_max_.pop_back(); // update for any bigger max loaded into queue
        }
        candidates_for_max_.emplace_back(x);
        cout << entries_.front() << " | " << candidates_for_max_.front() << endl;
    }

    T Dequeue() {
        T result = entries_.front();
        if (result == candidates_for_max_.front()) {
            candidates_for_max_.pop_front(); // remove the max as it leaves the normal queue
        }
        entries_.pop();
        cout << entries_.front() << " | " << candidates_for_max_.front() << endl;
        return result;
    }

    const T& Max() const {return candidates_for_max_.front();} // max_queue will always have descending pattern

  private:
    queue<T> entries_;
    deque<T> candidates_for_max_;
};

int main() {
    create_tree();
    auto result = BinaryTreeDepthOrder(A);
    print_vec_vec(result);
    Queue test_queue;
    for (int i = 0; i < 5; i++) {
        test_queue.Enqueue(i);
    }
    for (int i = 0; i < 5; i++) {
        cout << test_queue.Dequeue() << ",";
    }
    cout << endl;
    QueueWithMax<int> max_queue;
    auto load_array = vector<int>{3, 1, 3, 2, 0};
    for (auto n : load_array) {
        max_queue.Enqueue(n);
    }
    max_queue.Enqueue(1);
    max_queue.Dequeue();
    max_queue.Dequeue();
    max_queue.Enqueue(2);
    max_queue.Enqueue(4);
    max_queue.Dequeue();
    max_queue.Enqueue(4);
}