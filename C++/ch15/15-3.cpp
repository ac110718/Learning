#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <string>

TEST_CASE("std::string find") {
    using namespace std::literals::string_literals;
    std::string word("pizzazz");
    SECTION("locates substrings from strings") {
        REQUIRE(word.find("zz"s) == 2); // pi(z)zazz
    }
    SECTION("accepts a position argument") {
        REQUIRE(word.find("zz"s, 3) == 5); // start search from beginning position 3
    }
    SECTION("locates substrings from char*") {
        REQUIRE(word.find("zaz") == 3);
    }
    SECTION("returns npos when not found") {
        REQUIRE(word.find('x') == std::string::npos);
    }
}

TEST_CASE("std::string rfind") {
    using namespace std::literals::string_literals;
    std::string word("pizzazz");
    SECTION("locates substrings from strings") {
        REQUIRE(word.rfind("zz"s) == 5); // pizza(z)z
    }
    SECTION("accepts a position argument") {
        REQUIRE(word.rfind("zz"s, 3) == 2); // start search from beginning position 3
    }
    SECTION("locates substrings from char*") {
        REQUIRE(word.rfind("zaz") == 3);
    }
    SECTION("returns npos when not found") {
        REQUIRE(word.rfind('x') == std::string::npos);
    }
}

TEST_CASE("std::string find_first_of") {
    using namespace std::literals::string_literals;
    std::string sentence("I am a Zizzer-Zazzer-Zuzz as you can plainly see.");
    SECTION("locates characters within another string") {
        REQUIRE(sentence.find_first_of("Zz"s) == 7); //(Z)izzer
    }
    SECTION("accepts a position argument") {
        REQUIRE(sentence.find_first_of("Zz"s, 11) == 14); //(Z)azzer
    }
    SECTION("returns npos when not found") {
        REQUIRE(sentence.find_first_of("Xx"s) == std::string::npos);
    }
}

TEST_CASE("STL string conversion function") {
    using namespace std::literals::string_literals;
    SECTION("stoi") {
        REQUIRE(std::stoi("8675309"s) == 8675309);
        REQUIRE_THROWS_AS(std::stoi("1099511627776"s), std::out_of_range);
    }
    SECTION("stoul with all valid characters") {
        size_t last_character{};
        const auto result = std::stoul("0xD3C34C3D"s, &last_character, 16); // hexadecimal base
        REQUIRE(result == 0xD3C34C3D);
        REQUIRE(last_character == 10); // length 10 because every character could be parsed
    }
    SECTION("stoul") {
        size_t last_character{};
        const auto result = std::stoul("42six"s, &last_character);
        REQUIRE(result == 42);
        REQUIRE(last_character == 2); //only 2 characters parsed.
    }
    SECTION("stod") {
        REQUIRE(std::stod("2.7182818"s) == Approx(2.7182818));
    }

}