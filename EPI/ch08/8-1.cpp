#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template <typename T>
struct ListNode {
    T data;
    shared_ptr<ListNode<T>> next;
};

void PrintLinkedListInReverse(shared_ptr<ListNode<int>> head) {
    stack<int> nodes;
    while (head) {
        nodes.push(head->data);
        head = head->next;
    }
    while (!empty(nodes)) {
        cout << nodes.top() << endl;
        nodes.pop();
    }
}

int main() {
    vector<shared_ptr<ListNode<int>>> node_vec;
    shared_ptr<ListNode<int>> next_node;
    for (int i = 6; i > 0; i--) {
        if (i == 6) {
            next_node = nullptr;
        }
        auto temp = make_shared<ListNode<int>>(ListNode<int>{i, next_node});
        next_node = temp;
    }
    PrintLinkedListInReverse(next_node);
}