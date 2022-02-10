#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

TEST_CASE("find find_if find_if_not") {
    vector<string> words { "fiffer", "feffer", "feff" };
    const auto find_result = find(words.cbegin(), words.cend(), "feff");
    REQUIRE(*find_result == words.back());

    const auto defends_digital_privacy = [](const auto& word) {
        return string::npos != word.find("eff");
    };
    const auto find_if_result = find_if(words.cbegin(), words.cend(), defends_digital_privacy);
    REQUIRE(*find_if_result == "feffer");
    const auto find_if_not_result = find_if_not(words.cbegin(), words.cend(), defends_digital_privacy);
    REQUIRE(*find_if_not_result == words.front());
}

TEST_CASE("find_end") {
    vector<string> words1{ "Goat", "girl", "googoo", "goggles" };
    vector<string> words2 { "girl", "googoo" };
    const auto find_end_result1 = find_end(words1.cbegin(), words1.cend(), words2.cbegin(), words2.cend());
    REQUIRE(*find_end_result1 == words1[1]);

    //find subsequence with length 4, then 6
    const auto has_length = [](const auto& word, const auto& len) { return word.length() == len;};
    vector<size_t> sizes{ 4, 6 };
    const auto find_end_result2 = find_end(words1.cbegin(), words1.cend(),
                                            sizes.cbegin(), sizes.cend(), has_length);
    REQUIRE(*find_end_result2 == words1[1]);
}

TEST_CASE("adjacent_find") {
    vector<string> words{ "Icabod", "is", "itchy" };
    const auto first_letters_match = [](const auto& word1, const auto& word2) {
        if (word1.empty() || word2.empty()) return false;
        return word1.front() == word2.front();
    };
    const auto adjacent_find_result = adjacent_find(words.cbegin(), words.cend(), first_letters_match);
    REQUIRE(*adjacent_find_result == words[1]);
}

TEST_CASE("count") {
    vector<string> words{ "jelly", "jar", "and", "jam" };
    const auto n_ands = count(words.cbegin(), words.cend(), "and");
    REQUIRE(n_ands == 1);
    const auto contains_a = [](const auto& word) {
        return word.find('a') != string::npos;
    };
    const auto count_if_result = count_if(words.cbegin(), words.cend(), contains_a);
    REQUIRE(count_if_result == 3);
}

TEST_CASE("mismatch") {
    vector<string> words1{ "Kitten", "Kangaroo", "Kick" };
    vector<string> words2{ "Kitten", "bandicoot", "roundhouse" };
    const auto mismatch_result1 = mismatch(words1.cbegin(), words1.cend(), words2.cbegin());
    REQUIRE(*mismatch_result1.first == "Kangaroo");
    REQUIRE(*mismatch_result1.second == "bandicoot");

    const auto second_letter_matches = [](const auto& word1, const auto& word2) {
        if (word1.size() < 2 || word2.size() < 2) return false;
        return word1[1] == word2[1];
    };
    const auto mismatch_result2 = mismatch(words1.cbegin(), words1.cend(), words2.cbegin(), second_letter_matches);
    REQUIRE(*mismatch_result2.first == "Kick");
    REQUIRE(*mismatch_result2.second == "roundhouse");
}

TEST_CASE("search") {
    vector<string> words1 { "Nine", "new", "neckties", "and", "a", "nightshirt" };
    vector<string> words2 { "and", "a", "nightshirt" };
    const auto search_result_1 = search(words1.cbegin(), words1.cend(), words2.cbegin(), words2.cend());
    REQUIRE(*search_result_1 == "and");

    vector<string> words3{ "and", "a", "nightpant" };
    const auto search_result_2 = search(words1.cbegin(), words1.cend(), words3.cbegin(), words3.cend());
    REQUIRE(search_result_2 == words1.cend());
}