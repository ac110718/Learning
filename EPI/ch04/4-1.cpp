#include <iostream>

 short CountBits(unsigned int x) {
    short num_bits = 0;
    while (x) {
        num_bits += x & 1;
        x >>= 1; // right shift by 1 position
    }
    return num_bits;
}

//determine if odd or even number of bits
short Parity1(unsigned long long x) {
    short result = 0;
    while (x) {
        result ^= (x & 1); // will flip result opposite if 1 bit
        x >>= 1;
    }
    return result;
}

// reduce complexity to O(k)..
// x & (x-1) will turn least sig bit to zero.. because x-1 takes all bits to right of lsb and inverts
// while loop runs only k times

short Parity2(unsigned long long x) {
    short result = 0;
    while (x) { // break when zero, or after k bits
        result ^= 1;
        x &= (x-1); // drop lsb
    }
    return result;
}

// parity is associative.. so you can combine chunked with either precomputed cached results, or with the bitset itself
// an even number of bits XOR together will "cancel" each other out
// reducing runtime to log n

short Parity3(unsigned long long x) {
    x ^= x >> 32; // XOR with self in half
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 0x1;
}

int main() {
    std::cout << CountBits(3) << std::endl;
    std::cout << Parity1(31) << std::endl; 
    std::cout << Parity2(31) << std::endl; 
    std::cout << Parity3(31) << std::endl; 
}