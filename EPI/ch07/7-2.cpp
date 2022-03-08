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

//Overlapping list with no cycles? By definition will have the same tail (no way to diverge later)

int Length(shared_ptr<ListNode<int>> L) {
    int length = 0;
    while (L) {
        ++length;
        L = L->next;
    }
    return length;
}

void AdvanceListByK(int k, shared_ptr<ListNode<int>>* L) {
    while (k--) {
        *L = (*L)->next;
    }
}

shared_ptr<ListNode<int>> OverlappingNoCycleLists(shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
    int l0_len = Length(l0), l1_len = Length(l1);
    AdvanceListByK(abs(l0_len - l1_len), l0_len > l1_len ? &l0 : &l1);
    while (l0 && l1 && l0 != l1) {
        l0 = l0->next;
        l1 = l1->next;
    }
    return l0; // will return a node only if there is a mutual overlap (l0 == l1)
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
    auto l0 = shared_ptr<ListNode<int>>(new ListNode<int>{50});
    auto l1 = shared_ptr<ListNode<int>>(new ListNode<int>{51});
    auto build2 = shared_ptr<ListNode<int>>(new ListNode<int>{52});
    auto build2_head = build2;
    for (int i = 0; i < 10; i++) {
        auto temp = shared_ptr<ListNode<int>>(new ListNode<int>{i});
        AppendNode(&temp, &build2);
    }
    l0->next = shared_ptr<ListNode<int>>(new ListNode<int>{49});
    l0->next->next = build2_head->next->next->next->next;
    l1->next = build2_head;
    auto y = OverlappingNoCycleLists(l1, l0);
    cout << y->data << endl;
}