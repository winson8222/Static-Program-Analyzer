
#include "catch.hpp"
#include "qps/evaluator/strategies/suchThatStrategies/ParentStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"
#include "../../spa/src/qps/parser/QueryParser.h"
#include "../../spa/src/pkb/PKBManager.h"
#include "../../spa/src/qps/evaluator/QueryEvaluator.h"

ParsingResult createParsingResultForParent(int parentStmt, int childStmt, bool isTransitive = false) {
    ParsingResult parsingResult;
    TokenType relationshipType = isTransitive ? TokenType::ParentT : TokenType::Parent;

    SuchThatClause clause;
    clause.relationship = Token(relationshipType, "");
    clause.firstParam = Token(TokenType::INTEGER, std::to_string(parentStmt));
    clause.secondParam = Token(TokenType::INTEGER, std::to_string(childStmt));
    parsingResult.addSuchThatClause(clause);
    return parsingResult;
}

//TEST_CASE("src/qps/evaluator/suchThatStrategies/ParentStrategy/1") {
//    auto pkb = std::make_shared<PKB>();
//    auto parentStore = pkb->getParentStore();
//    parentStore->addRelationship(1, 2);
//    parentStore->addRelationship(2, 3);
//    parentStore->addRelationship(3, 4); // Added for Parent* (transitive) testing
//    parentStore->addRelationship(1, 3);
//    parentStore->addRelationship(1, 4);
//
//    auto pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
//    ParentStrategy parentStrategy;
//
//    SECTION("Direct Parent(1, 2) is true") {
//        auto parsingResult = createParsingResultForParent(1, 2, false); // false for non-transitive
//        auto resultTable = parentStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
//        REQUIRE(resultTable->isTableTrue()); // Expecting a non-empty result
//    }
//
//    SECTION("Direct Parent(2, 3) is true") {
//        auto parsingResult = createParsingResultForParent(2, 3, false); // false for non-transitive
//        auto resultTable = parentStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
//        REQUIRE(resultTable->isTableTrue()); // Expecting a non-empty result
//    }
//
//    SECTION("Transitive Parent*(1, 3) is true") {
//        auto parsingResult = createParsingResultForParent(1, 3, true); // true for transitive
//        auto resultTable = parentStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
//        REQUIRE(resultTable->isTableTrue()); // Expecting a non-empty result
//    }
//
//    SECTION("Transitive Parent*(1, 4) is true") {
//        auto parsingResult = createParsingResultForParent(1, 4, true); // true for transitive
//        auto resultTable = parentStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
//        REQUIRE(resultTable->isTableTrue()); // Expecting a non-empty result
//    }
//
//    SECTION("Transitive Parent*(1, 5) is false") {
//        auto parsingResult = createParsingResultForParent(1, 5, true); // true for transitive
//        auto resultTable = parentStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
//        REQUIRE_FALSE(resultTable->isTableTrue()); // Expecting an empty result
//    }
//}

TEST_CASE("src/qps/evaluator/suchThatStrategies/ParentStrategy/2") {
std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
statementWriter->insertStatement(1);
statementWriter->insertStatement(2);
statementWriter->insertStatement(3);
parentWriter->addParent(1, 2);



std::vector<Token> tokens = {
        Token(TokenType::DesignEntity, "stmt"),
        Token(TokenType::IDENT, "s"),
        Token(TokenType::Semicolon, ";"),
        Token(TokenType::SelectKeyword, "Select"),
        Token(TokenType::IDENT, "s"),
        Token(TokenType::SuchKeyword, "such"),
        Token(TokenType::ThatKeyword, "that"),
        Token(TokenType::Parent, "Parent"),
        Token(TokenType::Lparenthesis, "("),
        Token(TokenType::IDENT, "s"),
        Token(TokenType::Comma, ","),
        Token(TokenType::INTEGER, "2"),
        Token(TokenType::Rparenthesis, ")")

};

QueryParser parser(tokens);
auto parsingResult = parser.parse();
QueryEvaluator evaluator(pkbReaderManager, parsingResult);
std::unordered_set<string> res = evaluator.evaluateQuery();
REQUIRE(res == std::unordered_set<string>{ "1" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/ParentStrategy/3") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    parentWriter->addParent(2, 3);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Parent, "Parent"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "2"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "3" });

}

