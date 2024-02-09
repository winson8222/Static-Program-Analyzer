#include "ParsingResult.h"

// Constructor
ParsingResult::ParsingResult() {
    // Initialize members if needed
}

// Adds a single synonym to the declaredSynonyms map
void ParsingResult::addDeclaredSynonym(const std::string& key, const std::string& value) {
    declaredSynonyms[key] = value;
}

void ParsingResult::setRequiredSynonym(const string& synonym) {
    requiredSynonym = synonym;
}

void ParsingResult::setSuchThatClause(bool relationship,
    const pair<string, string>& firstParam,
    const pair<string, string>& secondParam) {
    suchThatClauseRelationship = relationship;
    suchThatClauseFirstParam = firstParam;
    suchThatClauseSecondParam = secondParam;
}

void ParsingResult::setPatternClause(bool relationship,
    const pair<string, string>& firstParam,
    const pair<string, string>& secondParam) {
    patternRelationship = relationship;
    patternFirstParam = firstParam;
    patternSecondParam = secondParam;
}

// Getters
const unordered_map<string, string>& ParsingResult::getDeclaredSynonyms() const {
    return declaredSynonyms;
}

string ParsingResult::getDeclaredSynonym(const string& key) const {
    auto it = declaredSynonyms.find(key);
    if (it != declaredSynonyms.end()) {
        return it->second;
    }
    
    return ""; 
}


const string& ParsingResult::getRequiredSynonym() const {
    return requiredSynonym;
}

bool ParsingResult::getSuchThatClauseRelationship() const {
    return suchThatClauseRelationship;
}

const pair<string, string>& ParsingResult::getSuchThatClauseFirstParam() const {
    return suchThatClauseFirstParam;
}

const pair<string, string>& ParsingResult::getSuchThatClauseSecondParam() const {
    return suchThatClauseSecondParam;
}

bool ParsingResult::getPatternClauseRelationship() const {
    return patternRelationship;
}

const pair<string, string>& ParsingResult::getPatternClauseFirstParam() const {
    return patternFirstParam;
}

const pair<string, string>& ParsingResult::getPatternClauseSecondParam() const {
    return patternSecondParam;
}

