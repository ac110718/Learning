#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

TEST_CASE("all_of") {
    vector<string> words { "Auntie", "Anne's", "alligator" };
    const auto starts_with_a =
        [] (const auto& word) {
            if (word.empty()) return false;
            return word[0] == 'A' || word[0] == 'a';
        };
    REQUIRE (all_of(words.cbegin(), words.cend(), starts_with_a));
    const auto has_length_six = [](const auto& word) { return word.length() == 6; };
    REQUIRE_FALSE(all_of(words.cbegin(), words.cend(), has_length_six));
}

TEST_CASE("any_of") {
    vector<string> words{ "Barber", "baby", "bubbles" };
    const auto contains_bar = [](const auto& word) {
        return word.find("Bar") != string::npos;
    };
    REQUIRE(any_of(words.cbegin(), words.cend(), contains_bar));

    const auto is_empty = [](const auto& word) { return word.empty(); };
    REQUIRE_FALSE(any_of(words.cbegin(), words.cend(), is_empty));
}

TEST_CASE("none_of") {
    vector<string> words{ "Camel", "on", "the", "ceiling" };
    const auto is_hump_day = [](const auto& word) { return word == "hump day";};
    REQUIRE(none_of(words.cbegin(), words.cend(), is_hump_day));
    const auto is_definite_article = [](const auto& word) {
        return word == "the" || word == "ye";
    };
    REQUIRE_FALSE(none_of(words.cbegin(), words.cend(), is_definite_article));
}
