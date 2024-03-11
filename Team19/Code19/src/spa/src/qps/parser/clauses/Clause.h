#ifndef CLAUSE_H
#define CLAUSE_H

#include <string>

struct Clause {
    virtual ~Clause() {}
    virtual std::string getTypeName() const = 0;
};

#endif // CLAUSE_H
