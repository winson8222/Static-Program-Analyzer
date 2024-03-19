
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
    std::shared_ptr<CallsWriter> CallsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);

    CallsWriter->addCalls("proc1", "proc3");
    CallsWriter->addCalls("proc2", "proc4");
    CallsWriter->addCalls("proc4", "proc1");
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
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "proc1" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/2") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> CallsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    CallsWriter->addCalls("proc1", "proc3");
    CallsWriter->addCalls("proc2", "proc4");
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
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "proc1", "proc2" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/3") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> CallsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    CallsWriter->addCalls("proc1", "proc3");
    CallsWriter->addCalls("proc2", "proc4");
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
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "proc3" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/4") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> CallsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);

    string query = "procedure p, q; Select p such that Calls*(p, q)";
    Tokenizer tokenizer(query);
    std::vector<Token> tokens = tokenizer.tokenize();
    QueryParser parser(tokens);
    ParsingResult parsingResult = parser.parse();


    CallsWriter->addCalls("proc1", "proc3");
    CallsWriter->addCalls("proc2", "proc4");
    CallsWriter->addCalls("proc4", "proc1");
    CallsTWriter->addCallsT("proc4", "proc3");
    CallsTWriter->addCallsT("proc1", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");


    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "proc1", "proc4" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/5") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> CallsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    CallsWriter->addCalls("proc1", "proc3");
    CallsWriter->addCalls("proc2", "proc4");
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
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "proc3", "proc4", "proc1", "proc2"});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/6") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> CallsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    CallsWriter->addCalls("proc1", "proc3");
    CallsWriter->addCalls("proc2", "proc4");
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
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/7") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> CallsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    CallsWriter->addCalls("proc1", "proc3");
    CallsWriter->addCalls("proc2", "proc4");
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
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"proc1" , "proc2", "proc3", "proc4"});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/8") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsWriter> CallsWriter = pkbWriterManager->getCallsWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    CallsWriter->addCalls("proc1", "proc3");
    CallsWriter->addCalls("proc2", "proc4");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("proc3");
    procedureWriter->insertProcedure("proc4");

    string query = "procedure p, q; Select p such that Calls(p, q)";

    Tokenizer tokenizer(query);
    std::vector<Token> tokens = tokenizer.tokenize();


    ParsingResult parsingResult;
    QueryParser parser(tokens);
    parsingResult = parser.parse();


    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "proc1", "proc2"});

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
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "proc2", "proc3"});

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
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "proc1", "proc2", "proc3"});

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
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "proc5" });

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
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "proc3", "proc4", "proc1", "proc2", "proc5"});

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
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{});

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

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::CallsT, "Calls*"));
    clause.setFirstParam(Token(TokenType::QuoutIDENT, "\"proc2\""));
    clause.setSecondParam(Token(TokenType::QuoutIDENT, "\"proc4\""));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"proc1" , "proc2", "proc3", "proc4", "proc5"});

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
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/CallsStrategy/16") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<CallsTWriter> CallsTWriter = pkbWriterManager->getCallsTWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    string query = "procedure p; Select p such that Calls*(p, \"proc4\")";

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
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "proc2", "proc3", "proc1"});

}
