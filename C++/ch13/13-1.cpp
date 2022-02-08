#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <vector>
#include <array>
#include <utility>
#include <deque>
#include <list>
#include <stack>
#include <queue>
#include <bitset>

TEST_CASE("std::vector supports default construction") {
    std::vector<const char*> vec;
    REQUIRE(vec.empty());
}

TEST_CASE("std::vector supports braced initialization") {
    std::vector<int> fib { 1, 1, 2, 3, 5 };
    REQUIRE(fib[4] == 5);
}

TEST_CASE("std::vector supports") {
    SECTION("braced initialization") {
        std::vector<int> five_nine{ 5, 9 };
        REQUIRE(five_nine[0] == 5);
        REQUIRE(five_nine[1] == 9);
    }
    SECTION("fill constructor") {
        std::vector<int> five_nines(5,9);
        REQUIRE(five_nines[0] == 9);
        REQUIRE(five_nines[4] == 9);
    }
}

TEST_CASE("std::vector supports construction from iterators") {
    std::array<int,5> fib_arr{ 1, 1, 2, 3, 5};
    std::vector<int> fib_vec(fib_arr.begin(), fib_arr.end());
    REQUIRE(fib_vec[4] == 5);
    REQUIRE(fib_vec.size() == fib_arr.size());
}

TEST_CASE("std::vector assign replaces existing elements") {
    std::vector<int> message{ 13, 80, 110, 114, 102, 110, 101 };
    REQUIRE(message.size() == 7);
    message.assign({67, 97, 101, 115, 97, 114 });
    REQUIRE(message[5] == 114);
    REQUIRE(message.size() == 6);
}

TEST_CASE("std:: vector insert places new elements") {
    std::vector<int> zeros(3, 0);
    auto third_element = zeros.begin() + 2;
    zeros.insert(third_element, 10);
    REQUIRE(zeros[2] == 10);
    REQUIRE(zeros.size() == 4);
}

TEST_CASE("std::vector push_back places new elements") {
    std::vector<int> zeros(3, 0);
    zeros.push_back(10);
    REQUIRE(zeros[3] == 10);
}

TEST_CASE("std::vector emplace methods forward arguments") {
    std::vector<std::pair<int, int>> factors;
    factors.emplace_back(2, 30);
    factors.emplace_back(3, 20);
    factors.emplace_back(4, 15);
    factors.emplace(factors.begin(), 1, 60);
    REQUIRE(factors[0].first == 1);
    REQUIRE(factors[0].second == 60);
}

TEST_CASE("std::deque supports front insertion") {
    std::deque<char> deckard;
    deckard.push_front('a');
    deckard.push_back('i');
    deckard.push_front('c');
    deckard.push_back('n');
    REQUIRE(deckard[0] == 'c');
    REQUIRE(deckard[1] == 'a');
    REQUIRE(deckard[2] == 'i');
    REQUIRE(deckard[3] == 'n');
}

TEST_CASE("std::list supports front insertion") {
    std::list<int> odds {11, 22, 33, 44, 55};
    odds.remove_if([](int x) { return x % 2 == 0;});
    auto odds_iter = odds.begin();
    REQUIRE(*odds_iter == 11);
    ++odds_iter;
    REQUIRE(*odds_iter == 33);
    odds_iter++;
    REQUIRE(*odds_iter == 55);
    odds_iter++;
    // REQUIRE(*odds_iter == odds.end());
}

TEST_CASE("std::stack supports push/pop/top operations") {
    std::vector<int> vec { 1, 3 };
    std::stack<int, decltype(vec)> easy_as(vec); // implementation using vector
    REQUIRE(easy_as.top() == 3);
    easy_as.pop();
    easy_as.push(2);
    REQUIRE(easy_as.top() == 2);
    easy_as.pop();
    REQUIRE(easy_as.top() == 1);
    easy_as.pop();
    REQUIRE(easy_as.empty());
}

TEST_CASE("std::queue supports push/pop/front/back") {
    std::deque<int> deq{ 1, 2 };
    std::queue<int> easy_as(deq);
    REQUIRE(easy_as.front() == 1);
    REQUIRE(easy_as.back() == 2);
    easy_as.pop();
    easy_as.push(3);
    REQUIRE(easy_as.front() == 2);
    REQUIRE(easy_as.back() == 3);
    easy_as.pop();
    REQUIRE(easy_as.front() == 3);
    easy_as.pop();
    REQUIRE(easy_as.empty());
}

TEST_CASE("std::priority_queue supports push/pop") {
    std::priority_queue<double> prique;
    prique.push(1.0);
    prique.push(2.0);
    prique.push(1.5);
    REQUIRE(prique.top() == Approx(2.0));
    prique.pop();
    prique.push(1.0);
    REQUIRE(prique.top() == Approx(1.5));
    prique.pop();
    REQUIRE(prique.top() == Approx(1.0));
    prique.pop();
    REQUIRE(prique.top() == Approx(1.0));
    prique.pop();
    REQUIRE(prique.empty());
}

TEST_CASE("std::bitset supports integrer initialization") {
    std::bitset<4> bs(0b1010);
    REQUIRE_FALSE(bs[0]);
    REQUIRE(bs[1]);
    REQUIRE_FALSE(bs[2]);
    REQUIRE(bs[3]);
}