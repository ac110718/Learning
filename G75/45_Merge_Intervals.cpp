class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<pair<int, int>> coord;
        for (int i = 0; i < intervals.size(); i++) {
            coord.push_back({intervals[i][0], intervals[i][1]});
        }
        sort(coord.begin(), coord.end());
        int curr_x = coord[0].first;
        int curr_y = coord[0].second;
        vector<vector<int>> result;
        for (int i = 1; i < intervals.size(); i++) {
            if (coord[i].first <= curr_y) {
                curr_y = max(curr_y, coord[i].second);
            } else {
                result.push_back({curr_x, curr_y});
                curr_x = coord[i].first;
                curr_y = coord[i].second;
            }
        }
        result.push_back({curr_x, curr_y});
        return result;
        
    }
};