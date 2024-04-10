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

void EntEntStrategy::setReader(const std::shared_ptr<IRelationshipReader<std::string, std::string>> &reader) {
    this->reader = reader;
}

std::shared_ptr<IRelationshipReader<std::string, std::string>> EntEntStrategy::getReader() {
    return reader;
}

void EntEntStrategy::processBothSynonyms(const ParsingResult &parsingResult,
                                        std::shared_ptr<ResultTable> resultTable) {
    // get the types of both synonyms

    std::string firstParamType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    std::string secondParamType = parsingResult.getDeclaredSynonym(secondParam.getValue());
    insertColsToTable(firstParam, secondParam, resultTable);

    if (firstParamType == "procedure") {
        std::unordered_set<std::string> allProcs = reader->getKeys();
//                this->usesPReader->getAllProcsThatUseAnyVariable();

        for (std::string proc : allProcs) {
            std::unordered_set<std::string> allVars =
                    reader->getRelationshipsByKey(proc);
            // copy the value of procs to a rvalue string
            insertRowsWithMatchedResults(firstParam, secondParam, proc, allVars, resultTable);
        }
    }
}


void EntEntStrategy::processFirstParam(const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable) {

    std::string colName = firstParam.getValue();
    insertSingleColToTable(firstParam, resultTable);
    std::unordered_set<std::string> allProcs;
    if (secondParam.getType() == TokenType::QuoutIDENT) {
        std::string secondParamValue = extractQuotedExpression(secondParam);
        allProcs = reader->getRelationshipsByValue(secondParamValue);

    } else {
        // it is a wildcard
        allProcs = reader->getKeys();

    }
    insertRowsWithSingleColumn(colName, allProcs, resultTable);
}

void EntEntStrategy::processSecondParam(const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable) {

    std::string colName = secondParam.getValue();
    insertSingleColToTable(secondParam, resultTable);
    std::unordered_set<std::string> allVars;
    if (firstParam.getType() == TokenType::QuoutIDENT) {
        std::string firstParamValue = extractQuotedExpression(firstParam);
        allVars = reader->getRelationshipsByKey(firstParamValue);

    } else {
        // it is a wildcard
        allVars = reader->getValues();

    }
    insertRowsWithSingleColumn(colName, allVars, resultTable);
}

void EntEntStrategy::processBothConstants(const ParsingResult &parsingResult,
                                         std::shared_ptr<ResultTable> resultTable) {

    if (isBothParamsWildcard(firstParam, secondParam)) {
        if (!reader->getKeys().empty()) {
            resultTable->setAsTruthTable();
        }
    } else {
        setTrueIfRelationShipExist(firstParam, secondParam, reader, resultTable);
    }
}


void EntEntStrategy::addToListIfKeyExists(
        const std::unordered_set<std::string>& values,
        std::vector<std::string>& filteredValues) {
    for (const auto& value : values) {
        if (reader->getRelationshipCountByKey(value) > 0) {
            filteredValues.push_back(value);
        }
    }
}

void EntEntStrategy::addToListIfValueExists(
        const std::unordered_set<std::string>& values,
        std::vector<std::string>& filteredValues) {
    for (const auto& value : values) {
        if (reader->getRelationshipCountByValue(value) > 0) {
            filteredValues.push_back(value);
        }
    }
}




void EntEntStrategy::addToListIfRelationshipExistsWithItself(const std::unordered_set<std::string> &values,
                                                              std::vector<std::string> &filteredValues) {
    for (const auto& value : values) {
        if (reader->hasRelationship(value, value)) {
            filteredValues.push_back(value);
        }
    }
}



void EntEntStrategy::addPairsToListsByKey(const std::unordered_set<std::string> &sourceKeys,
                                           const std::string &type, PKBReaderManager &pkbReaderManager,
                                           std::vector<std::string> &firstList, std::vector<std::string> &secondList) {
    for (const auto &sourceKey: sourceKeys) {
        // Fetch relationships for the source value
        std::unordered_set<std::string> allMatchingValues = reader->getRelationshipsByKey(sourceKey);


        // Add correlated values to lists
        addCorrelatedValuesToLists(sourceKey, allMatchingValues, firstList, secondList);
    }
}

void EntEntStrategy::addPairsToListsByValue(const std::unordered_set<std::string> &sourceValues,
                                             const std::string &type, PKBReaderManager &pkbReaderManager,
                                             std::vector<std::string> &firstList,
                                             std::vector<std::string> &secondList) {

    // Iterate over each source value
    for (const auto& sourceValue : sourceValues) {
        // Fetch all matching values based on the source value
        std::unordered_set<std::string> allMatchingKeys = reader->getRelationshipsByValue(sourceValue);
        addCorrelatedValuesToLists(sourceValue, allMatchingKeys, firstList, secondList);
    }

}


void EntEntStrategy::addPairIfRelationshipExists(const std::unordered_set<std::string> &sourceValues,
                                                  const std::unordered_set<std::string> &targetValues,
                                                  std::vector<std::string> &sourceList,
                                                  std::vector<std::string> &targetList) {
    for (const auto& sourceValue : sourceValues) {
        for (const auto& targetValue : targetValues) {
            if (reader->hasRelationship(sourceValue, targetValue)) {
                sourceList.push_back(sourceValue);
                targetList.push_back(targetValue);
            }
        }
    }
}

void EntEntStrategy::addToListIfKeyRelationshipExists(const std::unordered_set<std::string> &values,
                                                       std::vector<std::string> &filteredValues,
                                                       const Token &comparisonToken) {
    std::string comparisonValue = extractQuotedExpression(comparisonToken);
    for (const auto& value : values) {
        if (reader->hasRelationship(value, comparisonValue)) {
            filteredValues.push_back(value);
        }
    }
}

void EntEntStrategy::addToListIfValueRelationshipExists(const std::unordered_set<std::string> &values,
                                                         std::vector<std::string> &filteredValues,
                                                         const Token &comparisonToken)  {
    std::string comparisonValue = extractQuotedExpression(comparisonToken);
    for (const auto& value : values) {
        if (reader->hasRelationship(comparisonValue, value)) {
            filteredValues.push_back(value);
        }
    }
}

std::shared_ptr<ResultTable> EntEntStrategy::getEvaluatedResultTable(PKBReaderManager &pkbReaderManager,
                                                                     const ParsingResult &parsingResult,
                                                                     std::shared_ptr<ResultTable> resultTable) {
    if (isBothParamsSynonym(firstParam, secondParam)) {
        this->processBothSynonyms(parsingResult, resultTable);
    } else if (isParamOfType(firstParam, TokenType::IDENT)) {
        this->processFirstParam(parsingResult, resultTable);
    } else if (isParamOfType(secondParam, TokenType::IDENT)) {
        this->processSecondParam(parsingResult, resultTable);
    } else {
        this->processBothConstants(parsingResult, resultTable);
    }

    return resultTable;
}