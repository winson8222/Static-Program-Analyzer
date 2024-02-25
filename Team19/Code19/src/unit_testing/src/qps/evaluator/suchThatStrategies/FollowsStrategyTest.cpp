
#include "catch.hpp"
#include "qps/evaluator/suchThatStrategies/FollowsStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"
#include "../../spa/src/qps/parser/QueryParser.h"
#include "../../spa/src/pkb/PKBManager.h"
#include "../../spa/src/qps/evaluator/QueryEvaluator.h"

ParsingResult createParsingResultForFollows(int stmt1, int stmt2, bool isTransitive = false) {
    ParsingResult parsingResult;
    TokenType relationshipType = isTransitive ? TokenType::FollowsT : TokenType::Follows;
    parsingResult.setSuchThatClauseRelationship(Token(relationshipType, ""));
    parsingResult.setSuchThatClauseFirstParam(Token(TokenType::INTEGER, std::to_string(stmt1)));
    parsingResult.setSuchThatClauseSecondParam(Token(TokenType::INTEGER, std::to_string(stmt2)));
    return parsingResult;
}

TEST_CASE("FollowsStrategy Evaluation for Follows and FollowsT", "[Follows]") {
    auto pkb = std::make_shared<PKB>();
    auto followsStore = pkb->getFollowsStore();
    followsStore->addRelationship(1, 2);
    followsStore->addRelationship(2, 3);
    followsStore->addRelationship(3, 4); // Added for transitive testing

    auto pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
    FollowsStrategy followsStrategy;

    SECTION("Direct Follows(1, 2) is true") {
        auto parsingResult1 = createParsingResultForFollows(1, 2);
        auto resultTable = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult1);
        // Verify result for Follows(1, 2)
    }

    SECTION("Direct Follows(2, 3) is true") {
        auto parsingResult2 = createParsingResultForFollows(2, 3);
        auto resultTable = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult2);
        // Verify result for Follows(2, 3)
    }

    SECTION("Transitive Follows*(1, 3) is true") {
        auto parsingResult3 = createParsingResultForFollows(1, 3, true);
        auto resultTable = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult3);
        // Verify result for Follows*(1, 3)
    }

    SECTION("Transitive Follows*(1, 4) is true") {
        auto parsingResult4 = createParsingResultForFollows(1, 4, true);
        auto resultTable = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult4);
        // Verify result for Follows*(1, 4)
    }

    SECTION("Transitive Follows*(1, 5) is false") {
        auto parsingResult5 = createParsingResultForFollows(1, 5, true);
        auto resultTable = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult5);
        // Verify result for Follows*(1, 5) is correctly handled
    }
}

TEST_CASE("Check Evaluation result of a simple select follows* query") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<FollowsTWriter> followTWriter = pkbWriterManager->getFollowsTWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    followTWriter->addFollowsT(1, 2);
    followTWriter->addFollowsT(1, 3);
    followTWriter->addFollowsT(2, 3);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::FollowsT, "Follows*"),
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
    REQUIRE((res == std::unordered_set<string>{ "2", "1" } || res == std::unordered_set<string>{"1", "2"}));

}

TEST_CASE("Check Evaluation result of a simple select follows query") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    followWriter->addFollows(1, 2);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
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


TEST_CASE("Check Evaluation result of a simple select follows query (opposite)") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    followWriter->addFollows(2, 3);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
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

TEST_CASE("Check Evaluation result of a simple select followsT query") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<FollowsTWriter> followWriter = pkbWriterManager->getFollowsTWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    followWriter->addFollowsT(1, 2);
    followWriter->addFollowsT(2, 3);
    followWriter->addFollowsT(1, 3);


    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows*"),
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
    REQUIRE((res == std::unordered_set<string>{ "1", "2" } || res == std::unordered_set<string>{"2", "1"}));

}


TEST_CASE("Check Evaluation result of a simple select followsT query (opposite)") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<FollowsTWriter> followWriter = pkbWriterManager->getFollowsTWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    followWriter->addFollowsT(1, 2);
    followWriter->addFollowsT(2, 3);
    followWriter->addFollowsT(1, 3);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows*"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "1"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE((res == std::unordered_set<string>{ "3", "2" } || res == std::unordered_set<string>{"2", "3"}));

}

TEST_CASE("Check Evaluation result of a simple select s1 follows query synonyms") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    followWriter->addFollows(1, 2);
    followWriter->addFollows(2, 3);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s2"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s2"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "2", "1" });

}

TEST_CASE("Check Evaluation result of a simple select s2 follows query synonyms") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    followWriter->addFollows(1, 2);
    followWriter->addFollows(2, 3);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s2"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s2"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s2"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "3", "2" });

}

TEST_CASE("Check Evaluation result of a selecting from a false statement") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    followWriter->addFollows(1, 2);
    followWriter->addFollows(2, 3);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
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
    REQUIRE(res == std::unordered_set<string>{ });

}

