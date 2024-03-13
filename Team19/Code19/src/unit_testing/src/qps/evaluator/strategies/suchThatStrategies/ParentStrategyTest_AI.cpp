
#include "catch.hpp"
#include "qps/evaluator/strategies/suchThatStrategies/ParentStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"

ParsingResult createParsingResultForParent(int stmt1, int stmt2, bool isTransitive = false) {
    ParsingResult parsingResult;
    TokenType relationshipType = isTransitive ? TokenType::ParentT : TokenType::Parent;
    SuchThatClause clause;
    clause.setRelationship(Token(relationshipType, ""));
    clause.setFirstParam(Token(TokenType::INTEGER, std::to_string(stmt1)));
    clause.setSecondParam(Token(TokenType::INTEGER, std::to_string(stmt2)));
    parsingResult.addSuchThatClause(clause);
    return parsingResult;
}

TEST_CASE("src/qps/evaluator/suchThatStrategies/ParentStrategy/1") {
    auto pkb = std::make_shared<PKB>();
    auto ParentStore = pkb->getParentStore();
    ParentStore->addRelationship(1, 2);
    ParentStore->addRelationship(2, 3);
    ParentStore->addRelationship(3, 4);
    ParentStore->addRelationship(1, 3);
    ParentStore->addRelationship(1, 4);

    auto pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
    ParentStrategy ParentStrategy;

    SECTION("Direct Parent(1, 2) is true") {
        auto parsingResult = createParsingResultForParent(1, 2);
        auto result = ParentStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        REQUIRE(result->isTableTrue());
    }

    SECTION("Direct Parent(2, 3) is true") {
        auto parsingResult = createParsingResultForParent(2, 3);
        auto result = ParentStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        REQUIRE(result->isTableTrue());
    }

    SECTION("Transitive Parent*(1, 3) is true") {
        auto parsingResult = createParsingResultForParent(1, 3, true);
        auto result = ParentStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        REQUIRE(result->isTableTrue());
    }

    SECTION("Transitive Parent*(1, 4) is true") {
        auto parsingResult = createParsingResultForParent(1, 4, true);
        auto result = ParentStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        REQUIRE(result->isTableTrue());
    }

    SECTION("Transitive Parent*(1, 5) is false") {
        auto parsingResult = createParsingResultForParent(1, 5, true);
        auto result = ParentStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        REQUIRE_FALSE(result->isTableTrue()); // Expecting this to be false as no such relationship exists
    }
}

TEST_CASE("src/qps/evaluator/suchThatStrategies/ParentStrategy/2") {
std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    parentWriter->addParent(1, 2);
    parentWriter->addParent(2, 3);
    parentWriter->addParent(1, 3);

    ParentStrategy parentStrategy;


    SECTION("Verifying Direct Parent Relation: Parent of Statement 2") {
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

    SECTION("Verifying Direct Parent Relation: Children of Statement 2") {
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


    SECTION("Verifying Transitive Parent Relation: Parent* of Statement 3") {
        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::ParentT, "Parent*"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::INTEGER, "1"),
                Token(TokenType::Comma, ","),
                Token(TokenType::INTEGER, "3"),
                Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{"1", "2"});
    }

    SECTION("Verifying Parent Relation for Same Statement") {
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
                Token(TokenType::INTEGER, "1"),
                Token(TokenType::Comma, ","),
                Token(TokenType::INTEGER, "1"),  // Same statement as parent and child
                Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res.empty());
    }

    SECTION("Verifying No Parent Relation") {
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
                Token(TokenType::INTEGER, "1"),
                Token(TokenType::Comma, ","),
                Token(TokenType::INTEGER, "4"),  // Statement 4 has no parent
                Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res.empty());
    }

    SECTION("Verifying Parent Relation with Invalid Statement Numbers") {
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
                Token(TokenType::INTEGER, "10"),  // Invalid statement number
                Token(TokenType::Comma, ","),
                Token(TokenType::INTEGER, "2"),
                Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res.empty());
    }

    SECTION("Selecting tuple of parents") {
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
                Token(TokenType::Parent, "Parent"),
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
//        REQUIRE(res == std::unordered_set<string>{ "1 2", "2 3"});
    }

    SECTION("Selecting true boolean") {

        std::vector<Token> tokens = {
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::BooleanKeyword, "BOOLEAN"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Parent, "Parent"),
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

    SECTION("Selecting false boolean") {

        std::vector<Token> tokens = {
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::BooleanKeyword, "BOOLEAN"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Parent, "Parent"),
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

    SECTION("Selecting true boolean with stmt") {

        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::BooleanKeyword, "BOOLEAN"),
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
        REQUIRE(res == std::unordered_set<string>{ "TRUE" });

    }
}

