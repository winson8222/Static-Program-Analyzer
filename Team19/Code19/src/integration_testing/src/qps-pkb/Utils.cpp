#include "Utils.h"

unordered_set<std::string> Utils::getResultsFromQuery(const std::string& query, std::shared_ptr<PKBReaderManager> pkbReaderManager) {
    Tokenizer tokenizer(query);
    vector<Token> tokens = tokenizer.tokenize();
    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(std::move(pkbReaderManager), parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    std::unordered_set<std::string> results;
    for (auto & re : res) {
        results.insert(re);
        std::cout << re << std::endl;
    }
    return results;
}
