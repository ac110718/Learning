#include <cstdio>
//encapsulation is a design pattern that binds data with the functions. State and modification of state. 
//by doing this, you hide some of code and data. Access data via the member functions
struct ClockStruct {
    ClockStruct(int year_in) {
        if (!set_year(year_in)) year = 2022;
    }
    void add_year() {
        year++;
    }
    bool set_year(int new_year) {
        if (new_year < 2022) return false;
        year = new_year;
        return true;
    }
    int get_year() {
        return year;
    }
    private: //structs default public with private listed last. Class is flipped
        int year;
};

class ClockClass {
    int year;
public:
    ClockClass(int year_in) {
        if (!set_year(year_in)) year = 2022;
    }
    void add_year() {
        year++;
    }
    bool set_year(int new_year) {
        if (new_year < 2022) return false;
        year = new_year;
        return true;
    }
    int get_year() {
        return year;
    }
};

struct Taxonomist {
    Taxonomist() {
        printf("(no argument)\n");
    }
    Taxonomist(char x) {
        printf("char: %c\n", x);
    }
    Taxonomist(int x) {
        printf("int: %d\n", x);
    }
    Taxonomist(float x) {
        printf("float: %f\n", x);
    }
};

int main() {
    ClockStruct clock(2020);
    printf("year: %d\n", clock.get_year());
    clock.set_year(2023);
    printf("year: %d\n", clock.get_year());
    clock.add_year();
    printf("year: %d\n", clock.get_year());
    
    ClockClass clock2(2020);
    printf("year2: %d\n", clock2.get_year());
    clock2.set_year(2023);
    printf("year2: %d\n", clock2.get_year());
    clock2.add_year();
    printf("year2: %d\n", clock2.get_year());

    Taxonomist t1;
    Taxonomist t2('c');
    Taxonomist t3(3);
    Taxonomist t4(6.23e23f);
    // Taxonomist t5{'g'};
    // Taxonomist t6 = {'z'};
    // Taxonomist t7{};
    // Taxonomist t8();
}