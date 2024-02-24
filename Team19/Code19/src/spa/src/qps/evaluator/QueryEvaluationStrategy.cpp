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
    } else {
        throw "Invalid Query!";
    }

    return filteredResult;
}