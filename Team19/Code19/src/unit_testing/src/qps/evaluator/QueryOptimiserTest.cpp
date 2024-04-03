#include "catch.hpp"
#include "qps/evaluator/QueryOptimiser.h"
#include "qps/parser/clauses/Clause.h"
#include "qps/parser/clauses/SuchThatClause.h"
#include <memory>



TEST_CASE("qps/evaluator/QueryOptimiser with Single Clause") {


    std::vector<std::shared_ptr<Clause>> clauses;
    auto firstClause = std::make_shared<SuchThatClause>();

    Token firstParam = Token(TokenType::IDENT, "s");
    firstClause->setFirstParam(firstParam);
    Token secondParam = Token(TokenType::IDENT, "v");
    firstClause->setSecondParam(secondParam);
    Token relationship = Token(TokenType::Follows, "Follows");
    firstClause->setRelationship(relationship);

    clauses.push_back(firstClause);

    SECTION("with single Clause") {
        QueryOptimiser queryOptimiser = QueryOptimiser(clauses);
        std::vector<std::shared_ptr<QueryGroup>> queryGroups = queryOptimiser.optimise(true);
        REQUIRE(queryGroups.size() == 1);
        REQUIRE(queryGroups[0]->getClauses()[0]->getFirstParam().isEqual(firstParam));
        REQUIRE(queryGroups[0]->getClauses()[0]->getSecondParam().isEqual(secondParam));
        REQUIRE(queryGroups[0]->getClauses()[0]->getRelationship().isEqual(relationship));
        REQUIRE(queryGroups[0]->getCommonSynonyms() == std::unordered_set<std::string>{"s", "v"});
    }

    SECTION("With additional Clauses") {
        auto secondClause = std::make_shared<SuchThatClause>();
        Token firstParam2 = Token(TokenType::IDENT, "v");
        secondClause->setFirstParam(firstParam2);
        Token secondParam2 = Token(TokenType::QuoutIDENT, "\"x\"");
        secondClause->setSecondParam(secondParam2);
        Token relationship2 = Token(TokenType::Follows, "Follows");
        secondClause->setRelationship(relationship2);
        clauses.push_back(secondClause);

        QueryOptimiser queryOptimiser = QueryOptimiser(clauses);
        std::vector<std::shared_ptr<QueryGroup>> queryGroups = queryOptimiser.optimise(true);
        REQUIRE(queryGroups.size() == 1);
        REQUIRE(queryGroups[0]->getClauses()[0]->getFirstParam().isEqual(firstParam));
        REQUIRE(queryGroups[0]->getClauses()[0]->getSecondParam().isEqual(secondParam));
        REQUIRE(queryGroups[0]->getClauses()[0]->getRelationship().isEqual(relationship));
        REQUIRE(queryGroups[0]->getClauses()[1]->getFirstParam().isEqual(firstParam2));
        REQUIRE(queryGroups[0]->getClauses()[1]->getSecondParam().isEqual(secondParam2));
        REQUIRE(queryGroups[0]->getClauses()[1]->getRelationship().isEqual(relationship2));
        REQUIRE(queryGroups[0]->getCommonSynonyms() == std::unordered_set<std::string>{"s", "v"});
    }

    SECTION("With unrelated Clauses with no Synonyms") {
        auto secondClause = std::make_shared<SuchThatClause>();
        Token firstParam2 = Token(TokenType::QuoutIDENT, "\"k\"");
        secondClause->setFirstParam(firstParam2);
        Token secondParam2 = Token(TokenType::QuoutIDENT, "\"x\"");
        secondClause->setSecondParam(secondParam2);
        Token relationship2 = Token(TokenType::UsesS, "Uses");
        secondClause->setRelationship(relationship2);
        clauses.push_back(secondClause);

        QueryOptimiser queryOptimiser = QueryOptimiser(clauses);
        std::vector<std::shared_ptr<QueryGroup>> queryGroups = queryOptimiser.optimise(true);
        REQUIRE(queryGroups.size() == 2);
        REQUIRE(queryGroups[0]->getClauses()[0]->getFirstParam().isEqual(firstParam));
        REQUIRE(queryGroups[0]->getClauses()[0]->getSecondParam().isEqual(secondParam));
        REQUIRE(queryGroups[0]->getClauses()[0]->getRelationship().isEqual(relationship));
        REQUIRE(queryGroups[0]->getCommonSynonyms() == std::unordered_set<std::string>{"s", "v"});
        REQUIRE(queryGroups[1]->getClauses()[0]->getFirstParam().isEqual(firstParam2));
        REQUIRE(queryGroups[1]->getClauses()[0]->getSecondParam().isEqual(secondParam2));
        REQUIRE(queryGroups[1]->getClauses()[0]->getRelationship().isEqual(relationship2));
        REQUIRE(queryGroups[1]->getCommonSynonyms().empty());
    }

}

TEST_CASE("Overlapping Grouping") {
    std::vector<std::shared_ptr<Clause>> clauses;
    auto firstClause = std::make_shared<SuchThatClause>();

    Token firstParam = Token(TokenType::IDENT, "s");
    firstClause->setFirstParam(firstParam);
    Token secondParam = Token(TokenType::IDENT, "v");
    firstClause->setSecondParam(secondParam);
    Token relationship = Token(TokenType::Follows, "Follows");
    firstClause->setRelationship(relationship);

    clauses.push_back(firstClause);




    auto secondClause = std::make_shared<SuchThatClause>();
    Token firstParam2 = Token(TokenType::QuoutIDENT, "\"k\"");
    secondClause->setFirstParam(firstParam2);
    Token secondParam2 = Token(TokenType::QuoutIDENT, "\"x\"");
    secondClause->setSecondParam(secondParam2);
    Token relationship2 = Token(TokenType::UsesS, "Uses");
    secondClause->setRelationship(relationship2);
    clauses.push_back(secondClause);

    auto thirdClause = std::make_shared<SuchThatClause>();
    Token firstParam3 = Token(TokenType::IDENT, "s");
    thirdClause->setFirstParam(firstParam3);
    Token secondParam3 = Token(TokenType::IDENT, "x");
    thirdClause->setSecondParam(secondParam3);
    Token relationship3 = Token(TokenType::Follows, "Follows");
    thirdClause->setRelationship(relationship3);
    clauses.push_back(thirdClause);

    QueryOptimiser queryOptimiser = QueryOptimiser(clauses);
    std::vector<std::shared_ptr<QueryGroup>> queryGroups = queryOptimiser.optimise(true);
    REQUIRE(queryGroups.size() == 2);
    REQUIRE(queryGroups[0]->getClauses()[0]->getFirstParam().isEqual(firstParam));
    REQUIRE(queryGroups[0]->getClauses()[0]->getSecondParam().isEqual(secondParam));
    REQUIRE(queryGroups[0]->getClauses()[0]->getRelationship().isEqual(relationship));
    REQUIRE(queryGroups[0]->getClauses()[1]->getFirstParam().isEqual(firstParam3));
    REQUIRE(queryGroups[0]->getClauses()[1]->getSecondParam().isEqual(secondParam3));
    REQUIRE(queryGroups[0]->getClauses()[1]->getRelationship().isEqual(relationship3));
    REQUIRE(queryGroups[0]->getCommonSynonyms() == std::unordered_set<std::string>{"s", "v", "x"});
    REQUIRE(queryGroups[1]->getClauses()[0]->getFirstParam().isEqual(firstParam2));
    REQUIRE(queryGroups[1]->getClauses()[0]->getSecondParam().isEqual(secondParam2));
    REQUIRE(queryGroups[1]->getClauses()[0]->getRelationship().isEqual(relationship2));
    REQUIRE(queryGroups[1]->getCommonSynonyms().empty());
}


TEST_CASE("Non Overlapping Grouping of Synonyms") {
    std::vector<std::shared_ptr<Clause>> clauses;
    auto firstClause = std::make_shared<SuchThatClause>();

    Token firstParam = Token(TokenType::IDENT, "s");
    firstClause->setFirstParam(firstParam);
    Token secondParam = Token(TokenType::IDENT, "v");
    firstClause->setSecondParam(secondParam);
    Token relationship = Token(TokenType::Follows, "Follows");
    firstClause->setRelationship(relationship);

    clauses.push_back(firstClause);


    auto secondClause = std::make_shared<SuchThatClause>();
    Token firstParam2 = Token(TokenType::QuoutIDENT, "\"k\"");
    secondClause->setFirstParam(firstParam2);
    Token secondParam2 = Token(TokenType::QuoutIDENT, "\"x\"");
    secondClause->setSecondParam(secondParam2);
    Token relationship2 = Token(TokenType::UsesS, "Uses");
    secondClause->setRelationship(relationship2);
    clauses.push_back(secondClause);

    auto thirdClause = std::make_shared<SuchThatClause>();
    Token firstParam3 = Token(TokenType::IDENT, "y");
    thirdClause->setFirstParam(firstParam3);
    Token secondParam3 = Token(TokenType::IDENT, "x");
    thirdClause->setSecondParam(secondParam3);
    Token relationship3 = Token(TokenType::Follows, "Follows");
    thirdClause->setRelationship(relationship3);
    clauses.push_back(thirdClause);

    QueryOptimiser queryOptimiser = QueryOptimiser(clauses);
    std::vector<std::shared_ptr<QueryGroup>> queryGroups = queryOptimiser.optimise(true);
    REQUIRE(queryGroups.size() == 3);
    REQUIRE(queryGroups[0]->getClauses()[0]->getFirstParam().isEqual(firstParam));
    REQUIRE(queryGroups[0]->getClauses()[0]->getSecondParam().isEqual(secondParam));
    REQUIRE(queryGroups[0]->getClauses()[0]->getRelationship().isEqual(relationship));

    REQUIRE(queryGroups[0]->getCommonSynonyms() == std::unordered_set<std::string>{"s", "v"});
    REQUIRE(queryGroups[1]->getClauses()[0]->getFirstParam().isEqual(firstParam2));
    REQUIRE(queryGroups[1]->getClauses()[0]->getSecondParam().isEqual(secondParam2));
    REQUIRE(queryGroups[1]->getClauses()[0]->getRelationship().isEqual(relationship2));
    REQUIRE(queryGroups[1]->getCommonSynonyms().empty());
    REQUIRE(queryGroups[2]->getClauses()[0]->getFirstParam().isEqual(firstParam3));
    REQUIRE(queryGroups[2]->getClauses()[0]->getSecondParam().isEqual(secondParam3));
    REQUIRE(queryGroups[2]->getClauses()[0]->getRelationship().isEqual(relationship3));
    REQUIRE(queryGroups[2]->getCommonSynonyms() == std::unordered_set<std::string>{"y", "x"});

}


TEST_CASE("Non Overlapping Grouping of Synonyms changed order of clauses") {
    std::vector<std::shared_ptr<Clause>> clauses;
    auto firstClause = std::make_shared<SuchThatClause>();

    Token firstParam = Token(TokenType::IDENT, "s");
    firstClause->setFirstParam(firstParam);
    Token secondParam = Token(TokenType::IDENT, "v");
    firstClause->setSecondParam(secondParam);
    Token relationship = Token(TokenType::Follows, "Follows");
    firstClause->setRelationship(relationship);

    clauses.push_back(firstClause);


    auto thirdClause = std::make_shared<SuchThatClause>();
    Token firstParam3 = Token(TokenType::IDENT, "y");
    thirdClause->setFirstParam(firstParam3);
    Token secondParam3 = Token(TokenType::IDENT, "x");
    thirdClause->setSecondParam(secondParam3);
    Token relationship3 = Token(TokenType::Follows, "Follows");
    thirdClause->setRelationship(relationship3);
    clauses.push_back(thirdClause);


    auto secondClause = std::make_shared<SuchThatClause>();
    Token firstParam2 = Token(TokenType::QuoutIDENT, "\"k\"");
    secondClause->setFirstParam(firstParam2);
    Token secondParam2 = Token(TokenType::QuoutIDENT, "\"x\"");
    secondClause->setSecondParam(secondParam2);
    Token relationship2 = Token(TokenType::UsesS, "Uses");
    secondClause->setRelationship(relationship2);
    clauses.push_back(secondClause);


    QueryOptimiser queryOptimiser = QueryOptimiser(clauses);
    std::vector<std::shared_ptr<QueryGroup>> queryGroups = queryOptimiser.optimise(true);
    REQUIRE(queryGroups.size() == 3);
    REQUIRE(queryGroups[0]->getClauses()[0]->getFirstParam().isEqual(firstParam));
    REQUIRE(queryGroups[0]->getClauses()[0]->getSecondParam().isEqual(secondParam));
    REQUIRE(queryGroups[0]->getClauses()[0]->getRelationship().isEqual(relationship));

    REQUIRE(queryGroups[0]->getCommonSynonyms() == std::unordered_set<std::string>{"s", "v"});
    REQUIRE(queryGroups[2]->getClauses()[0]->getFirstParam().isEqual(firstParam2));
    REQUIRE(queryGroups[2]->getClauses()[0]->getSecondParam().isEqual(secondParam2));
    REQUIRE(queryGroups[2]->getClauses()[0]->getRelationship().isEqual(relationship2));
    REQUIRE(queryGroups[2]->getCommonSynonyms().empty());
    REQUIRE(queryGroups[1]->getClauses()[0]->getFirstParam().isEqual(firstParam3));
    REQUIRE(queryGroups[1]->getClauses()[0]->getSecondParam().isEqual(secondParam3));
    REQUIRE(queryGroups[1]->getClauses()[0]->getRelationship().isEqual(relationship3));
    REQUIRE(queryGroups[1]->getCommonSynonyms() == std::unordered_set<std::string>{"y", "x"});

}


TEST_CASE("Sorting of Groups") {
    std::vector<std::shared_ptr<Clause>> clauses;
    auto firstClause = std::make_shared<SuchThatClause>();

    Token firstParam = Token(TokenType::IDENT, "s");
    firstClause->setFirstParam(firstParam);
    Token secondParam = Token(TokenType::IDENT, "v");
    firstClause->setSecondParam(secondParam);
    Token relationship = Token(TokenType::Follows, "Follows");
    firstClause->setRelationship(relationship);

    clauses.push_back(firstClause);
    clauses.push_back(firstClause);



    auto thirdClause = std::make_shared<SuchThatClause>();
    Token firstParam3 = Token(TokenType::IDENT, "y");
    thirdClause->setFirstParam(firstParam3);
    Token secondParam3 = Token(TokenType::IDENT, "x");
    thirdClause->setSecondParam(secondParam3);
    Token relationship3 = Token(TokenType::Follows, "Follows");
    thirdClause->setRelationship(relationship3);
    clauses.push_back(thirdClause);
    clauses.push_back(thirdClause);
    clauses.push_back(thirdClause);



    auto secondClause = std::make_shared<SuchThatClause>();
    Token firstParam2 = Token(TokenType::QuoutIDENT, "\"k\"");
    secondClause->setFirstParam(firstParam2);
    Token secondParam2 = Token(TokenType::QuoutIDENT, "\"x\"");
    secondClause->setSecondParam(secondParam2);
    Token relationship2 = Token(TokenType::UsesS, "Uses");
    secondClause->setRelationship(relationship2);
    clauses.push_back(secondClause);


    QueryOptimiser queryOptimiser = QueryOptimiser(clauses);
    std::vector<std::shared_ptr<QueryGroup>> queryGroups = queryOptimiser.optimise(true);
    REQUIRE(queryGroups.size() == 3);
    REQUIRE(queryGroups[0]->getClauses().size()== 3);
    REQUIRE(queryGroups[0]->getClauses()[0]->getFirstParam().isEqual(firstParam3));
    REQUIRE(queryGroups[0]->getClauses()[0]->getSecondParam().isEqual(secondParam3));
    REQUIRE(queryGroups[0]->getClauses()[0]->getRelationship().isEqual(relationship3));
    REQUIRE(queryGroups[1]->getClauses().size() == 2);
    REQUIRE(queryGroups[1]->getClauses()[0]->getFirstParam().isEqual(firstParam));
    REQUIRE(queryGroups[1]->getClauses()[0]->getSecondParam().isEqual(secondParam));
    REQUIRE(queryGroups[1]->getClauses()[0]->getRelationship().isEqual(relationship));
    REQUIRE(queryGroups[2]->getClauses().size() == 1);
    REQUIRE(queryGroups[2]->getClauses()[0]->getFirstParam().isEqual(firstParam2));
    REQUIRE(queryGroups[2]->getClauses()[0]->getSecondParam().isEqual(secondParam2));
    REQUIRE(queryGroups[2]->getClauses()[0]->getRelationship().isEqual(relationship2));




}