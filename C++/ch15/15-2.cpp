#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <string>

TEST_CASE("std::string supports appending with") {
    std::string word("butt");
    SECTION("push_back") {
        word.push_back('e');
        REQUIRE(word == "butte");
    }
    SECTION("operator+=") {
        word += "erfinger";
        REQUIRE(word == "butterfinger");
    }
    SECTION("append char") {
        word.append(1, 's');
        REQUIRE(word == "butts");
    }
    SECTION("append (hald-open range)") {
        std::string other("onomatopoeia");
        word.append(other.begin(), other.begin()+2);
        REQUIRE(word == "button");
    }
}

TEST_CASE("std::string supports removal with") {
    std::string word("therein");
    SECTION("pop_back") {
        word.pop_back();
        word.pop_back();
        REQUIRE(word == "there");
    }
    SECTION("clear") {
        word.clear();
        REQUIRE(word.empty());
    }
    SECTION("erase using half-open range") {
        word.erase(word.begin(), word.begin()+3);
        REQUIRE(word == "rein");
    }
    SECTION("erase using an index and length") {
        word.erase(5, 2);
        REQUIRE(word == "there");
    }
}

TEST_CASE("std::string replace works with") {
    std::string word("substitution");
    SECTION("a range and a char*") {
        word.replace(word.begin()+9, word.end(),"e");
        REQUIRE(word == "substitute");
    }
    SECTION("two ranges") {
        std::string other("innuendo");
        word.replace(word.begin(), word.begin()+3, other.begin(), other.begin()+2);
        REQUIRE(word == "institution"); // "sub" for "in"
    }
    SECTION("an index/length and a string") {
        std::string other("vers");
        word.replace(3, 6, other);
        REQUIRE(word == "subversion"); // sub[stitut]->[vers]ion replace 6 chars with 'vers'
    }
}

TEST_CASE("std::string substr with") {
    std::string word("hobbits");
    SECTION("no arguments copies the string") {
        REQUIRE(word.substr() == "hobbits");
    }
    SECTION("position takes the remainder") {
        REQUIRE(word.substr(3) == "bits");
    }
    SECTION("position/index takes a subtring") {
        REQUIRE(word.substr(3,3) == "bit");
    }
}