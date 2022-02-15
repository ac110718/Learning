#include <iostream>

// swap bits in i and j position
// leverage fact that bits can only be 1 or 0
// if bits are same, don't do anything
// if differ, simply "flip" rather than "swap"

long long SwapBits(long long x, int i, int j) {
    if (((x >> i) & 1) != ((x >> j) & 1)) {
        // mask to "flip" bits in appropriate positions
        unsigned long long bit_mask = (1L << i) | (1L << j);
        x ^= bit_mask;
    }
    return x;
}

// provide number that has the same number of bits but still closest in value
// want to minimize the numerical difference.. so change (swap) the rightmost bits
// that are different to preserve the weighting while maintaining numerical proximity

unsigned long long ClosestIntSameBitCount(unsigned long long x) {
    const static int kNumUnsignedBits = 64;
    for (int i = 0; i < kNumUnsignedBits - 1 ; i++) {
        // check starting with LSB
        if (((x >> i) & 1) != ((x >> (i+1)) & 1)) {
            //flip and return two LSBs that differ
            x ^= ((1UL << i) | (1UL << (i+1)));
            return x;
        }
    }
    throw std::invalid_argument("All bits are 0 or 1");
}

int main() {
    std::cout << SwapBits(73, 1, 6) << std::endl; // result 11
    std::cout << ClosestIntSameBitCount(7) << std::endl;
    std::cout << ClosestIntSameBitCount(11) << std::endl;

}