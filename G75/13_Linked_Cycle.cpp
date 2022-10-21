// create two pointers linking to head
// one that will go twice as fast as slow
// push fast (and fast->next) until nullptr
// if there's a cycle.. fast will keep looping..
// but iterate on slow as well.. 
// there will be intersection of fast and slow if there's a cycle
// if fast reaches end without intersecting with slow, there is no cycle

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
};