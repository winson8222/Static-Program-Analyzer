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

TEST_CASE("NextStrategy/Verify Next Relationship") {
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
            Token(TokenType::Next, "Next"),
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

TEST_CASE("NextStrategy/Verify Next Relationship with 1 Int and 1 IDENT (FALSE)") {
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
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::BooleanKeyword, "BOOLEAN"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Next, "Next"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "1"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"FALSE"});
}

TEST_CASE("NextStrategy/Verify Next Relationship with 1 Int and 1 IDENT (TRUE)") {
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
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::BooleanKeyword, "BOOLEAN"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Next, "Next"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "3"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"TRUE"});
}

TEST_CASE("Select stmt from NextT Relationship") {
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
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Next, "Next"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "4"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"3", "1"});
}


TEST_CASE("Select stmt from Next Relationship with 1 Int and 1 IDENT") {
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
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Next, "Next"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "4"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"3", "1"});
}

TEST_CASE("Select stmt from Next Relationship with 1 wild card and 1 Integer") {
    // Setup PKB with Next* relationships
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    nextWriter->addNext(1, 2); // Direct relationships to simulate Next*
    nextWriter->addNext(2, 3);
    nextWriter->addNext(3, 4);
    nextWriter->addNext(1, 4);

    // Define tokens for the query testing transitive relationship
    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Next, "Next"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "4"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"3", "1", "2", "4"});
}


TEST_CASE("Select stmt from Next Relationship with 2 stmt and multiple Select") {
    // Setup PKB with Next* relationships
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    nextWriter->addNext(1, 2); // Direct relationships to simulate Next*
    nextWriter->addNext(2, 3);
    nextWriter->addNext(3, 4);
    nextWriter->addNext(1, 4);

    // Define tokens for the query testing transitive relationship
    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::LeftAngleBracket, "<"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::RightAngleBracket, ">"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Next, "Next"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"3 4", "1 4", "2 3", "1 2"});
}

TEST_CASE("NextStrategy/Verify Direct NextT Relationship") {
// Setup PKB with Next relationships
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
    nextWriter->addNext(2, 3);
    // add this for NextT since there is not NextTWriter
    pkbManager->getPKBCacheManager()->populateCache();

// Define tokens for the query
    std::vector<Token> tokens = {
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::BooleanKeyword, "BOOLEAN"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::NextT, "Next*"),
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

TEST_CASE("NextTStrategy/Verify Direct NextT Relationship") {
    // Setup PKB with NextT relationships
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
    nextWriter->addNext(2, 3);
    pkbManager->getPKBCacheManager()->populateCache();

    // Define tokens for the query
    std::vector<Token> tokens = {
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::BooleanKeyword, "BOOLEAN"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::NextT, "Next*"),
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
    REQUIRE(res == std::unordered_set<string>{"TRUE"}); // Expect TRUE as 2 Next* 3 is defined
}

TEST_CASE("NextTStrategy/Verify NextT Relationship") {
    // Setup PKB with NextT relationships
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    statementWriter->insertStatement(5);
    statementWriter->insertStatement(6);
    nextWriter->addNext(1, 2); // Direct relationships to simulate NextT
    nextWriter->addNext(2, 3);
    nextWriter->addNext(3, 4);
    nextWriter->addNext(1, 4);
    nextWriter->addNext(5, 6);
    pkbManager->getPKBCacheManager()->populateCache();

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
            Token(TokenType::INTEGER, "5"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"FALSE"});
}

TEST_CASE("NextTStrategy/Verify False NextT Relationship") {
    // Setup PKB with NextT relationships
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    statementWriter->insertStatement(5);
    statementWriter->insertStatement(6);
    nextWriter->addNext(1, 2); // Direct relationships to simulate NextT
    nextWriter->addNext(2, 3);
    nextWriter->addNext(3, 4);
    nextWriter->addNext(1, 4);
    nextWriter->addNext(5, 6);
    pkbManager->getPKBCacheManager()->populateCache();

    // Define tokens for the query testing transitive relationship
    std::vector<Token> tokens = {
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::BooleanKeyword, "BOOLEAN"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::NextT, "Next*"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "2"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "6"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"FALSE"});
}

TEST_CASE("NextTStrategy/Verify NextT Relationship with 1 Int and 1 IDENT (FALSE)") {
    // Setup PKB with NextT relationships
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
    nextWriter->addNext(1, 2); // Direct relationships to simulate NextT
    nextWriter->addNext(2, 3);
    nextWriter->addNext(3, 4);
    nextWriter->addNext(1, 4);
    pkbManager->getPKBCacheManager()->populateCache();

    // Define tokens for the query testing transitive relationship
    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::BooleanKeyword, "BOOLEAN"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::NextT, "Next*"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "1"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"FALSE"});
}

TEST_CASE("NextTStrategy/Verify NextT Relationship with 1 Int and 1 IDENT (TRUE)") {
    // Setup PKB with NextT relationships
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
    nextWriter->addNext(1, 2); // Direct relationships to simulate NextT
    nextWriter->addNext(2, 3);
    nextWriter->addNext(3, 4);
    nextWriter->addNext(1, 4);
    pkbManager->getPKBCacheManager()->populateCache();

    // Define tokens for the query testing transitive relationship
    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::BooleanKeyword, "BOOLEAN"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::NextT, "Next*"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "3"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"TRUE"});
}


TEST_CASE("Select stmt from NextT Relationship with 1 Int and 1 IDENT") {
    // Setup PKB with NextT relationships
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
    nextWriter->addNext(1, 2); // Direct relationships to simulate NextT
    nextWriter->addNext(2, 3);
    nextWriter->addNext(3, 4);
    nextWriter->addNext(1, 4);
    pkbManager->getPKBCacheManager()->populateCache();

    // Define tokens for the query testing transitive relationship
    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::NextT, "Next*"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "4"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"3", "1", "2"});
}

TEST_CASE("Select stmt from NextT Relationship with 1 wild card and 1 Integer") {
    // Setup PKB with NextT relationships
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    statementWriter->insertStatement(5);
    nextWriter->addNext(1, 2); // Direct relationships to simulate NextT
    nextWriter->addNext(2, 3);
    nextWriter->addNext(3, 4);
    nextWriter->addNext(1, 4);
    pkbManager->getPKBCacheManager()->populateCache();

    // Define tokens for the query testing transitive relationship
    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::NextT, "Next*"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "4"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"3", "1", "2", "4", "5"});
}

TEST_CASE("Select stmt from NextT Relationship with 2 stmt and multiple Select") {
    // Setup PKB with NextT relationships
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    nextWriter->addNext(1, 2); // Direct relationships to simulate NextT
    nextWriter->addNext(2, 3);
    nextWriter->addNext(3, 4);
    nextWriter->addNext(1, 4);
    pkbManager->getPKBCacheManager()->populateCache();

    // Define tokens for the query testing transitive relationship
    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::LeftAngleBracket, "<"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::RightAngleBracket, ">"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::NextT, "Next*"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"3 4", "2 4", "1 3", "1 4", "2 3", "1 2" });
}

TEST_CASE("Select stmt from NextT Relationship with 1 SYN and 1 Integer result none") {
    // Setup PKB with NextT relationships
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    nextWriter->addNext(1, 2); // Direct relationships to simulate NextT
    nextWriter->addNext(2, 3);
    nextWriter->addNext(3, 4);
    nextWriter->addNext(1, 4);
    pkbManager->getPKBCacheManager()->populateCache();

    // Define tokens for the query testing transitive relationship
    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::NextT, "Next*"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "4"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{});
}

TEST_CASE("Select stmt from NextT Relationship with 1 SYN and 1 Integer result") {
    // Setup PKB with NextT relationships
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    nextWriter->addNext(1, 2); // Direct relationships to simulate NextT
    nextWriter->addNext(2, 3);
    nextWriter->addNext(3, 4);
    nextWriter->addNext(1, 4);
    pkbManager->getPKBCacheManager()->populateCache();

    // Define tokens for the query testing transitive relationship
    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::NextT, "Next*"),
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
    REQUIRE(res == std::unordered_set<string>{"3", "4"});
}