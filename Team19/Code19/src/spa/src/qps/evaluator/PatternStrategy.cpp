#include "PatternStrategy.h"
#include "qps/parser/Token.h" // Include the Token header
#include <regex>
#include <iostream>

using namespace std;

// The PatternStrategy class evaluates queries to find pattern relationships in a program.
// A pattern relationship is defined between (entRef, expressionSpec),
// where ent can be a wildcard, a quoted IDENT, or a synonym,
// and expressionSpec is a wildcard, or a quoted expression or quoted expression surrounded by wildcards.

unordered_set<string> PatternStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) {
    string requiredSynonym = parsingResult.getRequiredSynonym();

    unordered_set<string> result;

    // Obtain readers from PKBReaderManager
    this->patternReader = pkbReaderManager.getAssignPatternReader();//dummy function
    this->assignReader = pkbReaderManager.getAssignReader();

    const Token& patternFirstParam = parsingResult.getPatternClauseFirstParam();
    const Token& patternSecondParam = parsingResult.getPatternClauseSecondParam();
    bool partialMatch = patternSecondParam.getValue()[0] == '_';

    processLHS(patternFirstParam, result);
    processRHS(patternSecondParam, result, partialMatch);


    return result;
}

/**
 * Processes the left-hand side (LHS) of the pattern.
 * @param firstParam - The first parameter of the pattern (LHS).
 * @param result - A set to store the processing results.
 */
void PatternStrategy::processLHS(const Token& firstParam,  unordered_set<string>& result)
{
    // now there are 3 cases, either wildcard where we retrieve all assignments
    // or quoted variable where we retrieve all assignment with this variable
    // or synonym - not sure how to handle this yet

    if (firstParam.getType() == TokenType::QuoutIDENT) {

        //extract the Identifier from the token
        regex pattern(R"(["](.*?)["])");
        smatch matches;
        string firstParamValue = firstParam.getValue();
        std::regex_search(firstParamValue, matches, pattern);
        string variable = matches[1].str();

		const unordered_set<int>& assignments = patternReader->getStatementNumbersWithLHS(variable); //dummy function
		fillResult(assignments, result);
	}
    else if (firstParam.getType() == TokenType::Wildcard) {
		const unordered_set<int>& assignments = assignReader->getAllAssigns();
		// can skip filling the result as all that matters is the RHS now
	}
    else if (firstParam.getType() == TokenType::IDENT) {
		// not sure how to handle this yet
	}
}

/**
 * Processes the right-hand side (RHS) of the pattern.
 * @param secondParam - The second parameter of the pattern (RHS).
 * @param result - A set to store the processing results.
 * @param partialMatch - Boolean flag indicating if partial matches should be considered.
 */
void PatternStrategy::processRHS(const Token& secondParam, unordered_set<string>& result, bool partialMatch)
{
    // First extract the quoted expression from the token using regex.
    // Now there are 3 cases, either wildcard where we retrieve all assignments
    // Or quoted expression where we retrieve all RHS assignment 
    // With this expression exactly or partially

    if (secondParam.getType() == TokenType::ExpressionSpec) {

        //extract the quoted expression from the token
        regex pattern(R"(["](.*?)["])");
        smatch matches;
        string secondParamValue = secondParam.getValue();
        std::regex_search(secondParamValue, matches, pattern);
        string expressionValue = matches[1].str();

        if (partialMatch) {
			const unordered_set<int>& assignments = patternReader->getStatementNumbersWithPartialRHS(expressionValue); //dummy function
            combineResults(assignments, result);
        }
        else {
            const unordered_set<int>& assignments = patternReader->getStatementNumbersWithRHS(expressionValue); //dummy function
            combineResults(assignments, result);
        }
        
    }
    else if (secondParam.getType() == TokenType::Wildcard) {
        if (result.empty()) {
            const unordered_set<int>& assignments = assignReader->getAllAssigns();
            fillResult(assignments, result);
        }
        // no need to do anything if the set is not empty as the intersection will be LHS only
	}
    
    

}

/**
 * Combines the results of LHS and RHS processing.
 * @param newResult - The new results to be combined.
 * @param result - The existing set of results to be updated.
 */
void PatternStrategy::combineResults(const unordered_set<int>& newResult, unordered_set<string>& result) {
    for (auto it = result.begin(); it != result.end(); ) {
        if (newResult.find(stoi(*it)) == newResult.end()) {
            it = result.erase(it);
        }
        else {
            ++it;
        }
    }
}

void PatternStrategy::fillResult(const unordered_set<int>& follows, unordered_set<std::string>& result) {
    for (int statement : follows) {
        result.insert(to_string(statement));
    }
}



