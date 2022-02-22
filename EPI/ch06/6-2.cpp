#include <iostream>

using namespace std;

// replace each 'a' with 2 'd's and delete all 'b'
int ReplaceAndRemove(int size, char s[]) {
    int write_idx = 0, a_count = 0; // write back the ds starting backwards since you don't know where string ends
    for (int i = 0 ; i < size; i++) {
        if (s[i] != 'b') {
            s[write_idx++] = s[i]; // only move write_idx up when NOT b and write s[i]
        }
        if (s[i] == 'a') {
            a_count++; // just remove the bs first, and do ds writing on the backpass
        }
    }

    int cur_idx = write_idx-1; // cur_idx is read index.. and is where write_idx left off
    write_idx = write_idx + a_count - 1; // need to allocate space for a_count more entries for the double d
    const int final_size = write_idx + 1;
    while (cur_idx >= 0) {
        if (s[cur_idx] == 'a') {
            s[write_idx--] = 'd';
            s[write_idx--] = 'd';
        } else {
            s[write_idx--] = s[cur_idx];
        }
        cur_idx--;
    }
    return final_size;
}

bool IsPalindrome(const string& s) {
    int i = 0, j = size(s) - 1;
    while (i < j) {
        while (!isalnum(s[i]) && i < j) {
            ++i; // shift i up to appropriate position to compare
        }
        while (!isalnum(s[j]) && i < j) {
            j--;
        }
        if (tolower(s[i++]) != tolower(s[j--])) {
            return false;
        }
    }
    return true;
}

// reverse just ordering of words.. which can be done by reversing all characters.. and 
// inverting each word back to forward order
void ReverseWords(string* s) {
    // reverse each character
    reverse(begin(*s), end(*s));
    // create offsets to mark beginning and end of individual words
    size_t start = 0, finish;
    while ((finish = s->find(" ", start)) != string::npos) {
        // reverse each word
        reverse(begin(*s) + start, begin(*s) + finish);
        // set start to beginning of next word after the space
        start = finish + 1;
    }
    // reverse the last word uncaught by while loop and last " "
    reverse(begin(*s) + start, end(*s));
}

int main() {
    char s[] = {'a', 'c', 'd', 'b', 'b', 'c', 'a'};
    int x = ReplaceAndRemove(7, s);
    for (auto c : s) {
        cout << c << ", ";
    }
    cout << endl;
    cout << boolalpha << IsPalindrome("A man, a plan, a canal, Panama") << endl;
    cout << boolalpha << IsPalindrome("Nope") << endl;
    string a = "A man, a plan, a canal, Panama";
    ReverseWords(&a);
    cout << a << endl;
}