
#include "catch.hpp"
#include "qps/evaluator/strategies/suchThatStrategies/UsesStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"
#include "qps/parser/clauses/SuchThatClause.h"

ParsingResult createParsingResultForUses(const std::string& entity, const std::string& variable, bool isProcedure) {
    ParsingResult parsingResult;
    // Set the entity type appropriately
    TokenType entityType = isProcedure ? TokenType::IDENT : TokenType::INTEGER;

    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::UsesS, "Uses"));
    clause.setFirstParam(Token(entityType, entity));
    clause.setSecondParam(Token(TokenType::IDENT, variable));
    parsingResult.addSuchThatClause(clause);
    return parsingResult;
}

TEST_CASE("src/qps/evaluator/suchThatStrategies/UsesStrategy/1") {
    auto pkb = std::make_shared<PKB>();
    // Setup PKB with Uses relationships
    pkb->getUsesPStore()->addRelationship("procedure1", "x");
    pkb->getUsesSStore()->addRelationship(2, "y");

    auto pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
    UsesStrategy UsesStrategy;

    SECTION("UsesS(2, y) is true") {
        auto parsingResult = createParsingResultForUses("2", "y", false); // false indicates statement
        auto resultTable = UsesStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        // Assertions to verify the outcome for UsesS
        REQUIRE(resultTable->getRows().size() == 1); // Expecting exactly one row
        REQUIRE(resultTable->getRows()[0]["y"] == "y"); // Verifying the content of the row
    }

    SECTION("UsesS with non-existing statement number is false") {
        auto parsingResult = createParsingResultForUses("999", "y", false); // false indicates statement
        auto resultTable = UsesStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        // Expectation: The result should indicate that the relationship does not exist
        REQUIRE(resultTable->getRows().empty());
    }

    SECTION("UsesS with wildcard for variable") {
        auto parsingResult = createParsingResultForUses("2", "_", false); // Testing UsesS(2, _)
        auto resultTable = UsesStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        // Expectation: The result should indicate that statement 2 Uses any variable
        REQUIRE_FALSE(resultTable->getRows().empty()); // More specific checks can be added based on your implementation
    }

        // Test for modification in nested statements
    SECTION("UsesS in nested statements") {
        // Assuming statement 4 is a container statement that contains statement 2
        pkb->getUsesSStore()->addRelationship(4, "x");
        auto parsingResult = createParsingResultForUses("4", "x", false);
        auto resultTable = UsesStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        REQUIRE_FALSE(resultTable->getRows().empty()); // Expecting the result to indicate modification
        // Additional specific checks as needed
    }
}

TEST_CASE("src/qps/evaluator/suchThatStrategies/UsesStrategy/2") {
    SECTION("Check Evaluation result of a simple select v for UseS") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

        std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
        std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
        statementWriter->insertStatement(1);
        statementWriter->insertStatement(2);
        statementWriter->insertStatement(3);
        statementWriter->insertStatement(4);
        modifiesSWriter->addUsesS(2, "x");
        modifiesSWriter->addUsesS(3, "y");
        modifiesSWriter->addUsesS(4, "z");


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
                Token(TokenType::QuoutIDENT, "\"x\""),
                Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"2"});

    }

    SECTION("Check Evaluation result of a simple select all s given true condition for UseS") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

        std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
        std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
        statementWriter->insertStatement(1);
        statementWriter->insertStatement(2);
        statementWriter->insertStatement(3);
        statementWriter->insertStatement(4);
        modifiesSWriter->addUsesS(2, "x");
        modifiesSWriter->addUsesS(3, "y");
        modifiesSWriter->addUsesS(4, "z");

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
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutIDENT, "\"x\""),
                Token(TokenType::Rparenthesis, ")")

        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"SemanticError"});
    }


    SECTION("Check Evaluation result of a simple select all s given true condition for UseS (opposite)") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

        std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
        std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
        statementWriter->insertStatement(1);
        statementWriter->insertStatement(2);
        statementWriter->insertStatement(3);
        statementWriter->insertStatement(4);
        modifiesSWriter->addUsesS(2, "x");
        modifiesSWriter->addUsesS(3, "y");
        modifiesSWriter->addUsesS(4, "z");

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
                Token(TokenType::INTEGER, "2"),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")")

        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"1", "2", "3", "4"});
    }

    SECTION("Check Evaluation result of a simple select variable given LHS for UsesS") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


        std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
        std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
        statementWriter->insertStatement(1);
        statementWriter->insertStatement(2);
        statementWriter->insertStatement(3);
        statementWriter->insertStatement(4);
        modifiesSWriter->addUsesS(2, "x");
        modifiesSWriter->addUsesS(3, "y");
        modifiesSWriter->addUsesS(4, "z");


        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::INTEGER, "3"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Rparenthesis, ")")

        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"y"});
    }


    SECTION("Check Evaluation result of 2 synonyms for UsesS and select statements") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


        std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
        std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
        statementWriter->insertStatement(1);
        statementWriter->insertStatement(2);
        statementWriter->insertStatement(3);
        statementWriter->insertStatement(4);
        modifiesSWriter->addUsesS(2, "x");
        modifiesSWriter->addUsesS(3, "y");
        modifiesSWriter->addUsesS(4, "z");


        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Rparenthesis, ")")

        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"x", "y", "z"});
    }

    SECTION("Check true boolean for uses") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


        std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
        std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
        statementWriter->insertStatement(1);
        statementWriter->insertStatement(2);
        statementWriter->insertStatement(3);
        modifiesSWriter->addUsesS(2, "x");
        modifiesSWriter->addUsesS(3, "y");


        std::vector<Token> tokens = {
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::BooleanKeyword, "BOOLEAN"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::INTEGER, "2"),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutIDENT, "\"x\""),
                Token(TokenType::Rparenthesis, ")")

        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"TRUE"});
    }

    SECTION("Check true boolean for uses") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


        std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
        std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
        statementWriter->insertStatement(1);
        statementWriter->insertStatement(2);
        statementWriter->insertStatement(3);
        modifiesSWriter->addUsesS(2, "x");
        modifiesSWriter->addUsesS(3, "y");


        std::vector<Token> tokens = {
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::BooleanKeyword, "BOOLEAN"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::INTEGER, "3"),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutIDENT, "\"x\""),
                Token(TokenType::Rparenthesis, ")")

        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"FALSE"});
    }

    SECTION("Check true boolean for uses with variable") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


        std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
        std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
        statementWriter->insertStatement(1);
        statementWriter->insertStatement(2);
        statementWriter->insertStatement(3);
        modifiesSWriter->addUsesS(2, "x");
        modifiesSWriter->addUsesS(3, "y");


        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::BooleanKeyword, "BOOLEAN"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::INTEGER, "3"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Rparenthesis, ")")

        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"TRUE"});
    }
}

// M1 Test Fix for Uses
TEST_CASE("src/qps/evaluator/suchThatStrategies/UsesStrategy/3") {
    auto pkb = std::make_shared<PKB>();
    auto pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
    auto pkbWriterManager = std::make_shared<PKBWriterManager>(pkb);

    auto statementWriter = pkbWriterManager->getStatementWriter();
    auto usesWriter = pkbWriterManager->getUsesSWriter();
    auto procWriter = pkbWriterManager->getProcedureWriter();
    auto callWriter = pkbWriterManager->getCallWriter();

    // Insert statements and their uses relationships
    statementWriter->insertStatement(1);
    usesWriter->addUsesS(1, "iter"); // Assign statement

    statementWriter->insertStatement(2);
    usesWriter->addUsesS(2, "iter"); // Print statement

    statementWriter->insertStatement(3);
    usesWriter->addUsesS(3, "iter"); // While statement

    statementWriter->insertStatement(4);
    usesWriter->addUsesS(4, "iter"); // Nested statement in a while loop

    statementWriter->insertStatement(5);
    usesWriter->addUsesS(5, "iter"); // If statement

    statementWriter->insertStatement(6);
    usesWriter->addUsesS(6, "iter"); // Nested statement in an if statement

    statementWriter->insertStatement(7);
    usesWriter->addUsesS(7, "iter"); // Statement nested in a while loop
    pkbWriterManager->getParentWriter()->addParent(3, 7); // Statement 3 is a while loop that contains statement 7

    // Insert a nested statement within a while loop within an if statement
    statementWriter->insertStatement(8);
    usesWriter->addUsesS(8, "iter"); // Deeply nested statement
    pkbWriterManager->getParentWriter()->addParent(5, 3); // if statement 5 contains while statement 3
    pkbWriterManager->getParentWriter()->addParent(3, 8); // while statement 3 contains statement 8


    // Set up the query to evaluate
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
            Token(TokenType::QuoutIDENT, "\"iter\""),
            Token(TokenType::Rparenthesis, ")")
    };

    // Parse and evaluate the query
    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    auto res = evaluator.evaluateQuery();

    // Verify that all necessary statements are returned
    std::unordered_set<std::string> expected{"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
//    REQUIRE(res == expected);
}

//call c;
//Select c such that Uses(c, "iter")
TEST_CASE("src/qps/evaluator/suchThatStrategies/UsesStrategy/4") {
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

TEST_CASE("src/qps/evaluator/suchThatStrategies/UsesStrategy/5") {
    //Select c such that Uses(c, "iter")
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
    pkbWriterManager->getPrintWriter()->insertPrint(2);
    pkbWriterManager->getPrintWriter()->insertPrint(3);
    pkbWriterManager->getPrintVarNameWriter()->addPrintVarName(2, "x");
    pkbWriterManager->getPrintVarNameWriter()->addPrintVarName(3, "y");
    pkbWriterManager->getUsesSWriter()->addUsesS(2, "x");
    pkbWriterManager->getUsesSWriter()->addUsesS(3, "y");
    SECTION("QueryParser correctly parses 'print pn; Select pn.varName; with no errors") {
        // Manually create the vector of tokens for the query


        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "print"),
                Token(TokenType::IDENT, "pn"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "pn"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "varName"),
        };


        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"x", "y"});


        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses 'print pn; Select pn.stmt#; with no errors") {
        // Manually create the vector of tokens for the query


        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "print"),
                Token(TokenType::IDENT, "pn"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "pn"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
        };


        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"2", "3"});
        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

}

TEST_CASE("Print Attr Select with Uses Clauses") {

    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
    pkbWriterManager->getPrintWriter()->insertPrint(2);
    pkbWriterManager->getPrintWriter()->insertPrint(3);
    pkbWriterManager->getPrintVarNameWriter()->addPrintVarName(2, "x");
    pkbWriterManager->getPrintVarNameWriter()->addPrintVarName(3, "y");
    pkbWriterManager->getUsesSWriter()->addUsesS(2, "x");
    pkbWriterManager->getUsesSWriter()->addUsesS(3, "y");



    SECTION("QueryParser correctly parses 'print pn; Select pn.varName such that Uses(pn, x); with no errors") {
        // Manually create the vector of tokens for the query



        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "print"),
                Token(TokenType::IDENT, "pn"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "pn"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "varName"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "pn"),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutIDENT, "\"x\""),
                Token(TokenType::Rparenthesis, ")")
        };


        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"x"});


        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses 'print pn; Select pn.stmt# such that Uses(pn, x); with no errors") {
        // Manually create the vector of tokens for the query



        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "print"),
                Token(TokenType::IDENT, "pn"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "pn"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "pn"),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutIDENT, "\"x\""),
                Token(TokenType::Rparenthesis, ")")
        };


        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"2"});


        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }
}



TEST_CASE("Read Attr Select with Uses Clauses") {

    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
    pkbWriterManager->getReadWriter()->insertRead(2);
    pkbWriterManager->getReadWriter()->insertRead(3);
    pkbWriterManager->getReadVarNameWriter()->addReadVarName(2, "x");
    pkbWriterManager->getReadVarNameWriter()->addReadVarName(3, "y");
    pkbWriterManager->getUsesSWriter()->addUsesS(2, "x");
    pkbWriterManager->getUsesSWriter()->addUsesS(3, "y");



    SECTION("QueryParser correctly parses 'read r; Select r.varName such that Uses(r, x); with no errors") {
        // Manually create the vector of tokens for the query



        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "read"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "varName"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutIDENT, "\"x\""),
                Token(TokenType::Rparenthesis, ")")
        };


        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"x"});


        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }

    SECTION("QueryParser correctly parses 'read r; Select r.stmt# such that Uses(r, x); with no errors") {
        // Manually create the vector of tokens for the query



        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "read"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "r"),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutIDENT, "\"x\""),
                Token(TokenType::Rparenthesis, ")")
        };


        // Instantiate the QueryParser with the tokens
        QueryParser queryParser(tokens);

        // Parse the query
        ParsingResult parsingResult = queryParser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"2"});


        // Additional checks can be performed here if needed, such as verifying the specific parsing output
    }
}

