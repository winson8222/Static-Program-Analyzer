#include "catch.hpp"
#include "commons/ShuntingYard.h"

TEST_CASE("commons/ShuntingYard") {
    SECTION("convertToPostfix: 1 + 2") {
        std::string infixExpression = "1 + 2";
        std::string expected = "'1''2''+'";
        std::string postfixExpression = ShuntingYard::convertToPostfix(infixExpression);
        REQUIRE(postfixExpression == expected);
    }

    SECTION("convertToPostfix: 1 + 2 * 3") {
        std::string infixExpression = "1 + 2 * 3";
        std::string postfixExpression = ShuntingYard::convertToPostfix(infixExpression);
        REQUIRE(postfixExpression == "'1''2''3''*''+'");
    }

    SECTION("convertToPostfix: v + x * y + z * t") {
        std::string infixExpression = "v + x * y + z * t";
        std::string postfixExpression = ShuntingYard::convertToPostfix(infixExpression);
        REQUIRE(postfixExpression == "'v''x''y''*''+''z''t''*''+'");
    }

    SECTION("convertToPostFix: y + z + t") {
        std::string infixExpression = "y + z + t";
        std::string postfixExpression = ShuntingYard::convertToPostfix(infixExpression);
        REQUIRE(postfixExpression == "'y''z''+''t''+'");
    }

    SECTION("convertToPostFix: v + x * y") {
      std::string infixExpression = "v + x * y";
      std::string postfixExpression = ShuntingYard::convertToPostfix(infixExpression);
      REQUIRE(postfixExpression == "'v''x''y''*''+'");
    }

    SECTION("convertToPostFix: Long") {
        std::string infixExpression = "100 + x";
        std::string postfixExpression = ShuntingYard::convertToPostfix(infixExpression);
        REQUIRE(postfixExpression == "'100''x''+'");
    }

    SECTION("convertToPostfix: longv + x * longy + z * t") {
        std::string infixExpression = "longv + x * longy + z * t";
        std::string postfixExpression = ShuntingYard::convertToPostfix(infixExpression);
        REQUIRE(postfixExpression == "'longv''x''longy''*''+''z''t''*''+'");
    }

    SECTION("convertToPostfix: 100 + 100 * (procedure % 2)") {
        std::string infixExpression = "100 + 100 * (procedure % 2)";
        std::string postfixExpression = ShuntingYard::convertToPostfix(infixExpression);
        REQUIRE(postfixExpression == "'100''100''procedure''2''%''*''+'");
    }


    SECTION("convertToPostfix: 1") {
        std::string infixExpression = "1";
        std::string postfixExpression = ShuntingYard::convertToPostfix(infixExpression);
        REQUIRE(postfixExpression == "'1'");
    }
}
