#ifndef WITHCLAUSE_H
#define WITHCLAUSE_H

#include "qps/parser/clauses/Clause.h"
#include "qps/parser/Token.h"

struct WithClause : public Clause {
    Token relationship, firstParam, secondParam;

    std::string getTypeName() const override {
        return "WithClause";
    }
};

#endif // WITHCLAUSE_H
