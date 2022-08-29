class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int fresh = 0;
        int minutes = 0;
        vector<pair<int, int>> rotten;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) fresh++;
                if (grid[i][j] == 2) rotten.push_back(make_pair(i, j));
            }
        }
        if (fresh == 0) return 0;
        vector<vector<int>> delta {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (rotten.size() != 0) {
            vector<pair<int, int>> infected;
            for (auto cord : rotten) {
                int r = cord.first;
                int c = cord.second;
                for (int k = 0; k < 4; k++) {
                    int x = r + delta[k][0];
                    int y = c + delta[k][1];
                    if (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size() && grid[x][y] == 1) {
                        infected.push_back(make_pair(x, y));
                        grid[x][y] = 2;
                        fresh--;
                    }
                }
            }
            rotten = infected;
            minutes++;
        }
        return fresh > 0 ? -1 : minutes - 1;  
    }
};