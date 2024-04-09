#include "StmtStmtStrategy.h"
#include <memory>
#include <string>
#include <utility>
#include <unordered_set>

bool StmtStmtStrategy::isBothParamsInteger(const Token& firstParam, const Token& secondParam) {
    // Implementation to check if both parameters are integers
    return firstParam.getType() == TokenType::INTEGER && secondParam.getType() == TokenType::INTEGER;
}

void StmtStmtStrategy::setTrueIfRelationShipExist(const Token &firstParam, const Token &secondParam,
                                                  const std::shared_ptr<IRelationshipReader<int, int>> &reader,
                                                  std::shared_ptr<ResultTable> resultTable) {
    if (firstParam.getType() == TokenType::Wildcard) {

        if (!reader->getRelationshipsByValue(std::stoi(secondParam.getValue())).empty()) {
            resultTable->setAsTruthTable();
        }
    } else if (secondParam.getType() == TokenType::Wildcard) {
        if (!reader->getRelationshipsByKey(std::stoi(firstParam.getValue())).empty()) {
            resultTable->setAsTruthTable();
        }
    } else {

        if (reader->hasRelationship(std::stoi(firstParam.getValue()), std::stoi(secondParam.getValue()))) {
            resultTable->setAsTruthTable();
        }
    }
}

void StmtStmtStrategy::insertRowsWithTwoCols(const Token &firstParam, const Token &secondParam,std::shared_ptr<IRelationshipReader<int ,int>> reader,
                                             const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable, PKBReaderManager &pkbReaderManager) {
    std::string firstParamValue = firstParam.getValue();
    std::string secondParamValue = secondParam.getValue();
    const std::string& firstStatementType = parsingResult.getRequiredSynonymType(firstParamValue);
    const std::string& secondStatementType = parsingResult.getRequiredSynonymType(secondParamValue);
    // Retrieve the relationships
    std::unordered_set<int> filteredParents;
    const std::unordered_set<int>& parents = reader->getKeys();

    filteredParents = getFilteredStmtsNumByType(parents, firstStatementType, pkbReaderManager);
    // Iterate through the preFollows set and find corresponding postFollows
    for (int stmt1 : filteredParents) {
        std::unordered_set<int> filteredChildren;
        std::unordered_set<int> children = reader->getRelationshipsByKey(stmt1);

        filteredChildren = getFilteredStmtsNumByType(children, secondStatementType, pkbReaderManager);
        // For each stmt1, iterate through all its postFollows
        for (int stmt2 : filteredChildren) {
            std::pair<std::string, std::string> col1Pair = std::make_pair<std::string, std::string>(firstParam.getValue(), std::to_string(stmt1));
            std::pair<std::string, std::string> col2Pair = std::make_pair<std::string, std::string>(secondParam.getValue(), std::to_string(stmt2));
            insertRowToTable(col1Pair, col2Pair, resultTable);
        }
    }
}



void StmtStmtStrategy::processSynonyms(std::shared_ptr<ResultTable> resultTable, const ParsingResult &parsingResult,
                                       PKBReaderManager &pkbReaderManager) {


    insertColsToTable(firstParam, secondParam, resultTable);
    // Choose the correct reader based on the variant indicating "Next" or "Next*"

    insertRowsWithTwoCols(firstParam, secondParam, reader, parsingResult, resultTable, pkbReaderManager);

}

void StmtStmtStrategy::processFirstParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {

    std::string colName = firstParam.getValue();
    resultTable->insertAllColumns({colName});
    std::unordered_set<std::string> keyStatementsInString;
    std::unordered_set<int> keyStatements;
    if (secondParam.getType() == TokenType::INTEGER) {
        int stmtNum = std::stoi(secondParam.getValue());
        // Get all statements that affect a specific statement number
        keyStatements = reader->getRelationshipsByValue(stmtNum);
    } else if (secondParam.getType() == TokenType::Wildcard) {
        // If the second parameter is a wildcard, fetch all statements that affect others
        keyStatements = reader->getKeys();
    }

    std::string statementType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    std::unordered_set<int> allFilteredAffectingStmts = getFilteredStmtsNumByType(keyStatements, statementType, pkbReaderManager);
    insertStmtRowsWithSingleCol(allFilteredAffectingStmts, resultTable, colName);
}

void StmtStmtStrategy::processSecondParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {

    std::string colName = secondParam.getValue();
    resultTable->insertAllColumns({colName});
    std::unordered_set<std::string> affectedStatementsInString;
    std::unordered_set<int> valueStatements;
    if (firstParam.getType() == TokenType::INTEGER) {
        // Specific statement number provided for the first parameter
        int stmtNum = std::stoi(firstParam.getValue());
        // Get all statements that are affected by the specific statement number
        valueStatements = reader->getRelationshipsByKey(stmtNum);
    } else if (firstParam.getType() == TokenType::Wildcard) {
        // If the first parameter is a wildcard, fetch all statements that are affected by others
        valueStatements = reader->getValues();
    }
    std::string statementType = parsingResult.getDeclaredSynonym(secondParam.getValue());
    std::unordered_set<int> allFilteredAffectedStmts = getFilteredStmtsNumByType(valueStatements, statementType, pkbReaderManager);
    insertStmtRowsWithSingleCol(allFilteredAffectedStmts, resultTable, colName);
}

void StmtStmtStrategy::processIntegerParams(std::shared_ptr<ResultTable> resultTable) {
    // Ensure both parameters are indeed integers
    bool relationshipExists;
    if (isBothParamsWildcard(firstParam, secondParam)) {
        // If both params are wildcards, we can just check if there is a next statement
        relationshipExists = !reader->getValues().empty();
        if (relationshipExists) {
            resultTable->setAsTruthTable();
        }
    } else {
        setTrueIfRelationShipExist(firstParam, secondParam, reader, resultTable);
    }
}

void StmtStmtStrategy::setReader(const std::shared_ptr<IRelationshipReader<int, int>> &reader) {
    this->reader = reader;
}



void StmtStmtStrategy::addTrueRelationshipsInResultTable(std::shared_ptr<ResultTable> newResultTable) {



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

void StmtStmtStrategy::addTrueLeftSynonymInResultTable(std::shared_ptr<ResultTable> newResultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager) {

    std::string leftSynonymName = firstParam.getValue();
    std::unordered_set<std::string> leftSynonymValues = intermediateResultTable->getColumnValues(leftSynonymName);
    std::vector<std::string> filteredLeftSynonymValues;
    std::string rightParamValue = secondParam.getValue();
    TokenType rightParamType = secondParam.getType();
    if (rightParamType == TokenType::Wildcard) {
        newResultTable->insertColumn(leftSynonymName);
        addToListIfKeyExists(leftSynonymValues, filteredLeftSynonymValues);
        newResultTable->populateWithOneColumnWithExactEntries(leftSynonymName, filteredLeftSynonymValues);
    } else if (rightParamType == TokenType::INTEGER) {
        newResultTable->insertColumn(leftSynonymName);
        addToListIfKeyRelationshipExists(leftSynonymValues, filteredLeftSynonymValues, rightParamValue);
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


void StmtStmtStrategy::addTrueRightSynonymInResultTable(std::shared_ptr<ResultTable> newResultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager) {

    std::string rightSynonymName = secondParam.getValue();
    std::unordered_set<std::string> rightSynonymValues = intermediateResultTable->getColumnValues(rightSynonymName);
    std::vector<std::string> filteredRightSynonymValues;
    std::string leftParamValue = firstParam.getValue();
    TokenType leftParamType = firstParam.getType();
    if (leftParamType == TokenType::Wildcard) {
        newResultTable->insertColumn(rightSynonymName);
        addToListIfValueExists(rightSynonymValues, filteredRightSynonymValues);
        newResultTable->populateWithOneColumnWithExactEntries(rightSynonymName, filteredRightSynonymValues);
    } else if (leftParamType == TokenType::INTEGER) {
        newResultTable->insertColumn(rightSynonymName);
        addToListIfValueRelationshipExists(rightSynonymValues, filteredRightSynonymValues, leftParamValue);
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


void StmtStmtStrategy::addToListIfKeyExists(
        const std::unordered_set<std::string>& values,
        std::vector<std::string>& filteredValues) {
    for (const auto& value : values) {
        if (reader->getRelationshipCountByKey(std::stoi(value)) > 0) {
            filteredValues.push_back(value);
        }
    }
}

void StmtStmtStrategy::addToListIfValueExists(
        const std::unordered_set<std::string>& values,
        std::vector<std::string>& filteredValues) {
    for (const auto& value : values) {
        if (reader->getRelationshipCountByValue(std::stoi(value)) > 0) {
            filteredValues.push_back(value);
        }
    }
}




void StmtStmtStrategy::addToListIfRelationshipExistsWithItself(const std::unordered_set<std::string> &values,
                                                               std::vector<std::string> &filteredValues) {
    for (const auto& value : values) {
        if (reader->hasRelationship(std::stoi(value), std::stoi(value))) {
            filteredValues.push_back(value);
        }
    }
}



void StmtStmtStrategy::addPairsToListsByKey(const std::unordered_set<std::string> &sourceKeys,
                                            const std::string &type, PKBReaderManager &pkbReaderManager,
                                            std::vector<std::string> &firstList, std::vector<std::string> &secondList) {
    for (const auto &sourceKey: sourceKeys) {
        // Fetch relationships for the source value
        std::unordered_set<int> allMatchingValues = reader->getRelationshipsByKey(std::stoi(sourceKey));

        // Filter these values by the specified type
        std::unordered_set<int> allFilteredMatchingValues = getFilteredStmtsNumByType(allMatchingValues, type,
                                                                                      pkbReaderManager);

        // Convert the set of integers to a set of strings
        std::unordered_set<std::string> allFilteredMatchingValuesInString;
        convertIntSetToStringSet(allFilteredMatchingValues, allFilteredMatchingValuesInString);

        // Add correlated values to lists
        addCorrelatedValuesToLists(sourceKey, allFilteredMatchingValuesInString, firstList, secondList);
    }
}

void StmtStmtStrategy::addPairsToListsByValue(const std::unordered_set<std::string> &sourceValues,
                                              const std::string &type, PKBReaderManager &pkbReaderManager,
                                              std::vector<std::string> &firstList,
                                              std::vector<std::string> &secondList) {

    // Iterate over each source value
    for (const auto& sourceValue : sourceValues) {
        // Fetch all matching values based on the source value
        std::unordered_set<int> allMatchingKeys = reader->getRelationshipsByValue(std::stoi(sourceValue));
        std::unordered_set<int> allFilteredMatchingKeys = getFilteredStmtsNumByType(allMatchingKeys, type, pkbReaderManager);
        std::unordered_set<std::string> allFilteredMatchingKeysInString;
        convertIntSetToStringSet(allFilteredMatchingKeys, allFilteredMatchingKeysInString);
        addCorrelatedValuesToLists(sourceValue, allFilteredMatchingKeysInString, firstList, secondList);
    }

}


void StmtStmtStrategy::addPairIfRelationshipExists(const std::unordered_set<std::string> &sourceValues,
                                                   const std::unordered_set<std::string> &targetValues,
                                                   std::vector<std::string> &sourceList,
                                                   std::vector<std::string> &targetList) {
    for (const auto& sourceValue : sourceValues) {
        for (const auto& targetValue : targetValues) {
            if (reader->hasRelationship(std::stoi(sourceValue), std::stoi(targetValue))) {
                sourceList.push_back(sourceValue);
                targetList.push_back(targetValue);
            }
        }
    }
}

void StmtStmtStrategy::addToListIfKeyRelationshipExists(const std::unordered_set<std::string> &values,
                                                        std::vector<std::string> &filteredValues,
                                                        const std::string &comparisonValue) {
    for (const auto& value : values) {
        if (reader->hasRelationship(std::stoi(value), std::stoi(comparisonValue))) {
            filteredValues.push_back(value);
        }
    }
}

void StmtStmtStrategy::addToListIfValueRelationshipExists(const std::unordered_set<std::string> &values,
                                                          std::vector<std::string> &filteredValues,
                                                          const std::string &comparisonValue) {
    for (const auto& value : values) {
        if (reader->hasRelationship(std::stoi(comparisonValue), std::stoi(value))) {
            filteredValues.push_back(value);
        }
    }
}