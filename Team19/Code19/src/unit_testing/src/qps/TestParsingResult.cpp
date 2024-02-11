#include "../../spa/src/qps/Parser/QueryParser.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Check Parsing Result of select all query") {
    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    REQUIRE(parsingResult.getDeclaredSynonym("s") == "stmt");
    REQUIRE(parsingResult.getRequiredSynonym() == "s");
}


TEST_CASE("Check Parsing Result for suchthat-cl Modifies with quoted variable") {
    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Modifies, "Modifies"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::QuoutIDENT, "\"existentVar\""),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    REQUIRE(parsingResult.getDeclaredSynonym("s") == "stmt");
    REQUIRE(parsingResult.getRequiredSynonym() == "s");
    REQUIRE(parsingResult.getSuchThatClauseRelationship().getType() == TokenType::Modifies);
    REQUIRE(parsingResult.getSuchThatClauseRelationship().getValue()  == "Modifies");
    REQUIRE(parsingResult.getSuchThatClauseFirstParam().getType() == TokenType::IDENT);
    REQUIRE(parsingResult.getSuchThatClauseFirstParam().getValue() == "s");
    REQUIRE(parsingResult.getSuchThatClauseSecondParam().getType() == TokenType::QuoutIDENT);
    REQUIRE(parsingResult.getSuchThatClauseSecondParam().getValue() == "\"existentVar\"");
    
}


TEST_CASE("Check Parsing Result of pattern query Quouted Constant") {

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::QuoutIDENT, "\"x\""),
            Token(TokenType::Comma, ","),
            Token(TokenType::QuoutConst, "\"1\""),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    REQUIRE(parsingResult.getDeclaredSynonym("a") == "assign");
    REQUIRE(parsingResult.getRequiredSynonym() == "a");
    REQUIRE(parsingResult.getPatternClauseRelationship().getType() == TokenType::IDENT);
    REQUIRE(parsingResult.getPatternClauseRelationship().getValue() == "a");
    REQUIRE(parsingResult.getPatternClauseFirstParam().getType() == TokenType::QuoutIDENT);
    REQUIRE(parsingResult.getPatternClauseFirstParam().getValue() == "\"x\"");
    REQUIRE(parsingResult.getPatternClauseSecondParam().getType() == TokenType::ExpressionSpec);
    REQUIRE(parsingResult.getPatternClauseSecondParam().getValue() == "\"1\"");
}


TEST_CASE("Check Parsing Result of valid tokens that Follows with variable and wildcard") {
    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    REQUIRE(parsingResult.getDeclaredSynonym("s") == "stmt");
    REQUIRE(parsingResult.getRequiredSynonym() == "s");
    REQUIRE(parsingResult.getSuchThatClauseRelationship().getType() == TokenType::Follows);
    REQUIRE(parsingResult.getSuchThatClauseRelationship().getValue() == "Follows");
    REQUIRE(parsingResult.getSuchThatClauseFirstParam().getType() == TokenType::IDENT);
    REQUIRE(parsingResult.getSuchThatClauseFirstParam().getValue() == "s");
    REQUIRE(parsingResult.getSuchThatClauseSecondParam().getType() == TokenType::Wildcard);
    REQUIRE(parsingResult.getSuchThatClauseSecondParam().getValue() == "_");
}



TEST_CASE("Check Parsing Result of Pattern with variable and an expressionSpec") {
    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::QuoutIDENT, "\"x\""),
            Token(TokenType::Comma, ","),
            Token(TokenType::DoubleQuote, "\""),
            Token(TokenType::INTEGER, "1"),
            Token(TokenType::Operator, "*"),
            Token(TokenType::INTEGER, "3"),
            Token(TokenType::DoubleQuote, "\""),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    REQUIRE(parsingResult.getDeclaredSynonym("a") == "assign");
    REQUIRE(parsingResult.getRequiredSynonym() == "a");
    REQUIRE(parsingResult.getPatternClauseRelationship().getType() == TokenType::IDENT);
    REQUIRE(parsingResult.getPatternClauseRelationship().getValue() == "a");
    REQUIRE(parsingResult.getPatternClauseFirstParam().getType() == TokenType::QuoutIDENT);
    REQUIRE(parsingResult.getPatternClauseFirstParam().getValue() == "\"x\"");
    REQUIRE(parsingResult.getPatternClauseSecondParam().getType() == TokenType::ExpressionSpec);
    REQUIRE(parsingResult.getPatternClauseSecondParam().getValue() == "\"1*3\"");
}


TEST_CASE("Check Parsing Result of Pattern with variable and an expressionSpec that contains an expression of _\"expr\"_ format") {
    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::QuoutIDENT, "\"x\""),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::DoubleQuote, "\""),
            Token(TokenType::INTEGER, "1"),
            Token(TokenType::Operator, "*"),
            Token(TokenType::INTEGER, "3"),
            Token(TokenType::DoubleQuote, "\""),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    REQUIRE(parsingResult.getDeclaredSynonym("a") == "assign");
    REQUIRE(parsingResult.getRequiredSynonym() == "a");
    REQUIRE(parsingResult.getPatternClauseRelationship().getType() == TokenType::IDENT);
    REQUIRE(parsingResult.getPatternClauseRelationship().getValue() == "a");
    REQUIRE(parsingResult.getPatternClauseFirstParam().getType() == TokenType::QuoutIDENT);
    REQUIRE(parsingResult.getPatternClauseFirstParam().getValue() == "\"x\"");
    REQUIRE(parsingResult.getPatternClauseSecondParam().getType() == TokenType::ExpressionSpec);
    REQUIRE(parsingResult.getPatternClauseSecondParam().getValue() == "_\"1*3\"_");

}
