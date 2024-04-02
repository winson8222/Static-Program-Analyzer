#include "qps/evaluator/strategies/patternStrategies/AssignPatternStrategy.h"
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

std::shared_ptr<ResultTable> AssignPatternStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
	auto resultTable = std::make_shared<ResultTable>();
	this->assignPatternReader = pkbReaderManager.getAssignPatternReader();
	this->assignReader = pkbReaderManager.getAssignReader();


	const PatternClause* patternClause = dynamic_cast<const PatternClause*>(&clause);
	this->firstParam = patternClause->getFirstParam();
	this->secondParam = patternClause->getSecondParam();
	this->relationShip = patternClause->getRelationship();


	if (this->firstParam.getType() == TokenType::IDENT) {
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

void AssignPatternStrategy::processSynonyms(ParsingResult parsingResult, std::shared_ptr<ResultTable> resultTable) {
	std::string firstColName = this->relationShip.getValue();
	std::string secondColName = this->firstParam.getValue();
	insertColsToTable(this->relationShip, this->firstParam, resultTable);
	std::unordered_set<int> allStmts;
	std::string secondParamValue;
	secondParamValue = extractQuotedExpression(secondParam);
	secondParamValue = ShuntingYard::convertToPostfix(secondParamValue);
	if (this->secondParam.getType() == TokenType::ExpressionSpec) {
		allStmts = assignPatternReader->getStatementNumbersWithRHS(secondParamValue);
	}
	else if (this->secondParam.getType() == TokenType::PartialExpressionSpec) {
		allStmts = assignPatternReader->getStatementNumbersWithPartialRHS(secondParamValue);
	}
	else {
		allStmts = assignPatternReader->getAllStatementNumbers();
	}
	for (auto stmt : allStmts) {
		std::string var = assignPatternReader->getLHS(stmt);
		std::pair<std::string, std::string> col1 = make_pair(firstParam.getValue(), var);
		std::pair<std::string, std::string> col2 = make_pair(relationShip.getValue(), std::to_string(stmt));
		insertRowToTable(col1, col2, resultTable);
	}
}

void AssignPatternStrategy::processQuotedIdent(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) {
	std::string firstColName = this->relationShip.getValue();
	insertSingleColToTable(this->relationShip, result);
	std::unordered_set<int> allStmts;
	std::string firstParamValue;
	std::string secondParamValue;
	firstParamValue = extractQuotedExpression(firstParam);
	//    firstParamValue = ShuntingYard::convertToPostfix(firstParamValue);
	secondParamValue = extractQuotedExpression(secondParam);
	secondParamValue = ShuntingYard::convertToPostfix(secondParamValue);
	if (this->secondParam.getType() == TokenType::ExpressionSpec) {
		allStmts = assignPatternReader->getStatementNumbersWithLHSRHS(firstParamValue, secondParamValue);
	}
	else if (this->secondParam.getType() == TokenType::PartialExpressionSpec) {
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
	std::string firstColName = this->relationShip.getValue();
	insertSingleColToTable(this->relationShip, result);
	std::unordered_set<int> allStmts;
	std::string secondParamValue;
	secondParamValue = extractQuotedExpression(secondParam);
	secondParamValue = ShuntingYard::convertToPostfix(secondParamValue);
	if (this->secondParam.getType() == TokenType::ExpressionSpec) {
		allStmts = assignPatternReader->getStatementNumbersWithRHS(secondParamValue);
	}
	else if (this->secondParam.getType() == TokenType::PartialExpressionSpec) {
		allStmts = assignPatternReader->getStatementNumbersWithPartialRHS(secondParamValue);
	}
	else {
		allStmts = assignReader->getAllAssigns();
	}

	std::unordered_set<std::string> allStmtInString;
	convertIntSetToStringSet(allStmts, allStmtInString);
	insertRowsWithSingleColumn(firstColName, allStmtInString, result);
}
