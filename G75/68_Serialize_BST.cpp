/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
private:
    int parse_one(string& data) {
        int pos = data.find(',');
        int val = stoi(data.substr(0,pos));
        data = data.substr(pos+1);
        return val;
    }
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) return "#";
        return to_string(root->val)+","+serialize(root->left)+","+serialize(root->right);
        
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        return helper(data);
    }
    TreeNode* helper(string& data) {
        if (data[0]=='#') {
            if (data.size() > 1) data = data.substr(2);
            return nullptr;
        } else {
            TreeNode* node = new TreeNode(parse_one(data));
            node->left = helper(data);
            node->right = helper(data);
            return node;
        }
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));