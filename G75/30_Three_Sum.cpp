// three numbers that add up to zero
// sort the numbers for optimal iteration
// curr pointer (i), start, end pointer
// push to results when i + start + end = 0
// accelerate forward and backwards when it's the same number
// push start forward if number is too small < 0, or end backwards if too big > 0

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; i++) {
            if (i > 0) while ( i < nums.size() && nums[i] == nums[i-1]) i++;
            int start = i + 1, end = nums.size() - 1;
            while (start < end) {
                if (nums[i] + nums[start] + nums[end] == 0) {
                    result.push_back({nums[i], nums[start], nums[end]});
                    start++;
                    while (nums[start] == nums[start-1] && start < end) start++;
                    while (nums[end] == nums[end-1] && start < end) end--;
                } else if (nums[i] + nums[start] + nums[end] < 0) {
                    start++;
                } else {
                    end--;
                }
            }
        }
        return result;
        
    }
};