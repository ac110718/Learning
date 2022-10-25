// for each path.. how many previous paths would get you there?
// one step prior.. and two steps prior
// load in base cases 0 steps and 1 step.. there is one path for each
// iterate through DP table, populating from bottoms up
// return dp[n] solution

class Solution {
public:
    int climbStairs(int n) {
        int dp[n+1];
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i < n+1; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
};