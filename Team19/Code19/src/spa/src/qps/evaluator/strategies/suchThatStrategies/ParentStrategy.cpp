#include "ParentStrategy.h"
#include <memory>
#include <string>
#include <unordered_set>

// The ParentStrategy class evaluates queries to find parents relationships in a program.
// A parents relationship is defined between two statements (stmtRef, stmtRef),
// where a stmtRef can be a wildcard, an integer, or a synonym.

std::shared_ptr<ResultTable> ParentStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                  const ParsingResult &parsingResult,
                                                                  const Clause &clause,
                                                                  std::shared_ptr<ResultTable> result) {
    const auto* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->variant = suchClause->getRelationship().getValue();
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<int, int>> reader;
    if (variant == "Parent") {
        reader = pkbReaderManager.getParentReader();
    } else if (variant == "Parent*") {
        reader = pkbReaderManager.getParentTReader();
    }
    setReader(reader);

    return getOptimallyEvaluatedResultTable(parsingResult, pkbReaderManager, clause, result);
}

std::shared_ptr<ResultTable> ParentStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();
    

    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    setBothParams(clause);
    this->variant   = suchClause->getRelationship().getValue();
    std::shared_ptr<IRelationshipReader<int, int>> reader;
    if (this->variant == "Parent") {
        reader = pkbReaderManager.getParentReader();
    } else {
        reader = pkbReaderManager.getParentTReader();
    }
    setReader(reader);
    return getEvaluatedResultTable(pkbReaderManager, parsingResult, resultTable);
}

