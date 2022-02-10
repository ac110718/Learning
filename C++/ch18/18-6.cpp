// #define CATCH_CONFIG_MAIN
// #include "../catch.hpp"
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

const string population = "ABCD";
const size_t n_samples{ 1'000'000 };
mt19937_64 urbg;

void sample_length(size_t n) {
    cout << "-- Length " << n << " --\n";
    map<string, size_t> counts;
    for (size_t i{}; i < n_samples; i++) {
        string result;
        //sample something of length n from population and store into result
        sample(population.begin(), population.end(), back_inserter(result), n, urbg);
        counts[result]++;
    }
    for (const auto[sample, n] : counts) {
        const auto percentage = 100 * n / static_cast<double>(n_samples);
        cout << percentage << " '" << sample << "'\n";
    }
}

int main() {
 cout << fixed << setprecision(1);
 sample_length(0);
 sample_length(1);
 sample_length(2);
 sample_length(3);
 sample_length(4);

 // generate random permutations of four chars
 map<string, size_t> samples;
 for (size_t i{}; i < n_samples; i++) {
     string result{ population };
     shuffle(result.begin(), result.end(), urbg);
     samples[result]++;
 }
 for (const auto[sample, n] : samples) {
     const auto percentage = 100 * n / static_cast<double>(n_samples);
     cout << percentage << " '" << sample << "'\n";
 }
}