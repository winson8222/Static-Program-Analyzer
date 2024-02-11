#pragma once

#include "PKB.h"
#include "PKBReader.h"
#include "PKBWriter.h"

class PKBManager {
private:
    std::shared_ptr<PKB> pkb;
    std::shared_ptr<PKBReader> pkbReader;
    std::shared_ptr<PKBWriter> pkbWriter;
public:
    PKBManager() {
        pkb = std::make_shared<PKB>();
        pkbReader = std::make_shared<PKBReader>(pkb);
        pkbWriter = std::make_shared<PKBWriter>(pkb);
    }
    std::shared_ptr<PKB> getPKB() {
        return pkb;
    }
    std::shared_ptr<PKBReader> getPKBReader() {
        return pkbReader;
    }
    std::shared_ptr<PKBWriter> getPKBWriter() {
        return pkbWriter;
    }
};
