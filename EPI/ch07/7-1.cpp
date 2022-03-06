#include <iostream>

using namespace std;
template <typename T>
struct ListNode {
    T data;
    shared_ptr<ListNode<T>> next;
};

void InsertAfter(const shared_ptr<ListNode<int>>& node, const shared_ptr<ListNode<int>>& new_node) {
    new_node->next = node->next;
    node->next = new_node;
}

void AppendNode(shared_ptr<ListNode<int>> *node, shared_ptr<ListNode<int>> *tail) {
    (*tail)->next = *node;
    *tail = *node; // update tail reference
    *node = (*node)->next;
}

shared_ptr<ListNode<int>> SearchList(shared_ptr<ListNode<int>> L, int key) {
    while (L && L->data != key) {
        L = L->next;
    }
    return L;
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

shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1, shared_ptr<ListNode<int>> L2) {
    shared_ptr<ListNode<int>> dummy_head(new ListNode<int>);
    auto tail = dummy_head;
    while(L1 && L2) {
        AppendNode(L1->data <= L2->data ? &L1 : &L2, &tail); // append least of L1 or L2 to tail builder
    }
    tail->next = L1 ? L1 : L2; // append remaining
    return dummy_head->next; // stayed in place whole time, pointing to 1st element
}

// Reverse a sublist from start position to finish position
// use trackers to point to "future" and "prior" orientations

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start, int finish) {
    auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
    auto sublist_head = dummy_head;
    int k = 1;
    while (k++ < start) {
        sublist_head = sublist_head->next;
    }
    // start reverse process, with sublist_iter as the forward progressor
    // sublist_head will point "prior"
    auto sublist_iter = sublist_head->next;
    while (start++ < finish) {
        auto temp = sublist_iter->next; // manipulate
        sublist_iter->next = temp->next; // push iter forward for next pass
        temp->next = sublist_head->next; // reverse orientation
        sublist_head->next = temp; // push prior forward
    }
    return dummy_head->next;
}



int main() {
    auto a = shared_ptr<ListNode<int>>(new ListNode<int>{1});
    auto b = shared_ptr<ListNode<int>>(new ListNode<int>{2});
    auto c = shared_ptr<ListNode<int>>(new ListNode<int>{3});
    auto d = shared_ptr<ListNode<int>>(new ListNode<int>{4});
    InsertAfter(a, b);
    InsertAfter(b, c);
    InsertAfter(c, d);
    cout << SearchList(a, 2)->data << endl;
    auto reversed = ReverseLL(a);
    auto reverse_head = reversed;
    auto x = reverse_head;
    while (reversed != NULL) {
        cout << reversed -> data;
        reversed = reversed -> next;
    }
    cout << endl;
    
    x = ReverseLL(x);
    auto e = shared_ptr<ListNode<int>>(new ListNode<int>{1});
    auto f = shared_ptr<ListNode<int>>(new ListNode<int>{2});
    auto g = shared_ptr<ListNode<int>>(new ListNode<int>{3});
    auto h = shared_ptr<ListNode<int>>(new ListNode<int>{4});
    InsertAfter(e, f);
    InsertAfter(f, g);
    InsertAfter(g, h);
    auto combined = MergeTwoSortedLists(e, x);
    auto extra = combined;
    while (combined != NULL) {
        cout << combined -> data;
        combined = combined -> next;
    }
    cout << endl;
    extra = ReverseSublist(extra, 2, 7);
    while (extra != NULL) {
        cout << extra -> data;
        extra = extra -> next;
    }
    cout << endl;
}