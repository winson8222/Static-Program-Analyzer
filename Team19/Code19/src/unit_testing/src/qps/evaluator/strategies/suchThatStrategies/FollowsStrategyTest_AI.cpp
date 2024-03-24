
#include "catch.hpp"
#include "qps/evaluator/strategies/suchThatStrategies/FollowsStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"

ParsingResult createParsingResultForFollows(int stmt1, int stmt2, bool isTransitive = false) {
    ParsingResult parsingResult;
    TokenType relationshipType = isTransitive ? TokenType::FollowsT : TokenType::Follows;
    SuchThatClause clause;
    string relationShipString = isTransitive ? "Follows*" : "Follows";
    clause.setRelationship(Token(relationshipType, relationShipString));
    clause.setFirstParam(Token(TokenType::INTEGER, std::to_string(stmt1)));
    clause.setSecondParam(Token(TokenType::INTEGER, std::to_string(stmt2)));
    parsingResult.addSuchThatClause(clause);
    return parsingResult;
}

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/1") {
    auto pkb = std::make_shared<PKB>();
    auto followsStore = pkb->getFollowsStore();
    auto followsTStore = pkb->getFollowsTStore();
    followsTStore->addRelationship(1, 3);
    followsTStore->addRelationship(1, 4);
    followsStore->addRelationship(1, 2);
    followsStore->addRelationship(2, 3);
    followsStore->addRelationship(3, 4);
    followsStore->addRelationship(1, 3);
    followsStore->addRelationship(1, 4);

    auto pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
    FollowsStrategy followsStrategy;


    SECTION("Direct Follows(1, 2) is true") {
        auto parsingResult = createParsingResultForFollows(1, 2);
        auto result = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        REQUIRE(result->isTableTrue());
    }

    SECTION("Direct Follows(2, 3) is true") {
        auto parsingResult = createParsingResultForFollows(2, 3);
        auto result = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        REQUIRE(result->isTableTrue());
    }

    SECTION("Transitive Follows*(1, 3) is true") {
        auto parsingResult = createParsingResultForFollows(1, 3, true);
        auto result = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        REQUIRE(result->isTableTrue());
    }

    SECTION("Transitive Follows*(1, 4) is true") {
        auto parsingResult = createParsingResultForFollows(1, 4, true);
        auto result = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        REQUIRE(result->isTableTrue());
    }

    SECTION("Transitive Follows*(1, 5) is false") {
        auto parsingResult = createParsingResultForFollows(1, 5, true);
        auto result = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        REQUIRE_FALSE(result->isTableTrue()); // Expecting this to be false as no such relationship exists
    }
}

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/2") {
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

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/3") {
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

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/4") {
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

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/5") {
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

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/6") {
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

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/7") {
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

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/8") {
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

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/9") {
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

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/10") {
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
            Token(TokenType::LeftAngleBracket, "<"),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s2"),
            Token(TokenType::RightAngleBracket, ">"),
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
    REQUIRE(res == std::unordered_set<string>{ "1 2", "2 3" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/11") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    followWriter->addFollows(1, 2);
    followWriter->addFollows(1, 3);
    followWriter->addFollows(2, 3);

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s3"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s4"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::LeftAngleBracket, "<"),
            Token(TokenType::IDENT, "s3"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s4"),
            Token(TokenType::RightAngleBracket, ">"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "1"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s3"),
            Token(TokenType::Rparenthesis, ")"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s4"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "2"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"3 1", "2 1"});

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/12") {
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
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::BooleanKeyword, "BOOLEAN"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "1"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "2"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "TRUE" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/13") {
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
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::BooleanKeyword, "BOOLEAN"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "2"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "1"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "FALSE" });

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/14") {
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
            Token(TokenType::BooleanKeyword, "BOOLEAN"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
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
    REQUIRE(res == std::unordered_set<string>{ "TRUE" });

}

//multi-clause
TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/15") {
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
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::Rparenthesis, ")"),

            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s1"),
            Token(TokenType::Comma, ","),
            Token(TokenType::INTEGER, "3"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{ "2" });

}
//stmt s; variable v;
//Select s such that Follows*(s, _) and Uses(s, v)
TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/16") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<FollowsTWriter> followWriter = pkbWriterManager->getFollowsTWriter();
    std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    statementWriter->insertStatement(5);
    followWriter->addFollowsT(1, 2);
    followWriter->addFollowsT(2, 3);
    followWriter->addFollowsT(1, 3);
    followWriter->addFollowsT(4, 5);
    usesWriter->addUsesS(1, "x");
    usesWriter->addUsesS(2, "y");
    usesWriter->addUsesS(3, "z");


    SECTION("Query for stmt with FollowsT with Uses Clause") {

        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::FollowsT, "Follows*"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")"),
                Token(TokenType::AndKeyword, "such that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{ "1","2" });
    }

    SECTION("Query for variable used by followedT statements") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::FollowsT, "Follows*"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Rparenthesis, ")"),
                Token(TokenType::AndKeyword, "such that"),
                Token(TokenType::Uses, "Uses"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{ "y", "z" });

    }

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/FollowsStrategy/17 Select AttrRef") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<FollowsTWriter> followWriter = pkbWriterManager->getFollowsTWriter();
    std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    followWriter->addFollowsT(1, 2);
    followWriter->addFollowsT(2, 3);
    followWriter->addFollowsT(1, 3);
    usesWriter->addUsesS(1, "x");
    usesWriter->addUsesS(2, "y");
    usesWriter->addUsesS(3, "z");
    variableWriter->insertVariable("x");
    variableWriter->insertVariable("y");
    variableWriter->insertVariable("z");

    pkbManager->getPKBCacheManager()->populateCache();



    SECTION("Simple stmt# AttrRef") {


        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "stmt#"),
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{ "1","2", "3" });

    }

    SECTION("Simple varName AttrRef Test") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "variable"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "v"),
                Token(TokenType::Dot, "."),
                Token(TokenType::AttrName, "varName"),
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{ "x","y", "z" });
    }

}

TEST_CASE("Select Boolean Follows(1, _)") {
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
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::BooleanKeyword, "BOOLEAN"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "1"),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "TRUE" });

}