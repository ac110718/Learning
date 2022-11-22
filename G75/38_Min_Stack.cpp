// create stack with a global min tracker for any given element within stack
// have parallel stacks.. one with elements (s1)
// one with global min up to ith position (s2), with repeated mins as appropriate
// once min is popped off, should have new global min up to that point.

class MinStack {
    stack<int> s1;
    stack<int> s2;
public:
    MinStack() {
        
    }
    
    void push(int val) {
        s1.push(val);
        if (s2.empty()) {
          s2.push(val);
        } else {
            s2.push(min((val), s2.top()));
        }
    }
    
    void pop() {
        s1.pop();
        s2.pop();
        
    }
    
    int top() {
        return s1.top();
    }
    
    int getMin() {
        return s2.top();
        
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */