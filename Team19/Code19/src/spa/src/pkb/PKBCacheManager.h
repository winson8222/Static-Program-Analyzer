#pragma once

#include <memory>
#include "pkb/PKB.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class PKBCacheManager {
private:
    std::shared_ptr<PKB> pkb;
public:
    explicit PKBCacheManager(const std::shared_ptr<PKB>& pkb): pkb(pkb) {}

    void populateCache() {
        pkb->getNextTStore()->populateNextTStore();
        pkb->getAffectsStore()->populateAffectsStore();
    }
    void clearCache() {
        pkb->getNextTStore()->clear();
        pkb->getAffectsStore()->clear();
    }
};
// ai-gen end
