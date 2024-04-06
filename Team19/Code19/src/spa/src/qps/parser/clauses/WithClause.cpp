#include "WithClause.h"

std::unordered_set<std::string> WithClause::getAllSynonyms() const {
    std::unordered_set<std::string> synonyms;
    std::vector<Token> allParams = getAllParams();
    for (const Token& param : allParams) {
        if (param.getType() != TokenType::Ref) {
            continue;
        }
        std::string refValue = param.getValue();
        if (isSynonym(refValue)) {
            std::string synonym = extractSynonym(refValue);
            synonyms.insert(synonym);
        }
    }
    return synonyms;
}

bool WithClause::isSynonym(std::string &ref) {
    // check if ref is a synonym
    return ref.find('.') != std::string::npos;
}

std::string WithClause::extractSynonym(std::string &ref) const {
    return ref.substr(0, ref.find('.'));
}

