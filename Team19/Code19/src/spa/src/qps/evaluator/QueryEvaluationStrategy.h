#pragma once

#include <unordered_set>
#include <string>
#include "qps/evaluator/ResultTable.h"
#include "qps/parser/ParsingResult.h" // Include your ParsingResult header
#include "pkb/PKBReaderManager.h" // Include your PKBReader header

class QueryEvaluationStrategy {

public:
    virtual std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) = 0;
    virtual std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause, const std::shared_ptr<ResultTable>& resultTable) {
        return std::make_shared<ResultTable>();
    }
    virtual ~QueryEvaluationStrategy() = default;

protected:
    static void convertIntSetToStringSet(const std::unordered_set<int>& intSet, std::unordered_set<std::string>& stringSet);
    static std::string extractQuotedExpression(const Token& token);
    static bool isBothParamsWildcard(const Token& firstParam, const Token& secondParam);
    static bool isBothParamsSynonym(const Token& firstParam, const Token& secondParam);
    static std::unordered_set<int> combineFoundStatements(const std::unordered_set<int>& newResult, const std::unordered_set<int>& result);
    static std::unordered_set<int> getFilteredStmtsNumByType(std::unordered_set<int> allStatements, std::string stmtType, PKBReaderManager& pkbReaderManager);
    static void insertColsToTable(const Token firstToken, const Token secondToken, std::shared_ptr<ResultTable> resultTable);
    static void insertRowToTable(const std::pair<std::string,std::string> col1Pair, const std::pair<std::string,std::string> col2Pair, std::shared_ptr<ResultTable> resultTable);
    static void insertSingleColRowToTable(const std::pair<std::string,std::string> col1Pair, std::shared_ptr<ResultTable> resultTable);
    static void insertSingleColToTable(const Token token,std::shared_ptr<ResultTable> resultTable);

    // used when there is 2 columns, example a matched with x y z, this will fill the table with ax, ay, az
    static void insertRowsWithMatchedResults(const Token& firstParam, const Token& secondParam, std::string searched, std::unordered_set<std::string> results,
                                             const std::shared_ptr<ResultTable>& resultTable);
    // used with there is only 1 column, it will fills the table with all possible results of this synonym
    static void insertRowsWithSingleColumn(std::string colName, std::unordered_set<std::string> results, std::shared_ptr<ResultTable> resultTable);
    static void insertStmtRowsWithSingleCol(std::unordered_set<int> filteredStmts, std::shared_ptr<ResultTable> resultTable, std::string colName);
};
