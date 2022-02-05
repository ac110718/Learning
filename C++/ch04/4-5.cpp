#include <cstdio>
#include <chrono>
#include <ctime>

struct TimerClass {
    
    TimerClass (char* name) 
        :   timestamp { std::chrono::system_clock::now() },
            name { name }  {
        print_time(timestamp);
    }

    //Copy Constructor
    TimerClass (const TimerClass& other)
        :   timestamp { other.timestamp },
            name { other.name } {
    }

    //Copy assignment
    TimerClass& operator=(const TimerClass& other) {
        if (this == &other) return *this;
        timestamp = other.timestamp;
        name = other.name;
    }

    //Move Constructor
    TimerClass (TimerClass&& other) noexcept
        :   timestamp {std::move(other.timestamp)},
            name {std::move(other.name)} {
    }


    ~TimerClass () {
        auto endtime = std::chrono::system_clock::now();
        auto age = endtime - timestamp;
        printf("%s Destroyed\n", name);
        print_time(endtime);
        printf("Elapsed ms: %d\n", age);
    }
    void print_time(std::chrono::system_clock::time_point ts) {
        auto c = std::chrono::system_clock::to_time_t(ts);
        printf("%s\n", std::ctime(&c));
    }
private:
    std::chrono::system_clock::time_point timestamp;
    char* name;
};

int main() {
    // TimerClass timer("first");
    // int arr[100000];
    // for (int i = 0; i<100000; i++) {
    //     arr[i] = i;
    // }
    // TimerClass timer2 {timer};
    TimerClass timer3("third");
    TimerClass timer4 {std::move(timer3)};
}