#include <iostream>
#include <vector>
using namespace std;

// avoid overflow by replacing M = (L + U) with M = L + (U - L) / 2
int bsearch(int t, const vector<int>& A) {
    int L = 0, U = size(A) - 1;
    while (L <= U) {
        int M = L + (U - L) / 2;
        if (A[M] < t) {
            L = M + 1;
        } else if (A[M] == t) {
            return M;
        } else {
            U = M - 1;
        }
    }
    return -1;
}

int main() {
    auto search = vector<int>{1, 3, 5, 6, 7, 8, 9};
    cout << bsearch(6, search) << endl;
    cout << bsearch(9, search) << endl;
}