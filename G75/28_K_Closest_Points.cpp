// to store the three SMALLEST distances
// store into MAX heap of k size 
// so that you compare to the top 3 largest easily
// automatically remove 4th largest element if size exceeds k
// load elements out of heap and into vector<int> result

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<int, vector<int>>> max_heap;
        for (int i = 0; i < points.size(); i++) {
            int sq_distance = points[i][0]*points[i][0] + points[i][1]*points[i][1];
            max_heap.push({sq_distance, points[i]});
            if (max_heap.size() > k) {
                max_heap.pop();
            }
        }
        vector<vector<int>> result;
        while (!max_heap.empty()) {
            result.push_back(max_heap.top().second);
            max_heap.pop();
        }
        return result;
        
    }
};