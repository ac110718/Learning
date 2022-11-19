// each TrieNode will have 26 potential branches for each letter
// keep bool parameter to denote end
// to insert.. for each character.. if no TrieNode exists, make one
// and point child to child[j] char
// after reaching end.. mark leaf as end
// to search.. trace through char leaf nodes and check bool for end
// to start with search, trace and then ensure last node is not nullptr

class Trie {
private:
    struct TrieNode {
        TrieNode* child[26];
        bool isLeafNode;
    };
    
    TrieNode* root = nullptr;
    
    TrieNode* makeTrieNode() {
        TrieNode* node = new TrieNode();
        for (int i = 0; i < 26; i++) {
            node->child[i] = nullptr;
        }
        node->isLeafNode = false;
        return node;
    }
    
public:
    Trie() {
    }
    
    void insert(string word) {
        if (search(word)) return;
        if (!root) root = makeTrieNode();
        TrieNode* node = root;
        for (int i = 0; i < word.size(); i++) {
            int j = word[i] - 'a';
            if (!node->child[j]) node->child[j] = makeTrieNode();
            node = node->child[j];
        }
        node->isLeafNode = true; 
    }
    
    bool search(string word) {
        TrieNode* node = root;
        if (!root) return false;
        for (int i = 0; i < word.size() && node; i++) {
            int j = word[i] - 'a';
            node = node->child[j];
        }
        if (node) {
            return node->isLeafNode;
        } else {
            return false;
        }
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = root;
        if (!root) return false;
        for (int i = 0; i < prefix.size() && node; i++) {
            int j = prefix[i] - 'a';
            node = node->child[j];
        }
        return node != nullptr;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */