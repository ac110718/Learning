// Use a Topological sort to trace dependencies
// Two maps.. one to store # incoming edges and one to store actual edge nodes
// increment number of incoming edges to extent you find more dependencies
// add these to list of outgoing edges
// start with zero dependency nodes.. and load into processing queue
// keep track of visited nodes
// for each edge processed, decrement number of dependencies
// when you hit zero.. add to processing queue
// this will process by order of least dependencies and
// only triggered when you've fulfilled all prerequisites


class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        if (prerequisites.size() == 0) return true;
        unordered_map<int, int> num_incoming_edges;
        unordered_map<int, unordered_set<int>> outgoing_edges;
        for (int i = 0; i < prerequisites.size(); i++) {
            if (num_incoming_edges.find(prerequisites[i][0]) == num_incoming_edges.end()) {
                num_incoming_edges[prerequisites[i][0]] = 0;
            }
            if (num_incoming_edges.find(prerequisites[i][1]) == num_incoming_edges.end()) {
                num_incoming_edges[prerequisites[i][1]] = 0;
            }
            num_incoming_edges[prerequisites[i][0]]++;
            if (outgoing_edges.find(prerequisites[i][1]) == outgoing_edges.end()) {
                outgoing_edges[prerequisites[i][1]] = {prerequisites[i][0]};
            } else {
                outgoing_edges[prerequisites[i][1]].insert(prerequisites[i][0]);
            }
        }
        unordered_set<int> visited;
        queue<int> q;
        for (auto node : num_incoming_edges) {
            if (node.second == 0) {
                q.push(node.first);
            }
        }
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            visited.insert(curr);
            for (int edge : outgoing_edges[curr]) {
                num_incoming_edges[edge]--;
                if (num_incoming_edges[edge] == 0 && visited.find(edge) == visited.end()) {
                    q.push(edge);
                }
            }
        }
        return visited.size() == outgoing_edges.size();
        
    }
};