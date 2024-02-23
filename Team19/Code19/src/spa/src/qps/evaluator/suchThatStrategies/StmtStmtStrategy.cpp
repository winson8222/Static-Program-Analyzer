//
// Created by Winson Zheng on 15/2/24.
//

#include "StmtStmtStrategy.h"

using namespace std;



bool StmtStmtStrategy::isBothParamsInteger(const Token& firstParam, const Token& secondParam) {
    // Implementation to check if both parameters are integers
    return firstParam.getType() == TokenType::INTEGER && secondParam.getType() == TokenType::INTEGER;
}

