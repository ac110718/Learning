// to sort three colors, have start and end index
// if 0, then swap (and push) start position forwards
// if 2, then swap (and push) end position backwards
// iterate current working index

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int start = 0, end = nums.size() - 1, index = 0;
        while (start < end && index <= end) {
            if (nums[index] == 0) {
                nums[index] = nums[start];
                nums[start] = 0;
                start++;
                index++;
            } else if (nums[index] == 2) {
                nums[index] = nums[end];
                nums[end] = 2;
                end--;
            } else {
                index++;
            }
        }
        
    }
};