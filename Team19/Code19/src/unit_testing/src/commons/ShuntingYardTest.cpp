#include "catch.hpp"
#include "commons/ShuntingYard.h"

TEST_CASE("commons/ShuntingYard") {
    ShuntingYard shuntingYard = ShuntingYard();
    SECTION("convertToPostfix: 1 + 2") {
        std::string infixExpression = "1 + 2";
        std::string expected = "12+";
        std::string postfixExpression = shuntingYard.convertToPostfix(infixExpression);
        REQUIRE(postfixExpression == expected);
    }

    SECTION("convertToPostfix: 1 + 2 * 3") {
        std::string infixExpression = "1 + 2 * 3";
        std::string postfixExpression = shuntingYard.convertToPostfix(infixExpression);
        REQUIRE(postfixExpression == "123*+");
    }

    SECTION("convertToPostfix: v + x * y + z * t") {
        std::string infixExpression = "v + x * y + z * t";
        std::string postfixExpression = shuntingYard.convertToPostfix(infixExpression);
        REQUIRE(postfixExpression == "vxy*+zt*+");
    }

    SECTION("convertToPostFix: y + z + t") {
        std::string infixExpression = "y + z + t";
        std::string postfixExpression = shuntingYard.convertToPostfix(infixExpression);
        REQUIRE(postfixExpression == "yz+t+");
    }

  SECTION("convertToPostFix: v + x * y") {
    std::string infixExpression = "v + x * y";
    std::string postfixExpression = shuntingYard.convertToPostfix(infixExpression);
    REQUIRE(postfixExpression == "vxy*+");
  }
}
