#include <iostream>
#include <vector>
#include <deque>

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

int main() {
    auto p = GeneratePrimes(200);
    for (int i : p) {
        cout << i << ", ";
    }
    cout << endl;
}