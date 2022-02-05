#include <cstdio>

int main() {
    int original = 100;
    int& original_ref = original;
    printf("Original: %d\n", original);
    printf("Reference: %d\n", original_ref);

    int new_value = 200;
    original_ref = new_value;

    //a reference can't be re-pointed. 
    //reassignment of the reference means over-writing the original value
    printf("Original: %d\n", original);
    printf("new_value: %d\n", new_value);
    printf("Reference: %d\n", original_ref);

}