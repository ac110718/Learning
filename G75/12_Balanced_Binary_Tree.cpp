// balanced tree has same number of children on right as left
// counter function to return length of branch depth (1 + max (either left or right depth)), recursively
// fast exit if different heights on either side
// return true, only if BOTH left and right branches are balanced.

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
    bool isBalanced(TreeNode* root) {
        if (root == nullptr || root->left == nullptr && root->right == nullptr) return true;
        if (abs(counter(root->left) - counter(root->right)) > 1) return false;
        return isBalanced(root->left) && isBalanced(root->right);
    }
    
    int counter(TreeNode* root) {
        if (root == nullptr) return 0;
        return 1 + max(counter(root->left), counter(root->right));
    }
};