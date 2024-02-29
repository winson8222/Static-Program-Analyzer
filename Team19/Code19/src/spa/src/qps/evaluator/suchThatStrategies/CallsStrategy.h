//#pragma
//#define PATTERNSTRATEGY_H
//
//#include "qps/evaluator/suchThatStrategies/StmtStmtStrategy.h"
//#include "qps/evaluator/suchThatStrategies/EntEntStrategy.h"
//
//using namespace std;
//
//class PatternStrategy : public EntEntStrategy {
//private:
//    std::shared_ptr<CallsReader> CallsReader;
//    std::shared_ptr<CallsTReader> CallsTReader;
//    std::shared_ptr<StatementReader> statementReader;
//
//
//
//public:
//    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) override;
//
//
//    
//    void processSynonyms(const Token& firstParam, const Token& secondParam, const string& variant,
//        std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager);
//    
//    void processFirstParam(const Token& firstParam, const Token& secondParam, const string& variant,
//        std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) override;
//
//    void processSecondParam(const Token& firstParam, const Token& secondParam, const string& variant,
//        std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) override;
//
//    void processQuotedParams(const Token& firstParam, const Token& secondParam, std::shared_ptr<ResultTable> resultTable) override;
//
//};
//
