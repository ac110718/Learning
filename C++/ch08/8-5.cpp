#include <cstdio>

// iterators need to support !=, ++ and operator * for the loops
// for (auto b = range.begin(); b != range.end(); b++) { const auto& element = *b }

struct FibonacciIterator {
    bool operator!=(int x) const {
        return x >= current;
    }
    FibonacciIterator& operator++() {
        const auto tmp = current;
        current += last;
        last = tmp;
        return *this;
    }
    int operator*() const {
        return current;
    }
private:
    int current {1}, last {1};
};

struct FibonnacciRange {
    explicit FibonnacciRange(int max) : max { max } {}
    FibonacciIterator begin() const {
        return FibonacciIterator{};
    }
    int end() const {
        return max;
    }
private:
    const int max;
};

int main() {
    for (const auto i : FibonnacciRange{ 5000 }) {
        if (i == 21) {
            printf("*** ");
            continue;
        }
        printf("%d ", i);
    }
}