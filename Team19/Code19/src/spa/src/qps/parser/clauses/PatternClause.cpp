#include "PatternClause.h"


std::unordered_set<std::string> PatternClause::getAllSynonyms() const {
    std::unordered_set<std::string> synonyms;
    std::vector<Token> allParams = getAllParams();
    for (const Token& param : allParams) {
        if (param.getType() == TokenType::IDENT) {
            synonyms.insert(param.getValue());
        }
    }
    return synonyms;
}