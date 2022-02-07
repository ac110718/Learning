#include <cstdio>

struct TextFile {
    bool success;
    const char* data;
    size_t n_bytes;
};

TextFile read_text_file(const char* path) {
    const static char contents[] { "Dummy data inside text file." };
    return TextFile {
        true,
        contents,
        sizeof(contents)
    };
}

int main() {
    const auto [success, contents, length] = read_text_file("README.txt");
    if (success) {
        printf("Read %zu bytes: %s\n", length, contents);
    } else {
        printf("Failed to open REAMDE.txt");
    }
}