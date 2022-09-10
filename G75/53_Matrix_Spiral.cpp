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
            if (m == 1) {
                for (int i = 0; i < n; i++) {
                    result.push_back(matrix[x][y++]);
                }
                break;
            } else if (n==1) {
                for (int i = 0; i < m; i++) {
                    result.push_back(matrix[x++][y]);
                }
                break;
            }
            for (int i = 0; i < n - 1; i++) {
                result.push_back(matrix[x][y++]);
            }
            for (int i = 0; i < m - 1; i++) {
                result.push_back(matrix[x++][y]);
            }
            for (int i = 0; i < n - 1; i++) {
                result.push_back(matrix[x][y--]);
            }
            for (int i = 0; i < m - 1; i++) {
                result.push_back(matrix[x--][y]);
            }
            x++;
            y++;
            m -= 2;
            n -= 2;
        }
        return result;
        
    }
};