#include <iostream>
#include <string>
#include <numeric>

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

// accumulate or reduce is under <numeric> library
int StringToInt(const string& s) {
    return (s[0] == '-' ? -1 : 1) * accumulate(begin(s) + (s[0] == '-'), end(s), 0, // begin pointer at either 0 or + 1 (s[0]=='-') is true
        [](int running_sum, char c) { 
            return running_sum * 10 + c - '0'; // offset against "char" 0;
        });
}


string ConstructFromBase(int num_as_int, int base) {
    return num_as_int == 0 ? "" :
        ConstructFromBase(num_as_int / base, base) + (char)(num_as_int % base >= 10 // build up remainder first as  prefix
            ? 'A' + num_as_int % base - 10 // find appropriate offset
            : '0' + num_as_int % base);
}

string ConvertBase(const string& num_as_string, int b1, int b2) {
    bool is_negative = num_as_string.front() == '-';
    int num_as_int = accumulate(begin(num_as_string) + is_negative, end(num_as_string), 0, [b1](int x, char c) {
        return x * b1 + (isdigit(c) ? c - '0' : c - 'A' + 10); // in case more than 10 in base1
    });
    return (is_negative ? "-" : "") + (num_as_int == 0 ? "0" : ConstructFromBase(num_as_int, b2));
}


int main() {
    cout << boolalpha << IsPalindromic("asdbdsa") << endl;
    cout << IntToString(-100291)+" is a string" << endl;
    cout << StringToInt("-139492")+1 << endl;
    cout << ConvertBase("615", 7, 13) << endl;
}