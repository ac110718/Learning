// keep pointer to starting position, max length
// map to remember what characters you've seen
// if seen character.. start at last time you saw character (+1), or later (prev start point)
// in map, update latest position of char to current position
// update max length to be curr position - safe start + 1

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