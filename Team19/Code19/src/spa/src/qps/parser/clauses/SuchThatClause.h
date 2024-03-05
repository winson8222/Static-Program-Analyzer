#ifndef SUCHTHATCLAUSE_H
#define SUCHTHATCLAUSE_H

#include "qps/parser/clauses/Clause.h"
#include "qps/parser/Token.h"

struct SuchThatClause : public Clause {
    Token relationship, firstParam, secondParam;

    std::string getTypeName() const override {
        return "SuchThatClause";
    }
};

#endif // SUCHTHATCLAUSE_H
