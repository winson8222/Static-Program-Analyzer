#include "catch.hpp"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"
#include <filesystem>
#include <fstream>
#include <memory>

#include "sp/SourceProcessor.h"

TEST_CASE("src/qps/evaluator/suchThatAndPatternStrategy/WhilePatternStrategy/1") {
std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
std::shared_ptr<WhilePatternWriter> whilePatternWriter = pkbWriterManager->getWhilePatternWriter();
std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();

statementWriter->insertStatement(1);
statementWriter->insertStatement(2);
statementWriter->insertStatement(3);
statementWriter->insertStatement(4);
whileWriter->insertWhile(1);
whileWriter->insertWhile(2);
whileWriter->insertWhile(3);
whilePatternWriter->addWhileControlVariable(1, "x");
whilePatternWriter->addWhileControlVariable(2, "y");
whilePatternWriter->addWhileControlVariable(3, "z");

PatternClause patternClause;
patternClause.setFirstParam(Token(TokenType::QuoutIDENT, "\"x\""));
patternClause.setRelationship(Token(TokenType::IDENT, "w"));
ParsingResult parsingResult;
parsingResult.addPatternClause(patternClause);
parsingResult.addDeclaredSynonym("w", "while");
parsingResult.setRequiredSynonym("w");

QueryEvaluator evaluator(pkbReaderManager, parsingResult);
std::unordered_set<string> res = evaluator.evaluateQuery();
REQUIRE(res == std::unordered_set<string>{ "1" });
}

TEST_CASE("src/qps/evaluator/suchThatAndPatternStrategy/WhilePatternStrategy/2") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<WhilePatternWriter> whilePatternWriter = pkbWriterManager->getWhilePatternWriter();
    std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    whileWriter->insertWhile(1);
    whileWriter->insertWhile(2);
    whileWriter->insertWhile(3);
    whilePatternWriter->addWhileControlVariable(1, "x");
    whilePatternWriter->addWhileControlVariable(2, "y");
    whilePatternWriter->addWhileControlVariable(3, "z");

    PatternClause patternClause;
    patternClause.setFirstParam(Token(TokenType::QuoutIDENT, "\"z\""));
    patternClause.setRelationship(Token(TokenType::IDENT, "w"));
    ParsingResult parsingResult;
    parsingResult.addPatternClause(patternClause);
    parsingResult.addDeclaredSynonym("w", "while");
    parsingResult.setRequiredSynonym("w");

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "3" });
}


TEST_CASE("src/qps/evaluator/suchThatAndPatternStrategy/WhilePatternStrategy/3") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<WhilePatternWriter> whilePatternWriter = pkbWriterManager->getWhilePatternWriter();
    std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    whileWriter->insertWhile(1);
    whileWriter->insertWhile(2);
    whileWriter->insertWhile(3);
    whilePatternWriter->addWhileControlVariable(1, "x");
    whilePatternWriter->addWhileControlVariable(2, "y");
    whilePatternWriter->addWhileControlVariable(3, "z");

    PatternClause patternClause;
    patternClause.setFirstParam(Token(TokenType::IDENT, "v"));
    patternClause.setRelationship(Token(TokenType::IDENT, "w"));
    ParsingResult parsingResult;
    parsingResult.addPatternClause(patternClause);
    parsingResult.addDeclaredSynonym("w", "while");
    parsingResult.addDeclaredSynonym("v", "variable");
    parsingResult.setRequiredSynonym("v");

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "x", "y", "z" });
}

TEST_CASE("src/qps/evaluator/suchThatAndPatternStrategy/WhilePatternStrategy/4") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<WhilePatternWriter> whilePatternWriter = pkbWriterManager->getWhilePatternWriter();
    std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    whileWriter->insertWhile(1);
    whileWriter->insertWhile(2);
    whileWriter->insertWhile(3);
    whilePatternWriter->addWhileControlVariable(1, "x");
    whilePatternWriter->addWhileControlVariable(2, "y");
    whilePatternWriter->addWhileControlVariable(3, "z");

    PatternClause patternClause;
    patternClause.setFirstParam(Token(TokenType::Wildcard, "_"));
    patternClause.setRelationship(Token(TokenType::IDENT, "w"));
    ParsingResult parsingResult;
    parsingResult.addPatternClause(patternClause);
    parsingResult.addDeclaredSynonym("w", "while");
    parsingResult.setRequiredSynonym("w");

    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "1", "2", "3" });
}