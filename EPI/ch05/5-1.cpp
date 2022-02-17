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

typedef enum { kRed, kWhite, kBlue } Color;

void DutchFlagPartition1(int pivot_index, vector<Color>* A_ptr) {
    vector<Color>& A = *A_ptr;
    Color pivot = A[pivot_index];
    for (int i = 0; i < size(A); ++i) {
        for (int j = i+1; j < size(A); ++j) {
            if (A[j] < pivot) {
                swap(A[i], A[j]); // switch pairs i, j one at a time, breaking out of loop and shifting up
                break;
            }
        }
    }
    for (int i = size(A)-1; i >= 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            if (A[j] > pivot) {
                swap(A[i], A[j]); // repeat but backwards and swap greater elements
                break;
            }
        }
    }
}

// use an index placeholder instead of an extra for loop

void DutchFlagPartition2(int pivot_index, vector<Color>* A_ptr) {
    vector<Color>& A = *A_ptr;
    Color pivot = A[pivot_index];
    int smaller = 0; //tracker index
    for (int i = 0; i < size(A); ++i) {
        if(A[i] < pivot) {
            swap(A[i], A[smaller++]); // smaller index will shift up
        }
    }
    //second pass, different comparison
    int larger = size(A) - 1;
    for (int i = size(A) - 1; i >= 0; --i) {
        if(A[i] > pivot) {
            swap(A[i], A[larger--]);
        }
    }
}

// use multiple ptrs instead of loops

void DutchFlagPartition3(int pivot_index, vector<Color>* A_ptr) {
    vector<Color>& A = *A_ptr;
    Color pivot = A[pivot_index];
    // [--->smaller<--equal-->larger<----]
    int smaller = 0, equal = 0, larger = size(A);
    while (equal < larger) {
        if (A[equal]<pivot) {
            swap(A[smaller++], A[equal++]);
        } else if (A[equal] == pivot) {
            equal++;
        } else {
            swap(A[equal], A[--larger]); // keep equal there because you'll need to re-examine post swap
        }
    }
}

int main() {
    auto A = vector{3, 3, 5, 5, 2, 2, 4};
    EvenOdd(&A);
    for (int i : A) {
        cout << i;
    }
    cout << endl;
    auto flag = vector{kRed, kWhite, kBlue, kRed, kWhite, kBlue, kRed, kWhite, kBlue};
    DutchFlagPartition3(1, &flag);
    for (Color k : flag) {
        cout << k << ", ";
    }
    cout << endl;

}