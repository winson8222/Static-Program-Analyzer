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
        REQUIRE(suchThatClause.getRelationship().getType() == TokenType::ModifiesS);
        REQUIRE(suchThatClause.getRelationship().getValue() == "Modifies");
        REQUIRE(suchThatClause.getFirstParam().getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.getFirstParam().getValue() == "s");
        REQUIRE(suchThatClause.getSecondParam().getType() == TokenType::QuoutIDENT);
        REQUIRE(suchThatClause.getSecondParam().getValue() == "\"existentVar\"");

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
        REQUIRE(suchThatClause.getRelationship().getType() == TokenType::UsesS);
        REQUIRE(suchThatClause.getRelationship().getValue() == "Uses");
        REQUIRE(suchThatClause.getFirstParam().getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.getFirstParam().getValue() == "s");
        REQUIRE(suchThatClause.getSecondParam().getType() == TokenType::QuoutIDENT);
        REQUIRE(suchThatClause.getSecondParam().getValue() == "\"existentVar\"");

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
        REQUIRE(patternClause.getRelationship().getType() == TokenType::IDENT);
        REQUIRE(patternClause.getRelationship().getValue() == "a");
        REQUIRE(patternClause.getFirstParam().getType() == TokenType::QuoutIDENT);
        REQUIRE(patternClause.getFirstParam().getValue() == "\"x\"");
        REQUIRE(patternClause.getSecondParam().getType() == TokenType::ExpressionSpec);
        REQUIRE(patternClause.getSecondParam().getValue() == "\"1\"");
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
        REQUIRE(suchThatClause.getRelationship().getType() == TokenType::Follows);
        REQUIRE(suchThatClause.getRelationship().getValue() == "Follows");
        REQUIRE(suchThatClause.getFirstParam().getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.getFirstParam().getValue() == "s");
        REQUIRE(suchThatClause.getSecondParam().getType() == TokenType::Wildcard);
        REQUIRE(suchThatClause.getSecondParam().getValue() == "_");
    }

//    SECTION("Check Parsing Result of 'procedure p, q; Select <p.stmt#, q.procName> such that Calls (p, q)'") {
//        std::vector<Token> tokens = {
//            Token(TokenType::DesignEntity, "procedure"),
//            Token(TokenType::IDENT, "p"),
//            Token(TokenType::Comma, ","),
//            Token(TokenType::IDENT, "q"),
//            Token(TokenType::Semicolon, ";"),
//            Token(TokenType::SelectKeyword, "Select"),
//            Token(TokenType::LeftAngleBracket, "<"),
//            Token(TokenType::IDENT, "p"),
//            Token(TokenType::Dot, "."),
//            Token(TokenType::AttrName, "stmt#"),
//            Token(TokenType::Comma, ","),
//            Token(TokenType::IDENT, "q"),
//            Token(TokenType::Dot, "."),
//            Token(TokenType::AttrName, "procName"),
//            Token(TokenType::RightAngleBracket, ">"),
//            Token(TokenType::SuchKeyword, "such"),
//            Token(TokenType::ThatKeyword, "that"),
//            Token(TokenType::Calls, "Calls"),
//            Token(TokenType::Lparenthesis, "("),
//            Token(TokenType::IDENT, "p"),
//            Token(TokenType::Comma, ","),
//            Token(TokenType::IDENT, "q"),
//            Token(TokenType::Rparenthesis, ")")
//        };
//
//        QueryParser parser(tokens);
//        auto parsingResult = parser.parse();
//        auto suchThatClause = parsingResult.getSuchThatClauses()[0];
//        REQUIRE(parsingResult.getDeclaredSynonym("p") == "procedure");
//        REQUIRE(parsingResult.getDeclaredSynonym("q") == "procedure");
//        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "p.stmt#");
//        REQUIRE(parsingResult.getRequiredSynonyms()[1] == "q.procName");
//        REQUIRE(suchThatClause.getRelationship().getType() == TokenType::Calls);
//        REQUIRE(suchThatClause.getRelationship().getValue() == "Calls");
//        REQUIRE(suchThatClause.getFirstParam().getType() == TokenType::IDENT);
//        REQUIRE(suchThatClause.getFirstParam().getValue() == "p");
//        REQUIRE(suchThatClause.getSecondParam().getType() == TokenType::IDENT);
//        REQUIRE(suchThatClause.getSecondParam().getValue() == "q");
//    }

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
        REQUIRE(patternClause.getRelationship().getType() == TokenType::IDENT);
        REQUIRE(patternClause.getRelationship().getValue() == "a");
        REQUIRE(patternClause.getFirstParam().getType() == TokenType::QuoutIDENT);
        REQUIRE(patternClause.getFirstParam().getValue() == "\"x\"");
        REQUIRE(patternClause.getSecondParam().getType() == TokenType::Wildcard);
        REQUIRE(patternClause.getSecondParam().getValue() == "_");

        auto suchThatClause = parsingResult.getSuchThatClauses()[0];
        REQUIRE(suchThatClause.getRelationship().getType() == TokenType::ParentT);
        REQUIRE(suchThatClause.getRelationship().getValue() == "Parent*");
        REQUIRE(suchThatClause.getFirstParam().getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.getFirstParam().getValue() == "w");
        REQUIRE(suchThatClause.getSecondParam().getType() == TokenType::IDENT);
        REQUIRE(suchThatClause.getSecondParam().getValue() == "a");

        auto suchThatClause2 = parsingResult.getSuchThatClauses()[1];
        REQUIRE(suchThatClause2.getRelationship().getType() == TokenType::NextT);
        REQUIRE(suchThatClause2.getRelationship().getValue() == "Next*");
        REQUIRE(suchThatClause2.getFirstParam().getType() == TokenType::INTEGER);
        REQUIRE(suchThatClause2.getFirstParam().getValue() == "1");
        REQUIRE(suchThatClause2.getSecondParam().getType() == TokenType::IDENT);
        REQUIRE(suchThatClause2.getSecondParam().getValue() == "a");
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
        REQUIRE(suchThatClause.getRelationship().getType() == TokenType::Follows);
        REQUIRE(suchThatClause.getRelationship().getValue() == "Follows");
        REQUIRE(suchThatClause.getFirstParam().getType() == TokenType::INTEGER);
        REQUIRE(suchThatClause.getFirstParam().getValue() == "3");
        REQUIRE(suchThatClause.getSecondParam().getType() == TokenType::INTEGER);
        REQUIRE(suchThatClause.getSecondParam().getValue() == "4");
    }
//
//    SECTION("Check Parsing Result of 'procedure p, q; Select p such that Calls(p, q) with q.procName = \"Third\"'") {
//        std::vector<Token> tokens = {
//            Token(TokenType::DesignEntity, "procedure"),
//            Token(TokenType::IDENT, "p"),
//            Token(TokenType::Comma, ","),
//            Token(TokenType::IDENT, "q"),
//            Token(TokenType::Semicolon, ";"),
//            Token(TokenType::SelectKeyword, "Select"),
//            Token(TokenType::IDENT, "p"),
//            Token(TokenType::SuchKeyword, "such"),
//            Token(TokenType::ThatKeyword, "that"),
//            Token(TokenType::Calls, "Calls"),
//            Token(TokenType::Lparenthesis, "("),
//            Token(TokenType::IDENT, "p"),
//            Token(TokenType::Comma, ","),
//            Token(TokenType::IDENT, "q"),
//            Token(TokenType::Rparenthesis, ")"),
//            Token(TokenType::WithKeyword, "with"),
//            Token(TokenType::IDENT, "q"),
//            Token(TokenType::Dot, "."),
//            Token(TokenType::AttrName, "procName"),
//            Token(TokenType::Equal, "="),
//            Token(TokenType::QuoutIDENT, "\"Third\"")
//        };
//
//        QueryParser parser(tokens);
//        auto parsingResult = parser.parse();
//        REQUIRE(parsingResult.getDeclaredSynonym("p") == "procedure");
//        REQUIRE(parsingResult.getDeclaredSynonym("q") == "procedure");
//        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "p");
//
//        auto suchThatClause = parsingResult.getSuchThatClauses()[0];
//        REQUIRE(suchThatClause.getRelationship().getType() == TokenType::Calls);
//        REQUIRE(suchThatClause.getRelationship().getValue() == "Calls");
//        REQUIRE(suchThatClause.getFirstParam().getType() == TokenType::IDENT);
//        REQUIRE(suchThatClause.getFirstParam().getValue() == "p");
//        REQUIRE(suchThatClause.getSecondParam().getType() == TokenType::IDENT);
//        REQUIRE(suchThatClause.getSecondParam().getValue() == "q");
//
//        auto withClause = parsingResult.getWithClauses()[0];
//        REQUIRE(withClause.getRelationship().getType() == TokenType::WithKeyword);
//        REQUIRE(withClause.getRelationship().getValue() == "with");
//        REQUIRE(withClause.getFirstParam().getType() == TokenType::Ref);
//        REQUIRE(withClause.getFirstParam().getValue() == "q.procName");
//        REQUIRE(withClause.getSecondParam().getType() == TokenType::Ref);
//        REQUIRE(withClause.getSecondParam().getValue() == "\"Third\"");
//    }
}




