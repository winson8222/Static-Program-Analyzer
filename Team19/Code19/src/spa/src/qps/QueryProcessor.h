#pragma once
#include "qps/parser/Tokenizer.h"
#include "qps/parser/QueryParser.h"
#include "qps/parser/ParsingResult.h"
#include "qps/evaluator/QueryEvaluator.h"
#include "pkb/PKBManager.h"
#include "list"

class QueryProcessor {
private:
    std::shared_ptr<PKBReaderManager> pkbReaderManager;
    std::shared_ptr<PKBCacheManager> pkbCacheManager;

public:
    QueryProcessor(std::shared_ptr<PKBReaderManager> pReaderManager, std::shared_ptr<PKBCacheManager> pkbCacheManager);
    ~QueryProcessor() = default;
    void processQuery(std::string query, std::list<std::string>& results);
    void setUpPKBReaderAndCache();
    std::vector<Token> tokenizeQuery(std::string query);
    ParsingResult parseQuery(std::vector<Token>& tokens);
    std::unordered_set<std::string> evaluateQuery(ParsingResult& parsingResult);
};

