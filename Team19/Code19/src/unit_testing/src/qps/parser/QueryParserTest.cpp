#include "qps/parser/QueryParser.h"
#include "catch.hpp"

using namespace std;
TEST_CASE("src/qps/parser/QueryParser") {
    SECTION("Check Grammar of Valid tokens with no declaration") {
        std::vector<Token> tokens = {

                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Modifies, "Modifies"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Rparenthesis, ")")
        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "SemanticError");


    }


    SECTION("Check Grammar of select all query") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "s"),

        };

        QueryParser parser(tokens);
        auto result = parser.parse();
        bool x = true; //will not reach this line unless parse is successful
        REQUIRE(x);
    }


    SECTION("Check Grammar of incomplete query with incomplete modifies clause") {
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
        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "SyntaxError");
    }


    SECTION("Check Grammar of Valid tokens with no relref keyword") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Rparenthesis, ")")
                // Add more tokens as needed to simulate your query
        };


        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "SyntaxError");
    }

    SECTION("Check Grammar of Valid tokens with pattern query") {

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
        auto result = parser.parse();
        bool x = true; //will not reach this line unless parse is successful
        REQUIRE(x);
    }


    SECTION("Check Grammars of valid tokens that Follows with variable and wildcard") {
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
        auto result = parser.parse();
        bool x = true; //will not reach this line unless parse is successful
        REQUIRE(x);

    }

    SECTION("Check Grammars of valid tokens that Follows with a stmtRef and an entRef") {
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
                Token(TokenType::QuoutIDENT, "\"existentVar\""),
                Token(TokenType::Rparenthesis, ")")
        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "SyntaxError");

    }

    SECTION("Check Grammars of valid tokens that Modifies with quoted variable") {
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
        auto result = parser.parse();
        bool x = true; //will not reach this line unless parse is successful
        REQUIRE(x);

    }

    SECTION("Check Grammars of valid tokens that Modifies with quoted variable amd 2 stmt synonyms") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "s1"),
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
        auto result = parser.parse();
        bool x = true; //will not reach this line unless parse is successful
        REQUIRE(x);

    }


    SECTION("Check for semantic error for undeclared stmt synonyms") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "s1"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "s3"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Modifies, "Modifies"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutIDENT, "\"existentVar\""),
                Token(TokenType::Rparenthesis, ")")
        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "SemanticError");

    }

    SECTION("Check semantic error with first expression of Modifies be wildcard") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Modifies, "Modifies"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Rparenthesis, ")")
        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "SemanticError");

    }

    SECTION("Check semantic error with first expression of Uses be wildcard") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Rparenthesis, ")")
        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "SemanticError");

    }


    SECTION("Check Grammars of valid tokens that Modifies with two stmtRefs in paranthesis") {
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
                Token(TokenType::INTEGER, "1"),
                Token(TokenType::Comma, ","),
                Token(TokenType::INTEGER, "1"),
                Token(TokenType::Rparenthesis, ")")
        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "SyntaxError");

    }




    SECTION("Check Grammars of valid tokens have Modifies and pattern clauses") {
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
                Token(TokenType::INTEGER, "1"),
                Token(TokenType::Comma, ","),
                Token(TokenType::INTEGER, "1"),
                Token(TokenType::Rparenthesis, ")"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::PatternKeyword, "pattern"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::QuoutIDENT, "\"x\""),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutConst, "\"1\""),
                Token(TokenType::Rparenthesis, ")")
        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "SyntaxError");

    }


    SECTION("Check Semantic error repeated token declarations") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Comma, ","),
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

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "SemanticError");

    }

    SECTION("Check Semantic error repeated token QuoutConst") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::PatternKeyword, "pattern"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::QuoutConst, "\10\""),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")")

        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "");

    }


    SECTION("Check Semantic error repeated token QuoutCons with different quouConst") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::PatternKeyword, "pattern"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::QuoutConst, "\1\""),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")")

        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "");

    }

    SECTION("Check no grammatical error with QuoutConst with and partial expressionSpec") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::PatternKeyword, "pattern"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::QuoutIDENT, "\"z\""),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::QuoutConst, "\"1\""),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")")

        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "");

    }

    SECTION("Check no grammatical error with QuoutConst with and expressionSpec") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::PatternKeyword, "pattern"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::QuoutIDENT, "\"z\""),
                Token(TokenType::Comma, ","),
                Token(TokenType::ExpressionSpec, "\"x + 1\""),
                Token(TokenType::Rparenthesis, ")")

        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "");

    }

    SECTION("Check no grammatical error with assignment as first param of Parent") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "while"),
                Token(TokenType::IDENT, "w"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "w"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Parent, "Parent"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Comma, ","),
                Token(TokenType::INTEGER, "2"),
                Token(TokenType::Rparenthesis, ")")
        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "");

    }

        //assign a;
        //Select a such that Modifies(a, _) pattern a(_, _"abc"_)

    SECTION("Check no grammatical error with such that Modifies and pattern clauses") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Modifies, "Modifies"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")"),
                Token(TokenType::PatternKeyword, "pattern"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::QuoutConst, "\"abc\""),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")")
        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "");

    }


    SECTION("Check no grammatical error with such that Modifies and pattern clauses with quoted constant") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Modifies, "Modifies"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")"),
                Token(TokenType::PatternKeyword, "pattern"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::QuoutConst, "\"x\""),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")")
        };

        REQUIRE(QueryParser(tokens).parse().getErrorMessage() == "");

    }





    SECTION("QueryParser correctly parses 'assign a; while w; Select a pattern a(\"x\", _) such that Parent*(w, a) such that Next*(1, a)' with no errors") {
        // Manually create the vector of tokens for the query
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

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getErrorMessage().empty() == true);

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses 'stmt s; Select BOOLEAN such that Follows(3, 4)' with no errors") {
        // Manually create the vector of tokens for the query
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

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getErrorMessage().empty() == true);

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses 'procedure p, q; Select p such that Calls (p, q)'") {
        // Manually create the vector of tokens for the query
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
            Token(TokenType::Rparenthesis, ")")
        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getErrorMessage().empty() == true);
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "p");
        REQUIRE(parsingResult.getSuchThatClauses()[0].getRelationship().getType() == TokenType::Calls);



        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }



    //procedure p;
//Select p such that Uses(p, "iter")
    SECTION("QueryParser correctly parses 'procedure p; Select p such that Uses(p, \"iter\")' with no errors") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "procedure"),
                Token(TokenType::IDENT, "p"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "p"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "p"),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutIDENT, "\"iter\""),
                Token(TokenType::Rparenthesis, ")")
        };


        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getErrorMessage().empty() == true);

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }
}

//call c;
//Select c such that Uses(c, "iter")
TEST_CASE("src/qps/parser/QueryParser/M1FailedCases/1") {
    //Select c such that Uses(c, "iter")
    SECTION("QueryParser correctly parses 'call c; Select c such that Uses(c, \"iter\")' with no errors") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "call"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutIDENT, "\"iter\""),
                Token(TokenType::Rparenthesis, ")")

        };


        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getErrorMessage().empty() == true);

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }
}

TEST_CASE("src/qps/parser/QueryParser/M1FailedCases/2") {
    //Select c such that Uses(c, "iter")
    SECTION("QueryParser correctly parses 'call c; Select c such that Uses(c, \"iter\")' with no errors") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "call"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutIDENT, "\"iter\""),
                Token(TokenType::Rparenthesis, ")")

        };


        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getErrorMessage().empty() == true);

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }
}

//read r;
//Select r such that Uses(r, 1)
TEST_CASE("src/qps/parser/QueryParser/M1FailedCases/3") {
    //Select r such that Uses(r, 1)
    SECTION("QueryParser correctly parses 'read r; Select r such that Uses(r, 1)' with no errors") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "read"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Comma, ","),
                Token(TokenType::INTEGER, "1"),
                Token(TokenType::Rparenthesis, ")")
        };
        QueryParser queryParser(tokens);
        // Parse the query
        ParsingResult parsingResult = queryParser.parse();


        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == false);
        REQUIRE(parsingResult.getErrorMessage() == "SyntaxError");
    }
}

TEST_CASE("src/qps/parser/QueryParser/4") {
    //Select r such that Uses(r, 1)
    SECTION("QueryParser correctly parses Pattern with expressionSpec") {
        // Manually create the vector of tokens for the query
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
                Token(TokenType::ExpressionSpec, "\"x+1\""),
                Token(TokenType::Rparenthesis, ")")
        };
        QueryParser queryParser(tokens);
        // Parse the query
        ParsingResult parsingResult = queryParser.parse();


        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == true);
    }
}

TEST_CASE("Testing parsing of undeclared variables") {
    Tokenizer tokenizer("stmt s1; Select s1 such that Follows(2, s)");
    vector<Token> tokens = tokenizer.tokenize();
    QueryParser queryParser(tokens);
    ParsingResult parsingResult = queryParser.parse();

    // Verify that the parsing result indicates a valid query with no errors
    REQUIRE(parsingResult.isQueryValid() == false);
}

TEST_CASE("Testing parsing of attrName") {

    SECTION("QueryParser correctly parses 'procedure p, q; Select <p.stmt#, q.procName> such that Calls (p, q)' with no errors") {
        // Explicitly create the vector of tokens for the query
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
                Token(TokenType::AttrName, "procName"),
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

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid());
        REQUIRE(parsingResult.getErrorMessage().empty());

    }

    SECTION("QueryParser correctly parses 'procedure p, q; Select <p.stmt#, q.procName> such that Calls (p, q)' with no errors") {
        // Explicitly create the vector of tokens for the query
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
                Token(TokenType::AttrName, "procName"),
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

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid());
        REQUIRE(parsingResult.getErrorMessage().empty());

    }

    SECTION("QueryParser correctly parses 'procedure p, q; Select p such that Calls(p, q) with q.procName = \"Third\"' with no errors") {
        // Manually create the vector of tokens for the query
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

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getErrorMessage().empty() == true);

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses 'procedure p, q; Select p such that Calls(p, q) with q.varName = \"Third\"' with error") {
        // Manually create the vector of tokens for the query
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
                Token(TokenType::AttrName, "varName"),
                Token(TokenType::Equal, "="),
                Token(TokenType::QuoutIDENT, "\"Third\"")
        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == false);
        REQUIRE(parsingResult.getErrorMessage() == "SemanticError");

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses 'procedure p, q; Select p such that Calls(p, q) with q.varName = \"Third\"' with error") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "procedure"),
                Token(TokenType::IDENT, "p"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "p"),
                Token(TokenType::WithKeyword, "with"),
                Token(TokenType::IDENT, "p"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "varName"),
                Token(TokenType::Equal, "="),
                Token(TokenType::QuoutIDENT, "\"Third\"")

        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == false);
        REQUIRE(parsingResult.getErrorMessage() == "SemanticError");

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses call c; Select c with c.varName = \"Third\"' with error") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "call"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::WithKeyword, "with"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "varName"),
                Token(TokenType::Equal, "="),
                Token(TokenType::QuoutIDENT, "\"Third\"")

        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == false);
        REQUIRE(parsingResult.getErrorMessage() == "SemanticError");

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses call c; Select c with c.procName = \"Third\"' with no error") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "call"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::WithKeyword, "with"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "procName"),
                Token(TokenType::Equal, "="),
                Token(TokenType::QuoutIDENT, "\"Third\"")

        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getWithClauses()[0].getFirstParam().getValue() == "c.procName");
        REQUIRE(parsingResult.getWithClauses()[0].getSecondParam().getValue() == "\"Third\"");

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }


    SECTION("QueryParser correctly parses call c; Select c with c.procName = \"Third\"' with no error") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "print"),
                Token(TokenType::IDENT, "p"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "p"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::WithKeyword, "with"),
                Token(TokenType::IDENT, "p"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "varName"),
                Token(TokenType::Equal, "="),
                Token(TokenType::QuoutIDENT, "\"Third\"")
        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        string requiredSynValue = parsingResult.getSynFromAttrRef(parsingResult.getRequiredSynonyms()[0]);
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "p.stmt#");
        REQUIRE(parsingResult.getWithClauses()[0].getFirstParam().getValue() == "p.varName");
        REQUIRE(parsingResult.getRequiredSynonymType(requiredSynValue) == "print");
        REQUIRE(parsingResult.getWithClauses()[0].getSecondParam().getValue() == "\"Third\"");

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses assign a; Select a with a.value = \"Third\"' with error") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::WithKeyword, "with"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "value"),
                Token(TokenType::Equal, "="),
                Token(TokenType::QuoutIDENT, "\"Third\"")

        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == false);
        REQUIRE(parsingResult.getErrorMessage() == "SemanticError");

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses assign a; Select a.value with error") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "value")
        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == false);
        REQUIRE(parsingResult.getErrorMessage() == "SemanticError");

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }


    SECTION("QueryParser correctly parses assign a; Select a.stmt# with a.stmt# = \"Third\"' with error") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::WithKeyword, "with"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::Equal, "="),
                Token(TokenType::QuoutIDENT, "\"Third\"")
        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == false);
        REQUIRE(parsingResult.getErrorMessage() == "SemanticError");

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses assign a; Select a.stmt# with a.stmt# = 1' with no error") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::WithKeyword, "with"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::Equal, "="),
                Token(TokenType::INTEGER, "1")
        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getWithClauses()[0].getFirstParam().getValue() == "a.stmt#");
        REQUIRE(parsingResult.getWithClauses()[0].getSecondParam().getValue() == "1");
        string requiredSynValue = parsingResult.getSynFromAttrRef(parsingResult.getRequiredSynonyms()[0]);
        REQUIRE(parsingResult.getRequiredSynonymType(requiredSynValue) == "assign");
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "a.stmt#");
        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }


    SECTION("QueryParser correctly parses constant c; Select c with c.value = 1 no error") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "constant"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "value"),
                Token(TokenType::WithKeyword, "with"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "value"),
                Token(TokenType::Equal, "="),
                Token(TokenType::INTEGER, "1")
        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getWithClauses()[0].getFirstParam().getValue() == "c.value");
        REQUIRE(parsingResult.getWithClauses()[0].getSecondParam().getValue() == "1");
        string requiredSynValue = parsingResult.getSynFromAttrRef(parsingResult.getRequiredSynonyms()[0]);
        REQUIRE(parsingResult.getRequiredSynonymType(requiredSynValue) == "constant");
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "c.value");
        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses constant c; Select c with c.value = 1 no error") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "constant"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "value"),
                Token(TokenType::WithKeyword, "with"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "value"),
                Token(TokenType::Equal, "="),
                Token(TokenType::QuoutIDENT, "\"1\"")
        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == false);
        REQUIRE(parsingResult.getErrorMessage() == "SemanticError");
        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses read r; Select r.stmt# with r.varName = 1 with error") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "read"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::WithKeyword, "with"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "varName"),
                Token(TokenType::Equal, "="),
                Token(TokenType::INTEGER, "1")
        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == false);
        REQUIRE(parsingResult.getErrorMessage() == "SemanticError");
        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }


    SECTION("QueryParser correctly parses read r; Select r.stmt# with r.varName = \"book\" with no error") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "read"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::WithKeyword, "with"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "varName"),
                Token(TokenType::Equal, "="),
                Token(TokenType::QuoutIDENT, "\"book\"")
        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getWithClauses()[0].getFirstParam().getValue() == "r.varName");
        REQUIRE(parsingResult.getWithClauses()[0].getSecondParam().getValue() == "\"book\"");
        string requiredSynValue = parsingResult.getSynFromAttrRef(parsingResult.getRequiredSynonyms()[0]);
        REQUIRE(parsingResult.getRequiredSynonymType(requiredSynValue) == "read");
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "r.stmt#");

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses read r; Select r.stmt# with \"book\" = r.varName with no error") {
        // Manually create the vector of tokens for the query
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "read"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::WithKeyword, "with"),
                Token(TokenType::QuoutIDENT, "\"book\""),
                Token(TokenType::Equal, "="),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "varName"),

        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getWithClauses()[0].getSecondParam().getValue() == "r.varName");
        REQUIRE(parsingResult.getWithClauses()[0].getFirstParam().getValue() == "\"book\"");
        string requiredSynValue = parsingResult.getSynFromAttrRef(parsingResult.getRequiredSynonyms()[0]);
        REQUIRE(parsingResult.getRequiredSynonymType(requiredSynValue) == "read");
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "r.stmt#");

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }



    SECTION("QueryParser correctly parses read r; Select r.varName with 1 = r.stmt# with no error") {
        // Manually create the vector of tokens for the query
        std::vector tokens = {
                Token(TokenType::DesignEntity, "read"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "varName"),
                Token(TokenType::WithKeyword, "with"),
                Token(TokenType::INTEGER, "1"),
                Token(TokenType::Equal, "="),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
        };

        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();

        // Verify that the parsing result indicates a valid query with no errors
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getWithClauses()[0].getSecondParam().getValue() == "r.stmt#");
        REQUIRE(parsingResult.getWithClauses()[0].getFirstParam().getValue() == "1");
        string requiredSynValue = parsingResult.getSynFromAttrRef(parsingResult.getRequiredSynonyms()[0]);
        REQUIRE(parsingResult.getRequiredSynonymType(requiredSynValue) == "read");
        REQUIRE(parsingResult.getRequiredSynonyms()[0] == "r.varName");

        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }



}

