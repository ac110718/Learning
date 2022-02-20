#include <iostream>
#include <string>

using namespace std;

bool IsPalindromic(const string& s) {
    for (int i = 0, j = size(s) - 1; i < j; i++, j--) {
        if (s[i] != s[j]) {
            return false;
        }
    }
    return true;
}

string IntToString(int x) {
    bool is_negative = false;
    if (x < 0) {
        is_negative = true;
    }
    string s;
    do { // ensure at least one iteration.. in case x = 0
        s += '0' + abs(x % 10); // take "char of zero position" and offset by last digit of x to append
        x /= 10; // take remaining number for next loop.
    } while (x);

    s += is_negative ? "-" : "";
    return {rbegin(s), rend(s)}; // reverse the order since appended LSD first
}

int main() {
    cout << boolalpha << IsPalindromic("asdbdsa") << endl;
    cout << IntToString(-100291) << endl;
}