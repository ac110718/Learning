#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int FindNearestRepitition(const vector<string>& paragraph) {
    unordered_map<string, int> word_to_latest_index;
    int nearest_repeated_distance = numeric_limits<int>::max();
    for (int i = 0; i < size(paragraph); ++i) {
        if (auto latest_equal_word = word_to_latest_index.find(paragraph[i]); latest_equal_word != end(word_to_latest_index)) {
            nearest_repeated_distance = min(nearest_repeated_distance, i - latest_equal_word->second);
            cout << "running min: " << nearest_repeated_distance << endl;
        }
        word_to_latest_index[paragraph[i]] = i;
    }
    return nearest_repeated_distance != numeric_limits<int>::max() ? nearest_repeated_distance : -1;
}

vector<string> para = {"All", "work", "and", "no", "play", "makes", "for", "no", "work", "no", "fun", "and", "no", "results"};

int main() {
    cout << FindNearestRepitition(para) << endl;
}