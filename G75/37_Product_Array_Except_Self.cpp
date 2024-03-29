// To get product of all nums except self...
// You want cumulative product of all numbers on "either" side
// Leftmost = cum product of rightside. Rightmost = cum product of leftside
// middle = cum product of rightside x cum product leftside
// keep track of two arrays.. left buildup.. and right buildup moving in opposite directions
// multiply together while keeping ith placeholder = 1
// result[0] = 1 x right cum product.. result[size] = left cum product x 1

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int left[nums.size()], right[nums.size()];
        left[0] = 1, right[nums.size() - 1] = 1;
        vector<int> result;
        for (int i = 1; i < nums.size(); i++) {
            left[i] = nums[i-1] * left[i-1];
        }
        for (int i = nums.size() - 2; i >= 0; i--) {
            right[i] = nums[i+1] * right[i+1];
        }
        for (int i = 0; i < nums.size(); i++) {
            result.push_back(left[i] * right[i]);
        }
        return result;     
    }
};