#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct ListNode {
    T data;
    shared_ptr<ListNode<T>> next;
};

void AppendNode(shared_ptr<ListNode<int>> *node, shared_ptr<ListNode<int>> *tail) {
    (*tail)->next = *node;
    *tail = *node; // update tail reference
    *node = (*node)->next;
}

// find cycle and start of cycle
// if you advance two pointers that are cycle length apart (with one starting in beginning and other at beginning of cycle)
// you are guaranteed to have them run into each other at the beginning of the cycle.. because the stem length with always be a multiple of (cycle-length) - stem length

shared_ptr<ListNode<int>> HasCycle(const shared_ptr<ListNode<int>>& head) {
    shared_ptr<ListNode<int>> fast = head, slow = head;
    while ( fast && fast -> next) {
        slow = slow->next, fast = fast->next->next;
        if (slow == fast) { // they meet and there is cycle
            int cycle_len = 0;
            do {
                ++cycle_len;
                fast = fast->next;
            } while (slow != fast);
            cout << "Found cycle. Length of " << cycle_len << endl;
            auto cycle_len_advanced_iter = head;
            while (cycle_len--) {
                cycle_len_advanced_iter = cycle_len_advanced_iter -> next;
            }
            auto iter = head;
            while (iter != cycle_len_advanced_iter) {
                iter = iter->next;
                cycle_len_advanced_iter = cycle_len_advanced_iter->next;
            }
            return iter;
        }
    }
    return nullptr; // no cycle
}

int main() {
    auto list = shared_ptr<ListNode<int>>(new ListNode<int>{0});
    auto build = list;
    auto cycle_starter = list;
    for (int i = 0; i < 10; i++) {
        auto temp = shared_ptr<ListNode<int>>(new ListNode<int>{i});
        AppendNode(&temp, &build);
    }
    int i = 3;
    while (i--) {
        cycle_starter = cycle_starter->next;
    }
    build->next = cycle_starter;
    auto x = HasCycle(list);
    cout << x->data << endl;
}