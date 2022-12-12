// you have m x n sized map
// how many different paths can you take to reach bottom right corner from top left
// recursive solution (options from top + options from left)
// so use DP to populate answers bottoms up

class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 1 || n == 1 || m == 0 || n == 0) return min(m, n);
        int dp[m][n];
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }
        for (int i = 0; i < n; i++) {
            dp[0][i] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
        
        
    }
};