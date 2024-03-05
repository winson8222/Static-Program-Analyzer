#ifndef PATTERNCLAUSE_H
#define PATTERNCLAUSE_H

#include "qps/parser/clauses/Clause.h"
#include "qps/parser/Token.h"

struct PatternClause : public Clause {
    Token relationship, firstParam, secondParam, thirdParam;

    std::string getTypeName() const override {
        return "PatternClause";
    }
};

#endif // PATTERNCLAUSE_H
