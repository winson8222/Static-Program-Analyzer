#pragma once

#include <memory>
#include "qps/evaluator/strategies/suchThatStrategies/StmtStmtStrategy.h"
#include "pkb/readers/relationships/AffectsReader.h"

class AffectsStrategy : public StmtStmtStrategy {
private:
    std::shared_ptr<AffectsReader> affectsReader;
    Token firstParam;
    Token secondParam;

public:
    // Override the evaluateQuery method to implement the Affects evaluation logic
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;

    // Evaluate Affects when both parameters are synonyms (i.e., both are statement numbers for assignments)
    void processSynonyms(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager);

    // Evaluate Affects when the first parameter is a synonym and the second is specific (i.e., s1 affects a specific statement number)
    void processFirstParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) override;

    // Evaluate Affects when the second parameter is a synonym and the first is specific (i.e., a specific statement number affects s2)
    void processSecondParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) override;

    // Evaluate Affects when both parameters are specific statement numbers
    void processIntegerParams(std::shared_ptr<ResultTable> resultTable) override;
};
