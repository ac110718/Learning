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
    int kthSmallest(TreeNode* root, int k) {
        int kval[2] = {0,0};
        in_order(root, k, kval);
        return kval[1];
    }
    void in_order(TreeNode* root, int k, int kval[]) {
        if (root == nullptr) return;
        in_order(root->left, k, kval);
        if (++kval[0] == k) kval[1] = root->val;
        in_order(root->right, k, kval);
    }
};