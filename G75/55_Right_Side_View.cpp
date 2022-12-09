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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) return result;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int level_size = q.size(); // track size of previous level depth
            for (int i = 0; i < level_size; i++) { // bounded by previous level depth
                TreeNode* curr = q.front();
                if (i == level_size - 1) {
                    result.push_back(curr->val); // push back the very last element within the level
                }
                q.pop(); // eject all elements in level
                if (curr->left != nullptr) q.push(curr->left); // inject all children back into processing queue for next iteration
                if (curr->right != nullptr) q.push(curr->right);
            }
        }
        return result;
        
    }
};