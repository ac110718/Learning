// can partition into two equal subset sums


class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int total = 0;
        for (int num : nums) {
            total += num;
        }
        if (total % 2 != 0) return false;
        int halfSum = total / 2;
        int n = nums.size();
        bool dp[n+1][halfSum + 1];
        memset(dp, 0, (n + 1) * (halfSum + 1) * sizeof(bool));
        dp[0][0] = true;
        for (int i = 1; i<n+1; i++) {
            int curr = nums[i-1];
            for (int j = 0; j < halfSum + 1; j++) {
                if (j < curr) {
                    dp[i][j] = dp[i-1][j]; // sum can be formed without element j
                } else {
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-curr]; // or exactly equals sum
                }
            }
        }
        return dp[n][halfSum];   
    }
};