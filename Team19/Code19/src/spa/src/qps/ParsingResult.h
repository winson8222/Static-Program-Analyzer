#ifndef PARSINGRESULT_H
#define PARSINGRESULT_H

#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

class ParsingResult {
public:
    // Constructor
    ParsingResult();

    // Setters
    // Method to add a single synonym
    void addDeclaredSynonym(const std::string& key, const std::string& value);
    void setRequiredSynonym(const string& synonym);
    void setSuchThatClause(bool relationship,
        const pair<string, string>& firstParam,
        const pair<string, string>& secondParam);
    void setPatternClause(bool relationship,
        const pair<string, string>& firstParam,
        const pair<string, string>& secondParam);

    // Getters
    const unordered_map<string, string>& getDeclaredSynonyms() const;
    string getDeclaredSynonym(const string& key) const;
    const string& getRequiredSynonym() const;
    bool getSuchThatClauseRelationship() const;
    const pair<string, string>& getSuchThatClauseFirstParam() const;
    const pair<string, string>& getSuchThatClauseSecondParam() const;
    bool getPatternClauseRelationship() const;
    const pair<string, string>& getPatternClauseFirstParam() const;
    const pair<string, string>& getPatternClauseSecondParam() const;

private:
    unordered_map<string, string> declaredSynonyms;
    string requiredSynonym;
    bool suchThatClauseRelationship;
    pair<string, string> suchThatClauseFirstParam;
    pair<string, string> suchThatClauseSecondParam;
    bool patternRelationship;
    pair<string, string> patternFirstParam;
    pair<string, string> patternSecondParam;
};

#endif 
