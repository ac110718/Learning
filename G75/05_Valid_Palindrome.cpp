// two pointers at front and back
// while front pointer is still "in front"...
// skip pointer to next alphanum on both ends
// if lowercase alnum == lowercase alnum at both ends.. move to middle
// else immediate exit
// if you make it to middle (i.e. front is no longer "in front"), then return true


class Solution {
public:
    bool isPalindrome(string s) {
        int i = 0;
        int j = size(s);
        while (i < j) {
            while (i<j && !isalnum(s[i])) i++;
            while (i<j && !isalnum(s[j])) j--;
            if (tolower(s[i]) == tolower(s[j])) {
                i++;
                j--;
            } else {
                return false;
            }
        }
        return true;
    }
};