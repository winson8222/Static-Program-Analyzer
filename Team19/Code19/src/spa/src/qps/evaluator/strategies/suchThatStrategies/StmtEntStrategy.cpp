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


void StmtEntStrategy::processBothSynonyms(const ParsingResult& parsingResult,
                                       std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager)
{

    // get all statements that modifies a variable
    std::unordered_set<int> allKeyStmts = reader->getKeys();
    // check what type of statement is the firstParam
    std::string statementType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    // filter the statements that modifies the variable based on the stmt type
    std::unordered_set<int> allFilteredKeyStmts;
    allFilteredKeyStmts = getFilteredStmtsNumByType(allKeyStmts,statementType, pkbReaderManager);

    // get all variables that are modified by a statement
    resultTable->addColumnsSet({firstParam.getValue(), secondParam.getValue()});
    for (int stmt: allFilteredKeyStmts) {
        std::unordered_set<std::string> allValues = reader->getRelationshipsByKey(stmt);
        std::string stmtString = std::to_string(stmt);
        insertRowsWithMatchedResults(firstParam, secondParam, stmtString, allValues, resultTable);
    }
}

void StmtEntStrategy::processFirstParam(const ParsingResult& parsingResult
        ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) {
    // get all statements that modifies a variable

    std::unordered_set<int> allKeyStmts;
    if (secondParam.getType() == TokenType::Wildcard) {
        allKeyStmts = reader->getKeys();
    } else {
        std::string unquotedValue = extractQuotedExpression(secondParam);
        allKeyStmts = reader->getRelationshipsByValue(unquotedValue);
    }
    std::string firstParamName = firstParam.getValue();

    // check what type of statement is the firstParam
    std::string statementType = parsingResult.getDeclaredSynonym(firstParamName);
    // filter the statements that modifies the variable based on the stmt type
    std::unordered_set<int> allFilteredKeyStmts;
    allFilteredKeyStmts = getFilteredStmtsNumByType(allKeyStmts,statementType, pkbReaderManager);
    // need to be changed, now is just any call statements not filtered by the proc used

    // get all filtered statements that modifies the variable
    resultTable->insertColumn(firstParamName);

    std::unordered_set<std::string> allKeyValuesInString;
    convertIntSetToStringSet(allFilteredKeyStmts, allKeyValuesInString);
    insertRowsWithSingleColumn(firstParamName, allKeyValuesInString, resultTable);

}


void StmtEntStrategy::processSecondParam(const ParsingResult &parsingResult,
                                      std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) {
    // get all variables that are modified by a statement

    std::unordered_set<std::string> allValues;
    if (firstParam.getType() == TokenType::Wildcard) {
        allValues = reader->getValues();

    } else {
        allValues = reader-> getRelationshipsByKey(
                stoi(firstParam.getValue()));
    }

    // add to result
    resultTable->insertColumn(secondParam.getValue());
    insertRowsWithSingleColumn(secondParam.getValue(), allValues, resultTable);
}

void StmtEntStrategy::processBothConstants(const ParsingResult &parsingResult,
                                        std::shared_ptr<ResultTable> resultTable) {

    if (isBothParamsWildcard(firstParam, secondParam)) {
        if (!reader->getKeys().empty()) {
            resultTable->setAsTruthTable();
        }
    } else {
        setTrueIfRelationShipExist(firstParam, secondParam, reader, resultTable);
    }
}

void StmtEntStrategy::setReader(std::shared_ptr<IRelationshipReader<int, std::string>> reader) {
    this->reader = reader;
}





void StmtEntStrategy::addToListIfKeyExists(
        const std::unordered_set<std::string>& values,
        std::vector<std::string>& filteredValues) {
    for (const auto& value : values) {
        if (reader->getRelationshipCountByKey(std::stoi(value)) > 0) {
            filteredValues.push_back(value);
        }
    }
}

void StmtEntStrategy::addToListIfValueExists(
        const std::unordered_set<std::string>& values,
        std::vector<std::string>& filteredValues) {
    for (const auto& value : values) {
        if (reader->getRelationshipCountByValue(value) > 0) {
            filteredValues.push_back(value);
        }
    }
}




void StmtEntStrategy::addToListIfRelationshipExistsWithItself(const std::unordered_set<std::string> &values,
                                                               std::vector<std::string> &filteredValues) {
    for (const auto& value : values) {
        if (reader->hasRelationship(std::stoi(value), value)) {
            filteredValues.push_back(value);
        }
    }
}



void StmtEntStrategy::addPairsToListsByKey(const std::unordered_set<std::string> &sourceKeys,
                                            const std::string &type, PKBReaderManager &pkbReaderManager,
                                            std::vector<std::string> &firstList, std::vector<std::string> &secondList) {
    for (const auto &sourceKey: sourceKeys) {
        // Fetch relationships for the source value
        std::unordered_set<std::string> allMatchingValues = reader->getRelationshipsByKey(std::stoi(sourceKey));


        // Add correlated values to lists
        addCorrelatedValuesToLists(sourceKey, allMatchingValues, firstList, secondList);
    }
}

void StmtEntStrategy::addPairsToListsByValue(const std::unordered_set<std::string> &sourceValues,
                                              const std::string &type, PKBReaderManager &pkbReaderManager,
                                              std::vector<std::string> &firstList,
                                              std::vector<std::string> &secondList) {

    // Iterate over each source value
    for (const auto& sourceValue : sourceValues) {
        // Fetch all matching values based on the source value
        std::unordered_set<int> allMatchingKeys = reader->getRelationshipsByValue(sourceValue);
        std::unordered_set<int> allFilteredMatchingKeys = getFilteredStmtsNumByType(allMatchingKeys, type, pkbReaderManager);
        std::unordered_set<std::string> allFilteredMatchingKeysInString;
        convertIntSetToStringSet(allFilteredMatchingKeys, allFilteredMatchingKeysInString);
        addCorrelatedValuesToLists(sourceValue, allFilteredMatchingKeysInString, firstList, secondList);
    }

}


void StmtEntStrategy::addPairIfRelationshipExists(const std::unordered_set<std::string> &sourceValues,
                                                   const std::unordered_set<std::string> &targetValues,
                                                   std::vector<std::string> &sourceList,
                                                   std::vector<std::string> &targetList) {
    for (const auto& sourceValue : sourceValues) {
        for (const auto& targetValue : targetValues) {
            if (reader->hasRelationship(std::stoi(sourceValue), targetValue)) {
                sourceList.push_back(sourceValue);
                targetList.push_back(targetValue);
            }
        }
    }
}

void StmtEntStrategy::addToListIfKeyRelationshipExists(const std::unordered_set<std::string> &values,
                                                       std::vector<std::string> &filteredValues,
                                                       const Token &comparisonToken) {
    std::string comparisonValue = extractQuotedExpression(comparisonToken);
    for (const auto& value : values) {
        if (reader->hasRelationship(std::stoi(value), comparisonValue)) {
            filteredValues.push_back(value);
        }
    }
}

void StmtEntStrategy::addToListIfValueRelationshipExists(const std::unordered_set<std::string> &values,
                                                         std::vector<std::string> &filteredValues,
                                                         const Token &comparisonToken)  {
    std::string comparisonValue = comparisonToken.getValue();
    for (const auto& value : values) {
        if (reader->hasRelationship(std::stoi(comparisonValue), value)) {
            filteredValues.push_back(value);
        }
    }
}