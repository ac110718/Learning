// Create three pointers: "in front" "in back" and "iterator"
// Thread curr (iterator) to head
// before hitting the end...
// set next to "front" (curr->next), 
// reverse curr's next pointer to point "back"
// push prev pointer forward (to curr)
// push curr (iterator) pointer to "front" (next)
// don't get confused by label of "next" pointer and curr->next (as structural property of curr)
// one is to orient direction.. and the other is a property of curr

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* next = nullptr;
        ListNode* curr = head;
        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};