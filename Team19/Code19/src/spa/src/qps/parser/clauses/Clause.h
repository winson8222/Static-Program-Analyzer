#pragma once

#include <string>

struct Clause {
    virtual ~Clause() {}
    virtual std::string getTypeName() const = 0;
};
