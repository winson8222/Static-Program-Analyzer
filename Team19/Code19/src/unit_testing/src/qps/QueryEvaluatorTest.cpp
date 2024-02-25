#include "../../spa/src/qps/parser/QueryParser.h"
#include "../../spa/src/pkb/PKBManager.h"
#include "../../spa/src/qps/evaluator/QueryEvaluator.h"
#include "catch.hpp"

using namespace std;
// Test for Parsing Result assuming that the query is valid
//TEST_CASE("Check Evaluation result of a simple select all query") {
//    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
//    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
//    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
//
//    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
//    statementWriter->insertStatement(1);
//    statementWriter->insertStatement(2);
//    statementWriter->insertStatement(3);
//
//
//    std::vector<Token> tokens = {
//            Token(TokenType::DesignEntity, "stmt"),
//            Token(TokenType::IDENT, "s"),
//            Token(TokenType::Semicolon, ";"),
//            Token(TokenType::SelectKeyword, "Select"),
//            Token(TokenType::IDENT, "s"),
//
//    };
//
//    QueryParser parser(tokens);
//    auto parsingResult = parser.parse();
//    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
//    std::vector<string> res = evaluator.evaluateQuery();
//    REQUIRE((res == std::vector<string>{ "3", "2", "1" } || res == std::vector<string>{"1", "2", "3"}));
//
//}


TEST_CASE("Check Evaluation result of a simple select pattern assign query") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignPatternWriter->addAssignPattern(1, "x", "1");
    assignPatternWriter->addAssignPattern(2, "x", "2");
    assignPatternWriter->addAssignPattern(3, "x", "3");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);


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
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::vector<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::vector<string>{ "1" });

}

TEST_CASE("Check Evaluation result of a select pattern query with variable") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignPatternWriter->addAssignPattern(1, "y", "1");
    assignPatternWriter->addAssignPattern(2, "x", "y");
    assignPatternWriter->addAssignPattern(3, "x", "3");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);

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
            Token(TokenType::QuoutIDENT, "\"y\""),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::vector<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::vector<string>{ "2" });

}

TEST_CASE("Check Evaluation result of a select pattern query with wildcard on RHS") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignPatternWriter->addAssignPattern(1, "y", "1");
    assignPatternWriter->addAssignPattern(2, "x", "y");
    assignPatternWriter->addAssignPattern(3, "x", "3");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);


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
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::vector<string> res = evaluator.evaluateQuery();

    REQUIRE((res == std::vector<string>{ "3", "2" } || res == std::vector<string>{"2", "3"}));

}

TEST_CASE("Check Evaluation result of a select pattern query with wildcard on RHS and LHS") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignPatternWriter->addAssignPattern(1, "y", "1");
    assignPatternWriter->addAssignPattern(2, "x", "y");
    assignPatternWriter->addAssignPattern(3, "x", "3");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);


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
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::vector<string> res = evaluator.evaluateQuery();
    REQUIRE((res == std::vector<string>{ "3", "2", "1" } || res == std::vector<string>{"1", "2", "3"}));

}

TEST_CASE("Check Evaluation result of a select pattern query with wildcard on LHS") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std:shared_ptr<AssignPatternReader> assignPatternReader = pkbReaderManager->getAssignPatternReader();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignPatternWriter->addAssignPattern(1, "y", "1");
    assignPatternWriter->addAssignPattern(2, "x", "y");
    assignPatternWriter->addAssignPattern(3, "x", "3");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);

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
            Token(TokenType::QuoutIDENT, "\"y\""),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::vector<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::vector<string>{ "2" });

}

TEST_CASE("Check Evaluation result of a select variable query with assign pattern query with synonym on LHS") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std:shared_ptr<AssignPatternReader> assignPatternReader = pkbReaderManager->getAssignPatternReader();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignPatternWriter->addAssignPattern(1, "y", "1");
    assignPatternWriter->addAssignPattern(2, "x", "y");
    assignPatternWriter->addAssignPattern(3, "x", "3");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::DesignEntity, "variable"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Comma, ","),
            Token(TokenType::QuoutIDENT, "\"y\""),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::vector<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::vector<string>{ "x" });

}

TEST_CASE("Check Evaluation result of a select variable query with assign pattern query with synonym on LHS and wild card on RHS") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std:shared_ptr<AssignPatternReader> assignPatternReader = pkbReaderManager->getAssignPatternReader();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignPatternWriter->addAssignPattern(1, "y", "1");
    assignPatternWriter->addAssignPattern(2, "x", "y");
    assignPatternWriter->addAssignPattern(3, "x", "3");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::DesignEntity, "variable"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::vector<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::vector<string>{ "x", "y" });

}