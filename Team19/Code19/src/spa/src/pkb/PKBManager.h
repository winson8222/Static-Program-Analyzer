#pragma once

#include "PKB.h"
#include "PKBReaderManager.h"
#include "PKBWriterManager.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class PKBManager {
private:
    std::shared_ptr<PKB> pkb;
    std::shared_ptr<PKBReaderManager> pkbReaderManager;
    std::shared_ptr<PKBWriterManager> pkbWriterManager;
public:
    PKBManager() {
      pkb = std::make_shared<PKB>(); // TODO: Change to private
      pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
      pkbWriterManager = std::make_shared<PKBWriterManager>(pkb);
    }
    std::shared_ptr<PKB> getPKB() {
        return pkb;
    }
    std::shared_ptr<PKBReaderManager> getPKBReaderManager() {
        return pkbReaderManager;
    }
    std::shared_ptr<PKBWriterManager> getPKBWriterManager() {
        return pkbWriterManager;
    }
};
// ai-gen end
