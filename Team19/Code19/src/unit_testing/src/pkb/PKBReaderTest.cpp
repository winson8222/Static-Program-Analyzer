#include "catch.hpp"

#include "pkb/PKB.h"
#include "pkb/PKBReader.h"
#include "pkb/PKBWriter.h"

TEST_CASE("pkb/PKBReader.h") {
  std::shared_ptr<PKB> pkb = std::make_shared<PKB>();
  std::shared_ptr<PKBReader> pkbReader = std::make_shared<PKBReader>(pkb);
  std::shared_ptr<PKBWriter> pkbWriter = std::make_shared<PKBWriter>(pkb);
  int one = 1;
  int two = 2;
  int three = 3;
  int four = 4;
  int five = 5;
  int six = 6;
  int seven = 7;
  SECTION("getAllPreFollows: Non-Empty") {
    pkbWriter->insertFollows(one, two);
    pkbWriter->insertFollows(two, three);
    pkbWriter->insertFollows(three, four);
    pkbWriter->insertFollows(four, five);
    pkbWriter->insertFollows(five, six);
    pkbWriter->insertFollows(six, seven);
    auto expected = std::unordered_set<int>{1, 2, 3, 4, 5, 6};
    REQUIRE(pkbReader->getAllPreFollows() == expected);
    pkbWriter->clear();
  }
  SECTION("getAllPreFollows: Empty") {
    auto expected = std::unordered_set<int>{};
    REQUIRE(pkbReader->getAllPreFollows() == expected);
  }
    SECTION("getAllPreFollows: Single") {
        pkbWriter->insertFollows(one, two);
        auto expected = std::unordered_set<int>{1};
        REQUIRE(pkbReader->getAllPreFollows() == expected);
        pkbWriter->clear();
    }
    SECTION("getAllPreFollows: Multiple") {
        pkbWriter->insertFollows(one, two);
        pkbWriter->insertFollows(two, three);
        pkbWriter->insertFollows(three, four);
        auto expected = std::unordered_set<int>{1, 2, 3};
        REQUIRE(pkbReader->getAllPreFollows() == expected);
        pkbWriter->clear();
    }
    SECTION("getAllPostFollows: Non-Empty") {
        pkbWriter->insertFollows(one, two);
        pkbWriter->insertFollows(two, three);
        pkbWriter->insertFollows(three, four);
        pkbWriter->insertFollows(four, five);
        pkbWriter->insertFollows(five, six);
        pkbWriter->insertFollows(six, seven);
        auto expected = std::unordered_set<int>{2, 3, 4, 5, 6, 7};
        REQUIRE(pkbReader->getAllPostFollows() == expected);
        pkbWriter->clear();
    }
    SECTION("getAllPostFollows: Empty") {
        auto expected = std::unordered_set<int>{};
        REQUIRE(pkbReader->getAllPostFollows() == expected);
    }
    SECTION("getAllPostFollows: Single") {
        pkbWriter->insertFollows(one, two);
        auto expected = std::unordered_set<int>{2};
        REQUIRE(pkbReader->getAllPostFollows() == expected);
        pkbWriter->clear();
    }
    SECTION("getAllPreFollowsT: Non-Empty") {
        pkbWriter->insertFollowsT(one, two);
        pkbWriter->insertFollowsT(two, three);
        pkbWriter->insertFollowsT(three, four);
        pkbWriter->insertFollowsT(four, five);
        auto expected = std::unordered_set<int>{1, 2, 3, 4};
        REQUIRE(pkbReader->getAllPreFollowsT() == expected);
        pkbWriter->clear();
    }

    SECTION("getAllPreFollowsT: Empty") {
        auto expected = std::unordered_set<int>{};
        REQUIRE(pkbReader->getAllPreFollowsT() == expected);
    }

    SECTION("getAllPreFollowsT: Single") {
        pkbWriter->insertFollowsT(one, two);
        auto expected = std::unordered_set<int>{1};
        REQUIRE(pkbReader->getAllPreFollowsT() == expected);
        pkbWriter->clear();
    }

    SECTION("getAllPostFollowsT: Non-Empty") {
        pkbWriter->insertFollowsT(one, two);
        pkbWriter->insertFollowsT(two, three);
        pkbWriter->insertFollowsT(three, four);
        pkbWriter->insertFollowsT(four, five);
        auto expected = std::unordered_set<int>{2, 3, 4, 5};
        REQUIRE(pkbReader->getAllPostFollowsT() == expected);
        pkbWriter->clear();
    }

    SECTION("getAllPostFollowsT: Empty") {
        auto expected = std::unordered_set<int>{};
        REQUIRE(pkbReader->getAllPostFollowsT() == expected);
    }

    SECTION("getAllPostFollowsT: Single") {
        pkbWriter->insertFollowsT(one, two);
        auto expected = std::unordered_set<int>{2};
        REQUIRE(pkbReader->getAllPostFollowsT() == expected);
        pkbWriter->clear();
    }

}
