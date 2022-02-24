#include <iostream>
#include <unordered_map>
#include <vector>

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

// determine if string of ints is a valid IP address

bool IsValidPart(const string& s) {
    if (size(s) > 3) {
        return false;
    }
    // only "0" is a valid part.. "01.." "00" etc fail
    if (s.front() == '0' && size(s) > 1) {
        return false;
    }
    int val = stoi(s);
    return val <= 255 && val >= 0; // valid range
}

vector<string> GetValidIpAddress (const string& s) {
    vector<string> result;
    // use if and for to drive depth of search
    for (size_t i = 1; i < 4 && i < size(s); i++) {
        if (const string first = s.substr(0, i); IsValidPart(first)) {
            for (size_t j = 1; j < 4 && i + 4 < size(s); j++) {
                if (const string second = s.substr(i, j); IsValidPart(second)) {
                    for (size_t k = 1; k < 4 && i + j + k < size(s); k++) {
                        const string third = s.substr(i + j, k);
                        const string fourth = s.substr(i+j+k);
                        if (IsValidPart(third) && IsValidPart(fourth)) {
                            result.emplace_back(first + "." + second + "." + third + "." + fourth);
                            // only when meeting all four requirements are you put into results
                        }
                    }
                }
            }
        }
    }
    return result;
}

int main() {
    cout << RomanToInteger("LVIIII") << endl;
    cout << RomanToInteger("LIX") << endl;
    auto x = GetValidIpAddress("19216811");
    for (auto ip : x) {
        cout << ip << endl;
    }
}