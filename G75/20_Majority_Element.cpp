// hold two variables: candidate and frequency of appearance
// when frequency is zero (either beginning.. or overwhelmed by # of other elements)
// then update to a new candidate
// majority element will appear with frequency greater than other non-candidate elements

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int candidate = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (count == 0) {
                candidate = nums[i];
                count++;
            } else if (candidate == nums[i]) {
                count++;
            } else {
                count--;
            }
        }
        return candidate;
        
    }
};