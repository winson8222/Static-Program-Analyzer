#include "catch.hpp"

#include "pkb/stores/patterns/control/ControlPatternStore.h"

TEST_CASE("pkb/stores/patterns/control/ControlPatternStore") {
  std::string x = "x";
  std::string y = "y";
  std::string one = "1";
  SECTION("addControlPattern") {
    ControlPatternStore controlPatternStore;
    controlPatternStore.addControlPattern(1, "x");
    REQUIRE(controlPatternStore.contains(1));
    REQUIRE_FALSE(controlPatternStore.contains(2));
  }

  SECTION("contains") {
    ControlPatternStore controlPatternStore;
    controlPatternStore.addControlPattern(1, "x");
    REQUIRE(controlPatternStore.contains(1));
    REQUIRE_FALSE(controlPatternStore.contains(2));
  }

  SECTION("clear") {
    ControlPatternStore controlPatternStore;
    controlPatternStore.addControlPattern(1, "x");
    controlPatternStore.addControlPattern(2, "y");
    controlPatternStore.clear();
    REQUIRE(controlPatternStore.getAllControlPatterns().empty());
  }

  SECTION("getControlPattern") {
    ControlPatternStore controlPatternStore;
    controlPatternStore.addControlPattern(1, "x");
    REQUIRE(controlPatternStore.getControlPattern(1) == "x");
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
}