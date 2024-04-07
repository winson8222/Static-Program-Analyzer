#include "qps/evaluator/strategies/suchThatStrategies/NextStrategy.h"
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

std::shared_ptr<ResultTable> NextStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                    const ParsingResult &parsingResult,
                                                                    const Clause &clause,
                                                                    std::shared_ptr<ResultTable> result) {
    // Determine if we're dealing with Next or Next*
    const auto* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->variant = suchClause->getRelationship().getValue();
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<int, int>> reader;
    if (variant == "Next") {
        reader = pkbReaderManager.getNextReader();
    } else if (variant == "Next*") {
        reader = pkbReaderManager.getNextTReader();
    }
    setReader(reader);


    // Get the parameters
    Token firstParam = getFirstParam();
    Token secondParam = getSecondParam();

    setIntermediateResultTable(result);
    std::unordered_set<std::string> allSynonyms = clause.getAllSynonyms();
    if (!hasCommonSynonyms(allSynonyms, result)) {
        std::shared_ptr<ResultTable> newResults = evaluateQuery(pkbReaderManager, parsingResult, clause);
        return newResults;
    }

    auto optimisedResultTable = std::make_shared<ResultTable>();

    if (hasBothCommonSynonyms(clause, result)) {
        addTrueRelationshipsInResultTable(optimisedResultTable);
    } else if (hasLeftCommonSynonym(clause, result)) {
        addTrueLeftSynonymInResultTable(optimisedResultTable, parsingResult, pkbReaderManager);
    } else if (hasRightCommonSynonym(clause, result)) {
        addTrueRightSynonymInResultTable(optimisedResultTable, parsingResult, pkbReaderManager);
    } else {
        return evaluateQuery(pkbReaderManager, parsingResult, clause);
    }
    return optimisedResultTable;

}

std::shared_ptr<ResultTable> NextStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();
    const auto* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->variant = suchClause->getRelationship().getValue();
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<int, int>> reader;
    if (variant == "Next") {
        reader = pkbReaderManager.getNextReader();
    } else if (variant == "Next*") {
        reader = pkbReaderManager.getNextTReader();
    }
    setReader(reader);

    Token firstParam = getFirstParam();
    Token secondParam = getSecondParam();



    // Process based on token types
    if (isBothParamsSynonym(firstParam, secondParam)) {
        processSynonyms(resultTable, parsingResult, pkbReaderManager);
    } else if (firstParam.getType() == TokenType::IDENT) {
        processFirstParam(resultTable, parsingResult, pkbReaderManager);
    } else if (secondParam.getType() == TokenType::IDENT) {
        processSecondParam(resultTable, parsingResult, pkbReaderManager);
    } else {
        processIntegerParams(resultTable);
    }

    return resultTable;
}


void NextStrategy::addTrueRelationshipsInResultTable(std::shared_ptr<ResultTable> newResultTable) {
    Token firstParam = getFirstParam();
    Token secondParam = getSecondParam();

    std::shared_ptr<ResultTable> result = getIntermediateResultTable();
    std::string leftSynonymName = firstParam.getValue();
    std::string rightSynonymName = secondParam.getValue();
    std::shared_ptr<IRelationshipReader<int, int>> reader = getReader();
    if (leftSynonymName == rightSynonymName) {
        const std::string& commonSynonym = leftSynonymName;
        newResultTable->insertColumn(commonSynonym);
        std::vector<std::string> filteredSynonymValues;
        std::unordered_set<std::string> allSynonymValues = result->getColumnValues(commonSynonym);
        // filter unordered set using reader->hasRelationship
        for (const auto& value : allSynonymValues) {
            if (reader->hasRelationship(std::stoi(value), std::stoi(value))) {
                filteredSynonymValues.push_back(value);
            }
        }
        newResultTable->populateWithOneColumnWithExactEntries(commonSynonym, filteredSynonymValues);
    } else {
        newResultTable->addColumnsSet({leftSynonymName, rightSynonymName});
        std::vector<std::string> filteredLeftSynonymValues;
        std::vector<std::string> filteredRightSynonymValues;
        std::unordered_set<std::string> allLeftSynonymsValues = result->getColumnValues(leftSynonymName);
        std::unordered_set<std::string> allRightSynonymsValues = result->getColumnValues(rightSynonymName);
        for (const auto& leftValue : allLeftSynonymsValues) {
            for (const auto& rightValue : allRightSynonymsValues) {
                if (reader->hasRelationship(std::stoi(leftValue), std::stoi(rightValue))) {
                    filteredLeftSynonymValues.push_back(leftValue);
                    filteredRightSynonymValues.push_back(rightValue);
                }
            }
        }
        newResultTable->populateWithTwoColumnsWithExactEntries(leftSynonymName, rightSynonymName, filteredLeftSynonymValues, filteredRightSynonymValues);
    }
}

void NextStrategy::addTrueLeftSynonymInResultTable(std::shared_ptr<ResultTable> newResultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager) {
    Token firstParam = getFirstParam();
    Token secondParam = getSecondParam();
    std::shared_ptr<IRelationshipReader<int, int>> reader = getReader();
    std::shared_ptr<ResultTable> result = getIntermediateResultTable();
    std::string leftSynonymName = firstParam.getValue();
    std::unordered_set<std::string> leftSynonymValues = result->getColumnValues(leftSynonymName);
    std::vector<std::string> filteredLeftSynonymValues;
    std::string rightParamValue = secondParam.getValue();
    TokenType rightParamType = secondParam.getType();
    if (rightParamType == TokenType::Wildcard) {
        newResultTable->insertColumn(leftSynonymName);
        for (const auto& leftValue : leftSynonymValues) {
            if (reader->getRelationshipCountByValue(std::stoi(leftValue)) > 0) {
                filteredLeftSynonymValues.push_back(leftValue);
            }
        }
        newResultTable->populateWithOneColumnWithExactEntries(leftSynonymName, filteredLeftSynonymValues);
    } else if (rightParamType == TokenType::INTEGER) {
        newResultTable->insertColumn(leftSynonymName);
        for (const auto& leftValue : leftSynonymValues) {
            if (reader->hasRelationship(std::stoi(leftValue), std::stoi(rightParamValue))) {
                filteredLeftSynonymValues.push_back(leftValue);
            }
        }
        newResultTable->populateWithOneColumnWithExactEntries(leftSynonymName, filteredLeftSynonymValues);
    } else {
        std::vector<std::string> filteredRightSynonymValues;
        std::string rightSynonymName = secondParam.getValue();
        std::string rightSynonymType = parsingResult.getRequiredSynonymType(rightSynonymName);
        newResultTable->addColumnsSet({leftSynonymName, rightSynonymName});
        for (const auto& leftValue : leftSynonymValues) {
            std::unordered_set<int> allMatchingRightValues = reader->getRelationshipsByKey(std::stoi(leftValue));
            std::unordered_set<int> allFilteredMatchingRightValues = getFilteredStmtsNumByType(allMatchingRightValues, rightSynonymType, pkbReaderManager);
            for (const auto& rightValue : allFilteredMatchingRightValues) {
                filteredLeftSynonymValues.push_back(leftValue);
                filteredRightSynonymValues.push_back(std::to_string(rightValue));
            }
        }
        newResultTable->populateWithTwoColumnsWithExactEntries(leftSynonymName, rightSynonymName, filteredLeftSynonymValues, filteredRightSynonymValues);
    }

}


void NextStrategy::addTrueRightSynonymInResultTable(std::shared_ptr<ResultTable> newResultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager) {
    Token firstParam = getFirstParam();
    Token secondParam = getSecondParam();
    std::shared_ptr<IRelationshipReader<int, int>> reader = getReader();
    std::shared_ptr<ResultTable> result = getIntermediateResultTable();
    std::string rightSynonymName = secondParam.getValue();
    std::unordered_set<std::string> rightSynonymValues = result->getColumnValues(rightSynonymName);
    std::vector<std::string> filteredRightSynonymValues;
    std::string leftParamValue = firstParam.getValue();
    TokenType leftParamType = firstParam.getType();
    if (leftParamType == TokenType::Wildcard) {
        newResultTable->insertColumn(rightSynonymName);
        for (const auto& rightValue : rightSynonymValues) {
            if (reader->getRelationshipCountByValue(std::stoi(rightValue)) > 0) {
                filteredRightSynonymValues.push_back(rightValue);
            }
        }
        newResultTable->populateWithOneColumnWithExactEntries(rightSynonymName, filteredRightSynonymValues);
    } else if (leftParamType == TokenType::INTEGER) {
        newResultTable->insertColumn(rightSynonymName);
        for (const auto& rightValue : rightSynonymValues) {
            if (reader->hasRelationship(std::stoi(leftParamValue), std::stoi(rightValue))) {
                filteredRightSynonymValues.push_back(rightValue);
            }
        }
        newResultTable->populateWithOneColumnWithExactEntries(rightSynonymName, filteredRightSynonymValues);
    } else {
        std::vector<std::string> filteredLeftSynonymValues;
        std::string leftSynonymName = firstParam.getValue();
        std::string leftSynonymType = parsingResult.getRequiredSynonymType(leftSynonymName);
        newResultTable->addColumnsSet({leftSynonymName, rightSynonymName});
        for (const auto& rightValue : rightSynonymValues) {
            std::unordered_set<int> allMatchingLeftValues = reader->getRelationshipsByValue(std::stoi(rightValue));
            std::unordered_set<int> allFilteredMatchingLeftValues = getFilteredStmtsNumByType(allMatchingLeftValues, leftSynonymType, pkbReaderManager);
            for (const auto& leftValue : allFilteredMatchingLeftValues) {
                filteredRightSynonymValues.push_back(rightValue);
                filteredLeftSynonymValues.push_back(std::to_string(leftValue));
            }
        }
        newResultTable->populateWithTwoColumnsWithExactEntries(leftSynonymName, rightSynonymName, filteredLeftSynonymValues, filteredRightSynonymValues);
    }
}



