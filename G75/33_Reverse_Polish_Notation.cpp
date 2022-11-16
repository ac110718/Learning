// if token is a digit (check last char with isdigit
// push token to stack with stoi
// else.. it's an operator
// first, grab the top two numbers from the stack and pop them
// then you have the operator (current tokens[i])
// operate on the two numbers and push it back to the stack
// return top of stack which will be answer.


class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> s;
        for (int i = 0; i < tokens.size(); i++) {
            if(isdigit(tokens[i][tokens[i].size()-1])) {
                s.push(stoi(tokens[i]));
            } else {
                int y = s.top();
                s.pop();
                int x = s.top();
                s.pop();
                if (tokens[i] == "+") {
                    s.push(x+y);
                } else if (tokens[i] == "-") {
                    s.push(x-y);
                } else if (tokens[i] == "*") {
                    s.push(x*y);
                } else {
                    s.push(x/y);
                }
            }
        }
        return s.top();
    }
};