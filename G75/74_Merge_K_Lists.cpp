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
    struct compare {
        bool operator() (const ListNode* l, const ListNode* r) {
            return l->val > r->val;
        }
    };
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, compare> q;
        for (auto l : lists) {
            if (l) q.push(l);
        }
        if (q.empty()) return nullptr;
        ListNode* result = q.top();
        q.pop();
        if (result->next) q.push(result->next);
        ListNode* tail = result;
        while (!q.empty()) {
            tail->next = q.top();
            q.pop();
            tail = tail->next;
            if (tail->next) {
                q.push(tail->next);
            }
        }
        return result;
        
    }
};