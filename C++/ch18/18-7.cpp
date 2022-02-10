#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>
#include <array>

using namespace std;

TEST_CASE("sort") {
    string goat_grass{ "spoilage" };
    sort(goat_grass.begin(), goat_grass.end());
    REQUIRE(goat_grass == "aegilops");
}

enum class CharCategory {
    Ascender,
    Normal,
    Descender
};

CharCategory categorize(char x) {
    switch (x) {
        case 'g':
        case 'j':
        case 'p':
        case 'q':
        case 'y':
            return CharCategory::Descender;
        case 'b':
        case 'd':
        case 'f':
        case 'h':
        case 'k':
        case 'l':
        case 't':
            return CharCategory::Ascender;
    }
    return CharCategory::Normal;
}

bool ascension_compare(char x, char y) {
    return categorize(x) < categorize(y);
}

TEST_CASE("stable_sort") {
    string word{ "outgrin" };
    stable_sort(word.begin(), word.end(), ascension_compare);
    REQUIRE(word == "touring");
}

// binary search

TEST_CASE("lower_bound") {
    vector<int> numbers{ 2, 4, 5, 6, 6, 9 };
    const auto result = lower_bound(numbers.begin(), numbers.end(), 5);
    REQUIRE(result == numbers.begin() + 2);
}

TEST_CASE("upper_bound") {
    vector<int> numbers { 2, 4, 5, 6, 6, 9 };
    const auto result = upper_bound(numbers.begin(), numbers.end(), 5);
    REQUIRE(result == numbers.begin() + 3);
}

TEST_CASE("equal_range") {
    vector<int> numbers{ 2, 4, 5, 6, 6, 9 };
    const auto[rbeg, rend] = equal_range(numbers.begin(), numbers.end(), 6);
    REQUIRE(rbeg == numbers.begin() + 3);
    REQUIRE(rend == numbers.begin() + 5);
}

TEST_CASE("binary_search") {
    vector<int> numbers {2, 4, 5, 6, 6, 9};
    REQUIRE(binary_search(numbers.begin(), numbers.end(), 6));
    REQUIRE_FALSE(binary_search(numbers.begin(), numbers.end(), 7));
}

TEST_CASE("is_partitioned") {
    auto is_odd = [](auto x) { return x % 2 == 1; };
    vector<int> numbers1 { 9, 5, 9, 6, 4, 2 };
    REQUIRE(is_partitioned(numbers1.begin(), numbers1.end(), is_odd));
    vector<int> numbers2 { 9, 4, 9, 6, 4, 2 };
    REQUIRE_FALSE(is_partitioned(numbers2.begin(), numbers2.end(), is_odd));
}

TEST_CASE("partition") {
    auto is_odd = [](auto x) { return x % 2 == 1; };
    vector<int> numbers{ 1, 2, 3, 4, 5};
    const auto partition_point = partition(numbers.begin(), numbers.end(), is_odd);
    REQUIRE(is_partitioned(numbers.begin(), numbers.end(), is_odd));
    REQUIRE(partition_point == numbers.begin() + 3);
}

TEST_CASE("partition_copy") {
    auto is_odd = [](auto x) { return x % 2 == 1; };
    vector<int> numbers{ 1, 2, 3, 4, 5 }, odds, evens;
    partition_copy(numbers.begin(), numbers.end(), back_inserter(odds), back_inserter(evens), is_odd);
    REQUIRE(all_of(odds.begin(), odds.end(), is_odd));
    REQUIRE(none_of(evens.begin(), evens.end(), is_odd));
}

TEST_CASE("merge") {
    vector<int> numbers1 { 1, 4, 5 }, numbers2 { 2, 3, 3, 6 }, result;
    merge(numbers1.begin(), numbers1.end(),
          numbers2.begin(), numbers2.end(),
          back_inserter(result));
    REQUIRE(result == vector<int>{ 1, 2, 3, 3, 4, 5, 6 });
}

TEST_CASE("max and min") {
    auto length_compare = [](const auto& x1, const auto& x2) {
        return x1.length() < x2.length();
    };
    string undisc="undiscriminativeness", vermin="vermin";
        REQUIRE(min(undisc, vermin, length_compare) == "vermin");
    string maxim="maxim", ultra="ultramaximal";
        REQUIRE(max(maxim, ultra, length_compare) == "ultramaximal");
    string mini="minimaxes", maxi="maximin";
        const auto result = minmax(mini, maxi, length_compare);
        REQUIRE(result.first == maxi);
        REQUIRE(result.second == mini);
}

TEST_CASE("min and max element") {
    auto length_compare = [](const auto& x1, const auto& x2) {
        return x1.length() < x2.length();
    };

    vector<string> words{ "civic", "deed", "kayak", "malayalam" };

    REQUIRE(*min_element(words.begin(), words.end(), length_compare) == "deed");
    REQUIRE(*max_element(words.begin(), words.end(), length_compare) == "malayalam");

    const auto result = minmax_element(words.begin(), words.end(), length_compare);
    REQUIRE(*result.first == "deed");
    REQUIRE(*result.second == "malayalam");
}

TEST_CASE("clamp") {
    REQUIRE(clamp(9000,0,100) == 100);
    REQUIRE(clamp(-123, 0, 100) == 0);
    REQUIRE(clamp(3.14, 0., 100.) == Approx(3.14)); //. needed for 0 and 100 for type match
}

//fill sequence will incremental values
TEST_CASE("iota") {
    array<int, 3> easy_as;
    iota(easy_as.begin(), easy_as.end(), 1);
    REQUIRE(easy_as == array<int, 3>{ 1, 2, 3 });
}

// always sequential processing
TEST_CASE("accumulate") {
    vector<int> nums { 1, 2, 3 };
    // start with -1.. default method is plus
    const auto result1 = accumulate(nums.begin(), nums.end(), -1);
    REQUIRE(result1 == 5);
    const auto result2 = accumulate(nums.begin(), nums.end(), 2, multiplies<>());
    REQUIRE(result2 == 12);
}

// same as accumulate but can be executed out of order

TEST_CASE("reduce") {
    vector<int> nums{ 1, 2, 3 };
    const auto result1 = reduce(nums.begin(), nums.end(), -1);
    REQUIRE(result1 == 5);
    const auto result2 = reduce(nums.begin(), nums.end(), 2, multiplies<>());
    REQUIRE(result2 == 12);
}

TEST_CASE("adjacent_difference") {
    vector<int> fib { 1, 1, 2, 3, 5, 8 }, fib_diff;
    adjacent_difference(fib.begin(), fib.end(), back_inserter(fib_diff));
    REQUIRE(fib_diff == vector<int>{ 1, 0, 1, 1, 2, 3 });
}