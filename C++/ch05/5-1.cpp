#include <cstdio>

struct Logger {
    virtual ~Logger() = default;
    virtual void log_transfer(long from, long to, double amount) = 0;
};

struct ConsoleLogger: Logger {
    void log_transfer(long from, long to, double amount) override {
        printf("[cons] %ld -> %ld: %f\n", from, to, amount);
    }
};

struct FileLogger: Logger {
    void log_transfer(long from, long to, double amount) override {
        printf("[file] %ld -> %ld: %f\n", from, to, amount);
    }
};

struct Bank {
    //constructor injection. Pointer to interface implementation
    Bank(Logger* logger) : logger { logger } {}
    //property injection
    void set_logger(Logger* new_logger) {
        logger = new_logger;
    }
    void make_transfer(long from, long to, double amount) {
        if (logger) logger->log_transfer(from, to, amount);
    }
private:
    Logger* logger;
};

int main() {
    ConsoleLogger console_logger;
    FileLogger file_logger;
    Bank bank { &console_logger }; //pass in the pointer reference
    bank.make_transfer (1000, 2000, 49.95);
    bank.set_logger( &file_logger ); //pass in the pointer reference
    bank.make_transfer(3000, 4000, 20.00);
}