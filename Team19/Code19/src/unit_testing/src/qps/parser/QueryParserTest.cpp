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


    SECTION("Check Grammars of Pattern with variable and constant") {
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

    SECTION("Check Grammars of Pattern with variable and an expressionSpec") {
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
                Token(TokenType::DoubleQuote, "\""),
                Token(TokenType::INTEGER, "1"),
                Token(TokenType::Operator, "*"),
                Token(TokenType::INTEGER, "3"),
                Token(TokenType::DoubleQuote, "\""),
                Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto result = parser.parse();
        bool x = true; //will not reach this line unless parse is successful
        REQUIRE(x);
    }

    SECTION("Check Grammars of Pattern with variable and an expressionSpec that contains an expression of _\"expr\"_ format") {
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
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::DoubleQuote, "\""),
                Token(TokenType::INTEGER, "1"),
                Token(TokenType::Operator, "*"),
                Token(TokenType::INTEGER, "3"),
                Token(TokenType::DoubleQuote, "\""),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto result = parser.parse();
        bool x = true; //will not reach this line unless parse is successful
        REQUIRE(x);

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

    // Instantiate the QueryParser with the tokens
    QueryParser queryParser(tokens);

    // Parse the query
    ParsingResult parsingResult = queryParser.parse();

    // Verify that the parsing result indicates a valid query with no errors
    REQUIRE(parsingResult.isQueryValid());
    REQUIRE(parsingResult.getErrorMessage().empty());

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
        REQUIRE(parsingResult.isQueryValid() == true);
        REQUIRE(parsingResult.getErrorMessage().empty() == true);
    }
}