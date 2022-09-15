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
    int preIdx;
    unordered_map<int, int> ordIdx;
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        preIdx = 0;
        for (int i = 0; i < inorder.size(); i++) {
            ordIdx[inorder[i]] = i;
        }
        return builder(preorder, 0, preorder.size() - 1);
    }
    TreeNode* builder(vector<int>& preorder, int left, int right) {
        if (left > right) return nullptr;
        int val = preorder[preIdx];
        preIdx++;
        TreeNode* root = new TreeNode(val);
        root->left = builder(preorder, left, ordIdx[val] - 1);
        root->right = builder(preorder, ordIdx[val] + 1, right);
        return root;
    }
};