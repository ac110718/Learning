class Solution {
public:
    string addBinary(string a, string b) {
        int m = a.size() - 1;
        int n = b.size() - 1;
        int sum = 0;
        string result = "";
        while ( m >= 0 || n >= 0 ) {
            if (m >= 0) {
                sum += a[m] - '0'; // get the int diff between '1' and '0'
                m--;
            }
            if (n >= 0) {
                sum += b[n] - '0';
                n--;
            }
            if (sum % 2) { // there is odd number i.e. 1, so add 1 to the result builder
                result = "1"+ result;
            } else {
                result = "0" + result; // there are two 1s so add a placeholder 0 to the result builder
            }
            sum /= 2; // iterate to next position by mod 2 to sum. If it's 1, it will go to zero.. if 2, then there's a 1 in the carryover
        }
        if (sum % 2 == 1) {
            result = "1" + result; // add the final 1 to the result builder
        }
        return result;
        
    }
};