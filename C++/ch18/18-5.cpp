#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <algorithm>
#include <vector>
#include <string>
#include <string_view>

using namespace std;

TEST_CASE("generate") {
    auto i{ 1 };
    auto pow_of_2 = [&i]() {
        const auto tmp = i;
        i *= 2;
        return tmp;
    };
    vector<int> series1(6);
    generate(series1.begin(), series1.end(), pow_of_2);
    REQUIRE(series1 == vector<int>{ 1, 2, 4, 8, 16, 32});

    vector<int> series2;
    generate_n(back_inserter(series2), 6, pow_of_2);
    // generator will continue preserving state
    REQUIRE(series2 == vector<int>{ 64, 128, 256, 512, 1024, 2048 });
}

TEST_CASE("remove") {
    auto is_vowel = [](char x) {
        const static string vowels{ "aeiouAEIOU" };
        return vowels.find(x) != string::npos;
    };
    string pilgrim = "Among the things Billy Pilgrim could not change "
                     "were the past, the present, and the future.";
    const auto new_end = remove_if(pilgrim.begin(), pilgrim.end(), is_vowel);
    //chars will be left over from the remove operation
    REQUIRE(pilgrim == "mng th thngs Blly Plgrm cld nt chng wr th pst, "
                       "th prsnt, nd th ftr.present, and the future.");
    //erase-remove idiom
    pilgrim.erase(new_end, pilgrim.end());
    REQUIRE(pilgrim == "mng th thngs Blly Plgrm cld nt chng wr th pst, "
                       "th prsnt, nd th ftr.");
}

TEST_CASE("unique") {
    string without_walls = "Wallless";
    const auto new_end = unique(without_walls.begin(), without_walls.end());
    without_walls.erase(new_end, without_walls.end());
    REQUIRE(without_walls == "Wales");
}

TEST_CASE("reverse") {
    string stinky = "diaper";
    reverse(stinky.begin(), stinky.end());
    REQUIRE(stinky == "repaid");
}
