#pragma once

#include "PKB.h"
#include "PKBReaderManager.h"
#include "PKBWriterManager.h"

class PKBManager {
private:
    std::shared_ptr<PKB> pkb;
    std::shared_ptr<PKBReaderManager> pkbReader;
    std::shared_ptr<PKBWriterManager> pkbWriter;
public:
    PKBManager() {
        pkb = std::make_shared<PKB>();
        pkbReader = std::make_shared<PKBReaderManager>(pkb);
        pkbWriter = std::make_shared<PKBWriterManager>(pkb);
    }
    std::shared_ptr<PKB> getPKB() {
        return pkb;
    }
    std::shared_ptr<PKBReaderManager> getPKBReader() {
        return pkbReader;
    }
    std::shared_ptr<PKBWriterManager> getPKBWriter() {
        return pkbWriter;
    }
};
