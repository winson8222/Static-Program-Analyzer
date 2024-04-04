#pragma once

#include "qps/parser/clauses/Clause.h"


struct WithClause : public Clause {
private:



public:
    ~WithClause() override = default;
    std::string getTypeName() const override {
        return "WithClause";
    }


};
