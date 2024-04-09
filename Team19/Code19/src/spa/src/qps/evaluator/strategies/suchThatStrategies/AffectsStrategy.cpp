#include "AffectsStrategy.h"
#include <memory>
#include <string>
#include <unordered_set>


std::shared_ptr<ResultTable> AffectsStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                    const ParsingResult &parsingResult,
                                                                    const Clause &clause,
                                                                    std::shared_ptr<ResultTable> result) {
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<int, int>> reader = pkbReaderManager.getAffectsReader();

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

std::shared_ptr<ResultTable> AffectsStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<int, int>> affectsReader = pkbReaderManager.getAffectsReader();
    setReader(affectsReader);



    if (isParamOfType(firstParam, TokenType::IDENT) && isParamOfType(secondParam, TokenType::IDENT)) {
        // Both parameters are synonyms, representing assignment statement numbers.
        processSynonyms(resultTable, parsingResult, pkbReaderManager);
    } else if (isParamOfType(firstParam, TokenType::IDENT)) {
        // Mixed parameter types: one is a specific statement number, and the other is a synonym.
            processFirstParam(resultTable, parsingResult, pkbReaderManager);

    } else if (isParamOfType(secondParam, TokenType::IDENT)) {
            processSecondParam(resultTable, parsingResult, pkbReaderManager);
    } else {
        // Both parameters are specific statement numbers
        processIntegerParams(resultTable);
    }

    return resultTable;
}
