
#include "catch.hpp"
#include "qps/evaluator/suchThatStrategies/UsesStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"
#include "../../spa/src/qps/parser/QueryParser.h"
#include "../../spa/src/pkb/PKBManager.h"
#include "../../spa/src/qps/evaluator/QueryEvaluator.h"

// Helper function for creating a ParsingResult tailored for Uses tests
ParsingResult createParsingResultForUses(const std::string& entity, const std::string& variable, bool isProcedure) {
    ParsingResult parsingResult;
    parsingResult.setSuchThatClauseRelationship(Token(TokenType::Uses, "Uses"));
    TokenType entityType = isProcedure ? TokenType::IDENT : TokenType::INTEGER;
    parsingResult.setSuchThatClauseFirstParam(Token(entityType, entity));
    parsingResult.setSuchThatClauseSecondParam(Token(TokenType::IDENT, variable));
    return parsingResult;
}

TEST_CASE("src/qps/evaluator/suchThatStrategies/UsesStrategy") {
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