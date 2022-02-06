#include <cstdio>
#include <cstddef>
#include <new> 

struct Point {
    Point() : x{}, y{}, z{} {
        printf("Point at %p constructed.\n", this);
    }
    ~Point() {
        printf("Point at %p destructed.\n", this);
    }
    double x, y, z;
};

int main() {
    // allocate memory space for three Points
    const auto point_size = sizeof(Point);
    std::byte data[3 * point_size];
    printf("Data starts at %p.\n", data);
    // manual assignment of 3 points
    auto point1 = new(&data[0 * point_size]) Point{}; 
    auto point2 = new(&data[1 * point_size]) Point{};
    auto point3 = new(&data[2 * point_size]) Point{};
    // manually destroy each point exactly once calling destructor
    point1->~Point();
    point2->~Point();
    point3->~Point();
}