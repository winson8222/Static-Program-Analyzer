#include "qps/parser/QueryParser.h"
#include "catch.hpp"

using namespace std;
TEST_CASE("src/qps/parser/ParsingResult") {
    SECTION("Check Parsing Result of select all query") {
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
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "s");
    }


    SECTION("Check Parsing Result for suchthat-cl ModifiesS with quoted variable") {
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
        auto suchThatClause = parsingResult.getSuchThatClauses()[0];
        REQUIRE(parsingResult.getDeclaredSynonym("s") == "stmt");
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "s");
        REQUIRE(suchThatClause.relationship.getType() == TokenType::ModifiesS);
        REQUIRE(suchThatClause.relationship.getValue() == "Modifies");
        REQUIRE(suchThatClause.firstParam.getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.firstParam.getValue() == "s");
        REQUIRE(suchThatClause.secondParam.getType() == TokenType::QuoutIDENT);
        REQUIRE(suchThatClause.secondParam.getValue() == "\"existentVar\"");

    }

    SECTION("Check Parsing Result for suchthat-cl ModifiesP with quoted variable") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Modifies, "Modifies"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutIDENT, "\"existentVar\""),
                Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        auto suchThatClause = parsingResult.getSuchThatClauses()[0];
        REQUIRE(parsingResult.getDeclaredSynonym("v") == "variable");
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "v");
        REQUIRE(suchThatClause.relationship.getType() == TokenType::ModifiesP);
        REQUIRE(suchThatClause.relationship.getValue() == "Modifies");
        REQUIRE(suchThatClause.firstParam.getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.firstParam.getValue() == "v");
        REQUIRE(suchThatClause.secondParam.getType() == TokenType::QuoutIDENT);
        REQUIRE(suchThatClause.secondParam.getValue() == "\"existentVar\"");

    }


    SECTION("Check Parsing Result for suchthat-cl ModifiesS with wild card as first param") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Modifies, "Modifies"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutIDENT, "\"existentVar\""),
                Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        REQUIRE(parsingResult.getErrorMessage() == "SemanticError");


    }

    SECTION("Check Parsing Result for suchthat-cl UsesS with quoted variable") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutIDENT, "\"existentVar\""),
                Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        auto suchThatClause = parsingResult.getSuchThatClauses()[0];
        REQUIRE(parsingResult.getDeclaredSynonym("s") == "stmt");
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "s");
        REQUIRE(suchThatClause.relationship.getType() == TokenType::UsesS);
        REQUIRE(suchThatClause.relationship.getValue() == "Uses");
        REQUIRE(suchThatClause.firstParam.getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.firstParam.getValue() == "s");
        REQUIRE(suchThatClause.secondParam.getType() == TokenType::QuoutIDENT);
        REQUIRE(suchThatClause.secondParam.getValue() == "\"existentVar\"");

    }


    SECTION("Check Parsing Result of pattern query Quouted Constant") {

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
        auto patternClause = parsingResult.getPatternClauses()[0];
        REQUIRE(parsingResult.getErrorMessage() == "");
        REQUIRE(parsingResult.getDeclaredSynonym("a") == "assign");
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "a");
        REQUIRE(patternClause.relationship.getType() == TokenType::IDENT);
        REQUIRE(patternClause.relationship.getValue() == "a");
        REQUIRE(patternClause.firstParam.getType() == TokenType::QuoutIDENT);
        REQUIRE(patternClause.firstParam.getValue() == "\"x\"");
        REQUIRE(patternClause.secondParam.getType() == TokenType::ExpressionSpec);
        REQUIRE(patternClause.secondParam.getValue() == "\"1\"");
    }


    SECTION("Check Parsing Result of valid tokens that Follows with variable and wildcard") {
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
        auto suchThatClause = parsingResult.getSuchThatClauses()[0];
        REQUIRE(parsingResult.getDeclaredSynonym("s") == "stmt");
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "s");
        REQUIRE(suchThatClause.relationship.getType() == TokenType::Follows);
        REQUIRE(suchThatClause.relationship.getValue() == "Follows");
        REQUIRE(suchThatClause.firstParam.getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.firstParam.getValue() == "s");
        REQUIRE(suchThatClause.secondParam.getType() == TokenType::Wildcard);
        REQUIRE(suchThatClause.secondParam.getValue() == "_");
    }

    SECTION("Check Parsing Result of 'procedure p, q; Select <p.stmt#, q.procName> such that Calls (p, q)'") {
        std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "procedure"),
            Token(TokenType::IDENT, "p"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "q"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::LeftAngleBracket, "<"),
            Token(TokenType::IDENT, "p"),
            Token(TokenType::Dot, "."),
            Token(TokenType::AttrName, "stmt#"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "q"),
            Token(TokenType::Dot, "."),
            Token(TokenType::AttrName, "procName"),
            Token(TokenType::RightAngleBracket, ">"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Calls, "Calls"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "p"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "q"),
            Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        auto suchThatClause = parsingResult.getSuchThatClauses()[0];
        REQUIRE(parsingResult.getDeclaredSynonym("p") == "procedure");
        REQUIRE(parsingResult.getDeclaredSynonym("q") == "procedure");
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "p.stmt#");
        REQUIRE(parsingResult.getRequiredSynonyms()[1] == "q.procName");
        REQUIRE(suchThatClause.relationship.getType() == TokenType::Calls);
        REQUIRE(suchThatClause.relationship.getValue() == "Calls");
        REQUIRE(suchThatClause.firstParam.getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.firstParam.getValue() == "p");
        REQUIRE(suchThatClause.secondParam.getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.secondParam.getValue() == "q");
    }

    SECTION("Check Parsing Result of 'assign a; while w; Select a pattern a(\"x\", _) such that Parent*(w, a) such that Next*(1, a)'") {
        std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::DesignEntity, "while"),
            Token(TokenType::IDENT, "w"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::QuoutIDENT, "\"x\""),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::ParentT, "Parent*"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "w"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Rparenthesis, ")"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::NextT, "Next*"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "1"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        
        REQUIRE(parsingResult.getDeclaredSynonym("a") == "assign");
        REQUIRE(parsingResult.getDeclaredSynonym("w") == "while");
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "a");

        auto patternClause = parsingResult.getPatternClauses()[0];
        REQUIRE(patternClause.relationship.getType() == TokenType::IDENT);
        REQUIRE(patternClause.relationship.getValue() == "a");
        REQUIRE(patternClause.firstParam.getType() == TokenType::QuoutIDENT);
        REQUIRE(patternClause.firstParam.getValue() == "\"x\"");
        REQUIRE(patternClause.secondParam.getType() == TokenType::ExpressionSpec);
        REQUIRE(patternClause.secondParam.getValue() == "_");

        auto suchThatClause = parsingResult.getSuchThatClauses()[0];
        REQUIRE(suchThatClause.relationship.getType() == TokenType::ParentT);
        REQUIRE(suchThatClause.relationship.getValue() == "Parent*");
        REQUIRE(suchThatClause.firstParam.getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.firstParam.getValue() == "w");
        REQUIRE(suchThatClause.secondParam.getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.secondParam.getValue() == "a");

        auto suchThatClause2 = parsingResult.getSuchThatClauses()[1];
        REQUIRE(suchThatClause2.relationship.getType() == TokenType::NextT);
        REQUIRE(suchThatClause2.relationship.getValue() == "Next*");
        REQUIRE(suchThatClause2.firstParam.getType() == TokenType::INTEGER);
        REQUIRE(suchThatClause2.firstParam.getValue() == "1");
        REQUIRE(suchThatClause2.secondParam.getType() == TokenType::IDENT);
        REQUIRE(suchThatClause2.secondParam.getValue() == "a");
    }

    SECTION("Check Parsing Result of 'stmt s; Select BOOLEAN such that Follows(3, 4)'") {
        std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::BooleanKeyword, "BOOLEAN"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "3"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "4"),
            Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        auto suchThatClause = parsingResult.getSuchThatClauses()[0];
        REQUIRE(parsingResult.getDeclaredSynonym("s") == "stmt");
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "BOOLEAN");
        REQUIRE(suchThatClause.relationship.getType() == TokenType::Follows);
        REQUIRE(suchThatClause.relationship.getValue() == "Follows");
        REQUIRE(suchThatClause.firstParam.getType() == TokenType::INTEGER);
        REQUIRE(suchThatClause.firstParam.getValue() == "3");
        REQUIRE(suchThatClause.secondParam.getType() == TokenType::INTEGER);
        REQUIRE(suchThatClause.secondParam.getValue() == "4");
    }

    SECTION("Check Parsing Result of 'procedure p, q; Select p such that Calls(p, q) with q.procName = \"Third\"'") {
        std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "procedure"),
            Token(TokenType::IDENT, "p"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "q"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "p"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Calls, "Calls"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "p"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "q"),
            Token(TokenType::Rparenthesis, ")"),
            Token(TokenType::WithKeyword, "with"),
            Token(TokenType::IDENT, "q"),
            Token(TokenType::Dot, "."),
            Token(TokenType::AttrName, "procName"),
            Token(TokenType::Equal, "="),
            Token(TokenType::QuoutIDENT, "\"Third\"")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        REQUIRE(parsingResult.getDeclaredSynonym("p") == "procedure");
        REQUIRE(parsingResult.getDeclaredSynonym("q") == "procedure");
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "p");

        auto suchThatClause = parsingResult.getSuchThatClauses()[0];
        REQUIRE(suchThatClause.relationship.getType() == TokenType::Calls);
        REQUIRE(suchThatClause.relationship.getValue() == "Calls");
        REQUIRE(suchThatClause.firstParam.getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.firstParam.getValue() == "p");
        REQUIRE(suchThatClause.secondParam.getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.secondParam.getValue() == "q");

        auto withClause = parsingResult.getWithClauses()[0];
        REQUIRE(withClause.relationship.getType() == TokenType::WithKeyword);
        REQUIRE(withClause.relationship.getValue() == "with");
        REQUIRE(withClause.firstParam.getType() == TokenType::Ref);
        REQUIRE(withClause.firstParam.getValue() == "q.procName");
        REQUIRE(withClause.secondParam.getType() == TokenType::Ref);
        REQUIRE(withClause.secondParam.getValue() == "\"Third\"");
    }
}


