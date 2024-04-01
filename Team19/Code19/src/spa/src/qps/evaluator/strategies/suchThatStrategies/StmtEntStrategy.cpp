#include "StmtEntStrategy.h"
#include <memory>
#include <string>

void StmtEntStrategy::setTrueIfRelationShipExist(const Token &firstParam, const Token &secondParam,
                                                  const std::shared_ptr<IRelationshipReader<int, std::string>> &reader,
                                                  std::shared_ptr<ResultTable> resultTable) {

    if (firstParam.getType() == TokenType::Wildcard) {
        std::string secondParamValue = extractQuotedExpression(secondParam);
        if (!reader->getRelationshipsByValue(secondParamValue).empty()) {
            resultTable->setAsTruthTable();
        }
    } else if (secondParam.getType() == TokenType::Wildcard) {
        if (!reader->getRelationshipsByKey(stoi(firstParam.getValue())).empty()) {
            resultTable->setAsTruthTable();
        }
    } else {
        std::string secondParamValue = extractQuotedExpression(secondParam);
        if (reader->hasRelationship(stoi(firstParam.getValue()), secondParamValue)) {
            resultTable->setAsTruthTable();
        }
    }

}
