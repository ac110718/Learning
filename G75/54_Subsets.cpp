// to build all permutations
// generate result + current candidate solution
// input original dataset, result tracker, candidate tracker, and starting position into recursive function
// for subsets specifically, push back every possible candidate result
// for permutations (bound by a size reaching desired state)


class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> curr;
        generate(nums, result, curr, 0);
        return result;
    }
    
    void generate(vector<int>& nums, vector<vector<int>>& result, vector<int>& curr, int start) {
        result.push_back(curr);
        for (int i = start; i < nums.size(); i++) {
            curr.push_back(nums[i]);
            generate(nums, result, curr, i+1);
            curr.pop_back();
        }
    }
};