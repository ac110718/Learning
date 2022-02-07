#include <cstdio>
#include <cstdint>

struct RandomNumberGenerator {
    explicit RandomNumberGenerator(uint32_t seed) // no implicit conversions
        : number { seed } {}
    uint32_t next();
    size_t get_iterations() const;
private:
    size_t iterations;
    uint32_t number;
};

int main() {
    RandomNumberGenerator rng { 0x4c4347 };
    while (rng.next() != 0x474343 ) {
        //Do nothing.. everything done via side effects of next()
    }
    printf("%zu", rng.get_iterations());
}

//implement member functions here, with access to member variables within struct

uint32_t RandomNumberGenerator::next() {
    ++iterations;
    number = 0x3FFFFFFF & (0x41C64E6D * number + 12345) % 0x80000000;
    return number;
}

size_t RandomNumberGenerator::get_iterations() const {
    return iterations;
}
