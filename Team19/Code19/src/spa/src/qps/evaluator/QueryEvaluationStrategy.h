// QueryEvaluationStrategy.h
#ifndef QUERYEVALUATIONSTRATEGY_H
#define QUERYEVALUATIONSTRATEGY_H

#include <unordered_set>
#include <string>
#include "../Parser/ParsingResult.h" // Include your ParsingResult header
#include "../../pkb/PKBReaderManager.h" // Include your PKBReader header

class QueryEvaluationStrategy {
public:
    virtual std::unordered_set<std::string> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) = 0;
    virtual ~QueryEvaluationStrategy() = default;
};

#endif //QUERYEVALUATIONSTRATEGY_H
