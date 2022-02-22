#include <iostream>


using namespace std;

// Look and say sequence.. consolidating repetition of next n
// <1, 11, 21, 1211, 111221, 312211, ... >

string NextNumber(const string& s) {
    string result;
    for (int i = 0; i < size(s); i++) { // process all elements
        int count = 1;
        // not out of bounds and there is repetition in digits..
        while (i+1 < size(s) && s[i] == s[i+1]) {
            // track number of times element is seen.. force forward iterate i above and beyond for loop
            i++, count++;
        }
        result += to_string(count) + s[i]; // append sub reptitiion to result
    }
    return result;
}
string LookAndSay(int n) {
    string s = "1";
    for (int i = 1; i < n; i++) {
        s = NextNumber(s); // process each subsequent number n times based on previous iteration
    }
    return s;
}

int main() {
    for (int i = 1; i < 11; i++) {
        cout << LookAndSay(i) << "\n";
    }
}