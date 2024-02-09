#include "../../spa/src/qps/QueryParser.h"
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
    parser.parse();
    REQUIRE(parser.getParsingResult().getDeclaredSynonym("s") == "stmt");
    REQUIRE(parser.getParsingResult().getRequiredSynonym() == "s");
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
    REQUIRE(parser.parse());
    REQUIRE(parser.getParsingResult().getDeclaredSynonym("s") == "stmt");
    REQUIRE(parser.getParsingResult().getRequiredSynonym() == "s");
    REQUIRE(parser.getParsingResult().getSuchThatClauseRelationship().getType() == TokenType::Modifies);
    REQUIRE(parser.getParsingResult().getSuchThatClauseRelationship().getValue()  == "Modifies");
    REQUIRE(parser.getParsingResult().getSuchThatClauseFirstParam().getType() == TokenType::IDENT);
    REQUIRE(parser.getParsingResult().getSuchThatClauseFirstParam().getValue() == "s");
    REQUIRE(parser.getParsingResult().getSuchThatClauseSecondParam().getType() == TokenType::QuoutIDENT);
    REQUIRE(parser.getParsingResult().getSuchThatClauseSecondParam().getValue() == "\"existentVar\"");
    
}


TEST_CASE("Check Grammar of Valid tokens with pattern query") {

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
    REQUIRE(parser.parse());
}
/*

TEST_CASE("Check Grammars of valid tokens that Follows with variable and wildcard") {
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
    REQUIRE(parser.parse());

}

TEST_CASE("Check Grammars of valid tokens that Modifies with quoted variable") {
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
    REQUIRE(parser.parse());

}

TEST_CASE("Check Grammars of Pattern with variable and constant") {
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
    REQUIRE(parser.parse());

}

TEST_CASE("Check Grammars of Pattern with variable and an expressionSpec") {
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
    REQUIRE(parser.parse());
}

TEST_CASE("Check Grammars of Pattern with variable and an expressionSpec that contains an expression of _\"expr\"_ format") {
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
    REQUIRE(parser.parse());

}
*/