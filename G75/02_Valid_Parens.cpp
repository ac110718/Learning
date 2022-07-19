class Solution {
public:
    bool isValid(string s) {
        stack<char> parens;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '(' || c == '{' || c == '[') {
                parens.push(c);
            } else {
                if (
                    parens.empty() ||
                    c == ')' && parens.top() != '(' ||
                    c == '}' && parens.top() != '{' ||
                    c == ']' && parens.top() != '[' 
                ) {
                    return false;
                }
                parens.pop();
            }
        }
        return parens.empty();
    }
};