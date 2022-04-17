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

int main() {
    auto search = vector<int>{1, 3, 5, 6, 7, 8, 9};
    cout << bsearch(6, search) << endl;
    cout << bsearch(9, search) << endl;
    Student n = {"k", 4.05};
    vector<Student> student_vec {Student{"anne", 4.1}, Student{"kim", 4.1}, n, Student{"joe", 4.0}, Student{"jim", 3.9}, Student{"bob", 3.9}, Student{"bill", 3.8}};
    cout << boolalpha << SearchStudent(student_vec, n, CompGPA) << endl;
    vector<int> sorted_array = {-14, -10, 2, 108, 108, 243, 285, 285, 285, 401};
    cout << SearchFirstOfK(sorted_array, 285) << ", " << SearchFirstOfK(sorted_array, 108) << endl;
}