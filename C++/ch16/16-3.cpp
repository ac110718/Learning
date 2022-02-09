// #define CATCH_CONFIG_MAIN
// #include "../catch.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    cout << "Gotham needs its " << boolalpha << true << " hero.";
    cout << "\nMark it " << noboolalpha << false << "!";
    cout << "\nYabba " << hex << 3669732608 << "!";
    cout << "\nthe Hogwarts platform: " << fixed << setprecision(2) << 9.750123;
    cout << "\nAlways eliminate " << 3735929054; // hex still applies
    cout << setw(4) << "\n"
         << 0x1 << "\n"
         << 0x10 << "\n"
         << 0x100 << "\n"
         << 0x1000 << endl;
}