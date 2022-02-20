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

int main() {
    cout << boolalpha << IsPalindromic("asdbdsa") << endl;
}