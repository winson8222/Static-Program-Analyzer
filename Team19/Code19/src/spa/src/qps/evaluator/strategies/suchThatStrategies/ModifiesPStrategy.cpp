#include "ModifiesPStrategy.h"
#include <unordered_set>

std::shared_ptr<ResultTable> ModifiesPStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, 
	const ParsingResult& parsingResult, const Clause& clause)
{
	auto resultTable = make_shared<ResultTable>();
	this->modifiesPReader = pkbReaderManager.getModifiesPReader();

	const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
	this->firstParam = suchClause->getFirstParam();
	this->secondParam = suchClause->getSecondParam();

	if (isBothParamsSynonym(this->firstParam, this->secondParam)) {
		this->processBothSynonyms(parsingResult, resultTable);
	}
	else if (this->firstParam.getType() == TokenType::IDENT) {
		this->processFirstParam(parsingResult, resultTable);
	}
	else if (this->secondParam.getType() == TokenType::IDENT) {
		this->processSecondParam(parsingResult, resultTable);
	}
	else {
		this->processBothConstants(parsingResult, resultTable);
	}

	return resultTable;
}

void ModifiesPStrategy::processBothSynonyms(const ParsingResult& parsingResult,	std::shared_ptr<ResultTable> resultTable) {
	// get the types of both synonyms
	std::string firstParamType = parsingResult.getDeclaredSynonym(this->firstParam.getValue());
	std::string secondParamType = parsingResult.getDeclaredSynonym(this->secondParam.getValue());
	insertColsToTable(this->firstParam, this->secondParam, resultTable);

	if (firstParamType == "procedure") {
		std::unordered_set<std::string> allProcs = this->modifiesPReader->getAllProcsThatModifyAnyVariable();

		for (std::string proc : allProcs) {
			std::unordered_set<std::string> allVars = this->modifiesPReader->getAllVariablesModifiedByProc(proc);
			// copy the value of procs to a rvalue string
			insertRowsWithMatchedResults(this->firstParam, this->secondParam, proc, allVars, resultTable);
		}
	}

}


void ModifiesPStrategy::processFirstParam(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable) {
	std::string colName = this->firstParam.getValue();
	insertSingleColToTable(this->firstParam, resultTable);
	std::unordered_set<std::string> allProcs;
	if (this->secondParam.getType() == TokenType::QuoutIDENT) {
		std::string secondParamValue = extractQuotedExpression(this->secondParam);

		allProcs = this->modifiesPReader->getAllProcsThatModifyVariable(secondParamValue);

	}
	else {
		// it is a wildcard
		allProcs = this->modifiesPReader->getAllProcsThatModifyAnyVariable();

	}
	insertRowsWithSingleColumn(colName, allProcs, resultTable);
}

void ModifiesPStrategy::processSecondParam(
	const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable) {
	std::string colName = this->secondParam.getValue();
	insertSingleColToTable(this->secondParam, resultTable);
	std::unordered_set<std::string> allVars;
	if (this->firstParam.getType() == TokenType::QuoutIDENT) {
		std::string firstParamValue = extractQuotedExpression(this->firstParam);
		allVars = this->modifiesPReader->getAllVariablesModifiedByProc(firstParamValue);
	}
	else {
		// it is a wildcard
		allVars = this->modifiesPReader->getAllVariablesModifiedByAnyProc();
	}
	insertRowsWithSingleColumn(colName, allVars, resultTable);
}

void ModifiesPStrategy::processBothConstants(
	const ParsingResult& parsingResult,
	std::shared_ptr<ResultTable> resultTable) {
	if (isBothParamsWildcard(this->firstParam, this->secondParam)) {
		if (!this->modifiesPReader->getAllProcsThatModifyAnyVariable().empty()) {
			resultTable->setAsTruthTable();
		}
	}
	else {
		setTrueIfRelationShipExist(this->firstParam, this->secondParam, this->modifiesPReader, resultTable);
	}
}
