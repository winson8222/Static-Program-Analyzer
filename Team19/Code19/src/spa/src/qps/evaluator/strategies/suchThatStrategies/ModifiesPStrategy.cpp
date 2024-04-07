#include "ModifiesPStrategy.h"

#include <memory>
#include <unordered_set>


std::shared_ptr<ResultTable> ModifiesPStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                    const ParsingResult &parsingResult,
                                                                    const Clause &clause,
                                                                    std::shared_ptr<ResultTable> result) {
    setIntermediateResultTable(result);
    return evaluateQuery(pkbReaderManager, parsingResult, clause);
}

std::shared_ptr<ResultTable> ModifiesPStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, 
	const ParsingResult& parsingResult, const Clause& clause)
{
	auto resultTable = std::make_shared<ResultTable>();
	std::shared_ptr<ModifiesPReader> reader = pkbReaderManager.getModifiesPReader();
    setReader(reader);

//	const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    setBothParams(clause);
    Token firstParam = getFirstParam();
    Token secondParam = getSecondParam();

	if (isBothParamsSynonym(firstParam, secondParam)) {
		this->processBothSynonyms(parsingResult, resultTable);
	}
	else if (firstParam.getType() == TokenType::IDENT) {
		this->processFirstParam(parsingResult, resultTable);
	}
	else if (secondParam.getType() == TokenType::IDENT) {
		this->processSecondParam(parsingResult, resultTable);
	}
	else {
		this->processBothConstants(parsingResult, resultTable);
	}

	return resultTable;
}


