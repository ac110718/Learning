class Solution {
public:
    string longestPalindrome(string s) {
        if (s.size() == 0 || s.size() == 1) return s;
        string result = s.substr(0,1);
        for (int i = 0; i < s.size(); i++) {
            string temp = growSeek(s, i, i); // start at new midpoint and expand "outwards" as much as possible
            result = temp.size() > result.size() ? temp : result;
            temp = growSeek(s, i, i+1); // do it twice as you can have either 0 or 1 repeats in the middle
            result = temp.size() > result.size() ? temp : result;
        }
        return result;
        
    }
    string growSeek(string s, int start, int end) {
        while (start >= 0 && end < s.size() && s[start] == s[end]) {
            start--;
            end++;
        }
        return s.substr(start + 1, end - start - 1);
    }
};