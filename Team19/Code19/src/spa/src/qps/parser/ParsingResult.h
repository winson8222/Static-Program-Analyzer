#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include "qps/parser/Token.h"
#include "qps/parser/clauses/SuchThatClause.h"
#include "qps/parser/clauses/PatternClause.h"
#include "qps/parser/clauses/WithClause.h"

class ParsingResult {
public:
    // Constructor
    ParsingResult();

    bool isQueryValid();
    std::string getErrorMessage();
    void setErrorMessage(const std::string& errorMessage);

    // Setters
    // Method to add a single synonym
    void addDeclaredSynonym(const std::string& key, const std::string& value);
    void setRequiredSynonym(const std::string& synonym);

    // New methods for adding clauses
    void addSuchThatClause(const SuchThatClause& clause);
    void addPatternClause(const PatternClause& clause);
    void addWithClause(const WithClause& clause);


    // Getters
    const std::unordered_map<std::string, std::string>& getDeclaredSynonyms() const;
    const std::string& getDeclaredSynonym(const std::string& key) const;
    const std::vector<std::string>& getRequiredSynonyms() const;
    const std::string& getRequiredSynonymType(const std::string& requiredSynonym) const;
    const std::string& getPatternClauseType(const PatternClause& clause) const;

    // New methods to get clause by index
    const std::vector<SuchThatClause>& getSuchThatClauses() const;
    const std::vector<PatternClause>& getPatternClauses() const;
    const std::vector<WithClause>& getWithClauses() const;

    // method to check if the synonym is delcared
    bool isSynonymDeclared(const std::string& synonym);
    static std::string getSynFromAttrRef(const std::string &attrRef);
    static std::string getAttrFromAttrRef(const std::string &attrRef);
    static const bool isAttrRef(const std::string &attrRef);

private:
    std::unordered_map<std::string, std::string> declaredSynonyms;
    std::vector<std::string> requiredSynonyms;

    // Use vectors of clause structs
    std::vector<SuchThatClause> suchThatClauses;
    std::vector<PatternClause> patternClauses;
    std::vector<WithClause> withClauses;

    std::string errorMessage;
};
