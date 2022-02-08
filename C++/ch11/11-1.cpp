#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <memory>

struct DeadMenOfDunharrow {
    DeadMenOfDunharrow(const char* m="")
        :   message{ m } {
            oaths_to_fulfill++;
    }
    ~DeadMenOfDunharrow() {
        oaths_to_fulfill--;
    }
    const char* message;
    //static member to keep tracker of ptr count
    static int oaths_to_fulfill;
};

int DeadMenOfDunharrow::oaths_to_fulfill{};

TEST_CASE("UniquePtr can be used in move") {
  auto aragorn = std::make_unique<DeadMenOfDunharrow>();
  SECTION("construction") {
      auto son_of_arathorn{ std::move(aragorn) };
      REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
  }
  SECTION("assignment") {
      auto son_of_arathorn = std::make_unique<DeadMenOfDunharrow>();
      REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 2);
      son_of_arathorn = std::move(aragorn);
      REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
  }
}

TEST_CASE("UniquePtr to array supports operator[]") {
    std::unique_ptr<int[]> squares {
        new int[5]{ 1, 4, 9, 16, 25}
    };
    squares[0] =1;
    REQUIRE(squares[0] == 1);
    REQUIRE(squares[1] == 4);
    REQUIRE(squares[2] == 9);
}

using SharedOathBreakers = std::shared_ptr<DeadMenOfDunharrow>;
TEST_CASE("SharedPtr can be used in copy") {
    auto aragorn = std::make_shared<DeadMenOfDunharrow>();
    SECTION("construction") {
        auto son_of_arathorn { aragorn };
        REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1); // pointing to same item
    }
    SECTION("assignment") {
        SharedOathBreakers son_of_arathorn;
        son_of_arathorn = aragorn;
        REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
    }
    SECTION("assignment, and original gets discarded") {
        auto son_of_arathorn = std::make_shared<DeadMenOfDunharrow>();
        REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 2);
        son_of_arathorn = aragorn;
        REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
    }
}

TEST_CASE("WeakPtr lock() creates a shared pointer but otherwise don't directly own") {
    auto message = "The way is shut.";
    SECTION("a shared pointer when tracked object is alive") {
        auto aragorn = std::make_shared<DeadMenOfDunharrow>(message);
        std::weak_ptr<DeadMenOfDunharrow> legolas { aragorn };
        auto sh_ptr = legolas.lock();
        REQUIRE(sh_ptr->message == message);
        REQUIRE(sh_ptr.use_count() == 2);
    }
    SECTION("empty when shared pointer empty") {
        std::weak_ptr<DeadMenOfDunharrow> legolas;
        {
            auto aragorn = std::make_shared<DeadMenOfDunharrow>(message);
            legolas = aragorn;
        } // aragorn destructed because it fell out of scope.
        auto sh_ptr = legolas.lock();
        REQUIRE(nullptr == sh_ptr);
    }
}
