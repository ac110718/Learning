#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

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

// Find Kth largest element
// Brute Force sorting is wasteful as you only want kth largest element
// So is using a heap, as you'd find k, k-1, k-2.. etc largest elements
// Partitioning is most efficient method

// Keep partitioning at random points to find k elements greater than index
// On average, you should be eliminating half the points on each search
// if you overshoot.. use "binary search" to partition again but only with either left half or right half


// need to input expact left and right boundaries as parent function will be doing subsearch
template <typename Compare>
int PartitionAroundPivot(int left, int right, int pivot_idx, Compare comp, vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    int pivot_value = A[pivot_idx];
    int new_pivot_idx = left; // track partition boundary with index pointer
    swap(A[pivot_idx], A[right]); // put partition element off to side
    for (int i = left; i < right; ++i) {
        if (comp(A[i], pivot_value)) {
            swap(A[i], A[new_pivot_idx++]); // bring A[i] to left partition and bump up index pointer
        } // in the end, all elements left of index pointer will be smaller
    } // bring the pivot element back to correct positioning (had been moved off to side)
    swap(A[right], A[new_pivot_idx]);
    return new_pivot_idx;
}

template<typename Compare>
int FindKth(int k, Compare comp, vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    int left = 0, right = size(A) - 1;
    default_random_engine gen((random_device())());
    while (left <= right) {
        // find random partitioning starting point (on average elements half bigger, half smaller in long run), within left right bounds
        int pivot_idx = uniform_int_distribution<int>{left, right}(gen);
        cout << "left : " << left << " | right : " << right << " | part_element: " << A[pivot_idx] << endl;
        if (int new_pivot_idx = PartitionAroundPivot(left, right, pivot_idx, comp, &A); new_pivot_idx == k - 1) {
            cout << "FOUND : " << A[new_pivot_idx] << " at index " << new_pivot_idx << endl;
            return A[new_pivot_idx];
        } else if (new_pivot_idx > k - 1) {
            right = new_pivot_idx - 1;
        } else {
            left = new_pivot_idx + 1;
        }
    }
    cout << "Not Found" << endl;
    return -1000000;
}

int FindKthLargest(int k, vector<int>* A_ptr) {
    return FindKth(k, greater<int>(), A_ptr);
}

int main() {
    MatrixSearch(twoD_array, 3);
    MatrixSearch(twoD_array, 11);
    auto result = FindMinMax(min_max_vec);
    cout << "smallest: " << result.smallest << " | largest : " << result.largest << endl;
    FindKthLargest(1, &k_search);
    FindKthLargest(2, &k_search);
    FindKthLargest(3, &k_search);
    FindKthLargest(4, &k_search);
}
