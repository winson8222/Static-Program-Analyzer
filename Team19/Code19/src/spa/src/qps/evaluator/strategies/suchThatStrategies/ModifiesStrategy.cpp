#include "ModifiesStrategy.h"


std::shared_ptr<ResultTable> ModifiesStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                    const ParsingResult &parsingResult,
                                                                    const Clause &clause,
                                                                    std::shared_ptr<ResultTable> result) {
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<int, std::string>> reader = pkbReaderManager.getModifiesSReader();

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

std::shared_ptr<ResultTable> ModifiesStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = std::make_shared<ResultTable>();
    setBothParams(clause);

    std::shared_ptr<ModifiesSReader> modifiesSReader = pkbReaderManager.getModifiesSReader();
    setReader(modifiesSReader);


    setBothParams(clause);

    if (isBothParamsSynonym(firstParam, secondParam)) {
        processBothSynonyms(parsingResult, resultTable, pkbReaderManager);
    } else if (firstParam.getType() == TokenType::IDENT) {
        processFirstParam(parsingResult, resultTable, pkbReaderManager);
    } else if (secondParam.getType() == TokenType::IDENT) {
        processSecondParam(parsingResult, resultTable, pkbReaderManager);
    } else {
        processBothConstants( parsingResult, resultTable);
    }
    return resultTable;
}

