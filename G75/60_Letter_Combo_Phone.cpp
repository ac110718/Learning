class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        vector<string> combo = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> result;
        string temp;
        build(digits, result, temp, combo, 0);
        return result;
    }
    
    void build(string digits, vector<string>& result, string& temp, vector<string>& combo, int start) {
        if (start == digits.size()) {
            result.push_back(temp);
            return;
        }
        int curr = digits[start] - '0';
        for (int i = 0; i < combo[curr].size(); i++) {
            temp.push_back(combo[curr][i]);
            build(digits, result, temp, combo, start+1);
            temp.pop_back();
        }
    }
};