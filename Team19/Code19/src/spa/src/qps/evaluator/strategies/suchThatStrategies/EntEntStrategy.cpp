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
void EntEntStrategy::addTrueRelationshipsInResultTable(std::shared_ptr<ResultTable> newResultTable) {



    std::string leftSynonymName = firstParam.getValue();
    std::string rightSynonymName = secondParam.getValue();

    if (leftSynonymName == rightSynonymName) {
        const std::string& commonSynonym = leftSynonymName;
        newResultTable->insertColumn(commonSynonym);
        std::vector<std::string> filteredSynonymValues;
        std::unordered_set<std::string> allSynonymValues = intermediateResultTable->getColumnValues(commonSynonym);
        // filter unordered set using reader->hasRelationship
        addToListIfRelationshipExistsWithItself(allSynonymValues, filteredSynonymValues);
        newResultTable->populateWithOneColumnWithExactEntries(commonSynonym, filteredSynonymValues);
    } else {
        newResultTable->addColumnsSet({leftSynonymName, rightSynonymName});
        std::vector<std::string> filteredLeftSynonymValues;
        std::vector<std::string> filteredRightSynonymValues;
        std::unordered_set<std::string> allLeftSynonymsValues = intermediateResultTable->getColumnValues(leftSynonymName);
        std::unordered_set<std::string> allRightSynonymsValues = intermediateResultTable->getColumnValues(rightSynonymName);
        addPairIfRelationshipExists(allLeftSynonymsValues, allRightSynonymsValues, filteredLeftSynonymValues, filteredRightSynonymValues);
        newResultTable->populateWithTwoColumnsWithExactEntries(leftSynonymName, rightSynonymName, filteredLeftSynonymValues, filteredRightSynonymValues);
    }
}

void EntEntStrategy::addTrueLeftSynonymInResultTable(std::shared_ptr<ResultTable> newResultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager) {

    std::string leftSynonymName = firstParam.getValue();
    std::unordered_set<std::string> leftSynonymValues = intermediateResultTable->getColumnValues(leftSynonymName);
    std::vector<std::string> filteredLeftSynonymValues;
    std::string rightParamValue = secondParam.getValue();
    TokenType rightParamType = secondParam.getType();
    if (rightParamType == TokenType::Wildcard) {
        newResultTable->insertColumn(leftSynonymName);
        addToListIfKeyExists(leftSynonymValues, filteredLeftSynonymValues);
        newResultTable->populateWithOneColumnWithExactEntries(leftSynonymName, filteredLeftSynonymValues);
    } else if (rightParamType == TokenType::QuoutIDENT) {
        newResultTable->insertColumn(leftSynonymName);
        addToListIfKeyRelationshipExists(leftSynonymValues, filteredLeftSynonymValues, secondParam);
        newResultTable->populateWithOneColumnWithExactEntries(leftSynonymName, filteredLeftSynonymValues);
    } else {
        std::vector<std::string> filteredRightSynonymValues;
        std::string rightSynonymName = secondParam.getValue();
        std::string rightSynonymType = parsingResult.getRequiredSynonymType(rightSynonymName);
        newResultTable->addColumnsSet({leftSynonymName, rightSynonymName});
        addPairsToListsByKey(leftSynonymValues, rightSynonymType, pkbReaderManager, filteredLeftSynonymValues, filteredRightSynonymValues);
        newResultTable->populateWithTwoColumnsWithExactEntries(leftSynonymName, rightSynonymName, filteredLeftSynonymValues, filteredRightSynonymValues);
    }

}


void EntEntStrategy::addTrueRightSynonymInResultTable(std::shared_ptr<ResultTable> newResultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager) {

    std::string rightSynonymName = secondParam.getValue();
    std::unordered_set<std::string> rightSynonymValues = intermediateResultTable->getColumnValues(rightSynonymName);
    std::vector<std::string> filteredRightSynonymValues;
    std::string leftParamValue = firstParam.getValue();
    TokenType leftParamType = firstParam.getType();
    if (leftParamType == TokenType::Wildcard) {
        newResultTable->insertColumn(rightSynonymName);
        addToListIfValueExists(rightSynonymValues, filteredRightSynonymValues);
        newResultTable->populateWithOneColumnWithExactEntries(rightSynonymName, filteredRightSynonymValues);
    } else if (leftParamType == TokenType::QuoutIDENT) {
        newResultTable->insertColumn(rightSynonymName);
        addToListIfValueRelationshipExists(rightSynonymValues, filteredRightSynonymValues, firstParam);
        newResultTable->populateWithOneColumnWithExactEntries(rightSynonymName, filteredRightSynonymValues);
    } else {
        std::vector<std::string> filteredLeftSynonymValues;
        std::string leftSynonymName = firstParam.getValue();
        std::string leftSynonymType = parsingResult.getRequiredSynonymType(leftSynonymName);
        newResultTable->addColumnsSet({leftSynonymName, rightSynonymName});
        addPairsToListsByValue(rightSynonymValues, leftSynonymType, pkbReaderManager, filteredRightSynonymValues, filteredLeftSynonymValues);
        newResultTable->populateWithTwoColumnsWithExactEntries(leftSynonymName, rightSynonymName, filteredLeftSynonymValues, filteredRightSynonymValues);
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