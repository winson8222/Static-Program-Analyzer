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
    this->parentReader = pkbReaderManager.getParentReader();
    this->parentTTReader = pkbReaderManager.getParentTReader();
    this->statementReader = pkbReaderManager.getStatementReader();

    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    const Token& suchThatFirstParam = suchClause->getFirstParam();
    const Token& suchThatSecondParam = suchClause->getSecondParam();
    string variant = suchClause->getRelationship().getValue();

    if (suchThatFirstParam.getType() == TokenType::IDENT && suchThatSecondParam.getType() == TokenType::IDENT) {
        processSynonyms(suchThatFirstParam, suchThatSecondParam, variant, resultTable, parsingResult, pkbReaderManager);
    }
    else if (suchThatFirstParam.getType() == TokenType::IDENT) {
        processFirstParam(suchThatFirstParam, suchThatSecondParam, variant, resultTable, parsingResult, pkbReaderManager);
    }
    else if (suchThatSecondParam.getType() == TokenType::IDENT) {
        processSecondParam(suchThatFirstParam, suchThatSecondParam, variant, resultTable, parsingResult, pkbReaderManager);
    }
    else if (isBothParamsWildcard(suchThatFirstParam, suchThatSecondParam)) {
        resultTable->setAsTruthTable();
    }
    else if (isBothParamsInteger(suchThatFirstParam, suchThatSecondParam)) {
        processIntegerParams(suchThatFirstParam, suchThatSecondParam, resultTable);
    }

    return resultTable;
}



void ParentStrategy::processSynonyms(const Token& firstParam, const Token& secondParam, const string& variant, std::shared_ptr<ResultTable> resultTable,
                                     const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager)
{
    // Implementation for processing when both parameters are synonyms
    insertColsToTable(firstParam, secondParam, resultTable);
    string firstStatementType = parsingResult.getDeclaredSynonyms().at(firstParam.getValue());
    string secondStatementType = parsingResult.getDeclaredSynonyms().at(secondParam.getValue());

    // Retrieve the relationships
    unordered_set<int> filteredParents;
    const unordered_set<int>& parents = (variant == "Parent") ?
                                        parentReader->getAllParents() :
                                        parentTTReader->getAllParentTs();

    filteredParents = getFilteredStmtsNumByType(parents, firstStatementType, pkbReaderManager);
    // Iterate through the preFollows set and find corresponding postFollows
    for (int stmt1 : filteredParents) {
        unordered_set<int> filteredChildren;
        unordered_set<int> children = (variant == "Parent") ?
            parentReader->getChild(stmt1) :
            parentTTReader->getChildT(stmt1);

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
void ParentStrategy::processFirstParam(const Token& firstParam, const Token& secondParam, const string& variant,
            std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    // Implementation of processing when the first parameter matches the required synonym
    string col1 = firstParam.getValue();
    string firstStatementType = parsingResult.getDeclaredSynonyms().at(col1);
    resultTable->insertAllColumns({ col1 });

    unordered_set<int> filteredParents;
    if (secondParam.getType() == TokenType::INTEGER) {
        int stmtNum = stoi(secondParam.getValue());
        const unordered_set<int>& parents = (variant == "Parent") ?
                                            parentReader->getParent(stmtNum) :
                                            parentTTReader->getParentT(stmtNum);
        filteredParents = getFilteredStmtsNumByType(parents, firstStatementType, pkbReaderManager);
        for (int stmt : filteredParents) {
            unordered_map<string, string> row;
            row[col1] = to_string(stmt);
            resultTable->insertNewRow(row);
        }
    }
    else if (secondParam.getType() == TokenType::Wildcard) {
        const unordered_set<int>& parents = (variant == "Parent") ?
                                            parentReader->getAllParents() :
                                            parentTTReader->getAllParentTs();
        filteredParents = getFilteredStmtsNumByType(parents, firstStatementType, pkbReaderManager);
        for (int stmt : filteredParents) {
            unordered_map<string, string> row;
            row[col1] = to_string(stmt);
            resultTable->insertNewRow(row);
        }
    }
}

void ParentStrategy::processSecondParam(const Token& firstParam, const Token& secondParam, const string& variant,
            std::shared_ptr<ResultTable> resultTable,const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    // Implementation of processing when the second parameter matches the required synonym
    string col2 = secondParam.getValue();
    string secondStatementType = parsingResult.getDeclaredSynonyms().at(col2);
    resultTable->insertAllColumns({ col2 });
    unordered_set<int> filteredParents;
    if (firstParam.getType() == TokenType::INTEGER) {
        int stmtNum = stoi(firstParam.getValue());
        const unordered_set<int>& parents = (variant == "Parent") ?
                                            parentReader->getChild(stmtNum) :
                                            parentTTReader->getChildT(stmtNum);
        filteredParents = getFilteredStmtsNumByType(parents, secondStatementType, pkbReaderManager);

        for (int stmt : filteredParents) {
            unordered_map<string, string> row;
            row[col2] = to_string(stmt);
            resultTable->insertNewRow(row);
        }
    }
    else if (firstParam.getType() == TokenType::Wildcard) {
        const unordered_set<int>& parents = (variant == "Parent") ?
                                            parentReader->getAllChildren() :
                                            parentTTReader->getAllChildrenT();
        filteredParents = getFilteredStmtsNumByType(parents, secondStatementType, pkbReaderManager);
        for (int stmt : filteredParents) {
            unordered_map<string, string> row;
            row[col2] = to_string(stmt);
            resultTable->insertNewRow(row);
        }
    }
}



void ParentStrategy::processIntegerParams(const Token& firstParam, const Token& secondParam,
            std::shared_ptr<ResultTable> resultTable) {
    // Implementation for processing when both parameters are integers
    int firstStmtNum = stoi(firstParam.getValue());
    int secondStmtNum = stoi(secondParam.getValue());

    if (parentReader->hasParent(firstStmtNum, secondStmtNum)) {
        resultTable->setAsTruthTable();
    }
}
