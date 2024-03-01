#ifndef PARSINGRESULT_H
#define PARSINGRESULT_H

#include <string>
#include <unordered_map>
#include <utility>
#include "Token.h"

using namespace std;

// Define clause structs
struct SuchThatClause {
    Token relationship, firstParam, secondParam;
};

struct PatternClause {
    Token relationship, firstParam, secondParam, thirdParam;
};

struct WithClause {
    Token relationship, firstParam, secondParam;
};

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

    // New methods to get clause by index
    const SuchThatClause& getSuchThatClause(int index) const;
    const PatternClause& getPatternClause(int index) const;
    const WithClause& getWithClause(int index) const;

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
