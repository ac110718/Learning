class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        vector<vector<int>> ans(mat.size(), vector<int>(mat[0].size(), INT_MAX));
        queue<pair<int,int>> q;
        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat[0].size(); j++) {
                if (mat[i][j] == 0) {
                    ans[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        int delta[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            for (int k = 0; k < 4; k++) {
                int x = r + delta[k][0];
                int y = c + delta[k][1];
                if (x >= 0 && y >= 0 && x < mat.size() && y < mat[0].size()) {
                    if (ans[x][y] > ans[r][c] + 1) {
                        ans[x][y] = ans[r][c] + 1;
                        q.push({x, y});
                    }
                }
            }
        }
        return ans;
        
    }
};