#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

vector<string> TopK(int k, vector<string>::const_iterator stream_begin, const vector<string>::const_iterator& stream_end) {
    // make heap that takes string, implemented with vector, with custom comparison
    priority_queue<string, vector<string>, function<bool(string, string)>> 
        min_heap( [](const string& a, const string& b) {
            return size(a) >= size(b);
        } );
    while (stream_begin != stream_end) {
        min_heap.emplace(*stream_begin);
        // evict anything smaller than kth largest item of min_heap
        if (size(min_heap) > k) {
            min_heap.pop();
        }
        stream_begin = next(stream_begin);
    }
    vector<string> result;
    while (!empty(min_heap)) {
        result.emplace_back(min_heap.top());
        min_heap.pop();
    }
    return result;
}

// merge multiple sorted vectors together using heap. Heap will need comparator so create a struct that compares first element of a vector

struct IteratorCurrentAndEnd {
    bool operator > (const IteratorCurrentAndEnd& that) const {
        return *current > *that.current;
    }
    vector<int>::const_iterator current;
    vector<int>::const_iterator end;
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
    priority_queue<IteratorCurrentAndEnd, vector<IteratorCurrentAndEnd>, greater<>> min_heap;
    // place each vector (actually struct) into the array
    for (const vector<int>& sorted_array : sorted_arrays) {
        if (!empty(sorted_array)) {
            min_heap.emplace(IteratorCurrentAndEnd{cbegin(sorted_array), cend(sorted_array)});
        }
    }
    // continuously poll the heap and pull the next smallest element to collate into result
    vector<int> result;
    while (!empty(min_heap)) {
        IteratorCurrentAndEnd smallest_array = min_heap.top(); // vec w smallest head element
        min_heap.pop();
        result.emplace_back(*smallest_array.current);
        if (next(smallest_array.current) != smallest_array.end) {
            min_heap.emplace(IteratorCurrentAndEnd{next(smallest_array.current), smallest_array.end});
        }
    }
    return result;
}

int main() {
    
    vector<string> string_vec = {"abc", "def", "something", "another", "a", "b", "testing", "reallyreallylongword"};
    auto output = TopK(3, string_vec.begin(), string_vec.end());
    for (auto word : output) {
        cout << word << ", ";
    }
    cout << endl;

    vector<vector<int>> sorted_lists = {{0, 0, 1, 3, 4, 8}, {1, 5, 8, 9}, {6, 6, 7}};
    auto output_1 = MergeSortedArrays(sorted_lists);
    for (auto n : output_1) {
        cout << n << ", ";
    }
    cout << endl;

}