#include <iostream>
#include <cmath>

// generate random number between bounds

int ZeroOneRandom() {
    return 1; // provided function
}

int UniformRandom(int lower_bound, int upper_bound) {
    int number_of_outcomes = upper_bound - lower_bound + 1, result;
    do {
        result = 0;
        // keep building a large enough binary number
        for (int i = 0; (1 << i) < number_of_outcomes; ++i) {
            //append random outcome of LSB
            result = (result << 1) | ZeroOneRandom();
        }
    } while (result >= number_of_outcomes); // in case result overshoots.. repeat.
    return result + lower_bound;
}

//return intersecting Rectangle

struct Rect {
    int x, y, width, height;
};


bool IsIntersect(const Rect& r1, const Rect& r2) {
    return  r1.x <= r2.x + r2.width && r1.x + r1.width >= r2.x && // x overlap
            r1.y <= r2.y + r2.height && r1.y + r1.height >= r2.y; // y overlap
}

Rect IntersectRectangle(const Rect& r1, const Rect& r2) {
    if (!IsIntersect(r1, r2)) {
        return {0, 0, -1, -1};
    }
    return {std::max(r1.x, r2.x), std::max(r1.y, r2.y), // max starting points
            std::min(r1.x + r1.width, r2.x + r2.width) - std::max(r1.x, r2.x), // min extensions
            std::min(r1.y + r1.height, r2.y + r2.height) - std::max(r1.y, r2.y)};
}

int main() {

}