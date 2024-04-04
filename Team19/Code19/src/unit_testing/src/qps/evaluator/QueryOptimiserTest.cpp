#include "catch.hpp"
#include "qps/evaluator/QueryOptimiser.h"
#include "qps/parser/clauses/Clause.h"
#include "qps/parser/clauses/SuchThatClause.h"
#include "qps/parser/Tokenizer.h"
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
        REQUIRE(queryGroups[0]->getClauses()[0]->getFirstParam().isEqual(firstParam2));
        REQUIRE(queryGroups[0]->getClauses()[0]->getSecondParam().isEqual(secondParam2));
        REQUIRE(queryGroups[0]->getClauses()[0]->getRelationship().isEqual(relationship2));
        REQUIRE(queryGroups[0]->getClauses()[1]->getFirstParam().isEqual(firstParam));
        REQUIRE(queryGroups[0]->getClauses()[1]->getSecondParam().isEqual(secondParam));
        REQUIRE(queryGroups[0]->getClauses()[1]->getRelationship().isEqual(relationship));
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
    REQUIRE(queryGroups[0]->getClauses().size() == 1);

}

TEST_CASE("Sorting of Related Groups") {
    std::vector<std::shared_ptr<Clause>> clauses;
    auto firstClause = std::make_shared<SuchThatClause>();

    Token firstParam = Token(TokenType::IDENT, "s");
    firstClause->setFirstParam(firstParam);
    Token secondParam = Token(TokenType::IDENT, "v");
    firstClause->setSecondParam(secondParam);
    Token relationship = Token(TokenType::Follows, "Follows");
    firstClause->setRelationship(relationship);

    auto secondClause = std::make_shared<SuchThatClause>();
    Token first2Param = Token(TokenType::IDENT, "i");
    secondClause->setFirstParam(first2Param);
    Token second2Param = Token(TokenType::IDENT, "v");
    secondClause ->setSecondParam(second2Param);
    Token relationship2 = Token(TokenType::Follows, "Follows");
    secondClause->setRelationship(relationship2);

    auto thirdClause = std::make_shared<SuchThatClause>();
    Token first3Param = Token(TokenType::IDENT, "i");
    thirdClause->setFirstParam(first3Param);
    Token second3Param = Token(TokenType::IDENT, "j");
    thirdClause->setSecondParam(second3Param);
    Token relationship3 = Token(TokenType::Follows, "Follows");
    thirdClause->setRelationship(relationship3);

    auto fourthClause = std::make_shared<SuchThatClause>();
    Token first4Param = Token(TokenType::IDENT, "s");
    fourthClause->setFirstParam(first4Param);
    Token second4Param = Token(TokenType::IDENT, "v");
    fourthClause->setSecondParam(second4Param);
    Token relationship4 = Token(TokenType::Follows, "Follows");
    fourthClause->setRelationship(relationship4);


    clauses.push_back(firstClause);
    clauses.push_back(secondClause);
    clauses.push_back(thirdClause);
    clauses.push_back(fourthClause);




    QueryOptimiser queryOptimiser = QueryOptimiser(clauses);
    std::vector<std::shared_ptr<QueryGroup>> queryGroups = queryOptimiser.optimise(true);
    REQUIRE(queryGroups.size() == 1);

}


TEST_CASE("Intra Group sorting of Related Groups") {
    std::vector<std::shared_ptr<Clause>> clauses;
    auto firstClause = std::make_shared<SuchThatClause>();

    Token firstParam = Token(TokenType::IDENT, "s");
    firstClause->setFirstParam(firstParam);
    Token secondParam = Token(TokenType::IDENT, "v");
    firstClause->setSecondParam(secondParam);
    Token relationship = Token(TokenType::Follows, "Follows");
    firstClause->setRelationship(relationship);

    auto secondClause = std::make_shared<SuchThatClause>();
    Token first2Param = Token(TokenType::IDENT, "i");
    secondClause->setFirstParam(first2Param);
    Token second2Param = Token(TokenType::IDENT, "v");
    secondClause ->setSecondParam(second2Param);
    Token relationship2 = Token(TokenType::Follows, "Follows");
    secondClause->setRelationship(relationship2);

    auto thirdClause = std::make_shared<SuchThatClause>();
    Token first3Param = Token(TokenType::IDENT, "i");
    thirdClause->setFirstParam(first3Param);
    Token second3Param = Token(TokenType::IDENT, "j");
    thirdClause->setSecondParam(second3Param);
    Token relationship3 = Token(TokenType::Follows, "Follows");
    thirdClause->setRelationship(relationship3);

    auto fourthClause = std::make_shared<SuchThatClause>();
    Token first4Param = Token(TokenType::IDENT, "s");
    fourthClause->setFirstParam(first4Param);
    Token second4Param = Token(TokenType::IDENT, "v");
    fourthClause->setSecondParam(second4Param);
    Token relationship4 = Token(TokenType::Follows, "Follows");
    fourthClause->setRelationship(relationship4);

    auto fifthClause = std::make_shared<SuchThatClause>();
    Token first5Param = Token(TokenType::IDENT, "s");
    fifthClause->setFirstParam(first5Param);
    Token second5Param = Token(TokenType::QuoutIDENT, "\"s\"");
    fifthClause->setSecondParam(second5Param);
    Token relationship5 = Token(TokenType::Follows, "Follows");
    fifthClause->setRelationship(relationship5);

    auto sixthClause = std::make_shared<SuchThatClause>();
    Token first6Param = Token(TokenType::QuoutIDENT, "\"s\"");
    sixthClause->setFirstParam(first6Param);
    Token second6Param = Token(TokenType::IDENT, "i");
    sixthClause->setSecondParam(second6Param);
    Token relationship6 = Token(TokenType::Follows, "Follows");
    sixthClause->setRelationship(relationship6);


    auto seventhClause = std::make_shared<SuchThatClause>();
    Token first7Param = Token(TokenType::QuoutIDENT, "\"s\"");
    seventhClause->setFirstParam(first7Param);
    Token second7Param = Token(TokenType::QuoutIDENT, "\"s\"");
    seventhClause->setSecondParam(second7Param);
    Token relationship7 = Token(TokenType::Follows, "Follows");
    seventhClause->setRelationship(relationship7);

    auto eighthClause = std::make_shared<SuchThatClause>();
    Token first8Param = Token(TokenType::QuoutIDENT, "\"s\"");
    eighthClause->setFirstParam(first8Param);
    Token second8Param = Token(TokenType::QuoutIDENT, "\"s\"");
    eighthClause->setSecondParam(second8Param);
    Token relationship8 = Token(TokenType::Follows, "Follows");
    eighthClause->setRelationship(relationship8);

    auto ninthClause = std::make_shared<SuchThatClause>();
    Token first9Param = Token(TokenType::QuoutIDENT, "\"s\"");
    ninthClause->setFirstParam(first9Param);
    Token second9Param = Token(TokenType::QuoutIDENT, "\"s\"");
    ninthClause->setSecondParam(second9Param);
    Token relationship9 = Token(TokenType::Affects, "Affects");
    ninthClause->setRelationship(relationship9);




    clauses.push_back(firstClause);
    clauses.push_back(secondClause);
    clauses.push_back(thirdClause);
    clauses.push_back(eighthClause);
    clauses.push_back(fourthClause);
    clauses.push_back(fifthClause);
    clauses.push_back(sixthClause);
    clauses.push_back(seventhClause);
    clauses.push_back(ninthClause);


    QueryOptimiser queryOptimiser = QueryOptimiser(clauses);
    std::vector<std::shared_ptr<QueryGroup>> queryGroups = queryOptimiser.optimise(true);
    REQUIRE(queryGroups.size() == 2);
}


