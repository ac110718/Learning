class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int low = INT_MAX;
        int max_profit = 0;
        for (int i = 0; i < prices.size(); i++) {
            low = min(low, prices[i]);
            max_profit = max(max_profit, prices[i] - low);
        }
        return max_profit;
    }
};