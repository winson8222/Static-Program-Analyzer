// QueryEvaluationStrategy.h
#ifndef QUERYEVALUATIONSTRATEGY_H
#define QUERYEVALUATIONSTRATEGY_H

#include <unordered_set>
#include <string>
#include "qps/parser/ParsingResult.h" // Include your ParsingResult header
#include "pkb/PKBReaderManager.h" // Include your PKBReader header
#include "qps/evaluator/ResultTable.h"


class QueryEvaluationStrategy {
public:
    virtual std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) = 0;
    virtual ~QueryEvaluationStrategy() = default;

protected:
    static void convertIntSetToStringSet(const std::unordered_set<int>& intSet, std::unordered_set<std::string>& stringSet);
    static string extractQuotedExpression(const Token& token);
    static bool isBothParamsWildcard(const Token& firstParam, const Token& secondParam);
    static bool isBothParamsSynonym(const Token& firstParam, const Token& secondParam);
    static unordered_set<int> combineFoundStatements(const unordered_set<int>& newResult, const unordered_set<int>& result);
    static unordered_set<int> getFilteredStmtsNumByType(unordered_set<int> allStatements, string stmtType, PKBReaderManager pkbReaderManager);
    static void insertColsToTable(const Token firstToken, const Token secondToken, std::shared_ptr<ResultTable> resultTable);
    static void insertRowToTable(const pair<string,string> col1Pair, const pair<string,string> col2Pair, std::shared_ptr<ResultTable> resultTable);
    static void insertSingleColRowToTable(const pair<string,string> col1Pair, std::shared_ptr<ResultTable> resultTable);
    static void insertSingleColToTable(const Token token,std::shared_ptr<ResultTable> resultTable);

    // used when there is 2 columns, example a matched with x y z, this will fill the table with ax, ay, az
    static void insertRowsWithMatchedResults(const Token& firstParam, const Token& secondParam, string searched, std::unordered_set<string> results,
                                             const std::shared_ptr<ResultTable>& resultTable);
    // used with there is only 1 column, it will fills the table with all possible results of this synonym
    static void insertRowsWithSingleColumn(string colName, std::unordered_set<std::string> results, std::shared_ptr<ResultTable> resultTable);
    static void setTrueIfRelationShipExist(const Token& firstParam, const Token& secondParam, const std::shared_ptr<IRelationshipReader<std::string, std::string> >& reader, std::shared_ptr<ResultTable> resultTable);
};

#endif //QUERYEVALUATIONSTRATEGY_H
