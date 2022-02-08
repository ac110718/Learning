#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <deque>
#include <iterator>
#include <forward_list>
#include <list>
#include <vector>

TEST_CASE("Insert iterators convert writes into container insertions.") {
    std::deque<int> dq;
    auto back_instr = std::back_inserter(dq);
    *back_instr = 2;
    ++back_instr;
    *back_instr = 4;
    ++back_instr;

    auto front_instr = std::front_inserter(dq);
    *front_instr = 1;
    ++front_instr;

    auto instr = std::inserter(dq, dq.begin()+2);
    *instr = 3;
    instr++;

    REQUIRE(dq[0] == 1);
    REQUIRE(dq[1] == 2);
    REQUIRE(dq[2] == 3);
    REQUIRE(dq[3] == 4);
}

TEST_CASE("std::forward_list's begin and end provide forward iterators") {
    const std::forward_list<int> easy_as{ 1, 2, 3 };
    auto itr1 = easy_as.begin();
    auto itr2{ itr1 };
    int double_sum{};
    while(itr1 != easy_as.end()) {
        double_sum += *(itr1++);
    }
    //loop again from second iterator still pointing at beg()
    while(itr2 != easy_as.end()) {
        double_sum += *(itr2++);
    }
    REQUIRE(double_sum == 12);
}

TEST_CASE("std::list begin and end provide bidirectional iterators") {
    const std::list<int> easy_as{ 1, 2, 3 };
    auto itr = easy_as.begin();
    REQUIRE(*itr == 1);
    itr++;
    REQUIRE(*itr == 2);
    itr--;
    REQUIRE(*itr == 1);
    REQUIRE(itr == easy_as.cbegin());
}

TEST_CASE("std::vector begin and end provide random-access iterators") {
    const std::vector<int> easy_as{ 1, 2, 3 };
    auto itr = easy_as.begin();
    REQUIRE( itr[0] == 1);
    itr++;
    REQUIRE(*(easy_as.cbegin() + 2) == 3);
    REQUIRE(easy_as.cend() - itr == 2);
}