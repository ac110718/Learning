#include <cstdio>
#include <cstdint>
#include <cstdarg>

int sum(size_t n, ...) { //declared as cariadic function
    va_list args;
    va_start(args, n); //va_list requires initialization
    int result{};
    while (n--) {
        auto next_element = va_arg (args, int); //iterator va_arg taking list and type
        result += next_element;
    }
    va_end(args);
    return result;
}

//implement with recursive template functions

//base case
template <typename T>
constexpr T tsum(T x) {
    return x;
}

template <typename T, typename... Args>
constexpr T tsum(T x, Args... args) {
    return x + tsum(args...);
}

//implement with fold expression

template <typename... T>
constexpr auto fsum(T... args) {
    return (... + args);
}

int main() {
    printf("The answer is %d.\n", sum(6, 2, 4, 6, 8, 10, 12));
    printf("The template answer is %d.\n", tsum(2, 4, 6, 8, 10, 12) );
    printf("The fold answer is %d.\n", fsum(2, 4, 6, 8, 10, 12));
}