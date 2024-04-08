#include "FollowsStrategy.h"
#include <memory>
#include <unordered_set>
#include <string>

// Standard library dependencies


std::shared_ptr<ResultTable> FollowsStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                    const ParsingResult &parsingResult,
                                                                    const Clause &clause,
                                                                    std::shared_ptr<ResultTable> result) {
    const auto* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->variant = suchClause->getRelationship().getValue();
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<int, int>> reader;
    if (variant == "Follows") {
        reader = pkbReaderManager.getFollowsReader();
    } else if (variant == "Follows*") {
        reader = pkbReaderManager.getFollowsTReader();
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
/**
 * Evaluates Follows or Follows* queries between two statements.
 * Determines the relationship based on the parsing result and updates the result table accordingly.
 *
 * @param pkbReaderManager Provides access to the program knowledge base.
 * @param parsingResult Contains the parsed query details.
 * @return A shared pointer to the populated result table.
 */
std::shared_ptr<ResultTable> FollowsStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager,
	const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();


    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    setBothParams(clause);
    this->variant   = suchClause->getRelationship().getValue();
    std::shared_ptr<IRelationshipReader<int, int>> reader;
    if (this->variant == "Follows") {
        reader = pkbReaderManager.getFollowsReader();
    } else {
        reader = pkbReaderManager.getFollowsTReader();
    }
    setReader(reader);



	// Handling different parameter types for the Follows relationship
	if (isBothParamsSynonym(firstParam, secondParam)) {
		processSynonyms(resultTable, parsingResult, pkbReaderManager);
	}
	else if (firstParam.getType() == TokenType::IDENT) {
		processFirstParam(resultTable, parsingResult, pkbReaderManager);
	}
	else if (secondParam.getType() == TokenType::IDENT) {
		processSecondParam(resultTable, parsingResult, pkbReaderManager);
	}
	else {
		processIntegerParams(resultTable);
	}

	return resultTable;
}

