#include "EntEntStrategy.h"
#include <memory>
#include <string>

void EntEntStrategy::setTrueIfRelationShipExist(const Token& firstParam, const Token& secondParam,
	const std::shared_ptr<IRelationshipReader<std::string, std::string>>& reader,
	std::shared_ptr<ResultTable> resultTable) {
	if (firstParam.getType() == TokenType::Wildcard) {
		std::string secondParamValue = extractQuotedExpression(secondParam);
		if (!reader->getRelationshipsByValue(secondParamValue).empty()) {
			resultTable->setAsTruthTable();
		}
	}
	else if (secondParam.getType() == TokenType::Wildcard) {
		std::string firstParamValue = extractQuotedExpression(firstParam);
		if (!reader->getRelationshipsByKey(firstParamValue).empty()) {
			resultTable->setAsTruthTable();
		}
	}
	else {
		std::string firstParamValue = extractQuotedExpression(firstParam);
		std::string secondParamValue = extractQuotedExpression(secondParam);

		if (reader->hasRelationship(firstParamValue, secondParamValue)) {
			resultTable->setAsTruthTable();
		}
	}
}
