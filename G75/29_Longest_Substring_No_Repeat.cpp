class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int safe_start = 0;
        int length = 0;
        unordered_map<char, int> map;
        for (int i = 0; i < s.size(); i++) {
            if (map.find(s[i]) != map.end()) {
                safe_start = max(safe_start, map[s[i]] + 1);
            }
            map[s[i]] = i;
            length = max(length, i - safe_start + 1);
        }
        return length;
        
    }
};