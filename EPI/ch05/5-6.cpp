#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <cmath>

using namespace std;

// track integer members of partial sudoku assignment
// return true if any element had previously already been toggled on
bool HasDuplicate(const vector<vector<int>>& partial_assignment, int start_row, int end_row, int start_col, int end_col) {
    deque<bool> is_present(size(partial_assignment) + 1, false);
    for (int i = start_row; i < end_row; i++) {
        for (int j = start_col; j < end_col; j++) {
            if (partial_assignment[i][j] !=0 && is_present[partial_assignment[i][j]]) {
                return true;
            }
            is_present[partial_assignment[i][j]] = true;
        }
    }
    return false;
}

bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
    // check rows
    for (int i = 0; i < size(partial_assignment); i++) {
        if(HasDuplicate(partial_assignment, i, i+1, 0, size(partial_assignment))) {
            return false;
        }
    }
    // check cols
    for (int j = 0; j < size(partial_assignment); j++) {
        if(HasDuplicate(partial_assignment, 0, size(partial_assignment), j, j+1)) {
            return false;
        }
    }
    // check mini-square
    int region_size = sqrt(size(partial_assignment));
    for (int i = 0; i < region_size; i++) {
        for (int j = 0; j < region_size; j++) {
            if (HasDuplicate(partial_assignment, region_size * i, region_size * (i + 1), region_size * j, region_size * (j+1))) {
                return false;
            }
        }
    }
    return true;
}

// Matrix spiral ordering
vector<int> MatrixInSpiralOrder(vector<vector<int>> square_matrix) {
    // navigation array {x, y} shifter
    const array<array<int, 2>, 4> kShift = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
    int dir = 0, x = 0, y = 0;
    vector<int> spiral_ordering;
    for (int i = 0; i < size(square_matrix) * size(square_matrix); i++) {
        spiral_ordering.emplace_back(square_matrix[x][y]);
        // mark where you've been with a 0 so that you don't go there again
        square_matrix[x][y] = 0;
        // get the next coordinate with navigation array
        // dir will be toggle that cycles to the next direction
        int next_x = x + kShift[dir][0], next_y = y + kShift[dir][1];
        // check boundaries or hitting a zero.. 
        // if so, CHANGE DIRECTION AND UPDATE THE NEXT POINTER
        if (next_x < 0 || next_x >= size(square_matrix) || next_y < 0 || next_y >= size(square_matrix) || square_matrix[next_x][next_y] == 0) {
            dir = (dir + 1) % 4;
            next_x = x + kShift[dir][0], next_y = y + kShift[dir][1];
        }
        // move forward
        x = next_x, y = next_y;
    }
    return spiral_ordering;
}

int main() {
    vector<vector<int>> x = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    vector<int> x_spiral = MatrixInSpiralOrder(x);
    for (int elt : x_spiral) {
        cout << elt << ", ";
    }
    cout << endl;
}