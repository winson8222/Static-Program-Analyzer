#include "sp/LexicalToken.h"
#include "sp/Tokenizer.h"
#include <fstream>     
#include "catch.hpp"
#include "sp/LexicalToken.h"

TEST_CASE("Symbol Tokens") {
    REQUIRE(LexicalTokenMapper::getToken("}") == LexicalToken::SYMBOL_CLOSE_BRACE);
    REQUIRE(LexicalTokenMapper::getToken("(") == LexicalToken::SYMBOL_OPEN_PAREN);
    // Add more symbol tokens as needed
}

TEST_CASE("Keyword Tokens") {
    REQUIRE(LexicalTokenMapper::getToken("if") == LexicalToken::KEYWORD_IF);
    REQUIRE(LexicalTokenMapper::getToken("then") == LexicalToken::KEYWORD_THEN);
    // Add more keyword tokens as needed
}

TEST_CASE("Digit::verifyToken", "[Digit]")
{
    LexicalTokens::Digit digitToken;

    SECTION("Valid Digits")
    {
        REQUIRE(digitToken.verifyToken("0"));
        REQUIRE(digitToken.verifyToken("9"));
    }

TEST_CASE("Name Tokens") {
    REQUIRE(LexicalTokenMapper::getToken("variable1") == LexicalToken::NAME);
    REQUIRE(LexicalTokenMapper::getToken("unknown") == LexicalToken::NAME);
    REQUIRE(LexicalTokenMapper::getToken("v") == LexicalToken::NAME);
    // Add more name tokens as needed
}

TEST_CASE("Error Tokens") {
    REQUIRE(LexicalTokenMapper::getToken("123abc") == LexicalToken::ERROR);
    REQUIRE(LexicalTokenMapper::getToken("!@#") == LexicalToken::ERROR);
    // Add more error cases as needed
}

TEST_CASE("Space and New Line Tokens") {
    REQUIRE(LexicalTokenMapper::getToken(" ") == LexicalToken::WHITESPACE);
    REQUIRE(LexicalTokenMapper::getToken("\n") == LexicalToken::NEW_LINE);
    // Add more space and new line tokens as needed
}

TEST_CASE("Unknown Token") {
    REQUIRE(LexicalTokenMapper::getToken("1variable") == LexicalToken::ERROR);
    REQUIRE(LexicalTokenMapper::getToken("variable_123") == LexicalToken::ERROR);
    REQUIRE(LexicalTokenMapper::getToken("@") == LexicalToken::ERROR);
    // Add more unknown cases as needed
}
