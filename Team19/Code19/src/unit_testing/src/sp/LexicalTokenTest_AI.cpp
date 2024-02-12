// ai-gen start(gpt,2,e)
// prompt: https://platform.openai.com/playground/p/vwMjpyCtExjgJwMs6KZaXnTE?model=gpt-4&mode=chat
#include "catch.hpp"
#include "sp/LexicalToken.h"

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

/*
// ai-gen start(gpt, 2, e)
// Prompt: https://platform.openai.com/playground/p/CRO1bXNAQZB3Adua8DmfPuWb?model=gpt-4&mode=chat
TEST_CASE("Testing CallStmt::buildTree()", "[CallStmt]") {
    LexicalToken lexicalToken(LexicalTokenType::KEYWORD_CALL, 1, 1, "variable");
    CallStmt callStmt(lexicalToken, 1, 1);

    SECTION("Testing tree root node") {
        std::shared_ptr<ASTNode> tree_ptr = callStmt.buildTree();

        REQUIRE(tree_ptr->type == ASTNodeType::CALL);
        REQUIRE(tree_ptr->lineNumber == 2);
        REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::CALL));

        SECTION("Testing tree child node") {
            const auto& children = tree_ptr->children;
            REQUIRE(children.size() == 1);
            REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
            REQUIRE(children[0]->lineNumber == 3);
            REQUIRE(children[0]->value == "exampleVariable");
        }
    }
}
// ai-gen end
*/