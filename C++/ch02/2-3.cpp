#include <cstdio>

enum Operation { //Don't use named scopes with class... uncompatible with switch
    Add,
    Subtract,
    Multiply,
    Divide
};

struct Calculator {
    Calculator(Operation o) {
        op = o;
    }
    int calculate(int a, int b) {
        int result;
        switch (op) {
            case Add: { 
                result = a + b;
            } break;
            case Divide: {
                result = a / b;
            } break;
            case Multiply: {
                result = a * b;
            } break;
            default: {
                result = a - b;
            }
        }
        return result;
    }
    
    private:
        Operation op;
};

int main() {
    Calculator adder(Add);
    Calculator sub(Subtract);
    Calculator mult(Multiply);
    Calculator divider(Divide);
    int a = 10;
    int b = 2;
    int x = adder.calculate(a, b);
    int y = sub.calculate(a, b);
    int z = mult.calculate(a, b);
    int w = divider.calculate(a, b);
    printf("add: %d\n", x);
    printf("sub: %d\n", y);
    printf("mult: %d\n", z);
    printf("divide: %d\n", w);
}