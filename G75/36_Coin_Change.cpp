// build up to total possible solutions up to amount times
// for each possible amount dollar...
// add one coin + min makeup for amount - coin = subamount
// base case is when amount - coin = zero.. in which case you'd have that exact coin
// build up from here..
// you fill up integers with amount + 1
// if above amount.. there was no solution.. otherwise
// you return number of coins needed to formulate that amount
// the hops are defined by coins[k] or the amount of each coin.

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