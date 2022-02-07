#include <cstdio>
#include <cstdint>

int main() {
    char to_count{ 's' };
    size_t tally{};
    //capture tally variable by reference to update
    //[&] default by reference, [=] default by value (and add mutable keyword if you want to modify variable in func)
    auto s_counter = [to_count, &tally] (const char* str) {
        size_t index{}, result{};
        while (str[index]) {
            if (str[index] == to_count) result++;
            index++;
        }
        tally += result;
        return result;
    };
    printf("Tally: %zu\n", tally);
    auto sally = s_counter("Sally sells seashells by the seashore.");
    printf("Sally: %zu\n", sally);
    printf("Tally: %zu\n", tally);
    auto sailor = s_counter("Sailor went to sea to see what he could see.");
    printf("Sailor: %zu\n", sailor);
    printf("Tally: %zu\n", tally);
}