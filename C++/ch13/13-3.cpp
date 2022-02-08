#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <map>

TEST_CASE("std::map is an associative array with") {
    std::map<const char*, int> pub_year {
        { "colour_of_magic", 1983 },
        { "the_light_fantastic", 1986 },
    };
    SECTION("operator[]") {
        REQUIRE(pub_year["colour_of_magic"] == 1983);
        pub_year["equal_rites"] = 1987;
        REQUIRE(pub_year["equal_rites"] == 1987);
        //implicit empty entry is zero
        REQUIRE(pub_year["mort"] == 0);
    }
    SECTION("at method") {
        REQUIRE(pub_year.at("colour_of_magic") == 1983);
        //not zero.
        REQUIRE_THROWS_AS(pub_year.at("equal_rites"), std::out_of_range);
    }
}

//use unordered_map when there's no sorted ordering of the keys, similar to unordered_set. Different implementation structure.
TEST_CASE("std::map supports insert") {
    std::map<const char*, int> pub_year;
    pub_year.insert({"colour_of_magic", 1983});
    REQUIRE(pub_year.size() == 1);
    std::pair<const char*, int> tlfp{ "the_light_fantastic", 1986 };
    pub_year.insert(tlfp);
    REQUIRE(pub_year.size() == 2);

    auto [itr, is_new ] = pub_year.insert({"the_light_fantastic", 9999 });
    REQUIRE(itr->first == "the_light_fantastic");
    REQUIRE(itr->second == 1986);
    REQUIRE_FALSE(is_new);
    REQUIRE(pub_year.size() == 2);
    auto [itr2, is_new2] = pub_year.insert_or_assign("the_light_fantastic", 9999);
    REQUIRE(itr2->second == 9999); // will actually update
    REQUIRE_FALSE(is_new); // would have been new if new insert
}
