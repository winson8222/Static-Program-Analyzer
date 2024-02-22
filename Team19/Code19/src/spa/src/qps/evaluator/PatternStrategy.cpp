#include "PatternStrategy.h"
#include "qps/parser/Token.h" // Include the Token header
#include <regex>
#include <iostream>
#include <utility>

using namespace std;

// The PatternStrategy class evaluates queries to find pattern relationships in a program.
// A pattern relationship is defined between (entRef, expressionSpec),
// where ent can be a wildcard, a quoted IDENT, or a synonym,
// and expressionSpec is a wildcard, or a quoted expression or quoted expression surrounded by wildcards.

std::shared_ptr<ResultTable> PatternStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) {

    std::shared_ptr<ResultTable> result = std::make_shared<ResultTable>();

    // Obtain readers from PKBReaderManager
    this->patternReader = pkbReaderManager.getAssignPatternReader();//dummy function
    this->assignReader = pkbReaderManager.getAssignReader();

    const Token& patternFirstParam = parsingResult.getPatternClauseFirstParam();
    const Token& patternSecondParam = parsingResult.getPatternClauseSecondParam();
    const Token& patternAssignParam = parsingResult.getPatternClauseRelationship();
    const string assignParamValue = patternAssignParam.getValue();
    bool partialMatch = patternSecondParam.getValue()[0] == '_' && patternSecondParam.getValue().length() > 1;
    string secondParamValue;




    // if the second param is an expressionSpec or a quoted IDENT, we need to retrieve the expression/identity within the quotes
    if (patternSecondParam.getType() == TokenType::ExpressionSpec || patternSecondParam.getType() == TokenType::QuoutIDENT){
        if (patternSecondParam.getValue() == "_") {
            secondParamValue = patternSecondParam.getValue();
        } else {
            secondParamValue = extractQuotedExpression(patternSecondParam);
        }
    } else {
        secondParamValue = patternSecondParam.getValue();
    }

    // if the first param is a synonym, we need to retrieve all variables and its corresponding statement number based on the right hand side
    if (patternFirstParam.getType() == TokenType::IDENT) {
        getMatchedStmtsWithVariable(patternFirstParam,secondParamValue, assignParamValue, result, partialMatch);
    } else if (patternFirstParam.getType() == TokenType::QuoutIDENT) {
        getStatementsByIdent(assignParamValue, patternFirstParam, secondParamValue , result, partialMatch);
    } else {
        // if the first param is a wildcard, we need to retrieve all stmts that match the right hand side
        getAllStatementsByRHS(assignParamValue, secondParamValue, result);
    }


    return result;
}






// create a unordered map with the column name and the value and add to the table as a row
void PatternStrategy::fillSingleColumnResult(const string& colName, const unordered_set<string>& valuesSet, std::shared_ptr<ResultTable> result) {
    // if the column exists, throw an error
    for (const string& value: valuesSet) {
        // create an unordered map with the column name and the value and add to the table
        std::unordered_map<std::string, std::string> row;
        row[colName] = value;
        result->insertNewRow(row);
    }
}



// get all the variables that match the pattern together with the corresponding statement numbers
void PatternStrategy::getMatchedStmtsWithVariable(const Token& firstParam, string secondParamValue,string assignSynonym, std::shared_ptr<ResultTable> result, bool partialMatch) {
    // if left side is a synonym, we need to retrieve all assignments stmt numbers based on the right hand side
    // using those numbers we can retrieve the left hand side variables, create a column for the assignment synonym too
    // then we can fill the result table with the left hand side
    unordered_set<int> patternNumbers;
    if(partialMatch) {
        // fill the table with the statement numbers that match the right hand side pattern
        if (secondParamValue == "_") {
            patternNumbers = assignReader->getAllAssigns();
        } else {
            patternNumbers = patternReader->getStatementNumbersWithPartialRHS(secondParamValue);
        }
    }
    else {
        if (secondParamValue == "_") {
            patternNumbers = assignReader->getAllAssigns();
        } else {
            patternNumbers = patternReader->getStatementNumbersWithRHS(secondParamValue);
        }
    }
    fillAssignAndSynonymPairResult(patternNumbers, assignSynonym, firstParam, result);

}

// fill the result table with the left hand side variables and the corresponding statement numbers
void PatternStrategy::fillAssignAndSynonymPairResult(const unordered_set<int>& patternNumbers, const string& assignSynonym, const Token& firstParam, const std::shared_ptr<ResultTable>& result) {
    result->insertAllColumns({ firstParam.getValue(), assignSynonym });
    for (const int stmtNumber: patternNumbers) {
        const string variable = patternReader->getLHS(stmtNumber);
        // need to refactor this
        const unordered_map<string, string> newRow = { { firstParam.getValue(), variable }, { assignSynonym, to_string(stmtNumber) } };
        result->insertNewRow(newRow);
    }
}

// fill the result table with the statement numbers that match the pattern
void PatternStrategy::getStatementsByIdent(const string& colName, const Token& firstParam,
                                              string expressionValue, std::shared_ptr<ResultTable> result, bool partialMatch) {
    result -> insertAllColumns({ colName });
    string identityName = extractQuotedExpression(firstParam);

    // get All the statements that match the pattern based on the left hand side
    const unordered_set<int>& leftMatchedAssignments = patternReader->getStatementNumbersWithLHS(identityName);
    unordered_set<int> rightMatchedAssignments;
    if (partialMatch) {
        // get All the statements that match the pattern based on the right hand side
        if (expressionValue == "_") {
            rightMatchedAssignments = assignReader->getAllAssigns();
        } else {
            rightMatchedAssignments = patternReader->getStatementNumbersWithPartialRHS(expressionValue);
        }
    } else {
        if (expressionValue == "_") {
            rightMatchedAssignments = assignReader->getAllAssigns();
        } else {
            rightMatchedAssignments = patternReader->getStatementNumbersWithRHS(expressionValue);
        }
    }

    // PLEASE REPLACE THE FOLLOWING CODE WITH A FUNCTION CALL IN THE FUTURE
    // combine the results of the left and right hand side
    unordered_set<int> combinedStatements = combineFoundStatements(rightMatchedAssignments, leftMatchedAssignments);
    // combine the results with All assignment statements
    combinedStatements = combineFoundStatements(assignReader->getAllAssigns(), combinedStatements);
    if (!combinedStatements.empty()) {
        // if there are matches then set the result as a truth table because it is true
        result->setAsTruthTable();
    }
    // convert combinedStatements into a set of strings
    unordered_set<string> combinedStatementsInString;

    // convert the result into a set of strings
    convertIntSetToStringSet(combinedStatements, combinedStatementsInString);

    // fill the result table with the statement numbers that match the pattern
    fillSingleColumnResult(colName, combinedStatementsInString, result);
}

void PatternStrategy::getAllStatementsByRHS(string patternSynonym , string expressionValue, std::shared_ptr<ResultTable> result) {
    result -> insertAllColumns({ patternSynonym });
    unordered_set<int> rightMatchedAssignments;
    if (expressionValue == "_") {
        rightMatchedAssignments = assignReader->getAllAssigns();
        // convert the result into a set of strings
    } else {
        rightMatchedAssignments = patternReader->getStatementNumbersWithRHS(expressionValue);
        // combine with all the assignment statements
        rightMatchedAssignments = combineFoundStatements(assignReader->getAllAssigns(), rightMatchedAssignments);
    }
    unordered_set<string> combinedStatementsInString;
    convertIntSetToStringSet(rightMatchedAssignments, combinedStatementsInString);
    fillSingleColumnResult(patternSynonym, combinedStatementsInString, result);
}
