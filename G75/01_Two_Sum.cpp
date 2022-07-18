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