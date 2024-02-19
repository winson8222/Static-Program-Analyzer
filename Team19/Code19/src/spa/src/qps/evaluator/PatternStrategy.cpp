//#include "PatternStrategy.h"
//#include "qps/parser/Token.h" // Include the Token header
//#include <regex>
//#include <string>
//
//using namespace std;
//
//// The PatternStrategy class evaluates queries to find pattern relationships in a program.
//// A pattern relationship is defined between (entRef, expressionSpec),
//// where ent can be a wildcard, a quoted IDENT, or a synonym,
//// and expressionSpec is a wildcard, or a quoted expression or quoted expression surrounded by wildcards.
//
//unordered_set<string> PatternStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) {
//    string requiredSynonym = parsingResult.getRequiredSynonym();
//
//    unordered_set<string> result;
//
//    // Obtain readers from PKBReaderManager
//    this->patternReader = pkbReaderManager.getPatternReader();//dummy function
//    this->assignReader = pkbReaderManager.getAssignReader();
//
//    const Token& patternFirstParam = parsingResult.getPatternClauseFirstParam();
//    const Token& patternSecondParam = parsingResult.getPatternClauseSecondParam();
//    bool partialMatch = patternSecondParam.getValue()[0] == '_';
//
//    processLHS(patternFirstParam, result);
//    processRHS(patternSecondParam, result, partialMatch);
//
//
//    return result;
//}
//
///**
// * Processes the left-hand side (LHS) of the pattern.
// * @param firstParam - The first parameter of the pattern (LHS).
// * @param result - A set to store the processing results.
// */
//void PatternStrategy::processLHS(const Token& firstParam,  unordered_set<string>& result)
//{
//    // now there are 3 cases, either wildcard where we retrieve all assignments
//    // or quoted variable where we retrieve all assignment with this variable
//    // or synonym - not sure how to handle this yet
//    if (firstParam.getType() == TokenType::QuoutIDENT) {
//
//        //extract the Identif  ier from the token
//        regex pattern(R"(["](.*?)["])");
//        smatch matches;
//        auto search = firstParam.getValue();
//        std::regex_search(search, matches, pattern);
//        string variable = matches[1].str();
//
//		const unordered_set<int>& assignments = patternReader->getAssignmentsWithLHS(variable); //dummy function
//		fillResult(assignments, result);
//	}
//    else if (firstParam.getType() == TokenType::Wildcard) {
//		const unordered_set<int>& assignments = assignReader->getAllAssigns();
//		// can skip filling the result as all that matters is the RHS now
//	}
//    else if (firstParam.getType() == TokenType::Synonym) {
//		// not sure how to handle this yet
//	}
//}
//
///**
// * Processes the right-hand side (RHS) of the pattern.
// * @param secondParam - The second parameter of the pattern (RHS).
// * @param result - A set to store the processing results.
// * @param partialMatch - Boolean flag indicating if partial matches should be considered.
// */
//void PatternStrategy::processRHS(const Token& secondParam, unordered_set<string>& result, bool partialMatch)
//{
//    // First extract the quoted expression from the token using regex.
//    // Now there are 3 cases, either wildcard where we retrieve all assignments
//    // Or quoted expression where we retrieve all RHS assignment
//    // With this expression exactly or partially
//
//    if (secondParam.getType() == TokenType::ExpressionSpec) {
//
//        //extract the quoted expression from the token
//        regex pattern(R"(["](.*?)["])");
//        smatch matches;
//        auto search = secondParam.getValue();
//        std::regex_search(search, matches, pattern);
//        string expressionValue = matches[1].str();
//
//        if (partialMatch) {
//			const unordered_set<int>& assignments = patternReader->getPartialAssignmentsWithRHS(expressionValue); //dummy function
//            combineResults(assignments, result);
//        }
//        else {
//            const unordered_set<int>& assignments = patternReader->getAssignmentsWithRHS(expressionValue); //dummy function
//            combineResults(assignments, result);
//        }
//
//    }
//    else if (secondParam.getType() == TokenType::Wildcard) {
//        if (result.empty()) {
//            const unordered_set<int>& assignments = assignReader->getAllAssigns();
//            fillResult(assignments, result);
//        }
//        // no need to do anything if the set is not empty as the intersection will be LHS only
//	}
//
//
//
//}
//
///**
// * Combines the results of LHS and RHS processing.
// * @param newResult - The new results to be combined.
// * @param result - The existing set of results to be updated.
// */
//void PatternStrategy::combineResults(const unordered_set<int>& newResult, unordered_set<string>& result) {
//    unordered_set<string> intersectedResult;
//    for (const string& val : result) {
//        int num = stoi(val);
//        if (newResult.find(num) != newResult.end()) {
//            intersectedResult.insert(val);
//        }
//    }
//    result = std::move(intersectedResult);
//}
//
//
//
//

