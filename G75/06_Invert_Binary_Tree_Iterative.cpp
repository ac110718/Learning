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

// output mirror image of tree
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return root;
        queue<TreeNode*> q;
        q.push(root); // kickstart the processing
        while (!q.empty()) {
            TreeNode* current = q.front(); // grab processing element, using new current TreeNode* to thread
            q.pop();
            TreeNode* temp = current->left; // perform swap, using new temp TreeNode* as swap placeholder
            current->left = current->right;
            current->right = temp;
            // note: NOW, left was the former right, and vice-versa
            // add it to the queue and iteratively continue processing
            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
            // loop back until there are no elements left
        }
        return root;
    }
};