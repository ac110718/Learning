class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int x = 0;
        int y = 0;
        vector<int> result;
        if (m == 0) return result;
        while (m > 0 && n > 0) {
            if (m == 1) { // solve for end case of only 1 row
                for (int i = 0; i < n; i++) {
                    result.push_back(matrix[x][y++]);
                }
                break;
            } else if (n==1) { // solve for end case of only 1 column
                for (int i = 0; i < m; i++) {
                    result.push_back(matrix[x++][y]);
                }
                break;
            }
            for (int i = 0; i < n - 1; i++) { // across
                result.push_back(matrix[x][y++]);
            }
            for (int i = 0; i < m - 1; i++) { // down
                result.push_back(matrix[x++][y]);
            }
            for (int i = 0; i < n - 1; i++) { // left
                result.push_back(matrix[x][y--]);
            }
            for (int i = 0; i < m - 1; i++) { // right
                result.push_back(matrix[x--][y]);
            }
            x++; // reposition to next iteration
            y++;
            m -= 2; // shrink outer edges (two)
            n -= 2;
        }
        return result;
        
    }
};