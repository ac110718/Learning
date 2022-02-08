#include <cstdio>
#include <memory>

using FileGuard = std::unique_ptr<FILE, int(*)(FILE*)>;

void say_hello(FileGuard file) {
    fprintf(file.get(), "MY MESSAGE HERE\n");
}

int main() {
    //create new file
    auto file = fopen("HAL9000", "w");
    if (!file) return 1;
    //unique ptr to this file with fclose as destructor
    FileGuard file_guard{ file, fclose };
    //pass this unique ptr to function and write into it.
    say_hello(std::move(file_guard));
    return 0;
}