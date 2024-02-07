#include "catch.hpp"
#include "sp/LexicalToken.h"

TEST_CASE("Symbol Tokens") {
    REQUIRE(LexicalTokenTypeMapper::getTokenType("}") == LexicalTokenType::SYMBOL_CLOSE_BRACE);
    REQUIRE(LexicalTokenTypeMapper::getTokenType("(") == LexicalTokenType::SYMBOL_OPEN_PAREN);
    // Add more symbol tokens as needed
}

TEST_CASE("Keyword Tokens") {
    REQUIRE(LexicalTokenTypeMapper::getTokenType("if") == LexicalTokenType::KEYWORD_IF);
    REQUIRE(LexicalTokenTypeMapper::getTokenType("then") == LexicalTokenType::KEYWORD_THEN);
    // Add more keyword tokens as needed
}

TEST_CASE("Integer Tokens") {
    REQUIRE(LexicalTokenTypeMapper::getTokenType("42") == LexicalTokenType::INTEGER);
    REQUIRE(LexicalTokenTypeMapper::getTokenType("123") == LexicalTokenType::INTEGER);
    // Add more integer tokens as needed
}

TEST_CASE("Name Tokens") {
    REQUIRE(LexicalTokenTypeMapper::getTokenType("variable1") == LexicalTokenType::NAME);
    REQUIRE(LexicalTokenTypeMapper::getTokenType("unknown") == LexicalTokenType::NAME);
    REQUIRE(LexicalTokenTypeMapper::getTokenType("v") == LexicalTokenType::NAME);
    // Add more name tokens as needed
}

TEST_CASE("Error Tokens") {
    REQUIRE(LexicalTokenTypeMapper::getTokenType("123abc") == LexicalTokenType::ERROR);
    REQUIRE(LexicalTokenTypeMapper::getTokenType("!@#") == LexicalTokenType::ERROR);
    // Add more error cases as needed
}

TEST_CASE("Space and New Line Tokens") {
    REQUIRE(LexicalTokenTypeMapper::getTokenType(" ") == LexicalTokenType::WHITESPACE);
    REQUIRE(LexicalTokenTypeMapper::getTokenType("\n") == LexicalTokenType::NEW_LINE);
    // Add more space and new line tokens as needed
}

TEST_CASE("Unknown Token") {
    REQUIRE(LexicalTokenTypeMapper::getTokenType("1variable") == LexicalTokenType::ERROR);
    REQUIRE(LexicalTokenTypeMapper::getTokenType("variable_123") == LexicalTokenType::ERROR);
    REQUIRE(LexicalTokenTypeMapper::getTokenType("@") == LexicalTokenType::ERROR);
    // Add more unknown cases as needed
}
