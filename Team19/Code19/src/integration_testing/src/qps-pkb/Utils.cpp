#include "Utils.h"

std::unordered_set<std::string> Utils::getResultsFromQuery(const std::string& query, std::shared_ptr<PKBReaderManager> pkbReaderManager, std::shared_ptr<PKBCacheManager> pkbCacheManager) {
    Tokenizer tokenizer(query);
    std::vector<Token> tokens = tokenizer.tokenize();
    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(std::move(pkbReaderManager), std::move(pkbCacheManager), parsingResult);
    std::unordered_set<std::string> res = evaluator.evaluateQuery();
    std::unordered_set<std::string> results;
    for (auto & re : res) {
        results.insert(re);
    }
    return results;
}
