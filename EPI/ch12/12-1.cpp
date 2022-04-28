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

// Is anonymous letter constructible? letter characters must be subset of magazine characters
// Increment character count while processing letter text. Decrement as you read through magazine. End when depleted

bool IsLetterConstructibleFromMagazine(const string& letter_text, const string& magazine_text) {
    unordered_map<char, int> char_frequency_letter;
    for (char c: letter_text) {
        ++char_frequency_letter[c];
    }
    for (char c: magazine_text) {
        if (auto it = char_frequency_letter.find(c); it != cend(char_frequency_letter)) {
            --it->second;
            if (it->second == 0) {
                char_frequency_letter.erase(it);
                if (empty(char_frequency_letter)) {
                    break; // All characters for letter have been matched
                }
            }
        }
    }
    return empty(char_frequency_letter);
}

string mag_text = "keyboard shortcuts for vim are great. they will improve productivity";
string let_text = "i ate you";
string false_text = "zero chance";

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
    cout << IsLetterConstructibleFromMagazine(let_text, mag_text) << " | " << IsLetterConstructibleFromMagazine(false_text, mag_text) << endl;
}

