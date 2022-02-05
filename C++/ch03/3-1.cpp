#include <cstdio>

int main() {
    int gettysburg;
    
    //assign address of int var to pointer
    int* gettysburg_address = &gettysburg;

    //get value from dereferenced pointer
    printf("Value at gettysburg_address: %d\n", *gettysburg_address);

    //print the actual address
    printf("Gettsburg Address: %p\n", gettysburg_address);

    //functionally identical to gettysburg = 17325
    *gettysburg_address = 17325;
    printf("Value at gettysburg_address: %d\n", *gettysburg_address);
    printf("Gettsburg Address: %p\n", gettysburg_address);
}