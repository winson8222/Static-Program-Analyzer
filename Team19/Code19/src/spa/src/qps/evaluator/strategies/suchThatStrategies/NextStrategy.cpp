#include "NextStrategy.h"

std::shared_ptr<ResultTable> NextStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();

    // Determine if we're dealing with Next or Next*
    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
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
        reader = pkbReaderManager.getNextReader();
    } else if (variant == "Next*") {
        reader = pkbReaderManager.getNextTReader();
    } else {
        // Handle unexpected variant
        return;
    }



    // Fetch all relationships from the selected reader
    auto relationships = reader->getKeyValueRelationships();

    // Iterate through all relationships, filtering based on the synonyms' criteria
    for (const auto& pair : relationships) {
        int fromStmt = pair.first;
        for (int toStmt : pair.second) {
            // Insert each relevant pair into the result table
            std::pair<string, string> col1Pair = make_pair<string, string>(firstParam.getValue(), to_string(fromStmt));
            std::pair<string, string> col2Pair = make_pair<string, string>(secondParam.getValue(), to_string(toStmt));
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
            auto reader = pkbReaderManager.getNextReader();
            previousStatements = reader->getAllPrevious();
        } else if (variant == "Next*") {
            auto reader = pkbReaderManager.getNextTReader();
            previousStatements = reader->getAllPreviousT();
        } else {
            // Handle unexpected scenario where neither isNext nor isNextT is true
            return;
        }
    } else {
        // Determine the reader based on isNext or isNextT and fetch the next statements accordingly
        if (variant == "Next") {
            auto reader = pkbReaderManager.getNextReader();
            previousStatements = reader->getPrevious(std::stoi(secondParam.getValue()));
        } else if (variant == "Next*"){
            auto reader = pkbReaderManager.getNextTReader();
            previousStatements = reader->getPreviousT(std::stoi(secondParam.getValue()));
        } else {
            // Handle unexpected scenario where neither isNext nor isNextT is true
            return;
        }
    }


    resultTable->insertColumn(firstParam.getValue());
    // convert the set of previous statements to a unordered set of strings
    std::unordered_set<std::string> previousStatementsStr;
    convertIntSetToStringSet(previousStatements, previousStatementsStr);
    insertRowsWithSingleColumn(firstParam.getValue(), previousStatementsStr, resultTable);

}


void NextStrategy::processSecondParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    // Define a container for storing statement numbers
    std::unordered_set<int> nextStatements;
    if (firstParam.getType() == TokenType::Wildcard) {
        // If the first param is a wildcard, we can just fetch all the next statements
        if (variant == "Next") {
            auto reader = pkbReaderManager.getNextReader();
            nextStatements = reader->getAllNext();
        } else if (variant == "Next*") {
            auto reader = pkbReaderManager.getNextTReader();
            nextStatements = reader->getAllNextT();
        } else {
            // Handle unexpected scenario where neither isNext nor isNextT is true
            return;
        }
    } else {
        // Determine the reader based on isNext or isNextT and fetch the next statements accordingly
        if (variant == "Next") {
            auto reader = pkbReaderManager.getNextReader();
            nextStatements = reader->getNext(std::stoi(firstParam.getValue()));
        } else if (variant == "Next*"){
            auto reader = pkbReaderManager.getNextTReader();
            nextStatements = reader->getNextT(std::stoi(firstParam.getValue()));
        } else {
            // Handle unexpected scenario where neither isNext nor isNextT is true
            return;
        }
    }

    resultTable->insertColumn(secondParam.getValue());
    // convert the set of next statements to a unordered set of strings
    std::unordered_set<std::string> nextStatementsStr;
    convertIntSetToStringSet(nextStatements, nextStatementsStr);
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
