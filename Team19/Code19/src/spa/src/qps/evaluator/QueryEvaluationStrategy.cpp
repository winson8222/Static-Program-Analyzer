#include "QueryEvaluationStrategy.h"
#include <regex>
#include <string>
#include <unordered_set>
#include <memory>

void QueryEvaluationStrategy::convertIntSetToStringSet(const std::unordered_set<int>& intSet, std::unordered_set<std::string>& stringSet) {
    for (int i : intSet) {
        stringSet.insert(std::to_string(i));
    }
}

std::string QueryEvaluationStrategy::extractQuotedExpression(const Token& token) {    // extract the quoted expression from the token using regex
    std::regex pattern(R"(["](.*?)["])");
    std::smatch matches;
    std::string tokenValue = token.getValue();
    if (std::regex_search(tokenValue, matches, pattern) && matches.size() > 1) {
        // If a quoted expression is found, return the first captured group
        return matches[1].str();
    } else {
        // If no quoted expression is found, return the original token value
        return tokenValue;
    }
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
std::unordered_set<int> QueryEvaluationStrategy::combineFoundStatements(const std::unordered_set<int> &newResult,
                                                                        const std::unordered_set<int> &result) {
    std::unordered_set<int> combinedResult;
    for (const auto& elem : newResult) {
        if (std::find(result.begin(), result.end(), elem) != result.end()) {
            combinedResult.insert(elem);
        }
    }
    return combinedResult;
}

const std::unordered_map<std::string, std::function<std::shared_ptr<IEntityReader<int>>(PKBReaderManager&)>> stmtTypeToEntities = {
        {"read",   [](PKBReaderManager &manager) -> std::shared_ptr<IEntityReader<int>> {
            return manager.getReadReader();
        }},
        {"assign", [](PKBReaderManager &manager) -> std::shared_ptr<IEntityReader<int>> {
            return manager.getAssignReader();
        }},
        {"while",  [](PKBReaderManager &manager) -> std::shared_ptr<IEntityReader<int>> {
            return manager.getWhileReader();
        }},
        {"if",     [](PKBReaderManager &manager) -> std::shared_ptr<IEntityReader<int>> {
            return manager.getIfReader();
        }},
        {"print",  [](PKBReaderManager &manager) -> std::shared_ptr<IEntityReader<int>> {
            return manager.getPrintReader();
        }},
        {"call",   [](PKBReaderManager &manager) -> std::shared_ptr<IEntityReader<int>> {
            return manager.getCallReader();
        }}

};


// Get the statements numbers based on the type of statement
std::unordered_set<int> QueryEvaluationStrategy::getFilteredStmtsNumByType(std::unordered_set<int> allStatements, std::string statementType, PKBReaderManager& pkbReaderManager) {
    std::unordered_set<int> filteredResult;
    std::unordered_set<int> allFoundEntities;
    std::shared_ptr<IEntityReader<int>> entityReader;

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

void QueryEvaluationStrategy::insertRowToTable(const std::pair<std::string,std::string> col1Pair, const std::pair<std::string,std::string> col2Pair, std::shared_ptr<ResultTable> resultTable) {
    std::string colName1 = col1Pair.first;
    std::string colName2 = col2Pair.first;
    std::string stmt1 = col1Pair.second;
    std::string stmt2 = col2Pair.second;

    if (colName1 == colName2) {
        if (stmt1 == stmt2) {
            resultTable->insertNewRow({{colName1, stmt1}});
        }
    } else {
        std::unordered_map<std::string, std::string> row;
        row[colName1] = stmt1;
        row[colName2] = stmt2;
        resultTable->insertNewRow(row);
    }
}

void QueryEvaluationStrategy::insertSingleColRowToTable(const std::pair<std::string,std::string> col1Pair, std::shared_ptr<ResultTable> resultTable) {
    std::string colName1 = col1Pair.first;
    std::string stmt1 = col1Pair.second;
    resultTable->insertNewRow({{colName1, stmt1}});
}

bool QueryEvaluationStrategy::isBothParamsSynonym(const Token& firstParam, const Token& secondParam) {
    return firstParam.getType() == TokenType::IDENT && secondParam.getType() == TokenType::IDENT;
}

void QueryEvaluationStrategy::insertRowsWithMatchedResults(const Token& firstParam, const Token& secondParam, std::string searched, std::unordered_set<std::string> results,
                                                           const std::shared_ptr<ResultTable>& resultTable) {
    std::pair<std::string, std::string> col1Pair = std::make_pair<std::string, std::string>(firstParam.getValue(), std::move(searched));
    for (std::string result : results) {
        std::pair<std::string, std::string> col2Pair = std::make_pair<std::string, std::string>(secondParam.getValue(), std::move(result));
        insertRowToTable(col1Pair, col2Pair, resultTable);
    }
}

void QueryEvaluationStrategy::insertStmtRowsWithSingleCol(std::unordered_set<int> filteredStmts, std::shared_ptr<ResultTable> resultTable, std::string colName){
    std::unordered_set<std::string> filteredStmtsStr;
    convertIntSetToStringSet(filteredStmts,filteredStmtsStr);
    insertRowsWithSingleColumn(colName, filteredStmtsStr, resultTable);
}

void QueryEvaluationStrategy::insertRowsWithSingleColumn(std::string colName, std::unordered_set<std::string> results,
                                                         std::shared_ptr<ResultTable> resultTable) {
    for (std::string result : results) {
        std::pair<std::string, std::string> colPair = make_pair(colName, std::move(result));
        insertSingleColRowToTable(colPair, resultTable);
    }
}

std::shared_ptr<ResultTable> QueryEvaluationStrategy::getIntermediateResultTable() {
    return intermediateResultTable;
}

void QueryEvaluationStrategy::setIntermediateResultTable(std::shared_ptr<ResultTable> resultTable) {
    intermediateResultTable = resultTable;
}

bool QueryEvaluationStrategy::hasCommonSynonyms(std::unordered_set<std::string> synonyms,
                                                std::shared_ptr<ResultTable> resultTable) {
    for (const std::string& synonym : synonyms) {
        if (resultTable->hasColumn(synonym)) {
            return true;
        }
    }
    return false;
}

bool QueryEvaluationStrategy::hasBothCommonSynonyms(const Clause &clause, std::shared_ptr<ResultTable> resultTable) {
    if (clause.getFirstParam().getType() == TokenType::IDENT && clause.getSecondParam().getType() == TokenType::IDENT) {
        return resultTable->hasColumn(clause.getFirstParam().getValue()) && resultTable->hasColumn(clause.getSecondParam().getValue());
    }
    return false;
}

bool QueryEvaluationStrategy::hasLeftCommonSynonym(const Clause &clause, std::shared_ptr<ResultTable> resultTable) {
    if (clause.getFirstParam().getType() == TokenType::IDENT) {
        return resultTable->hasColumn(clause.getFirstParam().getValue());
    }
    return false;
}

bool QueryEvaluationStrategy::hasRightCommonSynonym(const Clause &clause, std::shared_ptr<ResultTable> resultTable) {
    if (clause.getSecondParam().getType() == TokenType::IDENT) {
        return resultTable->hasColumn(clause.getSecondParam().getValue());
    }
    return false;
}



