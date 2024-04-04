#pragma once

#include "qps/parser/clauses/Clause.h"


struct PatternClause : public Clause {
private:
    Token thirdParam;



public:

    ~PatternClause() override = default;
    std::string getTypeName() const override {
        return "PatternClause";
    }

    // Getters

    Token getThirdParam() const { return thirdParam; }


    // Setters

    void setThirdParam(const Token& param) { thirdParam = param; }

};
