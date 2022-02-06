#include <cstdio>
#include <utility>

template <typename T>
struct SimpleUniquePointer {
    SimpleUniquePointer() = default; //sets to nullptr. Keep both default and custom constructor
    SimpleUniquePointer(T* pointer)
        : pointer { pointer } {
    }
    ~SimpleUniquePointer() {
        if (pointer) delete pointer;
    }
    //prevent copying
    SimpleUniquePointer(const SimpleUniquePointer&) = delete;
    SimpleUniquePointer& operator=(const SimpleUniquePointer&) = delete;

    SimpleUniquePointer(SimpleUniquePointer&& other) noexcept
        : pointer { other.pointer } {
            other.pointer = nullptr; // dereference so that moved from object can't accidentally change or delete this ptr
    }
    SimpleUniquePointer& operator=(SimpleUniquePointer&& other) noexcept {
        if(pointer) delete pointer;
        pointer = other.pointer;
        other.pointer = nullptr;
        return *this;
    }

    T* get() {
        return pointer;
    }
private:
    T* pointer;
};

struct Tracer {
    Tracer(const char* name) : name { name } {
        printf("%s constructed.\n", name);
    }
    ~Tracer() {
        printf("%s destructed.\n", name);
    }
private:
    const char* const name;
};

void consumer(SimpleUniquePointer<Tracer> consumer_ptr) {
    printf("(cons) consumer_ptr: 0x%p\n", consumer_ptr.get());
}

int main() {
    auto ptr_a = SimpleUniquePointer(new Tracer{ "ptr_a" });
    printf("(main) ptr_a: 0x%p\n", ptr_a.get());
    consumer(std::move(ptr_a)); //pass in via move rather than copy
    //ptr_a will be moved to argument used inside consumer function and original will be destroyed
    //original ptr_a points to nullptr as specified by move constructor of SimpleUniquePointer
    printf("(main) ptr_a: 0x%p\n", ptr_a.get()); //nullptr
}