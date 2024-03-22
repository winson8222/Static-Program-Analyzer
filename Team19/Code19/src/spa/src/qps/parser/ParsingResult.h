#ifndef PARSINGRESULT_H
#define PARSINGRESULT_H

#include <string>
#include <unordered_map>
#include <utility>
#include "Token.h"
#include "clauses/SuchThatClause.h"
#include "clauses/PatternClause.h"
#include "clauses/WithClause.h"

using namespace std;

class ParsingResult {
public:
    // Constructor
    ParsingResult();

    bool isQueryValid();
    string getErrorMessage();
    void setErrorMessage(const string& errorMessage);

    // Setters
    // Method to add a single synonym
    void addDeclaredSynonym(const std::string& key, const std::string& value);
    void setRequiredSynonym(const string& synonym);

    // New methods for adding clauses
    void addSuchThatClause(const SuchThatClause& clause);
    void addPatternClause(const PatternClause& clause);
    void addWithClause(const WithClause& clause);


    // Getters
    const unordered_map<string, string>& getDeclaredSynonyms() const;
    const string& getDeclaredSynonym(const string& key) const;
    const vector<string>& getRequiredSynonyms() const;
    const string& getRequiredSynonymType(const string& requiredSynonym) const;
    const string& getPatternClauseType(const PatternClause& clause) const;

    // New methods to get clause by index
    const vector<SuchThatClause>& getSuchThatClauses() const;
    const vector<PatternClause>& getPatternClauses() const;
    const vector<WithClause>& getWithClauses() const;

    // method to check if the synonym is delcared
    bool isSynonymDeclared(const string& synonym);


private:
    unordered_map<string, string> declaredSynonyms;
    vector<string> requiredSynonyms;

    // Use vectors of clause structs
    vector<SuchThatClause> suchThatClauses;
    vector<PatternClause> patternClauses;
    vector<WithClause> withClauses;

    string errorMessage;
};

#endif 
