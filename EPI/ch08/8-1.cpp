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

bool IsWellFormed(const string& s) {
    stack<char> left_chars;
    const unordered_map<char, char> kLookup = {
        {'(', ')'}, {'{', '}'}, {'[', ']'}
    };
    for (int i = 0; i < size(s); i++) {
        if (kLookup.count(s[i])) { // place any left parens into stack for comparison later
            left_chars.emplace(s[i]);
        } else {
            if (empty(left_chars) || kLookup.at(left_chars.top()) != s[i]) {
                return false; // no match for the right parens
            }
            left_chars.pop(); // next comparison
        }
    }
    return empty(left_chars); // successful completion of comparisons without extras
}

// Sunset view. Given array of buildings from east-to-west order, find buildings that will have sunset view when facing west
// store building into stack.. if top of stack is smaller than next building in array.. it has a blocked view..
// so eject from stack until top of stack (point of comparison) is bigger than current building in array.. then place into stack
// all buildings left in stack are the once that are from highest to lowest height with a sunset view

vector<int> ExamineBuildingsWithSunset(vector<int>::const_iterator sequence_begin, const vector<int>::const_iterator& sequence_end) {
    int building_idx = 0;
    struct BuildingWithHeight{
        int id, height;
    };
    stack<BuildingWithHeight> candidates;
    while (sequence_begin != sequence_end) {
        int building_height = *sequence_begin++;
        while (!empty(candidates) && building_height >= candidates.top().height) {
            candidates.pop(); // empty stack until you go back to building that's taller from east side b/c others will be blocked by curr
        }
        candidates.emplace(BuildingWithHeight{building_idx++, building_height}); // building is shorter. Add to stack
    }
    vector<int> buildings_with_sunset;
    while (!empty(candidates)) {
            buildings_with_sunset.emplace_back(candidates.top().id);
            candidates.pop();
    }
    return buildings_with_sunset;
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
    cout << boolalpha << IsWellFormed("(()][){}]") << endl;
    cout << IsWellFormed("[()[]]{}") << endl;
    vector<int> buildings = {7, 1, 5, 4, 2, 3, 1};
    auto result = ExamineBuildingsWithSunset(buildings.begin(), buildings.end());
    for (int i = size(result) - 1; i >= 0; i--) {
        cout << result[i] << ", ";
    }
    cout << endl;
}