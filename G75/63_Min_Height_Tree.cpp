class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n==1) return {0};
        vector<int> adj[n];
        vector<int> degrees(n, 0);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
            degrees[u]++;
            degrees[v]++;
        }
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (degrees[i] == 1) q.push(i);
        }
        vector<int> result;
        while (!q.empty()) {
            int length = q.size();
            result.clear(); // possible roots will be those with the most number of edges.. so get down to the last iteration..
            while (length > 0) {
                int root = q.front();
                q.pop();
                result.push_back(root);
                for (auto &e : adj[root]) {
                    degrees[e]--;
                    if (degrees[e] == 1) q.push(e);
                }
                length--;
            }
        }
        return result;
        
    }
};