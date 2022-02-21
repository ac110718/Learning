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

int main() {
    char s[] = {'a', 'c', 'd', 'b', 'b', 'c', 'a'};
    int x = ReplaceAndRemove(7, s);
    for (auto c : s) {
        cout << c << ", ";
    }
    cout << endl;
}