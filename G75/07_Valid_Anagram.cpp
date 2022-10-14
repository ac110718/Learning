// map all characters of first word along with count++ for each instance
// for second word, decrement count of corresponding character
// Iterate through map. If any count is not zero, immediately return false
// (too many or too few). Else return true.


class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        unordered_map<char, int> map;
        for (int i = 0; i < s.size(); i++) {
            map[s[i]]++;
        }
        for (int i = 0; i < t.size(); i++) {
            map[t[i]]--;
        }
        for (auto x : map) {
            if (x.second != 0) return false;
        }
        return true;
    }
};