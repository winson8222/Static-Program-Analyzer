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

// Get the statements numbers based on the type of statement
unordered_set<int> QueryEvaluationStrategy::getFilteredStmtsNumByType(unordered_set<int> allStatements, string statementType, PKBReaderManager pkbReaderManager) {
    unordered_set<int> filteredResult;
    if (statementType == "stmt") {
        filteredResult = allStatements;
    } else if (statementType == "read") {
        std::shared_ptr<ReadReader> readReader = pkbReaderManager.getReadReader();
        std::unordered_set<int> allReadStmts = readReader->getAllReads();
        filteredResult = combineFoundStatements(allStatements, allReadStmts);
    } else if (statementType == "assign") {
        std::shared_ptr<AssignReader> assignReader = pkbReaderManager.getAssignReader();
        std::unordered_set<int> allAssignStmts = assignReader->getAllAssigns();
        filteredResult = combineFoundStatements(allStatements, allAssignStmts);
    } else if (statementType == "while") {
        std::shared_ptr<WhileReader> whileReader = pkbReaderManager.getWhileReader();
        std::unordered_set<int> allWhileStmts = whileReader->getAllWhiles();
        filteredResult = combineFoundStatements(allStatements, allWhileStmts);
    } else if (statementType == "if") {
        std::shared_ptr<IfReader> ifReader = pkbReaderManager.getIfReader();
        std::unordered_set<int> allIfStmts = ifReader->getAllIfs();
        filteredResult = combineFoundStatements(allStatements, allIfStmts);
    } else if (statementType == "print") {
        std::shared_ptr<PrintReader> printReader = pkbReaderManager.getPrintReader();
        std::unordered_set<int> allPrintStmts = printReader->getAllPrints();
        filteredResult = combineFoundStatements(allStatements, allPrintStmts);
    } else if (statementType == "call") {

        std::shared_ptr<CallReader> callReader = pkbReaderManager.getCallReader();
        std::unordered_set<int> allCallStmts = callReader->getAllCalls();
        filteredResult = combineFoundStatements(allStatements, allCallStmts);
    }

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