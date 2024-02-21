#include "FollowsStrategy.h"
#include "qps/parser/Token.h" // Include the Token header

using namespace std;

// The FollowsStrategy class evaluates queries to find follows relationships in a program.
// A follows relationship is defined between two statements (stmtRef, stmtRef), 
// where a stmtRef can be a wildcard, an integer, or a synonym.

std::shared_ptr<ResultTable> FollowsStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) {
    auto resultTable = make_shared<ResultTable>();

    string requiredSynonym = parsingResult.getRequiredSynonym();
    string variant = parsingResult.getSuchThatClauseRelationship().getValue();

    // Obtain readers from PKBReaderManager
    this->followsReader = pkbReaderManager.getFollowsReader();
    this->followsTReader = pkbReaderManager.getFollowsTReader();

    const Token& suchThatFirstParam = parsingResult.getSuchThatClauseFirstParam();
    const Token& suchThatSecondParam = parsingResult.getSuchThatClauseSecondParam();

    //the idea is that to make the cases whether the param is integer, wildcard, or synonym
    if (suchThatFirstParam.getType() == TokenType::IDENT && suchThatSecondParam.getType() == TokenType::IDENT) {
        processSynonyms(suchThatFirstParam, suchThatSecondParam, variant, resultTable);
    }
    else if (suchThatFirstParam.getType() == TokenType::IDENT) {
        processFirstParam(suchThatFirstParam, suchThatSecondParam, variant, resultTable);
    }
    else if (suchThatSecondParam.getType() == TokenType::IDENT) {
        processSecondParam(suchThatFirstParam, suchThatSecondParam, variant, resultTable);
    }
    else if (isBothParamsWildcard(suchThatFirstParam, suchThatSecondParam)) {
        resultTable->setAsTruthTable();
    }
    else if (isBothParamsInteger(suchThatFirstParam, suchThatSecondParam)) {
        processIntegerParams(suchThatFirstParam, suchThatSecondParam, resultTable);
    }

    return resultTable;
}


void FollowsStrategy::processSynonyms(const Token& firstParam, const Token& secondParam,
    const string& variant, std::shared_ptr<ResultTable> resultTable) {
    // Implementation for processing when both parameters are synonyms
    string col1 = firstParam.getValue();
    string col2 = secondParam.getValue();
    resultTable->insertAllColumns({ col1, col2}); // Assuming results are pairs of statements
    // Retrieve the relationships
    const unordered_set<int>& preFollows = (variant == "Follows") ?
        followsReader->getAllPreFollows() :
        followsTReader->getAllPreFollowsT();

    // Iterate through the preFollows set and find corresponding postFollows
    for (int stmt1 : preFollows) {
        unordered_set<int> postFollows = (variant == "Follows") ?
            followsReader->getPostFollows(stmt1) :
            followsTReader->getPostFollowsT(stmt1);

        // For each stmt1, iterate through all its postFollows
        for (int stmt2 : postFollows) {
            unordered_map<string, string> row;
            row[col1] = to_string(stmt1);
            row[col2] = to_string(stmt2);
            resultTable->insertNewRow(row);
        }
    }
    
}



// Additional helper methods for readability
void FollowsStrategy::processFirstParam(const Token& firstParam, const Token& secondParam, const string& variant,
    std::shared_ptr<ResultTable> resultTable) {
    // Implementation of processing when the first parameter matches the required synonym
    string col1 = firstParam.getValue();
    resultTable->insertAllColumns({ col1 });
    if (secondParam.getType() == TokenType::INTEGER) {
        int stmtNum = stoi(secondParam.getValue());
        const unordered_set<int>& follows = (variant == "Follows") ?
            followsReader->getPreFollows(stmtNum) :
            followsTReader->getPreFollowsT(stmtNum);

        for (int stmt : follows) {
            unordered_map<string, string> row;
            row[col1] = to_string(stmt);
            resultTable->insertNewRow(row);
        }
    }
    else if (secondParam.getType() == TokenType::Wildcard) {
        const unordered_set<int>& follows = (variant == "Follows") ?
            followsReader->getAllPreFollows() :
            followsTReader->getAllPreFollowsT();
        for (int stmt : follows) {
            unordered_map<string, string> row;
            row[col1] = to_string(stmt);
            resultTable->insertNewRow(row);
        }
    }
}

void FollowsStrategy::processSecondParam(const Token& firstParam, const Token& secondParam, const string& variant,
    std::shared_ptr<ResultTable> resultTable) {

    string col2 = secondParam.getValue();
    resultTable->insertAllColumns({ col2 });
    // Implementation of processing when the second parameter matches the required synonym
    if (firstParam.getType() == TokenType::INTEGER) {
        int stmtNum = stoi(firstParam.getValue());
        const unordered_set<int>& follows = (variant == "Follows") ?
            followsReader->getPostFollows(stmtNum) :
            followsTReader->getPostFollowsT(stmtNum);
        for (int stmt : follows) {
            unordered_map<string, string> row;
            row[col2] = to_string(stmt);
            resultTable->insertNewRow(row);
        }
    }
    else if (firstParam.getType() == TokenType::Wildcard) {
        const unordered_set<int>& follows = (variant == "Follows") ?
            followsReader->getAllPostFollows() :
            followsTReader->getAllPostFollowsT();
        for (int stmt : follows) {
            unordered_map<string, string> row;
            row[col2] = to_string(stmt);
            resultTable->insertNewRow(row);
        }
    }
}



void FollowsStrategy::processIntegerParams(const Token& firstParam, const Token& secondParam,
    std::shared_ptr<ResultTable> resultTable) {
    // Implementation for processing when both parameters are integers
    int firstStmtNum = stoi(firstParam.getValue());
    int secondStmtNum = stoi(secondParam.getValue());

    if (followsReader->hasFollows(firstStmtNum, secondStmtNum)) {
        resultTable->setAsTruthTable();
    }
}
