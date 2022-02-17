#include <iostream>
#include <vector>

using namespace std;
//reorder elements such that even is first before odd

void EvenOdd(vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    int next_even = 0, next_odd = size(A) - 1; // index placeholders
    while (next_even < next_odd) {
        if (A[next_even] % 2 == 0) {
            ++next_even; // continue and do nothing
        } else {
            swap(A[next_even], A[next_odd--]); // move item to odd index, bring other item to front for reprocessing
        }
    }
};

int main() {
    auto A = vector{3, 3, 5, 5, 2, 2, 4};
    EvenOdd(&A);
    for (int i : A) {
        cout << i;
    }
    cout << endl;

}