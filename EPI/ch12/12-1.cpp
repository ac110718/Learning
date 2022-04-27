#include <iostream>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
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

// Can you form a palindrome. Store char into set.. delete on 2nd appearance. Can only have at most 1 leftover entry for middle element

bool CanFormPalindrome(const string& s) {
    unordered_set<char> chars_with_odd_frequency;
    for (char c: s) {
        if (chars_with_odd_frequency.count(c)) {
            chars_with_odd_frequency.erase(c);
        } else {
            chars_with_odd_frequency.insert(c);
        }
    }
    return size(chars_with_odd_frequency) <= 1;
}

int main() {
    auto result = FindAnagrams(input);
    for (auto vec : result) {
        cout << "{ ";
        for (auto word : vec) {
            cout << word << ", ";
        }
        cout << "}" << endl;
    }
    string palindrome = "foobaraboof";
    string not_palindrome = "foobaraboof3aosidjasd";
    cout << palindrome << boolalpha << " | " << CanFormPalindrome(palindrome) << endl;
    cout << not_palindrome << boolalpha << " | " << CanFormPalindrome(not_palindrome) << endl;
}

