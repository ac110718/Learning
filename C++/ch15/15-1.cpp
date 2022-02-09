#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <string>

TEST_CASE("std::string supports constructing") {
    SECTION("empty strings") {
        std::string cheese;
        REQUIRE(cheese.empty());
    }
    SECTION("repeated characters") {
        std::string roadside_assistance(3, 'A');
        REQUIRE(roadside_assistance == "AAA");
    }
}

TEST_CASE("std::string supports constructing substrings ") {
    auto word = "gobbledygook";
    REQUIRE(std::string(word) == "gobbledygook");
    REQUIRE(std::string(word, 6) == "gobble");
}

TEST_CASE("std::string supports") {
    std::string word("catawampus");
    SECTION("copy constructing") {
        REQUIRE(std::string(word) == "catawampus");
    }
    SECTION("move constructing") {
        REQUIRE (std::string(move(word)) == "catawampus");
    }
}

TEST_CASE("constructing a string with") {
    SECTION("std::string(char*) stops at embedded nulls") {
        std::string str("idioglossia\0ellohay!");
        REQUIRE(str.length() == 11); //stops at the \0
    }
    SECTION("operator\"\"s incorporates embedded nulls") {
        using namespace std::string_literals;
        auto str_lit = "idioglossia\0ellohay!"s;
        REQUIRE(str_lit.length() == 20);
    } // note that string as LENGTH method instead of size()
}

TEST_CASE("string's c_str method makes null-terminated strings") {
    std::string word("horripilation");
    auto as_cstr = word.c_str();
    REQUIRE(as_cstr[0] == 'h');
    REQUIRE(as_cstr[1] == 'o');
    REQUIRE(as_cstr[11] == 'o');
    REQUIRE(as_cstr[12] == 'n');
    REQUIRE(as_cstr[13] == '\0'); // still null terminated.
}