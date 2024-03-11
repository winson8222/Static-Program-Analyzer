#include "catch.hpp"
#include "sp/SPTokenizer/LexicalTokenType.h"

// ai-gen start(gpt, 2, e)
// Prompt:https://platform.openai.com/playground/p/fGLNOoOhfAXOZ9JOYT6EGplt?model=gpt-4&mode=chat
TEST_CASE("Lexical token to ASTNode mapping") {
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_ASSIGN) == ASTNodeType::ASSIGN);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_NOT) == ASTNodeType::NOT);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_AND) == ASTNodeType::AND);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_OR) == ASTNodeType::OR);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_GREATER) == ASTNodeType::GREATER);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_GREATER_EQUAL) == ASTNodeType::GREATER_OR_EQUAL);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_LESS) == ASTNodeType::LESSER);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_LESS_EQUAL) == ASTNodeType::LESSER_OR_EQUAL);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_IS_EQUAL) == ASTNodeType::EQUAL);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_NOT_EQUAL) == ASTNodeType::NOT_EQUAL);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_PLUS) == ASTNodeType::ADD);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_MINUS) == ASTNodeType::SUBTRACT);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_MULTIPLY) == ASTNodeType::MULTIPLY);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_DIVIDE) == ASTNodeType::DIVIDE);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::OPERATOR_MODULO) == ASTNodeType::MODULO);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::KEYWORD_PROCEDURE) == ASTNodeType::PROCEDURE);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::KEYWORD_WHILE) == ASTNodeType::WHILE);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::KEYWORD_IF) == ASTNodeType::IF_ELSE_THEN);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::KEYWORD_READ) == ASTNodeType::READ);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::KEYWORD_CALL) == ASTNodeType::CALL);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::KEYWORD_PRINT) == ASTNodeType::PRINT);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::INTEGER) == ASTNodeType::CONSTANT);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::NAME) == ASTNodeType::VARIABLE);
    REQUIRE(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::ERROR) == ASTNodeType::ERROR);

    // Test for an exception for a non-existing key
    REQUIRE_THROWS_AS(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::SYMBOL_CLOSE_BRACE), std::out_of_range);
    REQUIRE_THROWS_AS(LexicalTokenTypeMapper::lexicalToAstMap.at(LexicalTokenType::NULL_TOKEN), std::out_of_range);
    REQUIRE_THROWS_AS(LexicalTokenTypeMapper::lexicalToAstMap.at((LexicalTokenType)1), std::out_of_range);
}
// ai-gen end