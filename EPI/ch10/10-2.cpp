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

// streaming median. Use two heaps.. one to store the bottom half and one to store the top half and look at intersection of the two heaps

vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin, const vector<int>::const_iterator& sequence_end) {
    priority_queue<int, vector<int>, greater<>> min_heap; // top half
    priority_queue<int, vector<int>, less<>> max_heap; // bottom half
    vector<double> result;

    while (sequence_begin != sequence_end) {
        min_heap.emplace(*sequence_begin++);
        max_heap.emplace(min_heap.top());
        min_heap.pop();
        // default to ensure min_heap has at least 1 or 0 more than max_heap
        if (size(max_heap) > size(min_heap)) {
            min_heap.emplace(max_heap.top());
            max_heap.pop();
        }
        result.emplace_back(
            size(min_heap) == size(max_heap) ? 0.5 * (min_heap.top() + max_heap.top()) : min_heap.top()
        );
    }
    return result;
}

int main() {
    auto two_closest = FindClosestKStars(star_vec.begin(), star_vec.end(), 3);
    for (auto star : two_closest) {
        cout << star.x << ", " << star.y << ", " << star.z << endl;
    }
    auto streaming_vec = vector<int>{1, 0, 3, 5, 2, 0, 1};
    auto streaming_median = OnlineMedian(streaming_vec.begin(), streaming_vec.end());
    for (auto med : streaming_median) {
        cout << med << ", ";
    }
    cout << endl;
}