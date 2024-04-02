
#include "catch.hpp"
#include "qps/evaluator/strategies/suchThatStrategies/CallsStrategy.h"
#include "qps/evaluator/strategies/suchThatStrategies/CallsStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/1") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> callsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);

    callsWriter->addCalls("proc1", "proc3");
    callsWriter->addCalls("proc2", "proc4");
    callsWriter->addCalls("proc4", "proc1");
    CallsTWriter->addCallsT("proc4", "proc3");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::Calls, "Calls"));
    clause.setFirstParam(Token(TokenType::IDENT, "p"));
    clause.setSecondParam(Token(TokenType::QuoutIDENT, "\"proc3\""));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "proc1" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/2") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> callsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    callsWriter->addCalls("proc1", "proc3");
    callsWriter->addCalls("proc2", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::Calls, "Calls"));
    clause.setFirstParam(Token(TokenType::IDENT, "p"));
    clause.setSecondParam(Token(TokenType::Wildcard, "_"));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "proc1", "proc2" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/3") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> callsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    callsWriter->addCalls("proc1", "proc3");
    callsWriter->addCalls("proc2", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    variableWriter->insertVariable("proc3");
    variableWriter->insertVariable("proc4");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::Calls, "Calls"));
    clause.setFirstParam(Token(TokenType::QuoutIDENT, "\"proc1\""));
    clause.setSecondParam(Token(TokenType::IDENT, "p"));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "proc3" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/4") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> callsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);

    std::string query = "procedure p, q; Select p such that Calls*(p, q)";
    Tokenizer tokenizer(query);
    std::vector<Token> tokens = tokenizer.tokenize();
    QueryParser parser(tokens);
    ParsingResult parsingResult = parser.parse();


    callsWriter->addCalls("proc1", "proc3");
    callsWriter->addCalls("proc2", "proc4");
    callsWriter->addCalls("proc4", "proc1");
    CallsTWriter->addCallsT("proc4", "proc3");
    CallsTWriter->addCallsT("proc1", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");


    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "proc1", "proc4" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/5") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> callsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    callsWriter->addCalls("proc1", "proc3");
    callsWriter->addCalls("proc2", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::Calls, "Calls"));
    clause.setFirstParam(Token(TokenType::Wildcard, "_"));
    clause.setSecondParam(Token(TokenType::Wildcard, "_"));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "proc3", "proc4", "proc1", "proc2"});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/6") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> callsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    callsWriter->addCalls("proc1", "proc3");
    callsWriter->addCalls("proc2", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::Calls, "Calls"));
    clause.setFirstParam(Token(TokenType::Wildcard, "_"));
    clause.setSecondParam(Token(TokenType::QuoutIDENT, "\"proc5\""));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/7") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> callsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    callsWriter->addCalls("proc1", "proc3");
    callsWriter->addCalls("proc2", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    variableWriter->insertVariable("proc3");
    variableWriter->insertVariable("proc4");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::Calls, "Calls"));
    clause.setFirstParam(Token(TokenType::QuoutIDENT, "\"proc2\""));
    clause.setSecondParam(Token(TokenType::QuoutIDENT, "\"proc4\""));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{"proc1" , "proc2", "proc3", "proc4"});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/8") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> callsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    callsWriter->addCalls("proc1", "proc3");
    callsWriter->addCalls("proc2", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");

    std::string query = "procedure p, q; Select p such that Calls(p, q)";

    Tokenizer tokenizer(query);
    std::vector<Token> tokens = tokenizer.tokenize();


    ParsingResult parsingResult;
    QueryParser parser(tokens);
    parsingResult = parser.parse();


    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "proc1", "proc2"});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/9") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    CallsTWriter->addCallsT("proc1", "proc5");
    CallsTWriter->addCallsT("proc2", "proc4");
    CallsTWriter->addCallsT("proc3", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");
    procedureWriter->insertProcedure("proc5");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::CallsT, "Calls*"));
    clause.setFirstParam(Token(TokenType::IDENT, "p"));
    clause.setSecondParam(Token(TokenType::QuoutIDENT, "\"proc4\""));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "proc2", "proc3"});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/10") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    CallsTWriter->addCallsT("proc1", "proc5");
    CallsTWriter->addCallsT("proc2", "proc4");
    CallsTWriter->addCallsT("proc3", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");
    procedureWriter->insertProcedure("proc5");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::CallsT, "Calls*"));
    clause.setFirstParam(Token(TokenType::IDENT, "p"));
    clause.setSecondParam(Token(TokenType::Wildcard, "_"));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "proc1", "proc2", "proc3"});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/11") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    CallsTWriter->addCallsT("proc1", "proc5");
    CallsTWriter->addCallsT("proc2", "proc4");
    CallsTWriter->addCallsT("proc3", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");
    procedureWriter->insertProcedure("proc5");


    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::CallsT, "Calls*"));
    clause.setFirstParam(Token(TokenType::QuoutIDENT, "\"proc1\""));
    clause.setSecondParam(Token(TokenType::IDENT, "p"));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "proc5" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/12") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    CallsTWriter->addCallsT("proc1", "proc5");
    CallsTWriter->addCallsT("proc2", "proc4");
    CallsTWriter->addCallsT("proc3", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");
    procedureWriter->insertProcedure("proc5");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::CallsT, "Calls*"));
    clause.setFirstParam(Token(TokenType::Wildcard, "_"));
    clause.setSecondParam(Token(TokenType::Wildcard, "_"));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "proc3", "proc4", "proc1", "proc2", "proc5"});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/13") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    CallsTWriter->addCallsT("proc1", "proc5");
    CallsTWriter->addCallsT("proc2", "proc4");
    CallsTWriter->addCallsT("proc3", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");
    procedureWriter->insertProcedure("proc5");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::CallsT, "Calls*"));
    clause.setFirstParam(Token(TokenType::Wildcard, "_"));
    clause.setSecondParam(Token(TokenType::QuoutIDENT, "\"proc6\""));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/14") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    CallsTWriter->addCallsT("proc1", "proc5");
    CallsTWriter->addCallsT("proc2", "proc4");
    CallsTWriter->addCallsT("proc3", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");
    procedureWriter->insertProcedure("proc5");

//    ParsingResult parsingResult;
//    parsingResult.addDeclaredSynonym("p", "procedure");
//    parsingResult.setRequiredSynonym("p" );
//    SuchThatClause clause;
//    clause.setRelationship(Token(TokenType::CallsT, "Calls*"));
//    clause.setFirstParam(Token(TokenType::QuoutIDENT, "\"proc2\""));
//    clause.setSecondParam(Token(TokenType::QuoutIDENT, "\"proc4\""));
//    parsingResult.addSuchThatClause(clause);
    std::string query = "Select BOOLEAN such that Calls*(\"proc2\", \"proc4\")";
    Tokenizer tokenizer(query);
    ParsingResult parsingResult = QueryParser(tokenizer.tokenize()).parse();

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{"TRUE"});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/15") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    CallsTWriter->addCallsT("proc1", "proc5");
    CallsTWriter->addCallsT("proc2", "proc4");
    CallsTWriter->addCallsT("proc3", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");
    procedureWriter->insertProcedure("proc5");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::CallsT, "Calls*"));
    clause.setFirstParam(Token(TokenType::QuoutIDENT, "\"proc2\""));
    clause.setSecondParam(Token(TokenType::QuoutIDENT, "\"proc5\""));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/16") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::string query = "procedure p; Select p such that Calls*(p, \"proc4\")";

    Tokenizer tokenizer(query);
    std::vector<Token> tokens = tokenizer.tokenize();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    CallsTWriter->addCallsT("proc1", "proc4");
    CallsTWriter->addCallsT("proc2", "proc4");
    CallsTWriter->addCallsT("proc3", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");
    procedureWriter->insertProcedure("proc5");

    ParsingResult parsingResult;
    parsingResult = QueryParser(tokens).parse();

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "proc2", "proc3", "proc1"});

}


TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/18") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
    std::shared_ptr<CallWriter> callWriter = pkbWriterManager->getCallWriter();
    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> callsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<UsesSWriter> usesSWriter = pkbWriterManager->getUsesSWriter();
    std::shared_ptr<UsesPWriter> usesPWriter = pkbWriterManager->getUsesPWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<CallProcNameWriter> callProcNameWriter = pkbWriterManager->getCallProcNameWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    statementWriter->insertStatement(5);
    statementWriter->insertStatement(6);
    callsWriter->addCalls("proc1", "proc5");
    callsWriter->addCalls("proc2", "proc4");
    callsWriter->addCalls("proc3", "proc4");
    callWriter->insertCall(2);
    callWriter->insertCall(3);
    callWriter->insertCall(4);
    callWriter->insertCall(6);
    callWriter->insertCall(5);
    usesSWriter->addUsesS(2, "proc2");
    usesSWriter->addUsesS(4, "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");
    procedureWriter->insertProcedure("proc5");
    callProcNameWriter->addCallProcName(2,"proc2");
    callProcNameWriter->addCallProcName(3,"proc3");
    callProcNameWriter->addCallProcName(4,"proc4");
    callProcNameWriter->addCallProcName(6,"proc4");
    callProcNameWriter->addCallProcName(5,"proc5");
    pkbManager->getPKBCacheManager()->populateCache();



    SECTION("simple select of procsName using proc") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "procedure"),
                Token(TokenType::IDENT, "proc"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "proc"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "procName"),
        };

        ParsingResult parsingResult = QueryParser(tokens).parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{ "proc1", "proc2", "proc3", "proc4", "proc5"});
    }

    SECTION("simple select of procsName using call") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "call"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "procName"),
        };

        ParsingResult parsingResult = QueryParser(tokens).parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{ "proc2", "proc3", "proc4", "proc5"});
    }

    SECTION("simple select of stmt# using call") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "call"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
        };

        ParsingResult parsingResult = QueryParser(tokens).parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{ "2", "3", "4", "5", "6"});
    }

    SECTION("mutiple select of stmt# using call") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "call"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::LeftAngleBracket, "<"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "procName"),
                Token(TokenType::RightAngleBracket, ">")
        };

        ParsingResult parsingResult = QueryParser(tokens).parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{ "2 proc2", "3 proc3", "4 proc4", "6 proc4", "5 proc5"});
    }

    SECTION("mutiple select of stmt# using call if it is in result table") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "call"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::LeftAngleBracket, "<"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "procName"),
                Token(TokenType::RightAngleBracket, ">"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")")
        };

        ParsingResult parsingResult = QueryParser(tokens).parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{ "4 proc4", "2 proc2" });
    }

    SECTION("mutiple select of stmt# using call if it is in result table, if variable not in result table") {
        pkbWriterManager->getVariableWriter()->insertVariable("v");
        pkbWriterManager->getVariableWriter()->insertVariable("x");
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "call"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::LeftAngleBracket, "<"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "procName"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::RightAngleBracket, ">"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")")
        };

        ParsingResult parsingResult = QueryParser(tokens).parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{ "4 proc4 v", "2 proc2 v", "4 proc4 x", "2 proc2 x" });
    }

    SECTION("mutiple select of stmt# using call if it is in result table, if call not in result table") {
        pkbWriterManager->getVariableWriter()->insertVariable("v");
        pkbWriterManager->getVariableWriter()->insertVariable("x");
        usesPWriter->addUsesP("proc1", "v");

        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "call"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::LeftAngleBracket, "<"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "procName"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::RightAngleBracket, ">"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::QuoutIDENT, "\"proc1\""),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Rparenthesis, ")")
        };

        ParsingResult parsingResult = QueryParser(tokens).parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{ "2 proc2 v", "4 proc4 v", "6 proc4 v", "3 proc3 v", "5 proc5 v" });
    }

    SECTION("mutiple select of stmt# using call if it is in result table, both are in result table") {
        pkbWriterManager->getVariableWriter()->insertVariable("v");
        pkbWriterManager->getVariableWriter()->insertVariable("x");
        usesSWriter->addUsesS(3, "x");

        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "call"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::LeftAngleBracket, "<"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "procName"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::RightAngleBracket, ">"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Rparenthesis, ")")
        };

        ParsingResult parsingResult = QueryParser(tokens).parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{ "4 proc4 proc4", "3 proc3 x", "2 proc2 proc2" });
    }

    SECTION("mutiple select of stmt# using call if it is in result table, if call not in result table") {
        pkbWriterManager->getVariableWriter()->insertVariable("v");
        pkbWriterManager->getVariableWriter()->insertVariable("x");
        usesPWriter->addUsesP("proc1", "v");

        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "call"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::LeftAngleBracket, "<"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "procName"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::RightAngleBracket, ">"),
                Token(TokenType::WithKeyword, "with"),
                Token(TokenType::IDENT, "c"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
                Token(TokenType::Equal, "="),
                Token(TokenType::INTEGER, "2"),
        };

        ParsingResult parsingResult = QueryParser(tokens).parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{ "2 proc2 v", "2 proc2 x" });
    }


}
