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