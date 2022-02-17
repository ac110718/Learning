#include <iostream>
#include <vector>

using namespace std;

vector<int> PlusOne(vector<int> A) {
    ++A.back();
    for (int i = size(A) - 1; i > 0 && A[i] == 10; --i) { // where A[i] == 10...
        A[i] = 0; // place the 0
        ++A[i-1]; // increment prior.. and keep pushing through the for loop in case carry continues
    }
    if (A[0] == 10) {
        A[0] = 1;
        A.emplace_back(0);
    } // only way you could have gotten here is from going 99 to 100, or 999 to 1000 etc.. and the for loop would have already converted to 0
    // shift left by one digit with leading 1
    return A;
};

vector<int> Multiply(vector<int> num1, vector<int> num2) {
    const int sign = (num1.front() < 0) ^ (num2.front() < 0) ? -1 : 1;
    num1.front() = abs(num1.front()), num2.front() = abs(num2.front());
    vector<int> result(size(num1)+size(num2), 0);

    for (int i = size(num1) - 1; i >=0; --i) {
        for (int j = size(num2) - 1; j >= 0; --j) {
            result[i+j+1] += num1[i] * num2[j];
            result[i+j] += result[i+j+1] / 10; // place two-digit result of the individual multiplication
            result[i+j+1] %= 10;
        }
    }

    result = {
        find_if_not(begin(result), end(result), [](int a) { return a == 0;}), // remove leading zeros
        end(result)
    };
    if (empty(result)) return {0};
    result.front() *= sign;
    return result;
}

int main() {
    auto A = vector{9,9,9};
    auto B = PlusOne(A);
    for (int i : B) {
        cout << i << ", ";
    }
    cout << endl;
    auto X = vector{1, 9, 3, 7, 0, 7, 7, 2, 1};
    auto Y = vector{-7, 6, 1, 8, 3, 8, 2, 5, 7, 2, 8, 7};
    auto Z = Multiply(X, Y);
    for (int i : Z) {
        cout << i << ", ";
    }
}

