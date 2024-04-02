#pragma once

#include <string>
#include "qps/parser/Token.h"

struct Clause {
    public:
    enum ClauseOperations {
        NOT,
        AND,
    };
    virtual ~Clause() = default;
    bool isNegated() const { return negated; }
    void setAsNegated() {
        negated = true;
        clauseOperation = NOT;
    }
    ClauseOperations getClauseOperation() const { return clauseOperation; }
    virtual std::string getTypeName() const = 0;
    std::vector<Token> getAllParams() const {
        return {firstParam, secondParam, relationship};
         }
    Token getRelationship() const { return relationship; }
    Token getFirstParam() const { return firstParam; }
    Token getSecondParam() const { return secondParam; }
    void setRelationship(const Token& rel) { relationship = rel; }
    void setFirstParam(const Token& param) { firstParam = param; }
    void setSecondParam(const Token& param) { secondParam = param; }
    std::unordered_set<std::string> getAllSynonyms() const {
        std::unordered_set<std::string> synonyms;
        std::vector<Token> allParams = getAllParams();
        for (const Token& param : allParams) {
            if (param.getType() == TokenType::IDENT) {
                synonyms.insert(param.getValue());
            }
        }
        return synonyms;
    }

private:
    Token firstParam;
    Token secondParam;
    Token relationship;


    // create an enum of clause type
    bool negated = false;

    ClauseOperations clauseOperation = AND;

};
