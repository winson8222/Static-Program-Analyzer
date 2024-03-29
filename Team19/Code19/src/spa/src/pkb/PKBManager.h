#pragma once

#include "pkb/PKB.h"
#include "pkb/PKBCacheManager.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKBWriterManager.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class PKBManager {
private:
    std::shared_ptr<PKB> pkb;
    std::shared_ptr<PKBReaderManager> pkbReaderManager;
    std::shared_ptr<PKBWriterManager> pkbWriterManager;
    std::shared_ptr<PKBCacheManager> pkbCacheManager;
public:
    PKBManager() {
        pkb = std::make_shared<PKB>();
        pkbCacheManager = std::make_shared<PKBCacheManager>(pkb);
        pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
        pkbWriterManager = std::make_shared<PKBWriterManager>(pkb);
    }
    std::shared_ptr<PKBReaderManager> getPKBReaderManager() {
        return pkbReaderManager;
    }
    std::shared_ptr<PKBWriterManager> getPKBWriterManager() {
        return pkbWriterManager;
    }
    std::shared_ptr<PKBCacheManager> getPKBCacheManager() {
        return pkbCacheManager;
    }
};
// ai-gen end
