#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
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

// find smallest subarray containing all values
// first, find the right index that covers all values within the subset
// then, slowly shrink left index to try to close of possible repetitions

struct Subarray {
    int start, end;
};

Subarray FindSmallestSubarrayCoveringSet(const vector<string> &paragraph, const unordered_set<string> &keywords) {
    unordered_map<string, int> keywords_to_cover;
    for (const string &keyword : keywords) {
        ++keywords_to_cover[keyword];
    }
    Subarray result = Subarray{-1, -1};
    int remaining_to_cover = size(keywords);
    for (int left = 0, right = 0; right < size(paragraph); ++right) {
        cout << "left " << left << " | right " << right << " \t" << paragraph[right] << " : " << keywords_to_cover[paragraph[right]] << " | " << remaining_to_cover << " remaining" << endl;
        if (keywords.count(paragraph[right]) && --keywords_to_cover[paragraph[right]] >=0) {
            --remaining_to_cover; // keep going but decrement target for total count and specific keyword count
        }
        // when you're fully covered.. start moving left to shrink window..

        while(remaining_to_cover == 0) {
            // update start and end points at beginning or as window shrinks
            cout << "left " << left << " | right " << right << " \t" << paragraph[left] << " : " << keywords_to_cover[paragraph[left]] << " | " << remaining_to_cover << " remaining" << endl;
            if ((result.start == -1 && result.end == -1) || right - left < result.end - result.start) {
                result = {left, right};
            }
            if (keywords.count(paragraph[left]) && ++keywords_to_cover[paragraph[left]] > 0) {
                ++remaining_to_cover; // break out of loop. You no longer cover the set
            }
            left++;
        }
    }
    return result;
}

vector<string> para2 = {"apple", "banana", "apple", "apple", "dog", "cat", "apple", "dog", "banana", "apple", "cat", "dog", "blah"};
unordered_set<string> keywords = {"banana", "cat"};
unordered_set<string> keywords2 = {"banana", "dog", "cat"};

int main() {
    cout << FindNearestRepitition(para) << endl;
    auto result = FindSmallestSubarrayCoveringSet(para2, keywords);
    cout << result.start << " | " << result.end << endl;
    auto result2 = FindSmallestSubarrayCoveringSet(para2, keywords2);
    cout << result2.start << " | " << result2.end << endl;
}   