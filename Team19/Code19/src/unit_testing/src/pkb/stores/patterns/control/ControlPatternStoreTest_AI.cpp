#include "catch.hpp"

#include "pkb/stores/patterns/control/ControlPatternStore.h"

TEST_CASE("pkb/stores/patterns/control/ControlPatternStore") {
  std::string x = "x";
  std::string y = "y";
  std::string one = "1";
  SECTION("addControlPattern") {
    ControlPatternStore controlPatternStore;
    controlPatternStore.addControlPattern(1, "x");
    REQUIRE(controlPatternStore.hasStatementNumber(1));
    REQUIRE_FALSE(controlPatternStore.hasStatementNumber(2));
  }

  SECTION("contains") {
    ControlPatternStore controlPatternStore;
    controlPatternStore.addControlPattern(1, "x");
    REQUIRE(controlPatternStore.hasStatementNumber(1));
    REQUIRE_FALSE(controlPatternStore.hasStatementNumber(2));
  }

  SECTION("clear") {
    ControlPatternStore controlPatternStore;
    controlPatternStore.addControlPattern(1, "x");
    controlPatternStore.addControlPattern(2, "y");
    controlPatternStore.clear();
    REQUIRE(controlPatternStore.getAllControlPatterns().empty());
  }

  SECTION("getControlPatternsWithStatementNumber: Singular") {
    ControlPatternStore controlPatternStore;
    controlPatternStore.addControlPattern(1, "x");
    REQUIRE(controlPatternStore.getControlPatternsWithStatementNumber(1) == std::unordered_set<std::string>{"x"});
  }

  SECTION("getControlPatternsWithStatementNumber: Multiple") {
    ControlPatternStore controlPatternStore;
    controlPatternStore.addControlPattern(1, "x");
    controlPatternStore.addControlPattern(1, "y");
    REQUIRE(controlPatternStore.getControlPatternsWithStatementNumber(1) == std::unordered_set<std::string>{"x", "y"});
  }

  SECTION("getControlPatternsWithStatementNumber: Empty") {
    ControlPatternStore controlPatternStore;
    REQUIRE(controlPatternStore.getControlPatternsWithStatementNumber(1).empty());
  }

  SECTION("getAllStatementNumbers") {
    ControlPatternStore controlPatternStore;
    controlPatternStore.addControlPattern(1, "x");
    controlPatternStore.addControlPattern(2, "y");
    auto expected = std::unordered_set<int>{1, 2};
    REQUIRE(controlPatternStore.getAllStatementNumbers() == expected);
  }

  SECTION("getAllControlPatterns") {
    ControlPatternStore controlPatternStore;
    controlPatternStore.addControlPattern(1, "x");
    controlPatternStore.addControlPattern(2, "y");
    auto expected = std::unordered_set<std::string>{"x", "y"};
    REQUIRE(controlPatternStore.getAllControlPatterns() == expected);
  }

  SECTION("getStatementNumbersWithControlPattern") {
    ControlPatternStore controlPatternStore;
    controlPatternStore.addControlPattern(1, "x");
    controlPatternStore.addControlPattern(2, "y");
    controlPatternStore.addControlPattern(3, "x");
    auto expected = std::unordered_set<int>{1, 3};
    REQUIRE(controlPatternStore.getStatementNumbersWithControlPattern("x") == expected);
  }

    SECTION("hasControlPattern") {
        ControlPatternStore controlPatternStore;
        controlPatternStore.addControlPattern(1, "x");
        REQUIRE(controlPatternStore.hasControlPattern("x"));
        REQUIRE_FALSE(controlPatternStore.hasControlPattern("y"));
    }

    SECTION("hasControlPatternAtStatement") {
        ControlPatternStore controlPatternStore;
        controlPatternStore.addControlPattern(1, "x");
        controlPatternStore.addControlPattern(2, "y");
        controlPatternStore.addControlPattern(1, "z");
        REQUIRE(controlPatternStore.hasControlPatternAtStatement(1, "x"));
        REQUIRE(controlPatternStore.hasControlPatternAtStatement(1, "z"));
        REQUIRE_FALSE(controlPatternStore.hasControlPatternAtStatement(1, "y"));
        REQUIRE_FALSE(controlPatternStore.hasControlPatternAtStatement(2, "x"));
    }


}