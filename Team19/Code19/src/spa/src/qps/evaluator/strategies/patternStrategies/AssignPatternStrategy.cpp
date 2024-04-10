#include "qps/evaluator/strategies/patternStrategies/AssignPatternStrategy.h"
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>


std::shared_ptr<ResultTable> AssignPatternStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                     const ParsingResult &parsingResult,
                                                                     const Clause &clause,
                                                                     std::shared_ptr<ResultTable> result) {
    setIntermediateResultTable(result);
    return evaluateQuery(pkbReaderManager, parsingResult, clause);
}

std::shared_ptr<ResultTable> AssignPatternStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
	auto resultTable = std::make_shared<ResultTable>();
	this->assignPatternReader = pkbReaderManager.getAssignPatternReader();
	this->assignReader = pkbReaderManager.getAssignReader();


	const PatternClause* patternClause = dynamic_cast<const PatternClause*>(&clause);
    setBothParams(clause);
	Token relationship = patternClause->getRelationship();
    setRelationship(relationship);

    return getEvaluatedResultTable(pkbReaderManager, parsingResult, resultTable);

}

void AssignPatternStrategy::processSynonyms(ParsingResult parsingResult, std::shared_ptr<ResultTable> resultTable) {
	std::string firstColName = relationship.getValue();
	std::string secondColName = firstParam.getValue();
	insertColsToTable(relationship, firstParam, resultTable);
	std::unordered_set<int> allStmts;
	std::string secondParamValue;
	secondParamValue = extractQuotedExpression(secondParam);
	secondParamValue = ShuntingYard::convertToPostfix(secondParamValue);
	if (secondParam.getType() == TokenType::ExpressionSpec) {
		allStmts = assignPatternReader->getStatementNumbersWithRHS(secondParamValue);
	}
	else if (secondParam.getType() == TokenType::PartialExpressionSpec) {
		allStmts = assignPatternReader->getStatementNumbersWithPartialRHS(secondParamValue);
	}
	else {
		allStmts = assignPatternReader->getAllStatementNumbers();
	}
	for (auto stmt : allStmts) {
		std::string var = assignPatternReader->getLHS(stmt);
		std::pair<std::string, std::string> col1 = make_pair(firstParam.getValue(), var);
		std::pair<std::string, std::string> col2 = make_pair(relationship.getValue(), std::to_string(stmt));
		insertRowToTable(col1, col2, resultTable);
	}
}

void AssignPatternStrategy::processQuotedIdent(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) {
	std::string firstColName = relationship.getValue();
	insertSingleColToTable(relationship, result);
	std::unordered_set<int> allStmts;
	std::string firstParamValue;
	std::string secondParamValue;
	firstParamValue = extractQuotedExpression(firstParam);
	//    firstParamValue = ShuntingYard::convertToPostfix(firstParamValue);
	secondParamValue = extractQuotedExpression(secondParam);
	secondParamValue = ShuntingYard::convertToPostfix(secondParamValue);
	if (secondParam.getType() == TokenType::ExpressionSpec) {
		allStmts = assignPatternReader->getStatementNumbersWithLHSRHS(firstParamValue, secondParamValue);
	}
	else if (secondParam.getType() == TokenType::PartialExpressionSpec) {
		allStmts = assignPatternReader->getStatementNumbersWithLHSPartialRHS(firstParamValue, secondParamValue);
	}
	else {
		allStmts = assignPatternReader->getStatementNumbersWithLHS(firstParamValue);
	}

	std::unordered_set<std::string> allStmtInString;
	convertIntSetToStringSet(allStmts, allStmtInString);
	insertRowsWithSingleColumn(firstColName, allStmtInString, result);
}


void AssignPatternStrategy::processWildcard(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) {

	std::string firstColName = relationship.getValue();
	insertSingleColToTable(relationship, result);
	std::unordered_set<int> allStmts;
	std::string secondParamValue;
	secondParamValue = extractQuotedExpression(secondParam);
	secondParamValue = ShuntingYard::convertToPostfix(secondParamValue);
	if (secondParam.getType() == TokenType::ExpressionSpec) {
		allStmts = assignPatternReader->getStatementNumbersWithRHS(secondParamValue);
	}
	else if (secondParam.getType() == TokenType::PartialExpressionSpec) {
		allStmts = assignPatternReader->getStatementNumbersWithPartialRHS(secondParamValue);
	}
	else {
		allStmts = assignReader->getAllAssigns();
	}

	std::unordered_set<std::string> allStmtInString;
	convertIntSetToStringSet(allStmts, allStmtInString);
	insertRowsWithSingleColumn(firstColName, allStmtInString, result);
}

std::shared_ptr<ResultTable> AssignPatternStrategy::getEvaluatedResultTable(PKBReaderManager &pkbReaderManager,
                                                                            const ParsingResult &parsingResult,
                                                                            std::shared_ptr<ResultTable> resultTable) {


    if (firstParam.getType() == TokenType::IDENT) {
        processSynonyms(parsingResult, resultTable);
    }
    else if (firstParam.getType() == TokenType::QuoutIDENT) {
        processQuotedIdent(parsingResult, resultTable);
    }
    else if (firstParam.getType() == TokenType::Wildcard) {
        processWildcard(parsingResult, resultTable);
    }
    else {
        throw "Invalid firstParam type";
    }

    return resultTable;
}

