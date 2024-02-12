#ifndef PARSINGRESULT_H
#define PARSINGRESULT_H

#include <string>
#include <unordered_map>
#include <utility>
#include "Token.h"

using namespace std;

class ParsingResult {
public:
    // Constructor
    ParsingResult();

    // Setters
    // Method to add a single synonym
    void addDeclaredSynonym(const std::string& key, const std::string& value);
    void setRequiredSynonym(const string& synonym);

    // Methods for setting individual parts of SuchThatClause
    void setSuchThatClauseRelationship(const Token& relationship);
    void setSuchThatClauseFirstParam(const Token& firstParam);
    void setSuchThatClauseSecondParam(const Token& secondParam);

    // Methods for setting individual parts of PatternClause
    void setPatternClauseRelationship(const Token& relationship);
    void setPatternClauseFirstParam(const Token& firstParam);
    void setPatternClauseSecondParam(const Token& secondParam);;


    // Getters
    const unordered_map<string, string>& getDeclaredSynonyms() const;
    const string& getDeclaredSynonym(const string& key) const;
    const string& getRequiredSynonym() const;
    const string& getRequiredSynonymType() const;
    const Token& getSuchThatClauseRelationship() const;
    const Token& getSuchThatClauseFirstParam() const;
    const Token& getSuchThatClauseSecondParam() const;
    const Token& getPatternClauseRelationship() const;
    const Token& getPatternClauseFirstParam() const;
    const Token& getPatternClauseSecondParam() const;

private:
    unordered_map<string, string> declaredSynonyms;
    string requiredSynonym;

    Token suchThatClauseRelationship;
    Token suchThatClauseFirstParam;
    Token suchThatClauseSecondParam;
    
    Token patternRelationship;
    Token patternFirstParam;
    Token patternSecondParam;
};

#endif 
