// optimal search of SORTED set
// compare at middle so you can take out half ever iteration
// if mid is too big, move right ptr lower
// if mid is too small, move left ptr higher
// return either mid == search element, or false (-1)


class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }
};