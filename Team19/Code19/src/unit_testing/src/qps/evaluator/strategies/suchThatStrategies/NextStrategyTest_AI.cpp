#include "catch.hpp"
#include "qps/evaluator/strategies/suchThatStrategies/NextStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"

TEST_CASE("NextStrategy/Verify Direct Next Relationship") {
// Setup PKB with Next relationships
std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
nextWriter->addNext(2, 3);

// Define tokens for the query
std::vector<Token> tokens = {
        Token(TokenType::SelectKeyword, "Select"),
        Token(TokenType::BooleanKeyword, "BOOLEAN"),
        Token(TokenType::SuchKeyword, "such"),
        Token(TokenType::ThatKeyword, "that"),
        Token(TokenType::Next, "Next"),
        Token(TokenType::Lparenthesis, "("),
        Token(TokenType::INTEGER, "2"),
        Token(TokenType::Comma, ","),
        Token(TokenType::INTEGER, "3"),
        Token(TokenType::Rparenthesis, ")")
};

QueryParser parser(tokens);
auto parsingResult = parser.parse();
QueryEvaluator evaluator(pkbReaderManager, parsingResult);
std::unordered_set<string> res = evaluator.evaluateQuery();
REQUIRE(res == std::unordered_set<string>{"TRUE"}); // Expect TRUE as 2 Next 3 is defined
}

TEST_CASE("NextStrategy/Verify Transitive Next* Relationship") {
    // Setup PKB with Next* relationships
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
    nextWriter->addNext(1, 2); // Direct relationships to simulate Next*
    nextWriter->addNext(2, 3);
    nextWriter->addNext(3, 4);
    nextWriter->addNext(1, 4);

    // Define tokens for the query testing transitive relationship
    std::vector<Token> tokens = {
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::BooleanKeyword, "BOOLEAN"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::NextT, "Next*"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "1"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "4"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"TRUE"});
}

