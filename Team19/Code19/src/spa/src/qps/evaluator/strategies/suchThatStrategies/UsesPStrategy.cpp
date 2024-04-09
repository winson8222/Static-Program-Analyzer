#include "UsesPStrategy.h"
#include <string>
#include <memory>
#include <unordered_set>


std::shared_ptr<ResultTable> UsesPStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                  const ParsingResult &parsingResult,
                                                                  const Clause &clause,
                                                                  std::shared_ptr<ResultTable> result) {
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<std::string, std::string>> reader = pkbReaderManager.getUsesPReader();

    setReader(reader);

    setIntermediateResultTable(result);
    std::unordered_set<std::string> allSynonyms = clause.getAllSynonyms();
    if (!hasCommonSynonyms(allSynonyms, result)) {
        std::shared_ptr<ResultTable> newResults = evaluateQuery(pkbReaderManager, parsingResult, clause);
        return newResults;
    }

    auto optimisedResultTable = std::make_shared<ResultTable>();

    if (hasBothCommonSynonyms(clause, result)) {
        addTrueRelationshipsInResultTable(optimisedResultTable);
    } else if (hasLeftCommonSynonym(clause, result)) {
        addTrueLeftSynonymInResultTable(optimisedResultTable, parsingResult, pkbReaderManager);
    } else if (hasRightCommonSynonym(clause, result)) {
        addTrueRightSynonymInResultTable(optimisedResultTable, parsingResult, pkbReaderManager);
    } else {
        return evaluateQuery(pkbReaderManager, parsingResult, clause);
    }
    return optimisedResultTable;
}

std::shared_ptr<ResultTable> UsesPStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = std::make_shared<ResultTable>();
    std::shared_ptr<UsesPReader> usesPReader = pkbReaderManager.getUsesPReader();
    setReader(usesPReader);
    setBothParams(clause);

//    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);


    if (isBothParamsSynonym(firstParam, secondParam)) {
        this->processBothSynonyms(parsingResult, resultTable);
    } else if (isParamOfType(firstParam, TokenType::IDENT)) {
        this->processFirstParam(parsingResult, resultTable);
    } else if (isParamOfType(secondParam, TokenType::IDENT)) {
        this->processSecondParam(parsingResult, resultTable);
    } else {
        this->processBothConstants(parsingResult, resultTable);
    }

    return resultTable;
}


