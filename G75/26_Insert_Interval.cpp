// Three phases...
// While no overlap with interval end.. push to results
// While overlap.. take min of start, max of end to define new interval.. push to results
// While no overlap with interval beginning.. push to results
// Return list of interval results


class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        int i = 0;
        while (i < intervals.size() && intervals[i][1] < newInterval[0]) {
            result.push_back(intervals[i]);
            i++;
        }
        int newStart = newInterval[0];
        int newEnd = newInterval[1];
        while (i < intervals.size() && intervals[i][0] <= newInterval[1]) {
            newStart = min(newStart, intervals[i][0]);
            newEnd = max(newEnd, intervals[i][1]);
            i++;
        }
        result.push_back(vector<int>{newStart, newEnd});
        while (i < intervals.size()) {
            result.push_back(intervals[i]);
            i++;
        }
        return result;
        
    }
};