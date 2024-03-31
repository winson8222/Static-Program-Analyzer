#include "ParsingResult.h"

// Constructor
ParsingResult::ParsingResult() {
    // Initialize members if needed
}

// Adds a single synonym to the declaredSynonyms map
void ParsingResult::addDeclaredSynonym(const std::string& key, const std::string& value) {
    declaredSynonyms[key] = value;
}

void ParsingResult::setRequiredSynonym(const std::string& synonym) {
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

const std::vector<SuchThatClause>& ParsingResult::getSuchThatClauses() const {
    return suchThatClauses;
}

const std::vector<PatternClause>& ParsingResult::getPatternClauses() const {
    return patternClauses;
}

const std::vector<WithClause>& ParsingResult::getWithClauses() const {
    return withClauses;
}

// Getters
const unordered_map<std::string, std::string>& ParsingResult::getDeclaredSynonyms() const {
    return declaredSynonyms;
}

const std::string& ParsingResult::getDeclaredSynonym(const std::string& key) const {
    auto it = declaredSynonyms.find(key);
    if (it != declaredSynonyms.end()) {
        return it->second;
    }
    
    return ""; 
}


const std::vector<std::string>& ParsingResult::getRequiredSynonyms() const {
    return requiredSynonyms;
}

const std::string& ParsingResult::getRequiredSynonymType(const std::string& requiredSynonym) const {
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
std::string ParsingResult::getErrorMessage() {
    return errorMessage;
}

// set the error message
void ParsingResult::setErrorMessage(const std::string& message) {
    if (errorMessage.empty()) {
        errorMessage = message;
    }

}

bool ParsingResult::isSynonymDeclared(const std::string& synonym) {
    return declaredSynonyms.find(synonym) != declaredSynonyms.end();
}

const std::string& ParsingResult::getPatternClauseType(const PatternClause &clause) const {
    return getDeclaredSynonym(clause.getRelationship().getValue());
}

const bool ParsingResult::isAttrRef(const std::string &attrRef) {
    // check if it has .
    size_t pos = attrRef.find('.');
    return pos != std::string::npos;

}


std::string ParsingResult::getSynFromAttrRef(const std::string &attrRef) {
    size_t pos = attrRef.find('.');
    if (pos != std::string::npos) { // Check if the period is found
        return attrRef.substr(0, pos); // Extract substring from the beginning to the position of the period
    }
    return "";
}

std::string ParsingResult::getAttrFromAttrRef(const std::string &attrRef) {
    size_t pos = attrRef.find('.');
    if (pos != std::string::npos) { // Check if the period is found
        return attrRef.substr(pos + 1); // Extract substring from just after the position of the period to the end
    }
    return "";
}
