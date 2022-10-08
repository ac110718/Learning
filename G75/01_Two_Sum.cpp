// iterate through list, putting numbers into hashmap
// along the way, first check for existence of complement
// in which case, immediately return with answer

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        for (int i = 0; i < size(nums); i++) {
            int comp = target - nums[i];
            if (map.find(comp) != map.end()) {
                return vector<int> {map[comp], i};
            } else {
                map[nums[i]] = i;
            }
        }
        return vector<int> {};   
    }
};