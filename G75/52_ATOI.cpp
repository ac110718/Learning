class Solution {
public:
    int myAtoi(string s) {
        int sign = 1;
        int result = 0;
        int idx = 0;
        
        while (idx < s.size() && s[idx] == ' ') {
            idx++;
        }
        if (idx < s.size() && s[idx] == '-') {
            sign = -1;
            idx++;
        } else if (idx < s.size() && s[idx] == '+') {
            idx++;
        }
        while (idx < s.size() && isdigit(s[idx])) {
            int digit = s[idx] - '0';
             if ((result > INT_MAX / 10) || (result == INT_MAX / 10 && digit > INT_MAX % 10)) {
                return sign == 1 ? INT_MAX : INT_MIN;
            }
            result = 10 * result + digit;
            idx++;
           
        }
        return sign * result;
        
    }
};