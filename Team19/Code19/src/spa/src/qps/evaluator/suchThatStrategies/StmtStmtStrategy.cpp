//
// Created by Winson Zheng on 15/2/24.
//

#include "StmtStmtStrategy.h"

using namespace std;


bool StmtStmtStrategy::isBothParamsWildcard(const Token& firstParam, const Token& secondParam) {
    // Implementation to check if both parameters are wildcards
    return firstParam.getType() == TokenType::Wildcard && secondParam.getType() == TokenType::Wildcard;
}

bool StmtStmtStrategy::isBothParamsInteger(const Token& firstParam, const Token& secondParam) {
    // Implementation to check if both parameters are integers
    return firstParam.getType() == TokenType::INTEGER && secondParam.getType() == TokenType::INTEGER;
}

void StmtStmtStrategy::fillResult(const unordered_set<int> &follows, unordered_set<std::string> &result) {
    for (int statement : follows) {
        result.insert(to_string(statement));
    }
}
