#ifndef PATTERNCLAUSE_H
#define PATTERNCLAUSE_H

#include "qps/parser/clauses/Clause.h"
#include "qps/parser/Token.h"

struct PatternClause : public Clause {
private:
    Token relationship, firstParam, secondParam, thirdParam;



public:

    ~PatternClause() override = default;
    std::string getTypeName() const override {
        return "PatternClause";
    }

    // Getters
    Token getRelationship() const { return relationship; }
    Token getFirstParam() const { return firstParam; }
    Token getSecondParam() const { return secondParam; }
    Token getThirdParam() const { return thirdParam; }


    // Setters
    void setRelationship(const Token& rel) { relationship = rel; }
    void setFirstParam(const Token& param) { firstParam = param; }
    void setSecondParam(const Token& param) { secondParam = param; }
    void setThirdParam(const Token& param) { thirdParam = param; }

};

#endif // PATTERNCLAUSE_H
