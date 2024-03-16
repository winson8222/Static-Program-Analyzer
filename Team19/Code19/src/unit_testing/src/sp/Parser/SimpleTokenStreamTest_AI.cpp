#include "catch.hpp"
#include "sp/Parser/SimpleTokenStream.h"

// Tests constructor initializes tokenIndex to 0 and all tokens are right
TEST_CASE("Check SimpleTokenStream behavior for Whitespace at the end.") {
	std::vector<LexicalToken> tokens = { LexicalToken(LexicalTokenType::INTEGER), LexicalToken(LexicalTokenType::WHITESPACE), LexicalToken(LexicalTokenType::WHITESPACE) };
	auto token_ptr = std::make_shared<std::vector<LexicalToken>>(tokens);
	SimpleTokenStream tokenStream(token_ptr);
	REQUIRE(tokenStream.hasTokensLeft() == true);
	REQUIRE_NOTHROW(tokenStream.popAndAssertToken(LexicalTokenType::INTEGER));
	REQUIRE(tokenStream.hasTokensLeft() == false);
	REQUIRE_NOTHROW(tokenStream.popAndAssertToken(LexicalTokenType::NULL_TOKEN));
	REQUIRE(tokenStream.hasTokensLeft() == false);
}

// Check whether the next non-whitespace token function works correctly
TEST_CASE("Check SimpleTokenstream behavior for skipping whitespaces.") {
	std::vector<LexicalToken> tokens = { LexicalToken(LexicalTokenType::WHITESPACE), LexicalToken(LexicalTokenType::INTEGER) };
	auto token_ptr = std::make_shared<std::vector<LexicalToken>>(tokens);
	SimpleTokenStream tokenStream(token_ptr);
	REQUIRE_NOTHROW(tokenStream.popAndAssertToken(LexicalTokenType::INTEGER));
}

// Check behavior for empty input token vector
TEST_CASE("Test hasTokensLeft") {
	std::vector<LexicalToken> tokens;
	auto token_ptr = std::make_shared<std::vector<LexicalToken>>(tokens);
	SimpleTokenStream tokenStream(token_ptr);
	REQUIRE(tokenStream.hasTokensLeft() == false);
}

// Check whether peekToken function works correctly
TEST_CASE("Test peekToken") {
	std::vector<LexicalToken> tokens = { LexicalToken(LexicalTokenType::INTEGER), LexicalToken(LexicalTokenType::WHITESPACE), LexicalToken(LexicalTokenType::OPERATOR_AND), LexicalToken(LexicalTokenType::WHITESPACE) };
	auto token_ptr = std::make_shared<std::vector<LexicalToken>>(tokens);
	SimpleTokenStream tokenStream(token_ptr);

	REQUIRE(tokenStream.peekToken().getTokenType() == LexicalTokenType::INTEGER);
	REQUIRE(tokenStream.peekToken(1).getTokenType() == LexicalTokenType::INTEGER);
	REQUIRE(tokenStream.peekToken(2).getTokenType() == LexicalTokenType::OPERATOR_AND);
	REQUIRE(tokenStream.peekToken(3).getTokenType() == LexicalTokenType::NULL_TOKEN);

	REQUIRE_THROWS_AS(tokenStream.peekToken(0), std::runtime_error);
	REQUIRE_THROWS_AS(tokenStream.peekToken(-1), std::runtime_error);
}
