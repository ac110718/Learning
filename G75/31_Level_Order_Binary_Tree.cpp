// for each level, push current node into processing queue
// Get processing size (level size) by looking at size of queue
// for each node in queue, place left and right node into the queue
// But you will stop the loop after (level size) iterations
// Because you took stock of the queue size as first step in loop


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        queue<TreeNode*> q;
        if (root) q.push(root);
        while (!q.empty()) {
            int level_size = q.size();
            vector<int> level;
            for (int i = 0; i < level_size; i++) {
                TreeNode* current = q.front();
                q.pop();
                level.push_back(current->val);
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
            result.push_back(level);
        }
        return result;
        
    }
};