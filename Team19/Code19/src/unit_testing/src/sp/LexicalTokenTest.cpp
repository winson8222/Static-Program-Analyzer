#include "sp/LexicalToken.h"
#include "catch.hpp"

TEST_CASE("Letter::verifyToken", "[Letter]")
{
    LexicalTokens::Letter letterToken;

    SECTION("Valid Letters")
    {
        REQUIRE(letterToken.verifyToken("A"));
        REQUIRE(letterToken.verifyToken("z"));
    }

    SECTION("Invalid Characters")
    {
        REQUIRE_FALSE(letterToken.verifyToken(""));
        REQUIRE_FALSE(letterToken.verifyToken("1"));
        REQUIRE_FALSE(letterToken.verifyToken("az"));
        REQUIRE_FALSE(letterToken.verifyToken("_"));
    }
}

TEST_CASE("Digit::verifyToken", "[Digit]")
{
    LexicalTokens::Digit digitToken;

    SECTION("Valid Digits")
    {
        REQUIRE(digitToken.verifyToken("0"));
        REQUIRE(digitToken.verifyToken("9"));
    }

    SECTION("Invalid Characters")
    {
        REQUIRE_FALSE(digitToken.verifyToken(""));
        REQUIRE_FALSE(digitToken.verifyToken("a"));
        REQUIRE_FALSE(digitToken.verifyToken("10"));
        REQUIRE_FALSE(digitToken.verifyToken("_"));
    }
}

TEST_CASE("Name::verifyToken", "[Name]")
{
    LexicalTokens::Name nameToken;

    SECTION("Valid Names")
    {
        REQUIRE(nameToken.verifyToken("ducIsHandsome"));
        REQUIRE(nameToken.verifyToken("Name123"));
        REQUIRE(nameToken.verifyToken("v"));

    }

    SECTION("Invalid Characters")
    {
        REQUIRE_FALSE(nameToken.verifyToken("function_123"));
        REQUIRE_FALSE(nameToken.verifyToken(""));
        REQUIRE_FALSE(nameToken.verifyToken("1stVariable"));
        REQUIRE_FALSE(nameToken.verifyToken("_myVariable"));

    }
}

TEST_CASE("Integer::verifyToken", "[Integer]")
{
    LexicalTokens::Integer integerToken;

    SECTION("Valid Integers")
    {
        REQUIRE(integerToken.verifyToken("0"));
        REQUIRE(integerToken.verifyToken("987654321"));
    }

    SECTION("Invalid Characters")
    {
        REQUIRE_FALSE(integerToken.verifyToken("-123"));
        REQUIRE_FALSE(integerToken.verifyToken(""));
        REQUIRE_FALSE(integerToken.verifyToken("hello"));
    }
}
