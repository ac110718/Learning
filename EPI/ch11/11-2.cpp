#include <iostream>
#include <vector>

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

int main() {
    MatrixSearch(twoD_array, 3);
    MatrixSearch(twoD_array, 11);
}
