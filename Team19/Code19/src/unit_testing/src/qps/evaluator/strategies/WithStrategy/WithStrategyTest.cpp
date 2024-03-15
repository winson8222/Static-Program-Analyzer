#include "catch.hpp"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"
#include <filesystem>
#include <fstream>
#include <memory>

#include "sp/SourceProcessor.h"

// Test suite for evaluating integration between Parent*, Pattern, and Follows clauses
TEST_CASE("src/qps/evaluator/WithStrategy/WithStrategyTest/1") {
    // Setup shared PKBManager and related components for use in test cases
    auto pkbManager = std::make_shared<PKBManager>();
    auto pkbReaderManager = pkbManager->getPKBReaderManager();
    auto pkbWriterManager = pkbManager->getPKBWriterManager();
    auto statementWriter = pkbWriterManager->getStatementWriter();
    auto parentTWriter = pkbWriterManager->getParentTWriter();
    auto whileWriter = pkbWriterManager->getWhileWriter();
    auto assignWriter = pkbWriterManager->getAssignWriter();
    auto assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    auto ifWriter = pkbWriterManager->getIfWriter();
    auto followsWriter = pkbWriterManager->getFollowsWriter();
    std::shared_ptr<CallsWriter> CallsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignWriter->insertAssign(1);

    CallsWriter->addCalls("proc1", "proc3");
    CallsWriter->addCalls("proc2", "proc4");
    CallsWriter->addCalls("proc4", "proc1");
    CallsTWriter->addCallsT("proc4", "proc3");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");

    // Test case for evaluating a simple Parent* query with an assignment pattern
    SECTION("Check Evaluation result of a with clause and procname ") {

        Tokenizer tokenizer("procedure p, q; Select p such that Calls(p, q) with q.procName = \"proc3\"");
        vector<Token> tokens = tokenizer.tokenize();

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> actualResults = evaluator.evaluateQuery();
        std::unordered_set<string> expectedResults = { "proc1" };
        REQUIRE(actualResults == expectedResults);

    }

    // Test case for evaluating a simple Parent* query with an assignment pattern
    SECTION("Check Evaluation result of BOOLEAN  with clause") {

        Tokenizer tokenizer("Select BOOLEAN with 1 = 1");
        vector<Token> tokens = tokenizer.tokenize();

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> actualResults = evaluator.evaluateQuery();
        std::unordered_set<string> expectedResults = { "TRUE" };
        REQUIRE(actualResults == expectedResults);

    }

    // Test case for evaluating a simple Parent* query with an assignment pattern
    SECTION("Check Evaluation result of a with clause with select all statements") {

        Tokenizer tokenizer("stmt s; Select s with 2 = 2");
        vector<Token> tokens = tokenizer.tokenize();

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> actualResults = evaluator.evaluateQuery();
        std::unordered_set<string> expectedResults = { "1", "2", "3"};
        REQUIRE(actualResults == expectedResults);

    }

    // Test case for evaluating a simple Parent* query with an assignment pattern
    SECTION("Check Evaluation result of a with clause and procname ") {

        Tokenizer tokenizer("Select BOOLEAN with \"q\" = \"s\"");
        vector<Token> tokens = tokenizer.tokenize();

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> actualResults = evaluator.evaluateQuery();
        std::unordered_set<string> expectedResults = { "FALSE" };
        REQUIRE(actualResults == expectedResults);

    }

    // Test case for evaluating a simple Parent* query with an assignment pattern
    SECTION("Check Evaluation result of a with clause on attribute stmt#") {

        Tokenizer tokenizer("stmt s; assign a; Select s with s.stmt# = a.stmt#");
        vector<Token> tokens = tokenizer.tokenize();

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> actualResults = evaluator.evaluateQuery();
        std::unordered_set<string> expectedResults = { "1" };
        REQUIRE(actualResults == expectedResults);

    }

    

}

