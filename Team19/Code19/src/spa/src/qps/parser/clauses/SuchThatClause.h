#ifndef SUCHTHATCLAUSE_H
#define SUCHTHATCLAUSE_H

#include "qps/parser/clauses/Clause.h"
#include "qps/parser/Token.h"

struct SuchThatClause : public Clause {
private:
    Token relationship, firstParam, secondParam;

public:
    std::string getTypeName() const override {
        return "SuchThatClause";
    }

    // Getters
    Token getRelationship() const { return relationship; }
    Token getFirstParam() const { return firstParam; }
    Token getSecondParam() const { return secondParam; }

    // Setters
    void setRelationship(const Token& rel) { relationship = rel; }
    void setFirstParam(const Token& param) { firstParam = param; }
    void setSecondParam(const Token& param) { secondParam = param; }
};

#endif // SUCHTHATCLAUSE_H
