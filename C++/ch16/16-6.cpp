#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <string>
#include <sstream>

TEST_CASE("ostringstream produces strings with str") {
    std::ostringstream ss;
    ss << "Testing 123";
    ss << "Testing abd";
    const auto test = ss.str();
    ss.str("I am Groot.");
    const auto groot = ss.str();

    REQUIRE(test == "Testing 123"
                    "Testing abd");
    REQUIRE(groot == "I am Groot.");
}

TEST_CASE("istringstream supports construction from a string") {
    std::string numbers("1 2.23606 2");
    std::istringstream ss{ numbers };
    int a;
    float b, c, d;
    ss >> a;
    ss >> b;
    ss >> c;
    REQUIRE(a == 1);
    REQUIRE(b == Approx(2.23606));
    REQUIRE(c == Approx(2));
    REQUIRE_FALSE(ss >> d);
}