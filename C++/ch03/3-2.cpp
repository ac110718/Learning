#include <cstdio>

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
    int get_year() const {
        return year;
    }
    private:
        int year;
};



void add_year_out(ClockStruct& clock) {
    clock.set_year(clock.get_year() + 1);
}

bool is_leap_year(const ClockStruct& clock) {
    if (clock.get_year() % 4 > 0) return false;
    if (clock.get_year() % 100 > 0) return true;
    if (clock.get_year() % 400 > 0) return false;
    return true;
}

int main() {
    ClockStruct clock(2023);
    ClockStruct* clock_ptr = &clock;
    clock_ptr->set_year(2025);
    printf("Address of clock: %p\n", clock_ptr);
    printf("Value of clock's year: %d\n", clock_ptr->get_year());

    //use member notation if you just dereference ptr back to struct
    printf("Value of clock's year deref: %d\n", (*clock_ptr).get_year());

    add_year_out(clock);
    printf("Value of clock's year plusone: %d", clock.get_year());
}