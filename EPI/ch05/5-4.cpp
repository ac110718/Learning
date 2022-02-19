#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;


//better than using brute force test of all ints up to sqrt(n) to see if prime factor
vector<int> GeneratePrimes(int n) {
    vector<int> primes;
    deque<bool> is_prime(n+1, true); // table that stores whether or not is prime
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p <= n; p++) {
        if (is_prime[p]) {
            primes.emplace_back(p);
            for (int i = p*2 ; i <= n; i += p) { // set all forward factors to false.. but beginning with 2p, 3p, 4p etc
                is_prime[i] = false; // won't be checked going forward
            }
        }
    }
    return primes;
};

// two vectors.. ordering.. and elements.. apply permutation
void ApplyPermutation(vector<int> perm, vector<char>* A_ptr) {
    vector<char>& A = *A_ptr;
    for (int i = 0; i < size(A); i++) {
        while (perm[i] != i) { // keep apply swaps until ordering vector is naturally sorted. Execute through the full cycle
            swap(A[i], A[perm[i]]); // swap the elements
            swap(perm[i], perm[perm[i]]); // track the ordering of the positioning
        }
    }
}


// next permutation is lowest "incremental" swap possible
// find the "kink".. and then swap the element right after this kink with the smallest item in prior list that is still "greater" than the swapped element
// resort the remainder to minimize the suffix and "keep it as low" as possible

vector<int> NextPermutation(vector<int> perm) {
    auto inversion_point = is_sorted_until(rbegin(perm), rend(perm));
    if (inversion_point == rend(perm)) {
        return {}; // very last permutation if completely sorted
    }
    //return first element in range greater than val.. i.e. the deref inversion_point in the prefix
    auto least_upper_bound = upper_bound(rbegin(perm), inversion_point, *inversion_point);
    // next best you can do at the inversion point that is still an increment
    iter_swap(inversion_point, least_upper_bound);
    // resort remainder to minimize the suffix
    reverse(rbegin(perm), inversion_point);
    return perm;
}

int main() {

    auto p = GeneratePrimes(200);
    for (int i : p) {
        cout << i << ", ";
    }
    cout << endl;

    auto x = vector{'c', 'b', 'a', 'd'};
    auto o = vector{1, 0, 2, 3};
    ApplyPermutation(o, &x);
    for (auto n : x) {
        cout << n << ", ";
    }
    cout << endl;

    auto a = vector{6, 2, 1, 5, 4, 3, 0};
    auto b = NextPermutation(a);
    for (auto i : b) {
        cout << i << ", ";
    }
    cout << endl;

}