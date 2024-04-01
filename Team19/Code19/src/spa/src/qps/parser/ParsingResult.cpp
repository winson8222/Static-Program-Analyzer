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

const vector<SuchThatClause>& ParsingResult::getSuchThatClauses() const {
    return suchThatClauses;
}

const vector<PatternClause>& ParsingResult::getPatternClauses() const {
    return patternClauses;
}

const vector<WithClause>& ParsingResult::getWithClauses() const {
    return withClauses;
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
    if (ParsingResult::isAttrRef(requiredSynonym)) {
        return getDeclaredSynonym(getSynFromAttrRef(requiredSynonym));
    }
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

bool ParsingResult::isSynonymDeclared(const string& synonym) {
    return declaredSynonyms.find(synonym) != declaredSynonyms.end();
}

const string& ParsingResult::getPatternClauseType(const PatternClause &clause) const {
    return getDeclaredSynonym(clause.getRelationship().getValue());
}

const bool ParsingResult::isAttrRef(const string &attrRef) {
    // check if it has .
    size_t pos = attrRef.find('.');
    return pos != std::string::npos;

}


string ParsingResult::getSynFromAttrRef(const string &attrRef) {
    size_t pos = attrRef.find('.');
    if (pos != std::string::npos) { // Check if the period is found
        return attrRef.substr(0, pos); // Extract substring from the beginning to the position of the period
    }
    return "";
}

string ParsingResult::getAttrFromAttrRef(const string &attrRef) {
    size_t pos = attrRef.find('.');
    if (pos != std::string::npos) { // Check if the period is found
        return attrRef.substr(pos + 1); // Extract substring from just after the position of the period to the end
    }
    return "";
}

bool ParsingResult::isBooleanSelection() {
    return isBoolean;
}

void ParsingResult::setBooleanSelection() {
    isBoolean = true;
}

