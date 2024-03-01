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
    requiredSynonyms.push_back(synonym);
}

// Methods for adding clauses
void ParsingResult::addSuchThatClause(const SuchThatClause& clause) {
    suchThatClauses.push_back(clause);
}

void ParsingResult::addPatternClause(const PatternClause& clause) {
    patternClauses.push_back(clause);
}

void ParsingResult::addWithClause(const WithClause& clause) {
    withClauses.push_back(clause);
}

const SuchThatClause& ParsingResult::getSuchThatClause(int index) const {
    return suchThatClauses.at(index);
}

const PatternClause& ParsingResult::getPatternClause(int index) const {
    return patternClauses.at(index);
}

const WithClause& ParsingResult::getWithClause(int index) const {
    return withClauses.at(index);
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


const vector<string>& ParsingResult::getRequiredSynonyms() const {
    return requiredSynonyms;
}

const string& ParsingResult::getRequiredSynonymType(const string& requiredSynonym) const {
    return getDeclaredSynonym(requiredSynonym);
}


// check if the query is valid
bool ParsingResult::isQueryValid() {
    return errorMessage.empty();
}

// get the error message
string ParsingResult::getErrorMessage() {
    return errorMessage;
}

// set the error message
void ParsingResult::setErrorMessage(const string& message) {
    if (errorMessage.empty()) {
        errorMessage = message;
    }

}

