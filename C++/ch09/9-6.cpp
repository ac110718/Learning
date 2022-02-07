#include <cstdio>
#include <cstdint>

struct LambdaFactory {
    LambdaFactory(char in) : to_count{ in }, tally{} { }
    auto make_lambda() {
        //capture this variable and reference members within lambda
        return [this](const char* str) {
            size_t index{}, result{};
            while (str[index]) {
                if (str[index] == to_count) result++;
                index++;
            }
            tally += result;
            return result;
        };
    }
    const char to_count;
    size_t tally;
};

int main() {
    LambdaFactory factory{ 's' };
    auto lambda = factory.make_lambda();
    printf("Tally: %zu\n", factory.tally);
    auto sally = lambda("Sally sells seashells by the seashore.");
    printf("Sally: %zu\n", sally);
    printf("Tally: %zu\n", factory.tally);
    auto sailor = lambda("Sailor went to sea to see what he could see.");
    printf("Sailor: %zu\n", sailor);
    printf("Tally: %zu\n", factory.tally);
}