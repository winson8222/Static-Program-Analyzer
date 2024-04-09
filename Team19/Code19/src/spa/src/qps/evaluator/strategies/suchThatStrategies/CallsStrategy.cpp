#include "CallsStrategy.h"

#include <string>
#include <unordered_set>
#include <memory>


std::shared_ptr<ResultTable> CallsStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                    const ParsingResult &parsingResult,
                                                                    const Clause &clause,
                                                                    std::shared_ptr<ResultTable> result) {
    setIntermediateResultTable(result);
    return evaluateQuery(pkbReaderManager, parsingResult, clause);
}

std::shared_ptr<ResultTable> CallsStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = std::make_shared<ResultTable>();

    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    setBothParams(clause);
    this-> variant = suchClause->getRelationship().getValue();
    std::shared_ptr<IRelationshipReader<std::string, std::string>> reader;
    if (this->variant == "Calls") {
        reader = pkbReaderManager.getCallsReader();
    } else {
        reader = pkbReaderManager.getCallsTReader();
    }
    setReader(reader);


    if (isBothParamsSynonym(firstParam, secondParam)) {
        this->processBothSynonyms(parsingResult, resultTable);
    } else if (firstParam.getType() == TokenType::IDENT) {
        this->processFirstParam(parsingResult, resultTable);
    } else if (secondParam.getType() == TokenType::IDENT) {
        this->processSecondParam(parsingResult, resultTable);
    } else {
        this->processBothConstants(parsingResult, resultTable);
    }

    return resultTable;
}

