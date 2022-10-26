// add all character frequencies into map
// if even number of characters, can go into palindrome
// therefore, add freq to result (length counter)
// if odd, add lowest "even" number of characters (i.e. freq - 1) for palindrome

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