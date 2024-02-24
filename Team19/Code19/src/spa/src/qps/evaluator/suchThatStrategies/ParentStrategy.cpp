#include "ParentStrategy.h"
#include "qps/parser/Token.h" // Include the Token header

using namespace std;

// The ParentStrategy class evaluates queries to find parents relationships in a program.
// A parents relationship is defined between two statements (stmtRef, stmtRef),
// where a stmtRef can be a wildcard, an integer, or a synonym.

std::shared_ptr<ResultTable> ParentStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) {
    auto resultTable = make_shared<ResultTable>();
    string requiredSynonym = parsingResult.getRequiredSynonym();
    string variant = parsingResult.getSuchThatClauseRelationship().getValue();

    // Obtain readers from PKBReaderManager
    this->parentReader = pkbReaderManager.getParentReader();
    this->parentTTReader = pkbReaderManager.getParentTReader();
    this->statementReader = pkbReaderManager.getStatementReader();

    const Token& suchThatFirstParam = parsingResult.getSuchThatClauseFirstParam();
    const Token& suchThatSecondParam = parsingResult.getSuchThatClauseSecondParam();
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
    string col1 = firstParam.getValue();
    string col2 = secondParam.getValue();
    resultTable->insertAllColumns({ col1, col2 }); // Assuming results are pairs of statements
    // Retrieve the relationships
    const unordered_set<int>& parents = (variant == "Parent") ?
                                        parentReader->getAllParents() :
                                        parentTTReader->getAllParentTs();

    // Iterate through the preFollows set and find corresponding postFollows
    for (int stmt1 : parents) {
        unordered_set<int> children = (variant == "Parent") ?
            parentReader->getChild(stmt1) :
            parentTTReader->getChildT(stmt1);

        // For each stmt1, iterate through all its postFollows
        for (int stmt2 : children) {
            unordered_map<string, string> row;
            row[col1] = to_string(stmt1);
            row[col2] = to_string(stmt2);
            resultTable->insertNewRow(row);
        }
    }
}

// Additional helper methods for readability
void ParentStrategy::processFirstParam(const Token& firstParam, const Token& secondParam, const string& variant,
            std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    // Implementation of processing when the first parameter matches the required synonym
    string col1 = firstParam.getValue();
    resultTable->insertAllColumns({ col1 });
    if (secondParam.getType() == TokenType::INTEGER) {
        int stmtNum = stoi(secondParam.getValue());
        const unordered_set<int>& parents = (variant == "Parent") ?
                                            parentReader->getParent(stmtNum) :
                                            parentTTReader->getParentT(stmtNum);
        for (int stmt : parents) {
            unordered_map<string, string> row;
            row[col1] = to_string(stmt);
            resultTable->insertNewRow(row);
        }
    }
    else if (secondParam.getType() == TokenType::Wildcard) {
        const unordered_set<int>& parents = (variant == "Parent") ?
                                            parentReader->getAllParents() :
                                            parentTTReader->getAllParentTs();
        for (int stmt : parents) {
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
    resultTable->insertAllColumns({ col2 });
    if (firstParam.getType() == TokenType::INTEGER) {
        int stmtNum = stoi(firstParam.getValue());
        const unordered_set<int>& parents = (variant == "Parent") ?
                                            parentReader->getChild(stmtNum) :
                                            parentTTReader->getChildT(stmtNum);
        for (int stmt : parents) {
            unordered_map<string, string> row;
            row[col2] = to_string(stmt);
            resultTable->insertNewRow(row);
        }
    }
    else if (firstParam.getType() == TokenType::Wildcard) {
        const unordered_set<int>& parents = (variant == "Parent") ?
                                            parentReader->getAllChildren() :
                                            parentTTReader->getAllChildrenT();
        for (int stmt : parents) {
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
