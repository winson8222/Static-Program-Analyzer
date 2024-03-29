#pragma once

#include <string>

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

private:


    // create an enum of clause type
    bool negated = false;

    ClauseOperations clauseOperation = AND;

};
