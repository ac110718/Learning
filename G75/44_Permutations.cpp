// only add to answers when full size is achieved
// place desired element at start index
// but also progress the start index on each iteration

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        solve(0, nums, ans);
        return ans;
    }
    void solve(int idx, vector<int>& nums, vector<vector<int>>& ans) {
        if (idx == nums.size()) {
            ans.push_back(nums);
        }
        for (int i = idx; i < nums.size(); i++) {
            swap (nums[idx], nums[i]);
            solve(idx + 1, nums, ans);
            swap (nums[idx], nums[i]);
        }
    }
};