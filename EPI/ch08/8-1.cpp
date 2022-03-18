#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

template <typename T>
struct ListNode {
    T data;
    shared_ptr<ListNode<T>> next;
};

void PrintLinkedListInReverse(shared_ptr<ListNode<int>> head) {
    stack<int> nodes;
    while (head) {
        nodes.push(head->data);
        head = head->next;
    }
    while (!empty(nodes)) {
        cout << nodes.top() << endl;
        nodes.pop();
    }
}

// class with cached Max API. Each element is a struct w data + max

class Stack {
  public:
    bool Empty() const {
        return empty(element_with_cached_max_);
    }
    int Max() const {
        return element_with_cached_max_.top().max;
    }
    int Pop() {
        int pop_element = element_with_cached_max_.top().element;
        element_with_cached_max_.pop();
        return pop_element;
    }
    void Push(int x) {
        element_with_cached_max_.emplace(
            ElementWithCachedMax{x, max(x, Empty() ? x : Max())} // compare x to current Max()
        );
    }
  private:
    struct ElementWithCachedMax {
        int element;
        int max;
    };
    stack<ElementWithCachedMax> element_with_cached_max_;
};

// RPN
int Evaluate(const string& expression) {
    stack<int> intermediate_results;
    stringstream ss(expression);
    string token;
    const char kDelimiter = ',';
    const unordered_map<string, function<int(int, int)>> kOperators = {
        {"+", [](int x, int y) -> int { return x + y; }},
        {"-", [](int x, int y) -> int { return x - y; }},
        {"*", [](int x, int y) -> int { return x * y; }},
        {"/", [](int x, int y) -> int { return x / y; }}
    };
    while (getline(ss, token, kDelimiter)) { // extract token from ss with kDelimiter
        if (kOperators.count(token)) {
            // evalute expression and put back into stake
            const int y = intermediate_results.top();
            intermediate_results.pop();
            const int x = intermediate_results.top();
            intermediate_results.pop();
            intermediate_results.emplace(kOperators.at(token)(x, y));
        } else {
            intermediate_results.emplace(stoi(token));
        }
    }
    return intermediate_results.top();
}
int main() {
    vector<shared_ptr<ListNode<int>>> node_vec;
    shared_ptr<ListNode<int>> next_node;
    for (int i = 6; i > 0; i--) {
        if (i == 6) {
            next_node = nullptr;
        }
        auto temp = make_shared<ListNode<int>>(ListNode<int>{i, next_node});
        next_node = temp;
    }
    PrintLinkedListInReverse(next_node);
    Stack max_test;
    max_test.Push(5);
    max_test.Push(3);
    max_test.Push(7);
    while (!max_test.Empty()) {
        cout << "Max " << max_test.Max() << " | Element " << max_test.Pop() << endl;
    }
    cout << Evaluate("3,4,+,2,*,1,+") << endl;
}