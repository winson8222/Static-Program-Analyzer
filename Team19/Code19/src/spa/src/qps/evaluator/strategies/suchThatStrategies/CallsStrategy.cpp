#include "CallsStrategy.h"

#include <string>
#include <unordered_set>
#include <memory>


std::shared_ptr<ResultTable> CallsStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                    const ParsingResult &parsingResult,
                                                                    const Clause &clause,
                                                                    std::shared_ptr<ResultTable> result) {
    const auto* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->variant = suchClause->getRelationship().getValue();
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<std::string, std::string>> reader;
    if (variant == "Calls") {
        reader = pkbReaderManager.getCallsReader();
    } else if (variant == "Calls*") {
        reader = pkbReaderManager.getCallsTReader();
    }
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

