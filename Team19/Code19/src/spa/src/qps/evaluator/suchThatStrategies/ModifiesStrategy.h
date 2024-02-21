#pragma
#define MODIFIESSTRATEGY_H

#include "qps/evaluator/suchThatStrategies/StmtEntStrategy.h"


using namespace std;

class ModifiesStrategy : public StmtEntStrategy {
private:
    std::shared_ptr<StatementReader> statementReader;
    std::shared_ptr<ModifiesSReader> ModifiesSReader;

public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) override;
    void processBothSynonyms(const Token& firstParam, const Token& secondParam,
                             std::shared_ptr<ResultTable> resultTable) override;
    void processFirstParamOnly(const Token& firstParam, const Token& secondParam,
                            std::shared_ptr<ResultTable> resultTable) override ;
    void processSecondParamOnly(const Token& firstParam, const Token& secondParam,
                             std::shared_ptr<ResultTable> resultTable) override;
    void processBothConstants(const Token& firstParam, const Token& secondParam,
                              std::shared_ptr<ResultTable> resultTable) override;

        
};

