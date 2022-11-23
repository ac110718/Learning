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


// re-parameterize in context of lower bound and upper bound
// node must be less than high and higher than low
// if not, immediate exit
// else, return BOTH validBST left + validBST right...
// ... but with root as the new "high" and "low" parameter, respectively
// to ensure BST condition is true

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return validate(root, nullptr, nullptr); 
    }
    bool validate(TreeNode* root, TreeNode* low, TreeNode* high) {
        if (root == nullptr) return true;
        if ((low != nullptr && root->val <= low->val) || (high != nullptr && root->val >= high->val)) 
            return false;
        return validate(root->left, low, root) && validate(root->right, root, high);
    }
};