#include <cstdio>
#include <cstdint>

template <typename Fn>
void transform(Fn fn, const int* in, int* out, size_t length) {
    for(size_t i{}; i<length; i++) {
        out[i] = fn(in[i]);
    }
}

int main() {
    const size_t len{ 3 };
    //initialize base and output arrays
    int base[] {1, 2, 3}, a[len], b[len], c[len];
    transform([](int x) {return 1;}, base, a, len);
    transform([](int x) {return x;}, base, b, len);
    transform([](int x) {return 10*x+5;}, base, c, len);
    for (size_t i{}; i<len; i++) {
        printf("Element %zu: %d %d %d\n", i, a[i], b[i], c[i]);
    }
}