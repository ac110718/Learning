#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// search a sorted 2D array
// if x < A[m][n], eliminate any element bigger than m+1 row, or n+1 column
// search along the diagonal first to eliminate search space

bool MatrixSearch(const vector<vector<int>>& A, int x) {
    int row = 0, col = size(A[0]) - 1; // optimal to start from top right and travel down because you're either eliminating either a row or a column
    while (row < size(A) && col >= 0) {
        cout << "row : " << row << " | " << "col : " << col << endl;
        if (A[row][col] == x) {
            cout << "FOUND" << endl;
            return true;
        } else if (A[row][col] < x) {
            ++row;
        } else {
            --col;
        }
    }
    cout << "NOT FOUND" << endl;
    return false;
}

vector<vector<int>> twoD_array = {{-1,2,4,4,6}, {1,5,5,9,21}, {3,6,6,9,22}, {3,6,8,10,24}, {6,8,9,12,25}, {8,10,12,13,40}};

// Find min and max simultaneously. Keep track of global min and max while streaming

struct MinMax {
    int smallest, largest;
};

MinMax FindMinMax(const vector<int>& A) {
    if (size(A) <= 1) {
        return {A.front(), A.front()};
    }
    int global_min, global_max;
    tie(global_min, global_max) = minmax(A[0], A[1]); // assign min to the smaller of the two elements, and vice versa
    // can skip every 2 elements because local min will be captured within two element window for comparison to global min.
    cout << "min : " << global_min << " | max : " << global_max << endl;
    for (int i = 2; i + 1 < size(A); i += 2) {
        const auto& [local_min, local_max] = minmax(A[i], A[i+1]);
        global_min = min(global_min, local_min);
        global_max = max(global_max, local_max);
        cout << "min : " << global_min << " | max : " << global_max << endl;
    }
    if (size(A) % 2) {
        global_min = min(global_min, A.back());
        global_max = max(global_max, A.back());
    }
    cout << "min : " << global_min << " | max : " << global_max << endl;
    return {global_min, global_max};
}

vector<int> min_max_vec = {3, 2, 5, 1, 2, 4, -1, 2, 2, 6, 6, 9, -10};

int main() {
    MatrixSearch(twoD_array, 3);
    MatrixSearch(twoD_array, 11);
    auto result = FindMinMax(min_max_vec);
    cout << "smallest: " << result.smallest << " | largest : " << result.largest << endl;
}
