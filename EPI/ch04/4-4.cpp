#include <iostream>
#include <cmath>

// % 10 to extract. / 10 for remainder.. analogous to bit shifting
long long Reverse(int x) {
    long long result = 0;
    while (x) {
        // extract last digit of x and "shift" result left
        result = result * 10 + x % 10;
        // process remaining part of x
        x = x / 10;
    }
    return result;
}

bool isPalindromeNumber(int x) {
    if ( x <= 0) {
        return x == 0;
    }

    const int num_digits = static_cast<int>(floor(std::log10(x))) + 1;
    int msd_mask = static_cast<int>(std::pow(10, num_digits - 1));

    for (int i = 0; i < (num_digits / 2); i++) {
        //extract first and last digit. Immediately return if no match
        if (x / msd_mask != x % 10) return false;
        
        // remove first and last digit, shrink mask by 2 digits
        x %= 10;
        x /= 10;
        msd_mask /= 100;
    }

    return true;
}

int main() {
    std::cout << Reverse(12345) << std::endl;
    std::cout << isPalindromeNumber(543535345) << std::endl;
    std::cout << isPalindromeNumber(123) << std::endl;
}