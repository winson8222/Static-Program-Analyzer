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
    this->statementReader = pkbReaderManager.getStatementReader();
    if (variant == "Next") {
        reader = pkbReaderManager.getNextReader();
    } else if (variant == "Next*") {
        reader = pkbReaderManager.getNextTReader();
    }


    // Get the parameters
    this->firstParam = suchClause->getFirstParam();
    this->secondParam = suchClause->getSecondParam();

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
    this->statementReader = pkbReaderManager.getStatementReader();
    if (variant == "Next") {
        reader = pkbReaderManager.getNextReader();
    } else if (variant == "Next*") {
        reader = pkbReaderManager.getNextTReader();
    }


    // Get the parameters
    this->firstParam = suchClause->getFirstParam();
    this->secondParam = suchClause->getSecondParam();


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

void NextStrategy::processSynonyms(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    // Add columns to the result table
    insertColsToTable(firstParam, secondParam, resultTable);
    // Choose the correct reader based on the variant indicating "Next" or "Next*"

    // Fetch all relationships from the selected reader
    std::string firstParamType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    std::unordered_set<int> allPreviousStmts = reader->getKeys();
    std::unordered_set<int> filteredPreviousStmts = getFilteredStmtsNumByType(allPreviousStmts, firstParamType, pkbReaderManager);

    // Iterate through all relationships, filtering based on the synonyms' criteria
    for (const int stmt : filteredPreviousStmts) {
        std::unordered_set<int> allNextStmts = reader->getRelationshipsByKey(stmt);
        std::string secondStatementType = parsingResult.getDeclaredSynonym(secondParam.getValue());
        std::unordered_set<int>  filteredNextStatements = getFilteredStmtsNumByType(allNextStmts, secondStatementType, pkbReaderManager);
        for (int nextStmt : filteredNextStatements) {
            // Insert each relevant pair into the result table
            std::pair<std::string, std::string> col1Pair = std::make_pair<std::string, std::string>(firstParam.getValue(), std::to_string(stmt));
            std::pair<std::string, std::string> col2Pair = std::make_pair<std::string, std::string>(secondParam.getValue(), std::to_string(nextStmt));
            insertRowToTable(col1Pair, col2Pair, resultTable);
        }
    }
}

void NextStrategy::processFirstParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    // Define a container for storing statement numbers
    std::unordered_set<int> previousStatements;

    if (secondParam.getType() == TokenType::Wildcard) {
        // If the second param is a wildcard, we can just fetch all the next statements
        previousStatements = reader->getKeys();
    } else {
        // Determine the reader based on isNext or isNextT and fetch the next statements accordingly
        previousStatements = reader->getRelationshipsByValue(std::stoi(secondParam.getValue()));
    }

    std::string statementType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    std::unordered_set<int> allFilteredPreviousStmts = getFilteredStmtsNumByType(previousStatements, statementType, pkbReaderManager);
    std::string colName = firstParam.getValue();
    resultTable->insertColumn(colName);
    // convert the set of previous statements to a unordered set of std::strings
    insertStmtRowsWithSingleCol(allFilteredPreviousStmts, resultTable, colName);

}

void NextStrategy::processSecondParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    // Define a container for storing statement numbers
    std::unordered_set<int> nextStatements;
    if (firstParam.getType() == TokenType::Wildcard) {
        // If the first param is a wildcard, we can just fetch all the next statements
        nextStatements = reader->getValues();
    } else {
        // Determine the reader based on isNext or isNextT and fetch the next statements accordingly
        nextStatements = reader->getRelationshipsByKey(std::stoi(firstParam.getValue()));
    }
    std::string statementType = parsingResult.getDeclaredSynonym(secondParam.getValue());
    std::unordered_set<int> allFilteredNextStmts = getFilteredStmtsNumByType(nextStatements, statementType, pkbReaderManager);
    std::string colName = secondParam.getValue();
    resultTable->insertColumn(colName);
    // convert the set of next statements to a unordered set of std::strings
    std::unordered_set<std::string> nextStatementsStr;
    insertStmtRowsWithSingleCol(allFilteredNextStmts, resultTable, colName);
}

void NextStrategy::processIntegerParams(std::shared_ptr<ResultTable> resultTable) {
    bool relationshipExists;

    if (isBothParamsWildcard(firstParam, secondParam)) {
        // If both params are wildcards, we can just check if there is a next statement
        relationshipExists = !reader->isEmpty();
        if (relationshipExists) {
            resultTable->setAsTruthTable();
        }
    } else {
        setTrueIfRelationShipExist(firstParam, secondParam, reader, resultTable);
    }
}

void NextStrategy::addTrueRelationshipsInResultTable(std::shared_ptr<ResultTable> newResultTable) {
    std::shared_ptr<ResultTable> result = getIntermediateResultTable();
    std::string leftSynonymName = firstParam.getValue();
    std::string rightSynonymName = secondParam.getValue();

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



