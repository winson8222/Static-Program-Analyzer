#include "catch.hpp"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"
#include <memory>

#include "sp/SourceProcessor.h"

TEST_CASE("src/qps/evaluator/suchThatAndPatternStrategy/IfPatternStrategy/1") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<IfPatternWriter> ifPatternWriter = pkbWriterManager->getIfPatternWriter();
    std::shared_ptr<IfWriter> whileWriter = pkbWriterManager->getIfWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    whileWriter->insertIf(1);
    whileWriter->insertIf(2);
    whileWriter->insertIf(3);
    ifPatternWriter->addIfControlVariable(1, "x");
    ifPatternWriter->addIfControlVariable(2, "y");
    ifPatternWriter->addIfControlVariable(3, "z");

    PatternClause patternClause;
    patternClause.setFirstParam(Token(TokenType::QuoutIDENT, "\"x\""));
    patternClause.setRelationship(Token(TokenType::IDENT, "if"));
    ParsingResult parsingResult;
    parsingResult.addPatternClause(patternClause);
    parsingResult.addDeclaredSynonym("if", "if");
    parsingResult.setRequiredSynonym("if");

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "1" });
}

TEST_CASE("src/qps/evaluator/suchThatAndPatternStrategy/IfPatternStrategy/2") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<IfPatternWriter> ifPatternWriter = pkbWriterManager->getIfPatternWriter();
    std::shared_ptr<IfWriter> whileWriter = pkbWriterManager->getIfWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    whileWriter->insertIf(1);
    whileWriter->insertIf(2);
    whileWriter->insertIf(3);
    ifPatternWriter->addIfControlVariable(1, "x");
    ifPatternWriter->addIfControlVariable(2, "y");
    ifPatternWriter->addIfControlVariable(3, "z");

    PatternClause patternClause;
    patternClause.setFirstParam(Token(TokenType::QuoutIDENT, "\"z\""));
    patternClause.setRelationship(Token(TokenType::IDENT, "if"));
    ParsingResult parsingResult;
    parsingResult.addPatternClause(patternClause);
    parsingResult.addDeclaredSynonym("if", "if");
    parsingResult.setRequiredSynonym("if");
    
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "3" });
}


TEST_CASE("src/qps/evaluator/suchThatAndPatternStrategy/IfPatternStrategy/3") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<IfPatternWriter> ifPatternWriter = pkbWriterManager->getIfPatternWriter();
    std::shared_ptr<IfWriter> whileWriter = pkbWriterManager->getIfWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    whileWriter->insertIf(1);
    whileWriter->insertIf(2);
    whileWriter->insertIf(3);
    ifPatternWriter->addIfControlVariable(1, "x");
    ifPatternWriter->addIfControlVariable(2, "y");
    ifPatternWriter->addIfControlVariable(3, "z");

    PatternClause patternClause;
    patternClause.setFirstParam(Token(TokenType::IDENT, "v"));
    patternClause.setRelationship(Token(TokenType::IDENT, "if"));
    ParsingResult parsingResult;
    parsingResult.addPatternClause(patternClause);
    parsingResult.addDeclaredSynonym("if", "if");
    parsingResult.addDeclaredSynonym("v", "variable");
    parsingResult.setRequiredSynonym("v");

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "x", "y", "z" });
}

TEST_CASE("src/qps/evaluator/suchThatAndPatternStrategy/IfPatternStrategy/4") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<IfPatternWriter> ifPatternWriter = pkbWriterManager->getIfPatternWriter();
    std::shared_ptr<IfWriter> whileWriter = pkbWriterManager->getIfWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    whileWriter->insertIf(1);
    whileWriter->insertIf(2);
    whileWriter->insertIf(3);
    ifPatternWriter->addIfControlVariable(1, "x");
    ifPatternWriter->addIfControlVariable(2, "y");
    ifPatternWriter->addIfControlVariable(3, "z");

    PatternClause patternClause;
    patternClause.setFirstParam(Token(TokenType::Wildcard, "_"));
    patternClause.setRelationship(Token(TokenType::IDENT, "if"));
    ParsingResult parsingResult;
    parsingResult.addPatternClause(patternClause);
    parsingResult.addDeclaredSynonym("if", "if");
    parsingResult.setRequiredSynonym("if");

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<std::string>{ "1", "2", "3" });
}