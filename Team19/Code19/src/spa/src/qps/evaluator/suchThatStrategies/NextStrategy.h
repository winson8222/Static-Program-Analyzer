#pragma once // Ensures the file is included only once during compilation

#include "qps/evaluator/suchThatStrategies/StmtStmtStrategy.h"
#include <memory> // For std::shared_ptr


class NextStrategy : public StmtStmtStrategy {
private:
    std::shared_ptr<NextReader> NextReader; 
    std::shared_ptr<NextTReader> NextTReader; 
    std::shared_ptr<StatementReader> statementReader; 


public:
    
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) override;

    /**
     * Processes queries where both parameters are synonyms.
     * @param firstParam The first parameter token of the query.
     * @param secondParam The second parameter token of the query.
     * @param variant The variant of the Next relationship (direct or transitive).
     * @param resultTable The result table to be populated with the evaluation results.
     */
    void processSynonyms(const Token& firstParam, const Token& secondParam, const string& variant, std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager);

    /**
     * Processes queries where the first parameter is a synonym and the second parameter is specific.
     * @param firstParam The first parameter token of the query.
     * @param secondParam The second parameter token of the query.
     * @param variant The variant of the Next relationship (direct or transitive).
     * @param resultTable The result table to be populated with the evaluation results.
     */
    void processFirstParam(const Token& firstParam, const Token& secondParam, const string& variant, std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) override;

    /**
     * Processes queries where the second parameter is a synonym and the first parameter is specific.
     * @param firstParam The first parameter token of the query.
     * @param secondParam The second parameter token of the query.
     * @param variant The variant of the Next relationship (direct or transitive).
     * @param resultTable The result table to be populated with the evaluation results.
     */
    void processSecondParam(const Token& firstParam, const Token& secondParam, const string& variant, std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) override;

    /**
     * Processes queries where both parameters are integers.
     * @param firstParam The first parameter token of the query.
     * @param secondParam The second parameter token of the query.
     * @param resultTable The result table to be populated with the evaluation results.
     */
    void processIntegerParams(const Token& firstParam, const Token& secondParam, std::shared_ptr<ResultTable> resultTable) override;
};
