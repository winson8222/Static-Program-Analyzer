#include "NextStrategy.h"

std::shared_ptr<ResultTable> NextStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();

    // Determine if we're dealing with Next or Next*
    const auto* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->variant = suchClause->getRelationship().getValue();
    this->nextReader = pkbReaderManager.getNextReader();
    this->nextTReader = pkbReaderManager.getNextTReader();
    this->statementReader = pkbReaderManager.getStatementReader();


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
    std::shared_ptr<IRelationshipReader<int, int>> reader;
    if (variant == "Next") {
        reader = this->nextReader;
    } else if (variant == "Next*") {
        reader = this->nextTReader;
    } else {
        // Handle unexpected variant
        return;
    }

    // Fetch all relationships from the selected reader
    string firstParamType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    unordered_set<int> allPreviousStmts = reader->getKeys();
    unordered_set<int> filteredPreviousStmts = getFilteredStmtsNumByType(allPreviousStmts, firstParamType, pkbReaderManager);

    // Iterate through all relationships, filtering based on the synonyms' criteria
    for (const int stmt : filteredPreviousStmts) {
        unordered_set<int> allNextStmts = reader->getRelationshipsByKey(stmt);
        string secondStatementType = parsingResult.getDeclaredSynonym(secondParam.getValue());
        unordered_set<int>  filteredNextStatements = getFilteredStmtsNumByType(allNextStmts, secondStatementType, pkbReaderManager);
        for (int nextStmt : filteredNextStatements) {
            // Insert each relevant pair into the result table
            std::pair<string, string> col1Pair = make_pair<string, string>(firstParam.getValue(), to_string(stmt));
            std::pair<string, string> col2Pair = make_pair<string, string>(secondParam.getValue(), to_string(nextStmt));
            insertRowToTable(col1Pair, col2Pair, resultTable);
        }
    }
}



void NextStrategy::processFirstParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    // Define a container for storing statement numbers
    std::unordered_set<int> previousStatements;

    if (secondParam.getType() == TokenType::Wildcard) {
        // If the second param is a wildcard, we can just fetch all the next statements
        if (variant == "Next") {
            auto reader = this->nextReader;
            previousStatements = reader->getAllPrevious();
        } else if (variant == "Next*") {
            auto reader = this->nextTReader;
            previousStatements = reader->getAllPreviousT();
        } else {
            // Handle unexpected scenario where neither isNext nor isNextT is true
            return;
        }
    } else {
        // Determine the reader based on isNext or isNextT and fetch the next statements accordingly
        if (variant == "Next") {
            auto reader = this->nextReader;
            previousStatements = reader->getPrevious(std::stoi(secondParam.getValue()));
        } else if (variant == "Next*"){
            auto reader = this->nextTReader;
            previousStatements = reader->getPreviousT(std::stoi(secondParam.getValue()));
        } else {
            // Handle unexpected scenario where neither isNext nor isNextT is true
            return;
        }
    }

    string statementType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    std::unordered_set<int> allFilteredPreviousStmts = getFilteredStmtsNumByType(previousStatements, statementType, pkbReaderManager);
    resultTable->insertColumn(firstParam.getValue());
    // convert the set of previous statements to a unordered set of strings
    std::unordered_set<std::string> previousStatementsStr;
    convertIntSetToStringSet(allFilteredPreviousStmts, previousStatementsStr);
    insertRowsWithSingleColumn(firstParam.getValue(), previousStatementsStr, resultTable);

}


void NextStrategy::processSecondParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    // Define a container for storing statement numbers
    std::unordered_set<int> nextStatements;
    if (firstParam.getType() == TokenType::Wildcard) {
        // If the first param is a wildcard, we can just fetch all the next statements
        if (variant == "Next") {
            auto reader = this->nextReader;
            nextStatements = reader->getAllNext();
        } else if (variant == "Next*") {
            auto reader = this->nextTReader;
            nextStatements = reader->getAllNextT();
        } else {
            // Handle unexpected scenario where neither isNext nor isNextT is true
            return;
        }
    } else {
        // Determine the reader based on isNext or isNextT and fetch the next statements accordingly
        if (variant == "Next") {
            auto reader = this->nextReader;
            nextStatements = reader->getNext(std::stoi(firstParam.getValue()));
        } else if (variant == "Next*"){
            auto reader = this->nextTReader;
            nextStatements = reader->getNextT(std::stoi(firstParam.getValue()));
        } else {
            // Handle unexpected scenario where neither isNext nor isNextT is true
            return;
        }
    }
    string statementType = parsingResult.getDeclaredSynonym(secondParam.getValue());
    std::unordered_set<int> allFilteredNextStmts = getFilteredStmtsNumByType(nextStatements, statementType, pkbReaderManager);

    resultTable->insertColumn(secondParam.getValue());
    // convert the set of next statements to a unordered set of strings
    std::unordered_set<std::string> nextStatementsStr;
    convertIntSetToStringSet(allFilteredNextStmts, nextStatementsStr);
    insertRowsWithSingleColumn(secondParam.getValue(), nextStatementsStr, resultTable);
}

void NextStrategy::processIntegerParams(std::shared_ptr<ResultTable> resultTable) {
    bool relationshipExists;
    if (variant == "Next") {
        if (isBothParamsWildcard(firstParam, secondParam)) {
    // If both params are wildcards, we can just check if there is a next statement
            relationshipExists = !nextReader->getAllNext().empty();
            if (relationshipExists) {
                resultTable->setAsTruthTable();
            }
        } else {
            setTrueIfRelationShipExist(firstParam, secondParam, nextReader, resultTable);
        }
    } else if (variant == "Next*") {
        if (isBothParamsWildcard(firstParam, secondParam)) {
            // If both params are wildcards, we can just check if there is a next* statement
            relationshipExists = !nextTReader->getAllNextT().empty();
            if (relationshipExists) {
                resultTable->setAsTruthTable();
            }
        } else {
            setTrueIfRelationShipExist(firstParam, secondParam, nextTReader, resultTable);
        }

    } else {
        // Handle unexpected scenario where neither isNext nor isNextT is true
        return;
    }

}
