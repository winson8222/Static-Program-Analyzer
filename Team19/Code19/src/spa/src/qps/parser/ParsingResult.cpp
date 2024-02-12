#include "ParsingResult.h"
#include "Token.h"

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



// Implementations for setting individual parts of SuchThatClause
void ParsingResult::setSuchThatClauseRelationship(const Token& relationship) {
    suchThatClauseRelationship = relationship;
}

void ParsingResult::setSuchThatClauseFirstParam(const Token& firstParam) {
    suchThatClauseFirstParam = firstParam;
}

void ParsingResult::setSuchThatClauseSecondParam(const Token& secondParam) {
    suchThatClauseSecondParam = secondParam;
}

// Implementations for setting individual parts of PatternClause
void ParsingResult::setPatternClauseRelationship(const Token& relationship) {
    patternRelationship = relationship;
}

void ParsingResult::setPatternClauseFirstParam(const Token& firstParam) {
    patternFirstParam = firstParam;
}

void ParsingResult::setPatternClauseSecondParam(const Token& secondParam) {
    patternSecondParam = secondParam;
}

// Getters
const unordered_map<string, string>& ParsingResult::getDeclaredSynonyms() const {
    return declaredSynonyms;
}

const string& ParsingResult::getDeclaredSynonym(const string& key) const {
    auto it = declaredSynonyms.find(key);
    if (it != declaredSynonyms.end()) {
        return it->second;
    }
    
    return ""; 
}

const string& ParsingResult::getRequiredSynonym() const {
    return requiredSynonym;
}

const string& ParsingResult::getRequiredSynonymType() const {
    return getDeclaredSynonym(requiredSynonym);
}

const Token& ParsingResult::getSuchThatClauseRelationship() const {
    return suchThatClauseRelationship;
}

const Token& ParsingResult::getSuchThatClauseFirstParam() const {
    return suchThatClauseFirstParam;
}

const Token& ParsingResult::getSuchThatClauseSecondParam() const {
    return suchThatClauseSecondParam;
}

const Token& ParsingResult::getPatternClauseRelationship() const {
    return patternRelationship;
}

const Token& ParsingResult::getPatternClauseFirstParam() const {
    return patternFirstParam;
}

const Token& ParsingResult::getPatternClauseSecondParam() const {
    return patternSecondParam;
}

