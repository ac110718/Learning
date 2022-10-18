// Find max continuous subarray of numbers
// Two cases: Better off starting over (nums[i]), or continuing while including element (even if negative) ?
// While you're at least still in the positive on cumulative.. you would choose to take cum (max_local) + current element
// If you start over, max_local turns to nums[i].. but store max of local candidates in max_global variable

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max_local = nums[0];
        int max_global = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            max_local = max(nums[i], max_local + nums[i]);
            max_global = max(max_local, max_global);
        }
        return max_global;
    }
};