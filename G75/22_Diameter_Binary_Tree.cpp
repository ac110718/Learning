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

// Characterize the tree according to its left and right branches
// Your defining characteristic is the max of the left or the right
// What characteristic can you define using both the left and right branch (your own diameter = right + left branch depth)
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (root == nullptr) return 0;
        int current = maxDepth(root->left) + maxDepth(root->right);
        return max(current, max(diameterOfBinaryTree(root->left), diameterOfBinaryTree(root->right)));
        
    }
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};