
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
    clause.setRelationship(Token(TokenType::Uses, "Uses"));
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
        std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{"2"});

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
        std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{"SemanticError"});
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
        std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{"1", "2", "3", "4"});
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
        std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{"y"});
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
        std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{"x", "y", "z"});
    }
}
