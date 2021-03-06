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

struct Student {
    string name;
    double grade_point_average;
};

const static function<bool(const Student&, const Student&)> CompGPA = 
    [](const Student& a, const Student& b) {
        if (a.grade_point_average != b.grade_point_average) {
            return a.grade_point_average > b.grade_point_average;
        }
        return a.name < b.name;
    };

bool SearchStudent(
    const vector<Student>& students, const Student& target,
    const function<bool(const Student&, const Student&)>& comp_GPA) {
        return binary_search(begin(students), end(students), target, comp_GPA);
}

// find first occurence of k.. 
// what is all elements are k? don't stop binary search.. 
// keep going until pointers meet in middle but don't bother searching to the right (can't be first occurence)

int SearchFirstOfK(const vector<int>& A, int k) {
    int left = 0, right = size(A) - 1, result = -1;
    while (left <= right) {
        if (int mid = left + ((right - left) / 2); A[mid] > k) {
            right = mid - 1;
        } else if (A[mid] == k) {
            result = mid;
            right = mid - 1; // keep trying for a lower entry
            // keep pushing while loop until left = right, no early exits
        } else {
            left = mid + 1;
        }
    }
    return result;
}

// search sorted array for entry equal to its index

int SearchEntryEqualToItsIndex (const vector<int>& A) {
    int left = 0, right = size(A) - 1;
    while (left <= right) {
        int mid = left + ((right - left) / 2);
        if (int difference = A[mid] - mid; difference == 0) {
            return mid;
        } else if (difference > 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}

// search the min of a cyclically sorted array
// if A[m] > A[size], the kink (or min) must be in right half. 
// if A[m] < A[size], the kink (or min) must be in left half

int SearchSmallest(const vector<int>& A) {
    int left = 0, right = size(A) - 1;
    while (left < right) {
        if (int mid = left + ((right - left) / 2); A[mid] > A[right]) {
            left = mid + 1; // search right half, where kink is
        } else {
            right = mid; // search left half, where kink is. Right half is continuously increasing range.
        }
    }
    return left;
}

int SquareRoot(int k) {
    int left = 0, right = k;
    while (left <= right) {
        cout << "left: " << left << " | " << "right: " << right << endl;
        long long mid = left + ((right - left) / 2);
        if (long long mid_squared = mid * mid; mid_squared <= k) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    cout << "answer: " << left - 1 << endl;
    return left - 1;
}

// find floating point square root

typedef enum { kSmaller, kEqual, kLarger } Ordering;

Ordering Compare(double a, double b) {
    double diff = (a - b) / max(abs(a), abs(b));
    return diff < -numeric_limits<double>::epsilon() ? kSmaller :
        diff > numeric_limits<double>::epsilon() ? kLarger : kEqual;
}

double SquareRoot(double x) {
    double left, right;
    if (x < 1.0) {
        left = x, right = 1.0;
    } else {
        left = 1.0, right = x;
    }

    while (Compare(left, right) != kEqual) {
        double mid = left + 0.5 * (right - left);
        if (double mid_squared = mid * mid; Compare(mid_squared, x) == kLarger) {
            right = mid;
        } else {
            left = mid;
        }
        cout << "left : " << left << " | " << "right : " << right << endl;
    }
    cout << "answer : " << left;
    return left;
}


int main() {
    auto search = vector<int>{1, 3, 5, 6, 7, 8, 9};
    cout << bsearch(6, search) << endl;
    cout << bsearch(9, search) << endl;
    Student n = {"k", 4.05};
    vector<Student> student_vec {Student{"anne", 4.1}, Student{"kim", 4.1}, n, Student{"joe", 4.0}, Student{"jim", 3.9}, Student{"bob", 3.9}, Student{"bill", 3.8}};
    cout << boolalpha << SearchStudent(student_vec, n, CompGPA) << endl;
    vector<int> sorted_array = {-14, -10, 2, 108, 108, 243, 285, 285, 285, 401};
    cout << SearchFirstOfK(sorted_array, 285) << ", " << SearchFirstOfK(sorted_array, 108) << endl;
    vector<int> sorted_array_1 = {-2, 0, 2, 3, 6, 7, 9};
    cout << SearchEntryEqualToItsIndex(sorted_array_1) << endl;
    vector<int> sorted_array_cyclical = {378, 478, 550, 631, 103, 203, 220, 234, 279, 368};
    cout << SearchSmallest(sorted_array_cyclical) << endl;
    SquareRoot(145);
    SquareRoot(145.0);
}