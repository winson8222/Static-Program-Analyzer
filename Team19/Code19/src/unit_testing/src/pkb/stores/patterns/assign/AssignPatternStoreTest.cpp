#include "catch.hpp"
#include "iostream"
#include "pkb/stores/patterns/assign/AssignPatternStore.h"

TEST_CASE("pkb/stores/patterns/assign/AssignPatternStore") {
    std::string x = "x";
    std::string y = "y";
    std::string one = "1";
    SECTION("addAssignPattern") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "1");
        REQUIRE(assignPatternStore.contains(1));
        REQUIRE_FALSE(assignPatternStore.contains(2));
    }

    SECTION("clear") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "1");
        assignPatternStore.addAssignPattern(2, "y", "2");
        assignPatternStore.clear();
        REQUIRE(assignPatternStore.getAllPatterns().empty());
    }

    SECTION("Get Pattern") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "1");
        REQUIRE(assignPatternStore.getPattern(1).first == "x");
        REQUIRE(assignPatternStore.getPattern(1).second == "1");
    }

    SECTION("Get LHS") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "1");
        REQUIRE(assignPatternStore.getLHS(1) == "x");
    }

    SECTION("Get RHS") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "1");
        REQUIRE(assignPatternStore.getRHS(1) == "1");
    }


    SECTION("Contains Partial RHS") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "123+3");
        assignPatternStore.addAssignPattern(2, "x", "122+3");
        assignPatternStore.addAssignPattern(3, "x", "143+3");
        auto expected = std::unordered_set<int>{1, 3};
        REQUIRE(assignPatternStore.containsPartialRHS("3+3") == expected);
    }

    SECTION("Contains LHS and RHS") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "123+3");
        assignPatternStore.addAssignPattern(2, "x", "122+3");
        assignPatternStore.addAssignPattern(3, "x", "143+3");
        assignPatternStore.addAssignPattern(4, "y", "143+3");
        assignPatternStore.addAssignPattern(5, "z", "143+3");
        assignPatternStore.addAssignPattern(6, "x", "123+3");
        auto expected = std::unordered_set<int>{1, 6};
        REQUIRE(assignPatternStore.containsLHSRHS("x", "123+3") == expected);
    }

  SECTION("Contains LHS and Partial RHS") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "123+3");
        assignPatternStore.addAssignPattern(2, "x", "122+3");
        assignPatternStore.addAssignPattern(3, "x", "143+3");
        assignPatternStore.addAssignPattern(4, "y", "143+3");
        assignPatternStore.addAssignPattern(5, "z", "143+3");
        assignPatternStore.addAssignPattern(6, "x", "523+3");
        auto expected = std::unordered_set<int>{1, 3, 6};
        REQUIRE(assignPatternStore.containsLHSPartialRHS("x", "3+3") == expected);
    }
}
