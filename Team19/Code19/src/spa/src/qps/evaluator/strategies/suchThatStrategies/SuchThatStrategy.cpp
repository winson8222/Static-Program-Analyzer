
#include "SuchThatStrategy.h"

void SuchThatStrategy::addTrueRelationshipsInResultTable(std::shared_ptr<ResultTable> newResultTable) {



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

void SuchThatStrategy::addTrueLeftSynonymInResultTable(std::shared_ptr<ResultTable> newResultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager) {

    std::string leftSynonymName = firstParam.getValue();
    std::unordered_set<std::string> leftSynonymValues = intermediateResultTable->getColumnValues(leftSynonymName);
    std::vector<std::string> filteredLeftSynonymValues;
    std::string rightParamValue = secondParam.getValue();
    TokenType rightParamType = secondParam.getType();
    if (rightParamType == TokenType::Wildcard) {
        // if it is a wildcard
        newResultTable->insertColumn(leftSynonymName);
        addToListIfKeyExists(leftSynonymValues, filteredLeftSynonymValues);
        newResultTable->populateWithOneColumnWithExactEntries(leftSynonymName, filteredLeftSynonymValues);
    } else if (rightParamType == TokenType::IDENT) {
        // if it is a synonym
        std::vector<std::string> filteredRightSynonymValues;
        std::string rightSynonymName = secondParam.getValue();
        const std::string& rightSynonymType = parsingResult.getRequiredSynonymType(rightSynonymName);
        newResultTable->addColumnsSet({leftSynonymName, rightSynonymName});
        addPairsToListsByKey(leftSynonymValues, rightSynonymType, pkbReaderManager, filteredLeftSynonymValues, filteredRightSynonymValues);
        newResultTable->populateWithTwoColumnsWithExactEntries(leftSynonymName, rightSynonymName, filteredLeftSynonymValues, filteredRightSynonymValues);
    } else {
        // if it is of specific value
        newResultTable->insertColumn(leftSynonymName);
        addToListIfKeyRelationshipExists(leftSynonymValues, filteredLeftSynonymValues, secondParam);
        newResultTable->populateWithOneColumnWithExactEntries(leftSynonymName, filteredLeftSynonymValues);
    }

}


void SuchThatStrategy::addTrueRightSynonymInResultTable(std::shared_ptr<ResultTable> newResultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager) {

    std::string rightSynonymName = secondParam.getValue();
    std::unordered_set<std::string> rightSynonymValues = intermediateResultTable->getColumnValues(rightSynonymName);
    std::vector<std::string> filteredRightSynonymValues;
    std::string leftParamValue = firstParam.getValue();
    TokenType leftParamType = firstParam.getType();
    if (leftParamType == TokenType::Wildcard) {
        newResultTable->insertColumn(rightSynonymName);
        addToListIfValueExists(rightSynonymValues, filteredRightSynonymValues);
        newResultTable->populateWithOneColumnWithExactEntries(rightSynonymName, filteredRightSynonymValues);
    } else if (leftParamType == TokenType::IDENT) {
        std::vector<std::string> filteredLeftSynonymValues;
        std::string leftSynonymName = firstParam.getValue();
        std::string leftSynonymType = parsingResult.getRequiredSynonymType(leftSynonymName);
        newResultTable->addColumnsSet({leftSynonymName, rightSynonymName});
        addPairsToListsByValue(rightSynonymValues, leftSynonymType, pkbReaderManager, filteredRightSynonymValues, filteredLeftSynonymValues);
        newResultTable->populateWithTwoColumnsWithExactEntries(leftSynonymName, rightSynonymName, filteredLeftSynonymValues, filteredRightSynonymValues);
    } else {
        newResultTable->insertColumn(rightSynonymName);
        addToListIfValueRelationshipExists(rightSynonymValues, filteredRightSynonymValues, firstParam);
        newResultTable->populateWithOneColumnWithExactEntries(rightSynonymName, filteredRightSynonymValues);
    }
}

std::shared_ptr<ResultTable> SuchThatStrategy::getOptimallyEvaluatedResultTable(const ParsingResult &parsingResult,
                                                                                PKBReaderManager &pkbReaderManager,
                                                                                const Clause &clause, std::shared_ptr<ResultTable> result) {

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
