//
// Created by Winson Zheng on 21/2/24.
//
#include "QueryEvaluationStrategy.h"
#include <regex>

void QueryEvaluationStrategy::convertIntSetToStringSet(const std::unordered_set<int>& intSet, std::unordered_set<std::string>& stringSet) {
    for (int i : intSet) {
        stringSet.insert(std::to_string(i));
    }
}

string QueryEvaluationStrategy::extractQuotedExpression(const Token& token) {    // extract the quoted expression from the token using regex
    regex pattern(R"(["](.*?)["])");
    smatch matches;
    string tokenValue = token.getValue();
    std::regex_search(tokenValue, matches, pattern);
    return matches[1].str();
}


bool QueryEvaluationStrategy::isBothParamsWildcard(const Token& firstParam, const Token& secondParam) {
    // Implementation to check if both parameters are wildcards
    return firstParam.getType() == TokenType::Wildcard && secondParam.getType() == TokenType::Wildcard;
}

/**
 * Combines the results of right-hand side (RHS) processing with the left-hand side (LHS) results.
 * @param newResult - The new statements to be combined.
 * @param result - The existing set of statements numbers to be updated.
 * @return The updated set of statements numbers.
 */
std::unordered_set<int> QueryEvaluationStrategy::combineFoundStatements(const unordered_set<int> &newResult,
                                                                        const unordered_set<int> &result) {
    std::unordered_set<int> combinedResult;
    for (const auto& elem : newResult) {
        if (std::find(result.begin(), result.end(), elem) != result.end()) {
            combinedResult.insert(elem);
        }
    }
    return combinedResult;
}

const unordered_map<string, std::function<shared_ptr<IEntityReader<int>>(PKBReaderManager&)>> stmtTypeToEntities = {
        {"read",   [](PKBReaderManager &manager) -> shared_ptr<IEntityReader<int>> {
            return manager.getReadReader();
        }},
        {"assign", [](PKBReaderManager &manager) -> shared_ptr<IEntityReader<int>> {
            return manager.getAssignReader();
        }},
        {"while",  [](PKBReaderManager &manager) -> shared_ptr<IEntityReader<int>> {
            return manager.getWhileReader();
        }},
        {"if",     [](PKBReaderManager &manager) -> shared_ptr<IEntityReader<int>> {
            return manager.getIfReader();
        }},
        {"print",  [](PKBReaderManager &manager) -> shared_ptr<IEntityReader<int>> {
            return manager.getPrintReader();
        }},
        {"call",   [](PKBReaderManager &manager) -> shared_ptr<IEntityReader<int>> {
            return manager.getCallReader();
        }}

};


// Get the statements numbers based on the type of statement
unordered_set<int> QueryEvaluationStrategy::getFilteredStmtsNumByType(unordered_set<int> allStatements, string statementType, PKBReaderManager& pkbReaderManager) {
    unordered_set<int> filteredResult;
    std::unordered_set<int> allFoundEntities;
    shared_ptr<IEntityReader<int>> entityReader;

    if (statementType == "stmt") {
        return allStatements;
    }

    if (stmtTypeToEntities.find(statementType) != stmtTypeToEntities.end()) {
        entityReader = stmtTypeToEntities.at(statementType)(pkbReaderManager);
    }

    allFoundEntities = entityReader->getAllEntities();
    filteredResult = combineFoundStatements(allStatements, allFoundEntities);


    return filteredResult;
}

void QueryEvaluationStrategy::insertSingleColToTable(const Token token,std::shared_ptr<ResultTable> resultTable) {
    std::string colName = token.getValue();
    resultTable->insertAllColumns({colName});

}

void QueryEvaluationStrategy::insertColsToTable(const Token firstToken, const Token secondToken, std::shared_ptr<ResultTable> resultTable) {
    std::string colName1 = firstToken.getValue();
    std::string colName2 = secondToken.getValue();

    // check if the same synonym is being referred to
    if (colName1 == colName2) {
        resultTable->insertAllColumns({colName1});
    } else {
        resultTable->insertAllColumns({colName1, colName2});
    }
}

void QueryEvaluationStrategy::insertRowToTable(const pair<string,string> col1Pair, const pair<string,string> col2Pair, std::shared_ptr<ResultTable> resultTable) {
    std::string colName1 = col1Pair.first;
    std::string colName2 = col2Pair.first;
    std::string stmt1 = col1Pair.second;
    std::string stmt2 = col2Pair.second;

    if (colName1 == colName2) {
        if (stmt1 == stmt2) {
            resultTable->insertNewRow({{colName1, stmt1}});
        }
    } else {
        unordered_map<string, string> row;
        row[colName1] = stmt1;
        row[colName2] = stmt2;
        resultTable->insertNewRow(row);
    }
}

void QueryEvaluationStrategy::insertSingleColRowToTable(const pair<string,string> col1Pair, std::shared_ptr<ResultTable> resultTable) {
    std::string colName1 = col1Pair.first;
    std::string stmt1 = col1Pair.second;
    resultTable->insertNewRow({{colName1, stmt1}});
}

bool QueryEvaluationStrategy::isBothParamsSynonym(const Token& firstParam, const Token& secondParam) {
    return firstParam.getType() == TokenType::IDENT && secondParam.getType() == TokenType::IDENT;
}

void QueryEvaluationStrategy::insertRowsWithMatchedResults(const Token& firstParam, const Token& secondParam, string searched, std::unordered_set<string> results,
                                                           const std::shared_ptr<ResultTable>& resultTable) {
    pair<string, string> col1Pair = make_pair<string, string>(firstParam.getValue(), std::move(searched));
    for (string result : results) {
        pair<string, string> col2Pair = make_pair<string, string>(secondParam.getValue(), std::move(result));
        insertRowToTable(col1Pair, col2Pair, resultTable);
    }
}

void QueryEvaluationStrategy::insertStmtRowsWithSingleCol(unordered_set<int> filteredStmts, shared_ptr<ResultTable> resultTable, string colName){
    unordered_set<string> filteredStmtsStr;
    convertIntSetToStringSet(filteredStmts,filteredStmtsStr);
    insertRowsWithSingleColumn(colName, filteredStmtsStr, resultTable);
}

void QueryEvaluationStrategy::insertRowsWithSingleColumn(std::string colName, std::unordered_set<std::string> results,
                                                         std::shared_ptr<ResultTable> resultTable) {
    for (string result : results) {
        pair<string, string> colPair = make_pair(colName, std::move(result));
        insertSingleColRowToTable(colPair, resultTable);
    }
}

