
#include "catch.hpp"
#include "qps/evaluator/suchThatStrategies/StmtStmtStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"

// Derive a class from StmtStmtStrategy for testing
class TestableStmtStmtStrategy : public StmtStmtStrategy {
public:

    using StmtStmtStrategy::isBothParamsInteger; // Expose protected method
    using StmtStmtStrategy::isBothParamsWildcard; // Expose protected method

    // Implement pure virtual methods to satisfy compiler
    void processIntegerParams(const Token& firstParam, const Token& secondParam, std::shared_ptr<ResultTable> resultTable) override {}
    void processFirstParam(const Token& firstParam, const Token& secondParam, const string& variant, std::shared_ptr<ResultTable> resultTable) override {}
    void processSecondParam(const Token& firstParam, const Token& secondParam, const string& variant, std::shared_ptr<ResultTable> resultTable) override {}
};
//
//TEST_CASE("StmtStmtStrategy Protected Methods", "[StmtStmtStrategy]") {
//    TestableStmtStmtStrategy strategy;
//    Token wildcardToken(TokenType::Wildcard, "_");
//    Token integerToken(TokenType::INTEGER, "1");
//
//    SECTION("isBothParamsWildcard checks") {
//        REQUIRE(strategy.isBothParamsWildcard(wildcardToken, wildcardToken) == true);
//        REQUIRE(strategy.isBothParamsWildcard(wildcardToken, integerToken) == false);
//    }
//
//    SECTION("isBothParamsInteger checks") {
//        REQUIRE(strategy.isBothParamsInteger(integerToken, integerToken) == true);
//        REQUIRE(strategy.isBothParamsInteger(wildcardToken, integerToken) == false);
//    }
//
//    SECTION("fillResult functionality") {
//        unordered_set<int> testSet = {1, 2, 3};
//        unordered_set<string> resultSet;
//        strategy.fillResult(testSet, resultSet);
//        REQUIRE(resultSet.size() == 3);
//        REQUIRE(resultSet.find("1") != resultSet.end());
//    }
//}