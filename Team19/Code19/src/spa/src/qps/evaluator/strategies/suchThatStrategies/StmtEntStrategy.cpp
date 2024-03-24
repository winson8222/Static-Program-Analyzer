//
// Created by Winson Zheng on 22/2/24.
//

#include "StmtEntStrategy.h"


void StmtEntStrategy::setTrueIfRelationShipExist(const Token &firstParam, const Token &secondParam,
                                                  const std::shared_ptr<IRelationshipReader<int, string>> &reader,
                                                  std::shared_ptr<ResultTable> resultTable) {

    if (firstParam.getType() == TokenType::Wildcard) {
        string secondParamValue = extractQuotedExpression(secondParam);
        if (!reader->getRelationshipsByValue(secondParamValue).empty()) {
            resultTable->setAsTruthTable();
        }
    } else if (secondParam.getType() == TokenType::Wildcard) {
        if (!reader->getRelationshipsByKey(stoi(firstParam.getValue())).empty()) {
            resultTable->setAsTruthTable();
        }
    } else {
        string secondParamValue = extractQuotedExpression(secondParam);
        if (reader->hasRelationship(stoi(firstParam.getValue()), secondParamValue)) {
            resultTable->setAsTruthTable();
        }
    }

}