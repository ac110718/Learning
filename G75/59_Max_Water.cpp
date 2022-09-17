class Solution {
public:
    int maxArea(vector<int>& height) {
        int i = 0, j = height.size() - 1;
        int result = min(height[i], height[j]) * (j - i);
        while (i < j) {
            if (height[i] < height[j]) {
                int curr = height[i];
                while (height[i] <= curr && i < j) i++;
            } else {
                int curr = height[j];
                while (height[j] <= curr && i < j) j--;
            }
            result = max(result, min(height[i], height[j]) * (j - i));
        }
        return result;
       
    }
};