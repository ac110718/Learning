#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <future>
#include <string>

using namespace std;

TEST_CASE("async returns valid future") {
    using namespace literals::string_literals;
    auto the_future = async([] { return "female"s; });
    REQUIRE(the_future.valid());
}

TEST_CASE("async returns the return value of the function object") {
    using namespace literals::string_literals;
    auto the_future = async([] {return "female"s; });
    REQUIRE(the_future.get() == "female");
}

TEST_CASE("wait_for indicates whether a task is ready") {
    using namespace literals::chrono_literals;
    auto sleepy = async(launch::async, [] { this_thread::sleep_for(100ms); });
    const auto not_ready_yet = sleepy.wait_for(25ms);
    REQUIRE(not_ready_yet == future_status::timeout);
    const auto totally_ready = sleepy.wait_for(100ms);
    REQUIRE(totally_ready == future_status::ready);
}