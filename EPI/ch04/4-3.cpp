#include <iostream>

unsigned long long Add (unsigned long long a, unsigned long long b) {
    while (b) {
        unsigned long long carry = a & b; // get duplicate 1s
        a = a ^ b; // add individual ones together
        // add the carry on the next iteration
        b = carry << 1;
    }
    return a;
}

unsigned long long Multiply (unsigned long long x, unsigned long long y) {
    unsigned long long sum = 0;
    
    // rather than adding yourself y number of times.. 
    // reduce # of additions to factors of 2^k * y where the kth bit of x is 1
    while (x) {
        if (x & 1) {
            sum = Add(sum, y);
        }
        // set up next round
        x >>= 1; // iterate to next bit
        y <<= 1; // add bigger power of y for more significant bits of x
    }
    return sum;
}

// reduce number of subtractions out of x to 2^k * y times
// make y as big as possible and add to quotient accordingly
int Divide(int x, int y) {
    int result = 0;
    int power = 32;
    unsigned long long y_power = static_cast<unsigned long long>(y) << power;
    while (x >= y) {
        // find largest y_power that will still fit into x
        while(y_power > x) {
            y_power >>= 1;
            --power;
        }
        result += 1 << power; // add 1 ^ power to quotient
        // iterate again with reduced remainder
        x -= y_power;
    }
    return result;
}

// rather than multiple x to itself y times.. 
// do only k multiplications... whenever kth bit of y is 1
double Power(double x, int y) {
    double result = 1.0;
    long long power = y;
    if (y < 0) {
        power = -power;
        x = 1.0/x;
    }
    while (power) {
        if (power & 1) {
            result *= x;
        }
        x *= x; // keep "accumulating" the multiplier for next iteration
        power >>= 1; // examine next digit
    }
    return result;
}

int main() {
    std::cout << Multiply(12, 12) << std::endl;
    std::cout << Divide(10000, 100) << std::endl;
    std::cout << Power(2, 10) << std::endl;
}