#include <future> 
#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;

void goat_rodeo() {
    mutex m;
    condition_variable cv;
    const size_t iterations { 1'000'000 };
    int tin_cans_available{}; 
    auto eat_cans = async(launch::async, [&] {
        unique_lock<mutex> lock { m };
        cv.wait(lock, [&](){return tin_cans_available == 1'000'000;}); // waits until predicate returns true
        for (size_t i{}; i < iterations; i++)
            tin_cans_available--;
    });
    auto deposit_cans = async(launch::async, [&] {
        scoped_lock<mutex> lock { m };
        for (size_t i{}; i < iterations; i++)
            tin_cans_available++;
        cv.notify_all(); // notify all threads blocked on the condition variable
    });
    eat_cans.get();
    deposit_cans.get();
    cout << "Tin cans: " << tin_cans_available << "\n";
}

int main() {
    goat_rodeo();
    goat_rodeo();
    goat_rodeo();
}