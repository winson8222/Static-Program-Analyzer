#pragma once

#include "qps/parser/clauses/Clause.h"
#include "qps/parser/Token.h"

struct PatternClause : public Clause {
private:
    Token relationship, firstParam, secondParam, thirdParam;
    bool negated = false;

public:
    std::string getTypeName() const override {
        return "PatternClause";
    }

    // Getters
    Token getRelationship() const { return relationship; }
    Token getFirstParam() const { return firstParam; }
    Token getSecondParam() const { return secondParam; }
    Token getThirdParam() const { return thirdParam; }
    bool isNegated() const { return negated; }

    // Setters
    void setRelationship(const Token& rel) { relationship = rel; }
    void setFirstParam(const Token& param) { firstParam = param; }
    void setSecondParam(const Token& param) { secondParam = param; }
    void setThirdParam(const Token& param) { thirdParam = param; }
    void setAsNegated() { negated = true; }
};
