// keep a map of adjacent emails to retain associations
// for each name.. put in the first email
// for each email.. run DFS to find adjacent emails (skipping over visited)
// add neighboring emails to list and run DFS for the neighbor emails
// should be eliminating visited emails as you go through

class Solution {
    unordered_set<string> visited;
    unordered_map<string, vector<string>> adjacent;
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        for (vector<string>& account : accounts) {
            string first_email = account[1];
            for (int i = 2; i < account.size(); i++) {
                string email = account[i];
                adjacent[first_email].push_back(email);
                adjacent[email].push_back(first_email);
            }
        }
        vector<vector<string>> result;
        for (vector<string>& account : accounts) {
            string name = account[0];
            string first_email = account[1];
            if (visited.find(first_email) == visited.end()) {
                vector<string> merged;
                merged.push_back(name);
                DFS(merged, first_email);
                sort(merged.begin() + 1, merged.end());
                result.push_back(merged);
            }
        }
        return result;
        
    }
    
    void DFS(vector<string>& mergedAccount, string& email) {
        visited.insert(email);
        mergedAccount.push_back(email);
        for (string& neighbor : adjacent[email]) {
            if (visited.find(neighbor) == visited.end()) {
                DFS(mergedAccount, neighbor);
            }
        }
    }
};