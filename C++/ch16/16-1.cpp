// #define CATCH_CONFIG_MAIN
// #include "../catch.hpp"
#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main() {
    // bitset<8> s{ "01110011" };
    // string str{"Crying zeros and I'm hearing " };
    // size_t num { 111 };
    // cout << s;
    // cout << '\n';
    // cout << str;
    // cout << num;
    // cout << "s\n";
    // cout << s << '\n' << str << num << "s\n";

    double x, y;
    cout << "X: ";
    cin >> x;
    cout << "Y: ";
    cin >> y;

    string op;
    cout << "Operation: ";
    cin >> op;
    if (op == "+") {
        cout << x + y;
    } else if ( op == "-") {
        cout << x - y;
    } else if ( op == "*" ) {
        cout << x * y;
    } else if (op == "/") {
        cout << x / y;
    } else {
        cout << "Unknown operation " << op;
    }
}