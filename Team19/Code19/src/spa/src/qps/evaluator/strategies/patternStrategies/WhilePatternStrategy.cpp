#include "WhilePatternStrategy.h"
#include <memory>
#include <string>
#include <unordered_set>


std::shared_ptr<ResultTable> WhilePatternStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                     const ParsingResult &parsingResult,
                                                                     const Clause &clause,
                                                                     std::shared_ptr<ResultTable> result) {
    setIntermediateResultTable(result);
    return evaluateQuery(pkbReaderManager, parsingResult, clause);
}

std::shared_ptr<ResultTable> WhilePatternStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();
    whilePatternReader = pkbReaderManager.getWhilePatternReader();
    whileReader = pkbReaderManager.getWhileReader();


    const PatternClause *patternClause = dynamic_cast<const PatternClause *>(&clause);
    setBothParams(clause);
    Token relationship = patternClause->getRelationship();
    setRelationship(relationship);


    if (firstParam.getType() == TokenType::IDENT) {
        processSynonyms(parsingResult, resultTable);
    } else if (firstParam.getType() == TokenType::QuoutIDENT) {
        processQuotedIdent(parsingResult, resultTable);
    } else if (firstParam.getType() == TokenType::Wildcard) {
        processWildcard(parsingResult, resultTable);
    } else {
        throw "Invalid firstParam type";
    }

    return resultTable;

}

void WhilePatternStrategy::processSynonyms(ParsingResult parsingResult, std::shared_ptr<ResultTable> resultTable) {
    std::string firstColName = relationship.getValue();
    std::string secondColName = firstParam.getValue();
    insertColsToTable(relationship, firstParam, resultTable);
    insertRowsWithTwoCols(firstParam, relationship,  parsingResult, whilePatternReader, resultTable);
}

void WhilePatternStrategy::processQuotedIdent(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) {
    std::string firstColName = relationship.getValue();
    insertSingleColToTable(relationship, result);
    std::unordered_set<int> allStmts;
    std::string firstParamValue;
    std::string secondParamValue;
    firstParamValue = extractQuotedExpression(firstParam);

//    secondParamValue = ShuntingYard::convertToPostfix(secondParamValue);
    allStmts = whilePatternReader->getStatementNumbersOfWhileControlVariable(firstParamValue);
    insertStmtRowsWithSingleCol(allStmts, result, firstColName);
}


void WhilePatternStrategy::processWildcard(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) {
    std::string firstColName = relationship.getValue();
    insertSingleColToTable(relationship, result);
    std::unordered_set<int> allStmts;
    allStmts = whilePatternReader->getAllStatementNumbersOfWhileControlVariables();
    insertStmtRowsWithSingleCol(allStmts, result, firstColName);
}


void WhilePatternStrategy::addToListIfKeyExists(
        const std::unordered_set<std::string>& values,
        std::vector<std::string>& filteredValues) {
    for (const auto& value : values) {
        if (!whilePatternReader->getAllStatementNumbers().empty()) {
            filteredValues.push_back(value);
        }
    }
}

void WhilePatternStrategy::addToListIfValueExists(
        const std::unordered_set<std::string>& values,
        std::vector<std::string>& filteredValues) {
    for (const auto& value : values) {
        if (!whilePatternReader->getAllStatementNumbersOfWhileControlVariables().empty()) {
            filteredValues.push_back(value);
        }
    }
}




void WhilePatternStrategy::addToListIfRelationshipExistsWithItself(const std::unordered_set<std::string> &values,
                                                                std::vector<std::string> &filteredValues) {
    for (const auto& value : values) {
        if (whilePatternReader->hasControlPatternAtStatement(std::stoi(value), value)) {
            filteredValues.push_back(value);
        }
    }
}



void WhilePatternStrategy::addPairsToListsByKey(const std::unordered_set<std::string> &sourceKeys,
                                             const std::string &type, PKBReaderManager &pkbReaderManager,
                                             std::vector<std::string> &firstList, std::vector<std::string> &secondList) {
    for (const auto &sourceKey: sourceKeys) {
        // Fetch relationships for the source value
        std::unordered_set<std::string> allMatchingValues = whilePatternReader->getControlPatternsWithStatementNumber(std::stoi(sourceKey));



        addCorrelatedValuesToLists(sourceKey, allMatchingValues, firstList, secondList);
    }
}

void WhilePatternStrategy::addPairsToListsByValue(const std::unordered_set<std::string> &sourceValues,
                                               const std::string &type, PKBReaderManager &pkbReaderManager,
                                               std::vector<std::string> &firstList,
                                               std::vector<std::string> &secondList) {

    // Iterate over each source value
    for (const auto& sourceValue : sourceValues) {
        // Fetch all matching values based on the source value

        std::unordered_set<int> allMatchingKeys = whilePatternReader->getStatementNumbersWithControlPattern(sourceValue);
        std::unordered_set<int> allFilteredMatchingKeys = getFilteredStmtsNumByType(allMatchingKeys, type, pkbReaderManager);
        std::unordered_set<std::string> allFilteredMatchingKeysInString;
        convertIntSetToStringSet(allFilteredMatchingKeys, allFilteredMatchingKeysInString);
        addCorrelatedValuesToLists(sourceValue, allFilteredMatchingKeysInString, firstList, secondList);
    }

}


void WhilePatternStrategy::addPairIfRelationshipExists(const std::unordered_set<std::string> &sourceValues,
                                                    const std::unordered_set<std::string> &targetValues,
                                                    std::vector<std::string> &sourceList,
                                                    std::vector<std::string> &targetList) {
    for (const auto& sourceValue : sourceValues) {
        for (const auto& targetValue : targetValues) {
            if (whilePatternReader->hasControlPatternAtStatement(std::stoi(sourceValue), targetValue)) {
                sourceList.push_back(sourceValue);
                targetList.push_back(targetValue);
            }
        }
    }
}

void WhilePatternStrategy::addToListIfKeyRelationshipExists(const std::unordered_set<std::string> &values,
                                                         std::vector<std::string> &filteredValues,
                                                         const Token& comparisonToken) {
    std::string comparisonValue = extractQuotedExpression(comparisonToken);
    for (const auto& value : values) {
        if (whilePatternReader->hasControlPatternAtStatement(std::stoi(value), comparisonValue)) {
            filteredValues.push_back(value);
        }
    }
}

void WhilePatternStrategy::addToListIfValueRelationshipExists(const std::unordered_set<std::string> &values,
                                                           std::vector<std::string> &filteredValues,
                                                           const Token& comparisonToken) {
    std::string comparisonValue = comparisonToken.getValue();
    for (const auto& value : values) {
        if (whilePatternReader->hasControlPatternAtStatement(std::stoi(comparisonValue), value)){
            filteredValues.push_back(value);
        }
    }
}
