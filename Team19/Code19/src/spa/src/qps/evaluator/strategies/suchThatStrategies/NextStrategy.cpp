#include "qps/evaluator/strategies/suchThatStrategies/NextStrategy.h"
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

std::shared_ptr<ResultTable> NextStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();

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
