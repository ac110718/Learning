class Solution {
public:
    string addBinary(string a, string b) {
        int m = a.size() - 1;
        int n = b.size() - 1;
        int sum = 0;
        string result = "";
        while ( m >= 0 || n >= 0 ) {
            if (m >= 0) {
                sum += a[m] - '0';
                m--;
            }
            if (n >= 0) {
                sum += b[n] - '0';
                n--;
            }
            if (sum % 2) {
                result = "1"+ result;
            } else {
                result = "0" + result;
            }
            sum /= 2;
        }
        if (sum % 2 == 1) {
            result = "1" + result;
        }
        return result;
        
    }
};