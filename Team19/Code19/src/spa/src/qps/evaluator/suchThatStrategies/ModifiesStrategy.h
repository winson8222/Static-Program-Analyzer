#pragma
#define MODIFIESSTRATEGY_H

#include "qps/evaluator/suchThatStrategies/StmtStmtStrategy.h"


using namespace std;

class ModifiesStrategy : public QueryEvaluationStrategy {
private:
    std::shared_ptr<StatementReader> statementReader;

public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) override;

        
};

