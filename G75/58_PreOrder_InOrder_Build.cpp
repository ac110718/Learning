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
    unordered_map<int, int> ordIdx; // store positioning of specific value
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
        int val = preorder[preIdx]; // grab the values in order of tree traversal
        preIdx++; // get the values in the right order (by updating)
        TreeNode* root = new TreeNode(val);
        root->left = builder(preorder, left, ordIdx[val] - 1); // build out left branch, with updated bounds
        root->right = builder(preorder, ordIdx[val] + 1, right); // build out right branch, with updated bounds
        return root;
    }
};