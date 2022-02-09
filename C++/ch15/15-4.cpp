#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <string>
#include <regex>

TEST_CASE("std::basic_regex constructs from a string literal") {
    std::regex zip_regex{ R"((\w{2})?(\d{5})(-\d{4})?)" }; // R" " is for raw string literal that captures backslash.
    REQUIRE(zip_regex.mark_count() == 3); // 3 groupings
}

TEST_CASE("std::sub_match") {
    std::regex regex{ R"((\w{2})?(\d{5})(-\d{4})?)" };
    std::smatch results; // sub match
    SECTION("returns true given matching string") {
        std::string zip("NJ07936-3173");
        const auto matched = std::regex_match(zip, results, regex);
        REQUIRE(matched);
        REQUIRE(results[0] == "NJ07936-3173"); // entire expression first
        REQUIRE(results[1] == "NJ");
        REQUIRE(results[2] == "07936");
        REQUIRE(results[3] == "-3173");
    }
}

//match does COMPLETE match but string can search for embedded strings


TEST_CASE("when only part of a string matches a regex, std::regex_search") {
    std::regex regex{ R"((\w{2})?(\d{5})(-\d{4})?)" };
    std::string sentence("The string NJ07936-3173 is a ZIP code.");
    SECTION("match returns false") {
        REQUIRE_FALSE(std::regex_match(sentence, regex));
    }
    SECTION("search returns true") {
        REQUIRE(std::regex_search(sentence, regex));
    }
}

TEST_CASE("std::regex_replace") {
    std::regex regex{ "[aeoiu]" };
    std::string phrase("queueing and cooeeing in eutopia");
    const auto result = std::regex_replace(phrase, regex, "_");
    REQUIRE(result == "q_____ng _nd c_____ng _n __t_p__");
}