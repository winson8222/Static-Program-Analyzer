//
// Created by Winson Zheng on 22/2/24.
//

#include "qps/evaluator/strategies/suchThatStrategies/EntEntStrategy.h"
void EntEntStrategy::setTrueIfRelationShipExist(const Token &firstParam, const Token &secondParam,
                                                         const std::shared_ptr<IRelationshipReader<std::string, std::string>> &reader,
                                                         std::shared_ptr<ResultTable> resultTable) {
    if (firstParam.getType() == TokenType::Wildcard) {
        string secondParamValue = extractQuotedExpression(secondParam);
        if (!reader->getRelationshipsByValue(secondParamValue).empty()) {
            resultTable->setAsTruthTable();
        }
    } else if (secondParam.getType() == TokenType::Wildcard) {
        string firstParamValue = extractQuotedExpression(firstParam);
        if (!reader->getRelationshipsByKey(firstParamValue).empty()) {
            resultTable->setAsTruthTable();
        }
    } else {
        string firstParamValue = extractQuotedExpression(firstParam);
        string secondParamValue = extractQuotedExpression(secondParam);

        if (reader->hasRelationship(firstParamValue, secondParamValue)) {
            resultTable->setAsTruthTable();
        }
    }

}
