#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

TEST_CASE("for_each") {
    vector<string> words { "David", "Donald", "Doo" };
    size_t number_of_Ds{};
    const auto count_Ds = [&number_of_Ds](const auto& word) {
        if (word.empty()) return;
        if (word[0] == 'D') ++number_of_Ds;
    };
    for_each(words.cbegin(), words.cend(), count_Ds);
    REQUIRE(3 == number_of_Ds);
}

//Stop partially
TEST_CASE("for_each_n") {
    vector<string> words{ "ear", "egg", "elephant" };
    size_t characters{};
    const auto count_characters = [&characters](const auto& word) {
        characters += word.size();
    };
    for_each_n(words.cbegin(), 2, count_characters);
    REQUIRE(6 == characters);
}