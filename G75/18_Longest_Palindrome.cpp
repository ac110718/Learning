class Solution {
public:
    int longestPalindrome(string s) {
        int result = 0;
        unordered_map<char, int> map;
        for (int i = 0; i < s.size(); i++) {
            map[s[i]]++;
        }
        for (auto x : map) {
            if (x.second % 2 == 0 || result % 2 == 0) {
                result += x.second;
            } else {
                result += x.second - 1;
            }
        }
        return result; 
    }
};