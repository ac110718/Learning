// iterate through string, pushing open brackets along the way
// if not an open bracket, it MUST satisfy closing appropriately. 
// if so, pop and continue
// if conditions not satisfied, immediately return false
// last and final check, you should make it all the way through to end
// with no exceptions, hence parens.empty() check on the stack.

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