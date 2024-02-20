#pragma
// FollowsStrategy.h
#define FOLLOWSSTRATEGY_H

#include "qps/evaluator/suchThatStrategies/StmtStmtStrategy.h"


using namespace std;

class FollowsStrategy : public StmtStmtStrategy {
private:
    std::shared_ptr<FollowsReader> followsReader;
    std::shared_ptr<FollowsTReader> followsTReader;
    std::shared_ptr<StatementReader> statementReader;

public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) override;

        void processSynonyms(const Token& firstParam, const Token& secondParam, 
        const string& variant, std::shared_ptr<ResultTable> resultTable);
        
        void processFirstParam(const Token& firstParam, const Token& secondParam, const string& variant,
            std::shared_ptr<ResultTable> resultTable) override;
        
        void processSecondParam(const Token& firstParam, const Token& secondParam, const string& variant,
            std::shared_ptr<ResultTable> resultTable) override;
        
        void processIntegerParams(const Token& firstParam, const Token& secondParam,
            std::shared_ptr<ResultTable> resultTable) override;
};

