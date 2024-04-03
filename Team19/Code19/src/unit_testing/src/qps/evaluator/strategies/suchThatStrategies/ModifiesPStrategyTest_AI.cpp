#include "catch.hpp"
#include "qps/evaluator/strategies/suchThatStrategies/ModifiesStrategy.h"
#include "qps/evaluator/strategies/suchThatStrategies/ModifiesPStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"

TEST_CASE("src/qps/evaluator/suchThatStrategies/ModifiesPStrategy/1") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBCacheManager> pkbCacheManager = pkbManager->getPKBCacheManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesPWriter> modifiesPWriter = pkbWriterManager->getModifiesPWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    modifiesPWriter->addModifiesP("proc1", "x");
    modifiesPWriter->addModifiesP("proc2", "y");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::ModifiesP, "Modifies"));
    clause.setFirstParam(Token(TokenType::IDENT, "p"));
    clause.setSecondParam(Token(TokenType::QuoutIDENT, "\"x\""));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "proc1" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/ModifiesPStrategy/2") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBCacheManager> pkbCacheManager = pkbManager->getPKBCacheManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesPWriter> modifiesPWriter = pkbWriterManager->getModifiesPWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    modifiesPWriter->addModifiesP("proc1", "x");
    modifiesPWriter->addModifiesP("proc2", "y");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::ModifiesP, "Modifies"));
    clause.setFirstParam(Token(TokenType::IDENT, "p"));
    clause.setSecondParam(Token(TokenType::Wildcard, "_"));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "proc1", "proc2" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/ModifiesPStrategy/3") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
    std::shared_ptr<PKBCacheManager> pkbCacheManager = pkbManager->getPKBCacheManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesPWriter> modifiesPWriter = pkbWriterManager->getModifiesPWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    modifiesPWriter->addModifiesP("proc1", "x");
    modifiesPWriter->addModifiesP("proc2", "y");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    variableWriter->insertVariable("x");
    variableWriter->insertVariable("y");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("v", "variable");
    parsingResult.setRequiredSynonym("v" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::ModifiesP, "Modifies"));
    clause.setFirstParam(Token(TokenType::QuoutIDENT, "\"proc1\""));
    clause.setSecondParam(Token(TokenType::IDENT, "v"));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "x" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/ModifiesPStrategy/4") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBCacheManager> pkbCacheManager = pkbManager->getPKBCacheManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesPWriter> modifiesPWriter = pkbWriterManager->getModifiesPWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    modifiesPWriter->addModifiesP("proc1", "x");
    modifiesPWriter->addModifiesP("proc2", "y");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    variableWriter->insertVariable("x");
    variableWriter->insertVariable("y");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("v", "variable");
    parsingResult.setRequiredSynonym("v" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::ModifiesP, "Modifies"));
    clause.setFirstParam(Token(TokenType::Wildcard, "_"));
    clause.setSecondParam(Token(TokenType::Wildcard, "_"));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "x", "y" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/ModifiesPStrategy/5") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBCacheManager> pkbCacheManager = pkbManager->getPKBCacheManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesPWriter> modifiesPWriter = pkbWriterManager->getModifiesPWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    modifiesPWriter->addModifiesP("proc1", "x");
    modifiesPWriter->addModifiesP("proc2", "y");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    variableWriter->insertVariable("x");
    variableWriter->insertVariable("y");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("v", "variable");
    parsingResult.setRequiredSynonym("v" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::ModifiesP, "Modifies"));
    clause.setFirstParam(Token(TokenType::Wildcard, "_"));
    clause.setSecondParam(Token(TokenType::QuoutIDENT, "\"z\""));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/ModifiesPStrategy/6") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBCacheManager> pkbCacheManager = pkbManager->getPKBCacheManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesPWriter> modifiesPWriter = pkbWriterManager->getModifiesPWriter();
    std::shared_ptr<ProcedureWriter> procedureWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    modifiesPWriter->addModifiesP("proc1", "x");
    modifiesPWriter->addModifiesP("proc2", "y");
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    variableWriter->insertVariable("x");
    variableWriter->insertVariable("y");

    ParsingResult parsingResult;
    parsingResult.addDeclaredSynonym("p", "procedure");
    parsingResult.setRequiredSynonym("p" );
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::ModifiesP, "Modifies"));
    clause.setFirstParam(Token(TokenType::QuoutIDENT, "\"proc1\""));
    clause.setSecondParam(Token(TokenType::QuoutIDENT, "\"x\""));
    parsingResult.addSuchThatClause(clause);

    QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{"proc1" , "proc2"});

}