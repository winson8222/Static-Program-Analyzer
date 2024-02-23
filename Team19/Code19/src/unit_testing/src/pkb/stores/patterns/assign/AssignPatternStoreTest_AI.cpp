#include "catch.hpp"

#include "pkb/stores/patterns/assign/AssignPatternStore.h"

TEST_CASE("pkb/stores/patterns/assign/AssignPatternStore") {
    std::string x = "x";
    std::string y = "y";
    std::string one = "1";

    SECTION("contains") {
      AssignPatternStore assignPatternStore;
      assignPatternStore.addAssignPattern(1, "x", "1");
      REQUIRE(assignPatternStore.contains(1));
      REQUIRE_FALSE(assignPatternStore.contains(2));
    }

    SECTION("addAssignPattern") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "1");
        REQUIRE(assignPatternStore.contains(1));
        REQUIRE_FALSE(assignPatternStore.contains(2));
    }

    SECTION("clear: Non-Empty Store") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "1");
        assignPatternStore.addAssignPattern(2, "y", "2");
        assignPatternStore.clear();
        REQUIRE(assignPatternStore.getAllPatterns().empty());
    }

    SECTION("getPattern: Pattern Exists") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "1");
        REQUIRE(assignPatternStore.getPattern(1).first == "x");
        REQUIRE(assignPatternStore.getPattern(1).second == "1");
    }

    SECTION("getPattern: Pattern Does Not Exist") {
        AssignPatternStore assignPatternStore;
        std::pair<std::string, std::string> p = assignPatternStore.getPattern(1);
        REQUIRE(p.first.empty());
        REQUIRE(p.second.empty());
    }

    SECTION("getAllPatterns") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "1");
        assignPatternStore.addAssignPattern(2, "y", "2");
        auto expected = std::unordered_map<int, std::pair<std::string, std::string>>{{1, {"x", "1"}}, {2, {"y", "2"}}};
        REQUIRE(assignPatternStore.getAllPatterns() == expected);
    }

    SECTION("getLHS") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "1");
        REQUIRE(assignPatternStore.getLHS(1) == "x");
    }

    SECTION("getRHS") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "1");
        REQUIRE(assignPatternStore.getRHS(1) == "1");
    }

    SECTION("getStatementNumbersWithLHS") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "1");
        assignPatternStore.addAssignPattern(2, "x", "2");
        auto expected = std::unordered_set<int>{1, 2};
        REQUIRE(assignPatternStore.getStatementNumbersWithLHS("x") == expected);
        expected = std::unordered_set<int>{};
        REQUIRE(assignPatternStore.getStatementNumbersWithLHS("y") == expected);
    }

    SECTION("getStatementNumbersWithRHS") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "1");
        assignPatternStore.addAssignPattern(2, "x", "2");
        auto expected = std::unordered_set<int>{1};
        REQUIRE(assignPatternStore.getStatementNumbersWithRHS("1") == expected);
        expected = std::unordered_set<int>{};
        REQUIRE(assignPatternStore.getStatementNumbersWithRHS("3") == expected);
    }

    SECTION("getStatementNumbersWithPartialRHS") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "123+3");
        assignPatternStore.addAssignPattern(2, "x", "122+3");
        assignPatternStore.addAssignPattern(3, "x", "143+3");
        auto expected = std::unordered_set<int>{1, 3};
        REQUIRE(assignPatternStore.getStatementNumbersWithPartialRHS("3+3") == expected);
    }

    SECTION("getStatementNumbersWithLHSRHS") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "123+3");
        assignPatternStore.addAssignPattern(2, "x", "122+3");
        assignPatternStore.addAssignPattern(3, "x", "143+3");
        assignPatternStore.addAssignPattern(4, "y", "143+3");
        assignPatternStore.addAssignPattern(5, "z", "143+3");
        assignPatternStore.addAssignPattern(6, "x", "123+3");
        auto expected = std::unordered_set<int>{1, 6};
        REQUIRE(assignPatternStore.getStatementNumbersWithLHSRHS("x", "123+3") == expected);
    }

    SECTION("getStatementNumbersWithLHSPartialRHS") {
        AssignPatternStore assignPatternStore;
        assignPatternStore.addAssignPattern(1, "x", "123+3");
        assignPatternStore.addAssignPattern(2, "x", "122+3");
        assignPatternStore.addAssignPattern(3, "x", "143+3");
        assignPatternStore.addAssignPattern(4, "y", "143+3");
        assignPatternStore.addAssignPattern(5, "z", "143+3");
        assignPatternStore.addAssignPattern(6, "x", "523+3");
        auto expected = std::unordered_set<int>{1, 3, 6};
        REQUIRE(assignPatternStore.getStatementNumbersWithLHSPartialRHS("x", "3+3") == expected);
    }
}
