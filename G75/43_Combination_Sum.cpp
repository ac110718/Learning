class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> combo;
        helper(candidates, target, result, combo, 0);
        return result;
    }
    void helper(vector<int>& candidates, int target, vector<vector<int>>& result, vector<int>& combo, int start) {
        if (target == 0) {
            result.push_back(combo);
            return;
        }
        for (int i = start; i < candidates.size(); i++) {
            if (candidates[i] > target) continue;
            combo.push_back(candidates[i]);
            helper(candidates, target - candidates[i], result, combo, i);
            combo.pop_back();
        }
    }
};