#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <algorithm>
#include <vector>
#include <string>
#include <string_view>

using namespace std;

TEST_CASE("copy") {
    vector<string> words1{ "and", "prosper" };
    vector<string> words2{ "Live", "long" };
    copy(words1.cbegin(), words1.cend(), back_inserter(words2));
    REQUIRE(words2 == vector<string>{ "Live", "long", "and", "prosper" });
}

//will overwrite entries while copying backwards
TEST_CASE("copy_backward") {
    vector<string> words1{"A", "man", "a", "plan", "a", "bran", "muffin" };
    vector<string> words2{"a", "canal", "Panama" };
    const auto result = copy_backward(words2.begin(), words2.end(), words1.end());
    REQUIRE(words1 == vector<string>{"A", "man", "a", "plan", "a", "canal", "Panama"});
}

TEST_CASE("swap_ranges") {
    vector<string> words1{ "The", "king", "is", "dead." };
    vector<string> words2{ "Long", "live", "the", "king." };
    auto temp1 = vector<string>{ words1 };
    auto temp2 = vector<string>{ words2 };
    swap_ranges(words1.begin(), words1.end(), words2.begin());
    REQUIRE(temp1 == words2);
    REQUIRE(temp2 == words1);
}

TEST_CASE("transform") {
    // vector<string> words1{ "farewell", "hello", "farewell", "hello" };
    // vector<string> result1;
    // auto upper = [](string x) {
    //     boost::algorithm::to_upper(x);
    //     return x;
    // };
    // transform(words1.begin(), words1.end(), back_inserter(result1), upper);
    // REQUIRE(result1 == vector<string>{ "FAREWELL", "HELLO", "FAREWELL", "HELLO"});
    
    vector<string> words2{ "light", "human", "bro", "quantum" };
    vector<string> words3{ "radar", "robot", "pony", "bit" };
    vector<string> result2;
    //first two letters of x, append last three letters of y
    auto portmantize = [](const auto &x, const auto &y) {
        const auto x_letters = min(size_t{ 2 }, x.size());
        string result { x.begin(), x.begin() + x_letters };
        const auto y_letters = min(size_t{ 3 }, y.size());
        result.insert(result.end(), y.end() - y_letters, y.end());
        return result;
    };
    transform(words2.begin(), words2.end(), words3.begin(), back_inserter(result2), portmantize);
    REQUIRE(result2 == vector<string>{ "lidar", "hubot", "brony", "qubit"});
}

TEST_CASE("replace") {
    using namespace std::literals;
    vector<string> words1{ "There", "is", "no", "try" };
    replace(words1.begin(), words1.end(), "try"sv, "spoon"sv);
    REQUIRE(words1 == vector<string>{ "There", "is", "no", "spoon" });

    const vector<string> words2{ "There", "is", "no", "spoon" };
    vector<string> words3{ "There", "is", "no", "spoon" };
    auto has_two_os = [](const auto& x) {
        return count(x.begin(), x.end(), 'o') == 2;
    };
    replace_copy_if(words2.begin(), words2.end(), words3.begin(), has_two_os, "try"sv);
    REQUIRE(words3 == vector<string>{ "There", "is", "no", "try" });
}
