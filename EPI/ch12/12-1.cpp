#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

// rolling hash function
int StringHash(const string& s, int modulus) {
    const int kMult = 997;
    return accumulate(begin(s), end(s), 0, [kMult, modulus](int val, char c) {
        return (val * kMult + c) % modulus;
    });
}

vector<vector<string>> FindAnagrams(const vector<string>& dictionary) {
    unordered_map<string, vector<string>> sorted_string_to_anagrams;
    for (const string&s : dictionary) {
        string sorted_str(s);
        sort(begin(sorted_str), end(sorted_str));
        sorted_string_to_anagrams[sorted_str].emplace_back(s);
    }
    vector<vector<string>> anagram_groups;
    for (const auto& [key, group] : sorted_string_to_anagrams) {
        if (size(group) >= 2) {
            anagram_groups.emplace_back(group);
        }
    }
    return anagram_groups;
}

vector<string> input = {"debitcard", "elvis", "silent", "badcredit", "lives", "freedom", "listen", "levis", "money"};

int main() {
    auto result = FindAnagrams(input);
    for (auto vec : result) {
        cout << "{ ";
        for (auto word : vec) {
            cout << word << ", ";
        }
        cout << "}" << endl;
    }
}

