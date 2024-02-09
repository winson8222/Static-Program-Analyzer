#include "../../spa/src/qps/QueryParser.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Check Synonym in result of select all query parsing") {
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
}