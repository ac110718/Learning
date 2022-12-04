// Problem: Can string s be decomposed cleanly into words in wordDict
// Input words into a set
// Iterate through dynamic programming
// Can a word END with that specific character?
// Check all possibilities from j=0 through j < i (any possible start, but with definitive end)
// return true or false for last character (yes, you can break it up or not)

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        set<string> word_set(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1);
        dp[0] = true;
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && word_set.find(s.substr(j, i-j)) != word_set.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
        
    }
};