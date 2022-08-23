class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp (amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 1; i < amount + 1; i++) {
            for (int k = 0; k < coins.size(); k++) {
                if (coins[k] <= i) 
                    dp[i] = min(dp[i], dp[i-coins[k]] + 1);
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];   
    }
};