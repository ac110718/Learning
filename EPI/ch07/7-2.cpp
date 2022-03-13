#include <iostream>
#include <vector>
#include <array>
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

// remove kth last element from a list

shared_ptr<ListNode<int>> RemoveKthLast(const shared_ptr<ListNode<int>> &L, int k) {
    auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
    auto first = dummy_head->next;
    while (k--) { // advance k steps ahead to be placeholder
        first = first->next;
    }
    auto second = dummy_head;
    while (first) {
        second = second->next, first = first->next;
    } // hit dead end
    cout << "deleting " << second->next->data << endl;
    second->next = second->next->next; // delete the node
    return dummy_head->next; 
}

shared_ptr<ListNode<int>> RemoveDuplicates(const shared_ptr<ListNode<int>> &L) {
    auto iter = L;
    while (iter) {
        auto next_distinct = iter->next;
        while (next_distinct && next_distinct->data == iter->data) {
            next_distinct = next_distinct->next;
        }
        iter->next = next_distinct; // skip all the way till next unique node
        iter = next_distinct; // progress forward on next round within this while loop on iter
    }
    return L;
}

shared_ptr<ListNode<int>> CyclicalllyRightShiftList(shared_ptr<ListNode<int>> L, int k) {
    if (L == nullptr) {
        return L;
    }
    auto tail = L;
    int n = 1;
    while (tail->next) {
        ++n;
        tail = tail->next;
    }
    k %= n;
    if (k == 0) { return L; }
    tail->next = L; // create a new cycle
    int steps_to_new_head = n-k;
    auto new_tail = tail;
    while (steps_to_new_head--) {
        new_tail = new_tail->next; // advance to end of new tail positioning
    }
    auto new_head = new_tail->next; // ref to new head
    new_tail->next = nullptr; // snip the tail
    return new_head;
}

// even positioned first, followed by odd positioned nodes

shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>> &L) {
    if (L == nullptr) {
        return L;
    }
    auto even_dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
    auto odd_dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
    array<shared_ptr<ListNode<int>>, 2> tails = {even_dummy_head, odd_dummy_head};
    int turn = 0;
    for (auto iter = L; iter; iter = iter->next) { 
        // create two lists that pull out even and odd positioned nodes
        tails[turn]->next = iter;
        tails[turn] = tails[turn]->next;
        turn ^= 1; // flip alternate builder list
    }
    tails[1]->next = nullptr; // end with odd
    tails[0]->next = odd_dummy_head->next;
    return even_dummy_head->next;
}


shared_ptr<ListNode<int>> ReverseLL(shared_ptr<ListNode<int>> L) {
    shared_ptr<ListNode<int>> current = L;
    shared_ptr<ListNode<int>> prev = NULL;
    shared_ptr<ListNode<int>> next = NULL;
    while (current != NULL) {
        next = current->next; // set next placeholder
        current->next = prev; // reverse orientation of curr
        prev = current; // move prev and curr both forward (next already done and had to do it earlier)
        current = next;
    }
    shared_ptr<ListNode<int>> head = prev; // set head to be end right before null
    return head;
}

bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L) {
    shared_ptr<ListNode<int>> slow = L, fast = L;
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    auto first_half_iter = L;
    auto second_half_iter = ReverseLL(slow);
    while (second_half_iter && first_half_iter) {
        if (second_half_iter->data != first_half_iter->data) {
            return false;
        }
        second_half_iter = second_half_iter->next;
        first_half_iter = first_half_iter->next;
    }
    return true;
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
    RemoveKthLast(l0, 4);
    auto s0 = shared_ptr<ListNode<int>>(new ListNode<int>{0});
    auto s1 = shared_ptr<ListNode<int>>(new ListNode<int>{0});
    auto s2 = shared_ptr<ListNode<int>>(new ListNode<int>{1});
    auto s3 = shared_ptr<ListNode<int>>(new ListNode<int>{1});
    auto s4 = shared_ptr<ListNode<int>>(new ListNode<int>{2});
    auto s5 = shared_ptr<ListNode<int>>(new ListNode<int>{2});
    s0->next = s1;
    s1->next = s2;
    s2->next = s3;
    s3->next = s4;
    s4->next = s5;
    auto unique_L = RemoveDuplicates(s0);
    while (unique_L) {
        cout << unique_L->data;
        unique_L = unique_L->next;
    }
    cout << endl;
    s0->next = s1;
    s1->next = s2;
    s2->next = s3;
    s3->next = s4;
    s4->next = s5;
    auto test = CyclicalllyRightShiftList(s0, 2);
    while (test) {
        cout << test->data;
        test = test->next;
    }
    cout << endl;
    s0->next = s1;
    s1->next = s2;
    s2->next = s3;
    s3->next = s4;
    s4->next = s5;
    s5->next = nullptr;
    auto test2 = EvenOddMerge(s0);
    auto test3 = test2;
    while (test2) {
        cout << test2->data;
        test2 = test2->next;
    }
    cout << endl;
    s0->next = s2;
    s2->next = s4;
    s4->next = s5;
    s5->next = s3;
    s3->next = s1;
    s1->next = nullptr;
    cout << boolalpha << IsLinkedListAPalindrome(s0) << endl;
    cout << boolalpha << IsLinkedListAPalindrome(test3) << endl;
}