#include "NextStrategy.h"

std::shared_ptr<ResultTable> NextStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();

    // Determine if we're dealing with Next or Next*
    this->variant = clause.getTypeName();
    this->nextReader = pkbReaderManager.getNextReader();
    this->nextTReader = pkbReaderManager.getNextTReader();
    this->statementReader = pkbReaderManager.getStatementReader();


    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->firstParam = suchClause->getFirstParam();
    this->secondParam = suchClause->getSecondParam();


    // Process based on token types
    if (firstParam.getType() == TokenType::IDENT && secondParam.getType() == TokenType::IDENT) {
        processSynonyms(resultTable, parsingResult, pkbReaderManager);
    } else if (firstParam.getType() == TokenType::IDENT || firstParam.getType() == TokenType::INTEGER) {
        processFirstParam(resultTable, parsingResult, pkbReaderManager);
    } else if (secondParam.getType() == TokenType::IDENT || secondParam.getType() == TokenType::INTEGER) {
        processSecondParam(resultTable, parsingResult, pkbReaderManager);
    } else if (firstParam.getType() == TokenType::INTEGER && secondParam.getType() == TokenType::INTEGER) {
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

    // Assuming that synonyms represent statement numbers and both are expected to exist in the results.
    auto declaredSynonyms = parsingResult.getDeclaredSynonyms();
    if (declaredSynonyms.find(firstParam.getValue()) == declaredSynonyms.end() || declaredSynonyms.find(secondParam.getValue()) == declaredSynonyms.end()) {
        // One or both synonyms are not declared, handle this case appropriately.
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
    std::unordered_set<int> nextStatements;

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

    if (secondParam.getType() == TokenType::INTEGER || secondParam.getType() == TokenType::IDENT) {
        resultTable->insertColumn(secondParam.getValue());

        for (int stmt : nextStatements) {
            resultTable->insertNewRow({{firstParam.getValue(), std::to_string(stmt)}});
        }
    }
}

void NextStrategy::processSecondParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    // Define a container for storing statement numbers
    std::unordered_set<int> nextStatements;

    // Determine the reader based on isNext or isNextT and fetch the next statements accordingly
    if (variant == "Next") {
        auto reader = pkbReaderManager.getNextReader();
        nextStatements = reader->getPrevious(std::stoi(secondParam.getValue()));
    } else if (variant == "Next*") {
        auto reader = pkbReaderManager.getNextTReader();
        nextStatements = reader->getPreviousT(std::stoi(secondParam.getValue()));
    } else {
        // Handle unexpected scenario where neither isNext nor isNextT is true
        return;
    }

    if (secondParam.getType() == TokenType::INTEGER || secondParam.getType() == TokenType::IDENT) {
        resultTable->insertColumn(secondParam.getValue());

        for (int stmt : nextStatements) {
            resultTable->insertNewRow({{secondParam.getValue(), std::to_string(stmt)}});
        }
    }
}

void NextStrategy::processIntegerParams(std::shared_ptr<ResultTable> resultTable) {
    bool relationshipExists;
    if (variant == "Next") {

        relationshipExists = nextReader->hasRelationship(std::stoi(firstParam.getValue()), std::stoi(secondParam.getValue()));
    } else if (variant == "Next*") {

        relationshipExists = nextTReader->hasRelationship(std::stoi(firstParam.getValue()), std::stoi(secondParam.getValue()));
    } else {
        // Handle unexpected scenario where neither isNext nor isNextT is true
        return;
    }
    if (relationshipExists) {
        resultTable->setAsTruthTable();
    }
}
