/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/


// These nodes have both a value and a list of neighbors
// keep a map, mapping out node to node-clone
// keep queue for processing nodes
// For each node queue.. look at each neighbor..
// if neighbor isn't there.. add it to the map, as well as the queue
// add neighbor to list of neighbors for the cloned node (map[current])
// return cloned node.. map[node]

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return nullptr;
        unordered_map<Node*, Node*> map;
        queue<Node*> q;
        q.push(node);
        map[node] = new Node(node->val);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            for (auto neighbor : current->neighbors) {
                if (map.find(neighbor) == map.end()) {
                    map[neighbor] = new Node(neighbor->val);
                    q.push(neighbor);
                }
                map[current]->neighbors.push_back(map[neighbor]);
            }
        }
        return map[node];    
    }
};