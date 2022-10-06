class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        int n = heights.size(), area = 0;
        stack<int> indexes;
        for (int i = 0; i < n; i++) {
            // keep pushing, but stop when reaching declining height
            // check the max area of each rectangle you could have built leading into this
            // with i - 1 as the last stop position
            while (!indexes.empty() && heights[indexes.top()] > heights[i]) {
                int h = heights[indexes.top()]; indexes.pop();
                int l = indexes.empty() ? -1 : indexes.top();
                area = max(area, h * (i - l - 1)); // i doesn't change in this while loop
            }
            indexes.push(i);
        }
        return area;
        
    }
};