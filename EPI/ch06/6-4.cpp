#include <iostream>
#include <unordered_map>

using namespace std;

// start read from the right for easier processing
// always additive unless you run into a numeral less than the one to the right
// in which case you SUBTRACT rather than add
int RomanToInteger(const string& s) {
    unordered_map<char, int> T = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
    int sum = T[s.back()];
    for (int i = s.length() - 2; i >= 0; i--) {
        if (T[s[i]] < T[s[i+1]]) {
            sum -= T[s[i]];
        } else {
            sum += T[s[i]];
        }
    }
    return sum;
}

int main() {
    cout << RomanToInteger("LVIIII") << endl;
    cout << RomanToInteger("LIX") << endl;
}