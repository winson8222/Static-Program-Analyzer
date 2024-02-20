#pragma
#define MODIFIESSTRATEGY_H

#include "qps/evaluator/suchThatStrategies/StmtStmtStrategy.h"


using namespace std;

class ModifiesStrategy : public QueryEvaluationStrategy {
private:
    std::shared_ptr<StatementReader> statementReader;

public:
    unordered_set<string> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) override;

        
};

