// implement Queue with 2 stacks
// stack #2 will hold elements in last-in order (i.e. oldest element on top)
// upon a peek.. return the first element (oldest) from s2
// but if s2 has NOT been loaded yet.. load in from s1.. 
// freshest item from s1 will be at bottom of s2
// on push.. push to s1, which will have NEWEST on top
// on pop.. return item from peek and pop s2
// if empty.. BOTH stacks need to be empty


class MyQueue {
    
private:
    stack<int> s1, s2;
public:
    MyQueue() {
        
    }
    
    void push(int x) {
        s1.push(x);
    }
    
    int pop() {
        int result = peek();
        s2.pop();
        return result;
    }
    
    int peek() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        return s2.top();
    }
    
    bool empty() {
        return s1.empty() && s2.empty();
        
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */