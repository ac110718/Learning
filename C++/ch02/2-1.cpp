#include <cstdio>


int main() {
    unsigned short a = 0b10101010;
    printf("%hu\n", a); //170

    int b = 0123;
    printf("%d\n", b); //83

    unsigned long long d = 0xFFFFFFFFFFF;
    printf("%llu\n", d);

    unsigned int y = 3669732608;
    printf("Yabba %x!\n", y); //hexadecimal

    // int mit_zip_code = 02139; won't compile, interpreted as octal and 9 is not octal digit

    char x = 'M';
    wchar_t w = L'Z'; //L to declare character literal
    printf("Windows binaries start with %c%lc.\n", x, w);

    bool b1 = true;
    bool b2 = false;
    printf("%d %d\n", b1, b2); // 1 is true and 0 false, opposite of shell

    size_t size_c = sizeof(char);
    printf("char: %zu\n", size_c); //%zu for decimal representation for size_t
    size_t size_s = sizeof(short);
    printf("short: %zu\n", size_s);
    size_t size_i = sizeof(int);
    printf("int: %zu\n", size_i);
    size_t size_l = sizeof(long);
    printf("long: %zu\n", size_l);
    size_t size_ll = sizeof(long long);
    printf("long long: %zu\n", size_ll);

    int arr[] = {1, 2, 3, 4};
    char ts[] = "The third element is %d.\n";
    printf(ts, arr[2]);
    arr[2] = 100;
    printf(ts, arr[2]);

    unsigned long maximum = 0;
    unsigned long values[] = {10, 50, 20, 40, 0};
    for (size_t i=0; i < 5; i++) { // size_t for i because values could theoretically take up tons of storage and size_t is guaranteed to be able to index any value while int is not
        if (values[i] > maximum) maximum = values[i];
    }
    printf("The maximum value is %lu\n", maximum);

    maximum = 0;
    for (unsigned long value : values) {
        if (value > maximum) maximum = value;
    } // range-based loops discard iterator variable i allowing you to use elements directly and simplify meaning
    printf("The maximum value is %lu again\n", maximum);

    short array2[] = {103, 105, 32, 98, 105, 108, 108, 0};
    size_t n_elements = sizeof(array2) / sizeof(short);
    printf("%zu elements in array\n", n_elements);

    char house[] = "a house of gold";
    printf("A book holds %s\n", house); //%s for string

    char alphabet[27];
    for (int i = 0; i < 26; i++) {
        alphabet[i] = i + 97;
    }
    alphabet[26] = 0; // null-terminated string
    printf("%s\n", alphabet);

    for (int i = 0; i < 26; i++) {
        alphabet[i] = i + 65;
    }
    printf("%s\n", alphabet);

}