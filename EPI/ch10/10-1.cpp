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

int main() {
    vector<string> string_vec = {"abc", "def", "something", "another", "a", "b", "testing", "reallyreallylongword"};
    auto output = TopK(3, string_vec.begin(), string_vec.end());
    for (auto word : output) {
        cout << word << ", ";
    }
    cout << endl;

}