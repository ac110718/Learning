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
    while (reversed != NULL) {
        cout << reversed -> data;
        reversed = reversed -> next;
    }
    cout << endl;
}