#include <stdexcept>
#include <cstdio>
#include <cstring>

struct SimpleString {
    SimpleString(size_t max_size)
        :   max_size {max_size},
            length {} {
        if (max_size == 0) {
            throw std::runtime_error{ "Max size must be at least 1."};
        }
        buffer = new char[max_size];
        buffer[0] = 0;
    }

    //Copy constructor so that pointer to buffer doesn't point to same address after a copy

    SimpleString(const SimpleString& other)
        :   max_size{ other.max_size },
            buffer{ new char[other.max_size] }, //new buffer
            length { other.length } {
            std::strncpy(buffer, other.buffer, max_size);
    }

    SimpleString& operator=(const SimpleString& other) {
        if (this == &other) return *this;
        const auto new_buffer = new char[other.max_size];
        delete[] buffer;
        buffer = new_buffer;
        length = other.length;
        max_size = other.max_size;
        std::strncpy(buffer, other.buffer, max_size);
        return *this;
    }

    //Move constructor so that SimpleStringOwner can re-use the same resource rather than using a separate copy.
    SimpleString(SimpleString&& other) noexcept
        :   max_size { other.max_size },
            buffer(other.buffer),
            length(other.length) {
                other.length = 0;
                other.buffer = nullptr; //must break the link.. or else if you accidentally delete other, current data will get deleted too
                other.max_size = 0;
    }

    SimpleString& operator=(SimpleString&& other) noexcept {
        if (this == & other) return *this;
        delete[] buffer;
        buffer = other.buffer;
        length = other.length;
        max_size = other.max_size;
        other.buffer = nullptr;
        other.length = 0;
        other.max_size = 0;
        return *this;
    }

    ~SimpleString() {
        delete[] buffer;
    }

    void print(const char* tag) const {
        printf("%s: %s", tag, buffer);
    }

    void print_ptr() {
        printf("address: %p\n", buffer);
    }

    bool append_line(const char* x) {
        const auto x_len = strlen(x);
        if (x_len + length + 2 > max_size) return false;
        std::strcpy(buffer + length, x);
        length += x_len;
        buffer[length++] = '\n';
        buffer[length] = 0;
        return true;
    }
private:
    size_t max_size;
    char* buffer;
    size_t length;
};

struct SimpleStringOwner {
    SimpleStringOwner(const char* x)
        : string{ 10 } {
        if (!string.append_line(x)) {
            throw std::runtime_error{"Not enough memory!"};
        }
        string.print("Constructed");
    }

    //Constructor using move to take in SimpleString

    SimpleStringOwner(SimpleString&& x) : string { std::move(x) } {
        string.print("Constructed");
        string.print_ptr();
    }

    ~SimpleStringOwner() {
        string.print("About to destroy");
    }
private:
    SimpleString string;
};

int main() {
    // SimpleString a{50};
    // a.append_line("We apologize for the");
    // SimpleString a_copy { a };
    // a.append_line("inconvenience.");
    // a_copy.append_line("incontinence.");
    // a.print("a");
    // a_copy.print("a_copy");

    // SimpleString a{ 50 };
    // a.append_line("We apologize for the");
    // SimpleString b{ 50 };
    // b.append_line("Last message");
    // a.print("a");
    // b.print("b");
    // b=a;
    // a.print("a");
    // b.print("b");

    SimpleString x{ 50 };
    x.append_line("We apologize for the");
    x.print_ptr();
    SimpleStringOwner a {std::move(x)}; //std::move is simply a recast of x to an rval
}