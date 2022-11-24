// to count islands, count the first immediate 1
// then zero out the rest of the island to eliminate double counting
// zero out by setting all adjacent cells to zero
// if already zero (or boundary), immediately return

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int result = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') result++;
                zero_out_island(grid, i, j);
            }
        }
        return result;
    }
    void zero_out_island(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == '0') return;
        grid[i][j] = '0';
        zero_out_island(grid, i-1, j);
        zero_out_island(grid, i+1, j);
        zero_out_island(grid, i, j-1);
        zero_out_island(grid, i, j+1);
    }
};