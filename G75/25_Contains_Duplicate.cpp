// insert numbers into a set
// if you find current number in set, immediately return true (dup)
// else, add number to set
// if you reach the end, all unique, return false.

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        set<int> s;
        for (int i = 0; i < nums.size(); i++) {
            if (s.find(nums[i]) != s.end()) {
                return true;
            } else {
                s.insert(nums[i]);
            }
        }
        return false;
        
    }
};