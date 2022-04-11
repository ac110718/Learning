#include <iostream>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;


// find k closest stars

struct Star {
    bool operator<(const Star& that) const {
        return Distance() < that.Distance();
    }

    double Distance() const { return hypot(x, y, z); }
    double x, y, z;
};

vector<Star> FindClosestKStars(vector<Star>::const_iterator stars_begin, const vector<Star>::const_iterator& stars_end, int k) {
    priority_queue<Star> max_heap;
    while (stars_begin != stars_end) {
        max_heap.emplace(*stars_begin++);
        // will always eject the k+1 biggest star out of the heap
        if (size(max_heap) == k+1) {
            max_heap.pop();
        }
    }
    // fill the result to be returned
    vector<Star> closest_stars;
    while (!empty(max_heap)) {
        closest_stars.emplace_back(max_heap.top());
        max_heap.pop();
    }
    return {rbegin(closest_stars), rend(closest_stars)};
}

auto star_vec = vector<Star>{{1, 2, 3}, {3, 5, 6}, {0, 0, 0}, {10, 11, 12}, {0, 0, 1}, {2, 1, 1}};

int main() {
    auto two_closest = FindClosestKStars(star_vec.begin(), star_vec.end(), 3);
    for (auto star : two_closest) {
        cout << star.x << ", " << star.y << ", " << star.z << endl;
    }
}