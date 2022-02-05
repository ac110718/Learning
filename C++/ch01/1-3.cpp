#include <cstdio>

int absolute_value(int x) {
    // int result = x < 0 ? -x : x;
    // return result;
    return x < 0 ? -x : x;
}

int sum(int x, int y) {
    // int result = x + y;
    // return result;
    return x + y;
}

int main() {
    int num1 = -12;
    int num2 = 55;
    int num3 = 300;
    
    printf("The absolute value of %d is %d.\n", num1, absolute_value(num1));
    
    printf("The sum of %d and %d is %d.\n", num1, num2, sum(num1, num2));
    
    const char* template_string = "The sum of %d and %d is %d.\n";
    //string literals with const
    printf(template_string, num2, num3, sum(num2, num3));
    
    return 0;
}