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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode result = ListNode();
        ListNode* builder = &result;
        while (list1 && list2) {
            if (list1->val < list2->val) {
                builder->next = list1;
                list1 = list1->next;
            } else {
                builder->next = list2;
                list2 = list2->next;
            }
            builder = builder->next;
        }
        builder->next = list1? list1 : list2;
        return result.next;
    }
};