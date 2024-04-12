#pragma once
#include "QueryProcessor.h"

#include <utility>

QueryProcessor::QueryProcessor(std::shared_ptr<PKBReaderManager> pReaderManager, std::shared_ptr<PKBCacheManager> pkbCacheManager) {
    this->pkbReaderManager = std::move(pReaderManager);
    this->pkbCacheManager = std::move(pkbCacheManager);
}

void QueryProcessor::processQuery(std::string query, std::list<std::string>& results) {
    // Parse the query
    setUpPKBReaderAndCache();
    std::vector<Token> tokens = tokenizeQuery(query);
    ParsingResult parsingResult = parseQuery(tokens);
    std::unordered_set<std::string> res = evaluateQuery(parsingResult);
    for (auto & re : res) {
        results.push_back(re);
    }
    pkbCacheManager->clearCache();
}

void QueryProcessor::setUpPKBReaderAndCache() {
    pkbCacheManager->populateCache();
}
std::vector<Token> QueryProcessor::tokenizeQuery(std::string query) {
    Tokenizer tokenizer(query);
    std::vector<Token> tokens = tokenizer.tokenize();
    return tokens;
}

ParsingResult QueryProcessor::parseQuery(std::vector<Token>& tokens) {
    QueryParser parser(tokens);
    return parser.parse();
}

std::unordered_set<std::string> QueryProcessor::evaluateQuery(ParsingResult& parsingResult) {
    QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
    return evaluator.evaluateQuery();
}


