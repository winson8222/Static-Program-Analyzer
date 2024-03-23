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
    auto constantWriter = pkbWriterManager->getConstantWriter();

    auto readWriter = pkbWriterManager->getReadWriter();
    auto printWriter = pkbWriterManager->getPrintWriter();
    auto callWriter = pkbWriterManager->getCallWriter();
    auto readVarWriter = pkbWriterManager->getReadVarNameWriter();
    auto printVarWriter = pkbWriterManager->getPrintVarNameWriter();
    auto callProcWriter = pkbWriterManager->getCallProcNameWriter();
    auto constantReader = pkbReaderManager->getConstantReader();
    std::shared_ptr<CallsWriter> CallsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    statementWriter->insertStatement(5);
    assignWriter->insertAssign(1);
    constantWriter->insertConstant(0);
    

    CallsWriter->addCalls("proc1", "proc3");
    CallsWriter->addCalls("proc2", "proc4");
    CallsWriter->addCalls("proc4", "proc1");
    CallsTWriter->addCallsT("proc4", "proc3");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");

    readWriter->insertRead(4);
    readVarWriter->addReadVarName(4, "x");
    readWriter->insertRead(5);
    readVarWriter->addReadVarName(5, "z");
    

    printWriter->insertPrint(3);
    printVarWriter->addPrintVarName(3, "y");

    
    callProcWriter->addCallProcName(1, "proc3");



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
        std::unordered_set<string> expectedResults = { "1", "2", "3", "4", "5"};
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
    //
    SECTION("Check Evaluation result of a with clause on attribute stmt#") {

        Tokenizer tokenizer("call c; Select BOOLEAN with c.procName = \"proc3\"");
        vector<Token> tokens = tokenizer.tokenize();

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> actualResults = evaluator.evaluateQuery();
        std::unordered_set<string> expectedResults = { "TRUE" };
        REQUIRE(actualResults == expectedResults);

    }

    SECTION("Check Evaluation result of a with clause on attribute stmt#") {

        Tokenizer tokenizer("print p; Select BOOLEAN with p.varName = \"y\"");
        vector<Token> tokens = tokenizer.tokenize();

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> actualResults = evaluator.evaluateQuery();
        std::unordered_set<string> expectedResults = { "TRUE" };
        REQUIRE(actualResults == expectedResults);

    }

    SECTION("Check Evaluation result of a with clause on attribute stmt#") {

        Tokenizer tokenizer("print p; Select BOOLEAN with p.varName = \"x\"");
        vector<Token> tokens = tokenizer.tokenize();

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> actualResults = evaluator.evaluateQuery();
        std::unordered_set<string> expectedResults = { "FALSE" };
        REQUIRE(actualResults == expectedResults);

    }

    SECTION("Check Evaluation result of a with clause on attribute stmt#") {

        Tokenizer tokenizer("read r; Select BOOLEAN with r.varName = \"x\"");
        vector<Token> tokens = tokenizer.tokenize();

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> actualResults = evaluator.evaluateQuery();
        std::unordered_set<string> expectedResults = { "TRUE" };
        REQUIRE(actualResults == expectedResults);

    }

    SECTION("Check Evaluation result of a with clause on attribute stmt#") {

        Tokenizer tokenizer("read r; Select BOOLEAN with r.varName = \"y\"");
        vector<Token> tokens = tokenizer.tokenize();

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> actualResults = evaluator.evaluateQuery();
        std::unordered_set<string> expectedResults = { "FALSE" };
        REQUIRE(actualResults == expectedResults);

    }

    SECTION("Check Evaluation result of a with clause on attribute stmt#") {

        Tokenizer tokenizer("read r; Select r with r.varName = \"z\"");
        vector<Token> tokens = tokenizer.tokenize();

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> actualResults = evaluator.evaluateQuery();
        std::unordered_set<string> expectedResults = { "5" };
        REQUIRE(actualResults == expectedResults);

    }

    SECTION("Select BOOLEAN with 1 = 0") {

        Tokenizer tokenizer("Select BOOLEAN with 1 = 0");
        vector<Token> tokens = tokenizer.tokenize();

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> actualResults = evaluator.evaluateQuery();
        std::unordered_set<string> expectedResults = { "FALSE" };
        REQUIRE(actualResults == expectedResults);

    }

    SECTION("constant c; Select c with 0 = c.value") {
        unordered_set<string> a;
        auto x = constantReader->getAllConstants();

        for (auto i : x) {
            a.insert(to_string(i));
        }
        Tokenizer tokenizer("constant c; Select c with 0 = c.value");
        vector<Token> tokens = tokenizer.tokenize();

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> actualResults = evaluator.evaluateQuery();
        std::unordered_set<string> expectedResults = { "FALSE" };
        
		
        REQUIRE(actualResults == a);

    }


    

}


TEST_CASE("With strategy with multiple clauses") {

    auto pkbManager = std::make_shared<PKBManager>();
    auto pkbReaderManager = pkbManager->getPKBReaderManager();
    auto pkbWriterManager = pkbManager->getPKBWriterManager();
    auto statementWriter = pkbWriterManager->getStatementWriter();
    auto readWriter = pkbWriterManager->getReadWriter();
    auto readVarWriter = pkbWriterManager->getReadVarNameWriter();
    auto procedureWriter = pkbWriterManager->getProcedureWriter();
    auto callWriter = pkbWriterManager->getCallWriter();
    auto callProcWriter = pkbWriterManager->getCallProcNameWriter();
    auto variableWriter = pkbWriterManager->getVariableWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    readWriter->insertRead(1);
    readVarWriter->addReadVarName(1, "hello");
    procedureWriter->insertProcedure("hello");
    callWriter->insertCall(2);
    callProcWriter->addCallProcName(2, "hello");
    variableWriter->insertVariable("hello");


    SECTION("read r; call c; variable v; procedure p; Select r.varName with r.varName = c.procName and v.varName = p.procName with 1 = 1") {
        string query = "read r; call c; variable v; procedure p; Select r.varName with r.varName = c.procName and v.varName = p.procName with 1 = 1";
        Tokenizer tokenizer(query);
        vector<Token> tokens = tokenizer.tokenize();
        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> actualResults = evaluator.evaluateQuery();
        REQUIRE(actualResults == std::unordered_set<string>{"hello"});
    }
}
