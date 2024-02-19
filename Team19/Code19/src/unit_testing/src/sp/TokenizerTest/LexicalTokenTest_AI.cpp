// ai-gen start(gpt,2,e)
// prompt: https://platform.openai.com/playground/p/vwMjpyCtExjgJwMs6KZaXnTE?model=gpt-4&mode=chat
#include "catch.hpp"
#include "sp/SPTokenizer/LexicalToken.h"

// Test the constructor with only token type.
TEST_CASE("Constructor with only type", "[LexicalToken]")
{
    LexicalToken token(LexicalTokenType::SYMBOL_OPEN_BRACE,1,1,"(");
    REQUIRE(token.getTokenType() == LexicalTokenType::SYMBOL_OPEN_BRACE);
}

// Test getting the token type.
TEST_CASE("Get TokenType", "[LexicalToken]")
{
    LexicalToken token(LexicalTokenType::OPERATOR_PLUS,1,1,"+");
    REQUIRE(token.getTokenType() == LexicalTokenType::OPERATOR_PLUS);
}
//ai-gen end

