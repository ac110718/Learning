class Solution {
public:
    string minWindow(string s, string t) {
        if (s.size() == 0 || t.size() == 0) return "";
        vector<int> char_count(128, 0);
        int required = t.size();
        for (int i = 0; i < required; i++) char_count[t[i]]++;
        int min_length = INT_MAX, start = 0, min_start = 0, i = 0;
        while (i <= s.size() && start < s.size()) {
            if (required) {
                if (i == s.size()) break;
                char_count[s[i]]--;
                if (char_count[s[i]] >= 0) required--;
                i++;
            } else {
                if (i - start < min_length) {
                    min_length = i - start;
                    min_start = start;
                }
                char_count[s[start]]++;
                if (char_count[s[start]] > 0) required++;
                start++;
            }
        }
        return min_length == INT_MAX ? "" : s.substr(min_start, min_length);
        
    }
};