#pragma once

#include "PKB.h"
#include "PKBReader.h"
#include "PKBWriter.h"

class PKBManager {
private:
    shared_ptr<PKB> pkb;
    shared_ptr<PKBReader> pkbReader;
    shared_ptr<PKBWriter> pkbWriter;
public:
    PKBManager() {
        pkb = make_shared<PKB>();
        pkbReader = make_shared<PKBReader>(pkb);
        pkbWriter = make_shared<PKBWriter>(pkb);
    }
    shared_ptr<PKB> getPKB() {
        return pkb;
    }
    shared_ptr<PKBReader> getPKBReader() {
        return pkbReader;
    }
    shared_ptr<PKBWriter> getPKBWriter() {
        return pkbWriter;
    }
};
