#include "ParentStrategy.h"
#include <memory>
#include <string>
#include <unordered_set>

// The ParentStrategy class evaluates queries to find parents relationships in a program.
// A parents relationship is defined between two statements (stmtRef, stmtRef),
// where a stmtRef can be a wildcard, an integer, or a synonym.

std::shared_ptr<ResultTable> ParentStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();
    std::string requiredSynonym;
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
    insertRowsWithTwoCols(firstParam,secondParam,reader, parsingResult, resultTable, pkbReaderManager);

}

// Additional helper methods for readability
void ParentStrategy::processFirstParam(
        std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    // Implementation of processing when the first parameter matches the required synonym
    std::string col1 = firstParam.getValue();
    std::string firstStatementType = parsingResult.getDeclaredSynonyms().at(col1);
    resultTable->insertAllColumns({ col1 });

    std::unordered_set<int> filteredParents;
    std::unordered_set<int> parents;
    if (secondParam.getType() == TokenType::INTEGER) {
        int stmtNum = stoi(secondParam.getValue());
        parents = reader->getRelationshipsByValue(stmtNum);
    }
    else if (secondParam.getType() == TokenType::Wildcard) {
        parents = reader->getKeys();
    }

    filteredParents = getFilteredStmtsNumByType(parents, firstStatementType, pkbReaderManager);
    insertStmtRowsWithSingleCol(filteredParents, resultTable, col1);
}

void ParentStrategy::processSecondParam(std::shared_ptr<ResultTable> resultTable,
    const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    // Implementation of processing when the second parameter matches the required synonym
    std::string col2 = secondParam.getValue();
    std::string secondStatementType = parsingResult.getDeclaredSynonyms().at(col2);
    resultTable->insertAllColumns({ col2 });
    std::unordered_set<int> parents;
    std::unordered_set<int> filteredParents;
    if (firstParam.getType() == TokenType::INTEGER) {
        int stmtNum = stoi(firstParam.getValue());
        parents = reader->getRelationshipsByKey(stmtNum);
    }
    else if (firstParam.getType() == TokenType::Wildcard) {
        parents = reader->getValues();
    }

    filteredParents = getFilteredStmtsNumByType(parents, secondStatementType, pkbReaderManager);
    insertStmtRowsWithSingleCol(filteredParents, resultTable, col2);
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
