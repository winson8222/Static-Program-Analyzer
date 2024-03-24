#include "ParentStrategy.h"
#include "qps/parser/Token.h" // Include the Token header
#include <iostream>

using namespace std;

// The ParentStrategy class evaluates queries to find parents relationships in a program.
// A parents relationship is defined between two statements (stmtRef, stmtRef),
// where a stmtRef can be a wildcard, an integer, or a synonym.

std::shared_ptr<ResultTable> ParentStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = make_shared<ResultTable>();
    string requiredSynonym;
    if (!parsingResult.getRequiredSynonyms().empty()) {
        requiredSynonym = parsingResult.getRequiredSynonyms()[0];
    } else {
        // Handle the case where there are no required synonyms
    }
    
    // Obtain readers from PKBReaderManager
    this->statementReader = pkbReaderManager.getStatementReader();

    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->firstParam = suchClause->getFirstParam();
    this->secondParam = suchClause->getSecondParam();
    this->variant   = suchClause->getRelationship().getValue();
    if (this->variant == "Parent") {
        reader = pkbReaderManager.getParentReader();
    } else {
        reader = pkbReaderManager.getParentTReader();
    }

    if (this->firstParam.getType() == TokenType::IDENT && this->secondParam.getType() == TokenType::IDENT) {
        processSynonyms(resultTable, parsingResult, pkbReaderManager);
    }
    else if (this->firstParam.getType() == TokenType::IDENT) {
        processFirstParam(resultTable, parsingResult, pkbReaderManager);
    }
    else if (this->secondParam.getType() == TokenType::IDENT) {
        processSecondParam(resultTable, parsingResult, pkbReaderManager);
    }
    else {
        processIntegerParams(resultTable);
    }

    return resultTable;
}



void ParentStrategy::processSynonyms(std::shared_ptr<ResultTable> resultTable,
                                     const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager)
{
    // Implementation for processing when both parameters are synonyms
    insertColsToTable(firstParam, secondParam, resultTable);
    string firstStatementType = parsingResult.getDeclaredSynonyms().at(firstParam.getValue());
    string secondStatementType = parsingResult.getDeclaredSynonyms().at(secondParam.getValue());

    // Retrieve the relationships
    unordered_set<int> filteredParents;
    const unordered_set<int>& parents = reader->getKeys();

    filteredParents = getFilteredStmtsNumByType(parents, firstStatementType, pkbReaderManager);
    // Iterate through the preFollows set and find corresponding postFollows
    for (int stmt1 : filteredParents) {
        unordered_set<int> filteredChildren;
        unordered_set<int> children = reader->getRelationshipsByKey(stmt1);

        filteredChildren = getFilteredStmtsNumByType(children, secondStatementType, pkbReaderManager);
        // For each stmt1, iterate through all its postFollows
        for (int stmt2 : filteredChildren) {
            pair<string, string> col1Pair = make_pair<string, string>(firstParam.getValue(), to_string(stmt1));
            pair<string, string> col2Pair = make_pair<string, string>(secondParam.getValue(), to_string(stmt2));
            insertRowToTable(col1Pair, col2Pair, resultTable);

        }
    }
}

// Additional helper methods for readability
void ParentStrategy::processFirstParam(
        std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    // Implementation of processing when the first parameter matches the required synonym
    string col1 = firstParam.getValue();
    string firstStatementType = parsingResult.getDeclaredSynonyms().at(col1);
    resultTable->insertAllColumns({ col1 });

    unordered_set<int> filteredParents;
    if (secondParam.getType() == TokenType::INTEGER) {
        int stmtNum = stoi(secondParam.getValue());
        const unordered_set<int>& parents = reader->getRelationshipsByValue(stmtNum);
        filteredParents = getFilteredStmtsNumByType(parents, firstStatementType, pkbReaderManager);
        for (int stmt : filteredParents) {
            unordered_map<string, string> row;
            row[col1] = to_string(stmt);
            resultTable->insertNewRow(row);
        }
    }
    else if (secondParam.getType() == TokenType::Wildcard) {
        const unordered_set<int>& parents = reader->getKeys();
        filteredParents = getFilteredStmtsNumByType(parents, firstStatementType, pkbReaderManager);
        for (int stmt : filteredParents) {
            unordered_map<string, string> row;
            row[col1] = to_string(stmt);
            resultTable->insertNewRow(row);
        }
    }
}

void ParentStrategy::processSecondParam(
            std::shared_ptr<ResultTable> resultTable,const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    // Implementation of processing when the second parameter matches the required synonym
    string col2 = secondParam.getValue();
    string secondStatementType = parsingResult.getDeclaredSynonyms().at(col2);
    resultTable->insertAllColumns({ col2 });
    unordered_set<int> filteredParents;
    if (firstParam.getType() == TokenType::INTEGER) {
        int stmtNum = stoi(firstParam.getValue());
        const unordered_set<int>& parents = reader->getRelationshipsByKey(stmtNum);
        filteredParents = getFilteredStmtsNumByType(parents, secondStatementType, pkbReaderManager);

        for (int stmt : filteredParents) {
            unordered_map<string, string> row;
            row[col2] = to_string(stmt);
            resultTable->insertNewRow(row);
        }
    }
    else if (firstParam.getType() == TokenType::Wildcard) {
        const unordered_set<int>& parents = reader->getValues();
        filteredParents = getFilteredStmtsNumByType(parents, secondStatementType, pkbReaderManager);
        for (int stmt : filteredParents) {
            unordered_map<string, string> row;
            row[col2] = to_string(stmt);
            resultTable->insertNewRow(row);
        }
    }
}



void ParentStrategy::processIntegerParams(
            std::shared_ptr<ResultTable> resultTable) {
    // Implementation for processing when both parameters are integers
    if (isBothParamsWildcard(firstParam, secondParam)) {
        bool hasRelationship = !reader->isEmpty();
        if (hasRelationship) {
            resultTable->setAsTruthTable();
        }
        return;
    } else {
        setTrueIfRelationShipExist(firstParam, secondParam, reader, resultTable);
    }
}
