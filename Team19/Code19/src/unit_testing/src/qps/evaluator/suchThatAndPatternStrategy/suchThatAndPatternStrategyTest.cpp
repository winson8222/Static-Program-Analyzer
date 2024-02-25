#include "catch.hpp"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"
// Including necessary headers for testing

// Test case for evaluating Parent* query with assignment pattern
TEST_CASE("src/qps/evaluator/ParentTAndAssignPatternEvaluation") {

    SECTION("Check Evaluation result of a simple select Parent* query ") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

        std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
        std::shared_ptr<ParentTWriter> parentTWriter = pkbWriterManager->getParentTWriter();
        std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
        std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
        std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();


        statementWriter->insertStatement(1);
        statementWriter->insertStatement(2);
        statementWriter->insertStatement(3);
        whileWriter->insertWhile(1);
        whileWriter->insertWhile(3);
        assignWriter->insertAssign(2);
        assignWriter->insertAssign(4);
        assignPatternWriter->addAssignPattern(2, "x", "1 + x");
        assignPatternWriter->addAssignPattern(4, "x", "2 + x");
        parentTWriter->addParentT(1, 2);
        parentTWriter->addParentT(3, 4);





        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "while"),
                Token(TokenType::IDENT, "w"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "w"),
                Token(TokenType::PatternKeyword, "pattern"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::QuoutConst, "\"1\""),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::ParentT, "Parent*"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "w"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{ "1" });

    }


    SECTION("Check Evaluation result of a simple select Parent* query + adding ifs ") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

        std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
        std::shared_ptr<ParentTWriter> parentTWriter = pkbWriterManager->getParentTWriter();
        std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
        std::shared_ptr<IfWriter> ifWriter = pkbWriterManager->getIfWriter();
        std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
        std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();


        statementWriter->insertStatement(1);
        statementWriter->insertStatement(2);
        statementWriter->insertStatement(3);
        statementWriter->insertStatement(4);
        statementWriter->insertStatement(5);
        statementWriter->insertStatement(6);
        whileWriter->insertWhile(1);
        whileWriter->insertWhile(3);
        assignWriter->insertAssign(2);
        assignWriter->insertAssign(4);
        ifWriter->insertIf(5);
        assignPatternWriter->addAssignPattern(2, "x", "1 + x");
        assignPatternWriter->addAssignPattern(4, "x", "2 + x");
        assignPatternWriter->addAssignPattern(6, "x", "1 + x");
        parentTWriter->addParentT(1, 2);
        parentTWriter->addParentT(1, 6);
        parentTWriter->addParentT(3, 4);
        parentTWriter->addParentT(5,6);





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
                Token(TokenType::ParentT, "Parent*"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "w"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Rparenthesis, ")"),
                Token(TokenType::PatternKeyword, "pattern"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::QuoutConst, "\"1\""),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")"),

        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{ "1" });

    }
}
